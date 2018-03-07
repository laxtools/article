# Scripting Data 

or data scripting. 

행동을 제어할 수 있는 일반적인 데이터 포맷으로 C++ 코드로 생성되고 빌드 되는 언어를 찾아보려고 한다. 어떤 semantic 모델을 갖고 C++ 함수와 데이터 사용이 가능하면 C++ 코드를 내장한 구조의 어떤 것이다. 

데이터와 행동 제어가 통합된 구조의 데이터 구조는 많은 것을 할 수 있다. 특히, UI 관련된 프레임워크들은 이런 preprocessor와 코드 generator를 갖는 형태의 데이터를 포함한 언어들을 갖고 있다. CSS/HTML과 javascript과 혼합된 형태의 웹 기술이 React나 Flutter와 같은 형태의 발전이 있었다. 그렇다면 C++ 게임 서버에도 이런 기술의 발전을 수용할 수 있지 않을까? 

json은 문법 자체가 데이터 교환을 위한 것이라 적절해 보이지는 않고 flutter의 dart 형식이 괜찮을 것 같다. 아니면 list를 기본 자료형으로 사용하고 코드도 list인 lisp 계열의 언어 집합도 대상이 될 수 있다. 지금까지 데이터와 코드는 분리되어 있었다. 그게 더 나은 방법일 수도 있다. 일단, 퀘스트를 진행해 본다. 

## Understanding Flutter 

https://flutter.io/

flutter is based on dart programmong language. dart is an object oriented, AOT compiled native with optional javascript target language. 

https://www.dartlang.org/

생각보다 복잡하고 C++ 연동이 좀 어려워 보인다. 그리고 문법도 다르다. Flutter의 preprocessor 문법이 추가되어 데이터와 합쳐서 처리 가능한 것으로 보인다. 

## 게임의 세 가지 영역

- 분산 처리
  - 서비스 
  - 클라이언트
  - 메세지
- 상태 처리 
- 데이터 처리 
  - 정의된 데이터
  - 생성된 데이터 (데이터베이스와 동적 변수)
- 관계 처리
  - 공간 
  - 객체

각 영역과 게임에 고유한 DSEL을 찾고 구현하는 게 게임 개발이다.  데이터도 스킬, 아이템, 미션 등이 모두 다르다. 어떤 관점에서 전체를 구성하고 조합할 것인가? 어떤 관점에서 데이터를 구성할 것인가? 

### 게임 코드의 구성 

조건과 메세지에 따른 처리 분기의 구성.  

메세지 --> 조건 --> 처리 --> 조건 --> 처리 --> 처리 

메세지를 시간을 포함하면 모두 경우에 해당한다. 메세지로 시작되지 않는 경우는 없다. 

on: 

​     when:    do: 

​     when:     do: 

   

when에 상태를 포함한 조건 체크가 있다. 

do는 여러 종류가 있다. 

- 응답 (post)
- 상태 변경 (update state)
- DB 처리 (update db)

on을 결정하는 메세지 수신과 시간에 대한 처리가 있어야 한다. 

위의 개념에서 시작해서 정리해 나간다. BDD (Behavior Driven Development)와 유사한 구조이며 하나의 상위 레벨 서술 구조를 확보하면 전체 코드를 이해하기 쉽도록 구성할 수 있다. 







  

   



























