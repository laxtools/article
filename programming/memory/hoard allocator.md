# hoard allocator 

게임 서버는 많은 오브젝트를 다룬다. 오브젝트 풀로 메모리 관련 이슈를 대부분 해결할 수 있다. 가끔 예외적인 경우도 있는데 다른 라이브러리에 있는 코드 버그로 힙이 깨진다던가 하는 경우가 그렇다. 이런 경우 원인을 찾기가 사실상 거의 불가능하다. 

할당 / 해제의 통계 정보를 갖고 추적이 어느 정도 가능하게 하여 메모리 누수나 오류를 처리할 수 있게 하고, 아주 예외적인 경우 힙을 분리하여 불안정한 환경에 대응할 수 있는, 멀티 쓰레드 환경에서도 빠른 메모리 관리기는 여전히 유용하다. 

hoard는 tbb의 메모리 관리기를 비롯하여 많은 메모리 관리 기술의 발전에 기여한 라이브러리이다.  GPL과 상용 라이선스를 제공하고 있다. 비싸지는 않으나 불편하게 만드는 면이 있기도 하고 추가 기능이 필요하기 하여 코드를 분석하고 알고리즘을 이해한 후 개선하여 일반적인 메모리 관리자를 만든다. 많은 프로젝트에서 큰 도움이 될 수 있다. 

# 논문.  Hoard: A Scalable Memory Allocator for Multithreaded Applications 

호드를 받으면 doc 폴더에 있는 논문이다. 기본 아이디어와 개념들을 설명하고 있어 먼저 읽고 이해해야 한다. 



## Abstract 

**기능:** 

- fast 
- scalable 
- avoids false sharing 
- low fragementation



**구성:** 

- one global heap 
- per-processor heaps 
  - low synchronization costs 



## Introduction 

- blowup 
  - the maximum amount of memory allocated by a given allocator divided by 
  - the maximum amount of memory allocated by an idean uniprocessor allocator 
- nearly zero synchronization costs in practice
- per process heap and one global heap
  - per process heap이 많이 비면 global heap으로 chunk를 이동 
- scales linearly and framgementation costs are low 



## Motivation 



### Allocator-Induced False Sharing of Heap Objects

False sharing occurs when multiple processors share words in the same cache line without actually sharing data and is a notorious cause of poor performance in parallel applications. 

한 할당기에서 여러 쓰레드에 동일한 캐시 라인의 메모리를 주면 false sharing이 발생할 수 있다. 쓰레드 별 메모리 할당기를 만들면 확실히 많이 줄일 수 있다. 



### Blowup 

producer / consumer 모델에서 producer가 할당한 메모리를 consumer가 사용한 후 해제하면 다시 producer가 사용할 수 있어야 한다. 그렇지 않으면 메모리가 지속적으로 증가할 수 있다. 



## The Hoard Memory Allocator 

Hoard augments per-processor heaps with a global heap that every thread may access. Each thread can access only its heap and the global heap. 

Heap 0를 글로벌 힙으로 하고 1..P를 쓰레드 힙으로 한다. 실제 구현에서 동시에 같은 힙을 접근하는 쓰레드를 줄이기위해 2P 힙을 사용한다.  

각 힙에 대한 사용 통계를 갖는다. 

- u : the amount of memory in use ("live")
- $a_i$ : the amount of memory allocated 

청크 단위로 OS에서 할당하고 이를 수퍼블럭(superblock)이라 한다.  수퍼블럭은 오브젝트의 배열이고 LIFO로 관리되는 자유 목록 (Free list)를 갖는다.  모든 수퍼블럭은 시스템 페이지 크기의 정수배에 해당하는 같은 크기를 갖는다. 수퍼블럭의 절반보다 큰 오브젝트는 OS 메모리 관리자로 직접 할당 / 해제 한다. 같은 수퍼블럭에 있는 오브젝트는 같은 크기를 갖는다. 

빈 수퍼블럭은 오브젝트 크기를 재할당한다. 이렇게 함으로써 외부 단편화를 막는다. 

### Bounding Blowup 

각 힙은 여러 수퍼블럭을 갖는다. 수퍼블럭에 가용한 메모리가 없으면 글로벌 힙에서 먼저 할당을 시도한다. 실패하면 OS에서 하나 할당받는다. 현재 빈 수퍼블럭을 OS로 돌려주지 않는다.  

Hoard finds f-empty superblocks in constant time by dividing superblocks into a number of bins that we call "fullness groups". 각 통은 차 있는 정도가 같은 수퍼블럭에 대한 이중연결리스트를 갖는다. 호드는 하나의 그룹에서 다른 그룹으로 적절할 때 수퍼블럭을 옮기고, 항상 거의 차있는 수퍼블럭에서 할당한다.  

지역성(locality)을 올리기 위해 LIFO 방식으로 할당하고, 수퍼블럭도 할당하면 해당 블럭을 가장 앞으로 옮긴다. 

### Avoiding False Sharing 

여러 쓰레드에서 할당 요청은 항상 다른 수퍼블럭에서 할당한다. 해제할 때는 이전에 할당한 블럭으로 돌려준다. 

































