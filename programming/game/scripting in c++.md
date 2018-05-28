# Scripting in C++

게임의 데이터 측면이 아닌 규칙과 동작을 처리하는 부분 전체를 말한다. C++로 작성하면서도 개별 기능의 코드가 매우 간결하고 깔끔하고 새로운 기능을 추가하기 쉬워야 한다. 기능 개발을 할 때마다 뭔가 구조를 작성하기 보다는 어떤 단위로 개발된 기능들을 연결하면 되도록 해야 한다.

##  방향 

- 최대한 public 인터페이스를 줄여야 한다. 
- 데이터에 기반하여 기능이 동작하도록 한다
- 메세지로 연결 가능한 부분은 메세지로 한다
- 기능을 쌓아갈 수 있는 단위는 여러 계층으로 나뉘어야 한다.
- 기능의 재사용과 연결이 쉬워야 한다.
- 영역별로 타잎화와 DSL화가 이루어져야 한다.
- 개발과 서비스 중 디버깅이 쉬워야 한다.



## 전제

처리 구조가 어떤 지는 고려하지 않는다. Entity / Actor 단위와 Component는 가정한다.  Scene을 가정하고 Scene 단위로 모든 것이 있다고 가정한다. Thread safety를 신 단위로 제공하기 위해 모든 오브젝트는 신 단위로 생성되고 신에서 관리된다.

Server를 통해 필요한 서비스 참조를 얻어 올 수 있다. Server를 통해 메세지 전달이 가능하다.



## 기본 모델 

- Scene
- Actor
  - State
  - Component
    - Element
- System 
  - SpatialSystem
- ADT 
  -  DSL을 포함
  - Component 뒤
  - System 뒤
  - 정적인 단위 테스트가 가능한 영역으로 함 



동적인 영역과 정적인 영역을 구분하고 전체가 메세지와 데이터 (엘리먼트)로 동작하도록 한다. 정적인 영역은 단위 테스트가 가능하도록 구성하여 견고하게 만든다. 동적인 영역은 메세지 기반 기능 테스트로 검증한다.


































