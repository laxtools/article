# message IDL 



## Why another IDL? 

thrift와 유사한 방식의 형식에서 serialization, de-serialization 코드를 생성하고 관리 코드를 포함하는 처리기를 작성한다. thrift도 괜찮긴 하지만 게임에 사용하기에는 다소 무거운 형식이며 float를 지원하지 않아 추가해야 하는 등 손이 가게 되어 있다. thrift는 RPC를 거의 모든 언어에 제공하는 것이 주된 목적으로 매우 범용적이다. 여기서 한계도 나온다. 자체 포맷을 갖추면 지속적으로 발전 시킬 수 있다. 



## 컴파일러 

flex와 bison 기반으로 작성한다. 문법은 최대한 간결하게 한다. 게임에 맞게 빠르게 처리하는 것을 목표로 한다. 

### 기본 기능 

- 타잎들 
  - i8, i16, i32, i64 
  - float, double 
  - u8, u16 문자열 
    - 각 utf8, utf16le
    - 길이 제한 
      - u8  ab[32]; 
      - u16 name[16];
      - 제한 없으면 기본 최대 길이로 제한 
  - 초기화 
- 컨테이너 
  - arr
    - arr<i8, 16> vs; 
  - vec
    - vec<i8> vs 
      - 길이 제한이 없는 형식 (default maximum까지)
    - vec<i8, 32> vs 
      - 최대 길이 제한이 있는 형식
  - 길이에 간단한 expression 허용 
    - 예) limits.MaxVecSize + 1
- struct 
- enum 
- message
  - topic  { group.base.id }
  - factory 등록 등 처리 

버전 관리 : 

- \#if, #else, #endif 지원 
- struct, enum, message에서만 지원



### 코드 생성 

c#과 c++를 우선 지원한다. 게임 개발에 필요할 때만 언어를 추가한다. 

- include 처리
- c++ rtt 코드 생성
- topic enum generation
- factory registration
- per topic message pool 



## Serialization 

- little endian always 
- inline serialization code for c++ 
- length{32} | topic{32} | payload 
- thrift의 간결하고 빠른 버전으로 구현



## 메세지 풀 

- new / delete 코드 생성 
  - 코드 생성을 하면 풀을 사용하기 쉽다. 
  - concurrent queue를 사용하면 lock 이슈도 적다. 
  - free count를 보고 os로 돌려줄 지 결정한다. 
    - 구성 가능하게 한다. 

이와 같이 하면 메모리 할당 / 해제가 많이 줄어든다. 





