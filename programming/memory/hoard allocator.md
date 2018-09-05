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
- memory efficient 



**구성:** 

- one global heap 
- per-processor heaps 
  - low synchronization costs 



## Introduction 

- per process heap and one global heap
  - per process heap이 많이 비면 global heap으로 chunk를 이동 
- 























