# object system 

게임은 다수의 오브젝트를 다룬다. Item, Pc, Npc, Skill 등이 주 대상이다.  이들을 object와 actor로 나누고 actor는 컴포넌트를 갖도록 하며 서로 시그널로 이벤트를 받을 수 있도록 한다. 또 라이프 사이클을 관리하고 필요하면 빠르게 풀에서 할당 / 해제 가능하도록 한다.  reflection을 포함하여 로깅이 가능하도록 한다.  적절한 성능을 갖도록 한다. 

오브젝트 상태는 시각화가 가능하도록 한다. 이를 바탕으로 디버깅 가능한 서버를 만든다. 오브젝트 시스템은 통신, 서비스, 데이터, 공간, DB 처리와 함께 서버의 핵심 기반이 된다. 

데이터 사용과 통신을 고려하여 진행해야 한다.  타이머와 메세지 처리도 함께 고려한다. 좀 비대해질 가능성이 있으므로 기능을 나눠야 할 수 있다. 



# 프로토타잎 







# 아이디어 

object, actor, component를 한 축으로 한다. object_pool, object_container, scene, spatial_scene을 한 축으로 한다. 게임을 만들지 않고도 미리 테스트 가능하도록 한다.  

개념으로 잘 분할된 클래스들을 만든다. observable, observer, message_sink 와 같은 개념을 포함하도록 한다. 

actor : object, observable, observer, message_sink 

item : object, observable

component : object, observable, observer, message_sink 

comp_inven : component

comp_ability : component 

- signal::id sub( comp_inven::ref inv, remove / add / update ) 
- void unsub( signal::id id)



## 리플렉션

https://github.com/rttrorg/rttr

필드가 많은 경우 전부 등록하기가 번거로울 수 있지만 한번 등록하고 나중에는 수정만 하면 되므로 크게 어렵지는 않다. 게임에서 사용하는 object들이 꽤 있지만 클라이언트 만큼 많지는 않다. 







## 시그널 

https://github.com/larspensjo/SimpleSignal. 

단순한 함수 기반의 콜백 시스템. 코드를 맞게 수정해서 테스트 한다. 

https://testbit.eu/cpp11-signal-system-performance/

원 구현에 대한 설명과 벤치마크를 포함하고 있다. 매우 단순한 구현이라 더 빠르기는 어려울 듯 하다. 



TODO: 

- 성능 테스트 
  - signal과 callback 성능 비교 
- 사용성 분석 
  - lambda 
  - member 함수 



등록과 사용 시 버그가 없도록 하려면 자동 해제 기능이 있어야 하고 등록 한 주체를 알 수 있어야 한다. 옵션으로 해당 정보를 기록하여 디버깅 가능하도록 한다. 



## object_pool 

쓰레드에 안전한 클래스별 풀이 되어야 한다.  pc::construct( )와 같은 함수로 pc::ref를 얻는다. new mem ( ) 형태의 placement new를 사용한다.  이전 구현이 있어 각 클래스에 쉽게 포함할 수 있도록 한다. 

pooled<T> 와 같은 것에서 상속 받도록 한다. 

pc : actor, pooled<pc> 



사용성을 포함 구현을 통해 확인한다. 자동으로 해제 되어야 한다. 































