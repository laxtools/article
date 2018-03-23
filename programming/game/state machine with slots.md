# State Machine with Slots 

HFSM은 구조가 단순하고 이해하기가 쉬워 AI나 처리 구조를 만들기 수월하다. 타이머와 메세지를 연결하여 처리 할 수 있다. 이에 더하여 트랜지션을 구성할 수 있으면 좋은데 게임은 트랜지션 지점이 많아 그간 어려움이 많았다. 간단한 아이디어로 슬롯들을 만들고 각 슬롯이 트리거 되면 다음 상태를 지정하는 방식으로 전환을 처리할 수 있다. 이렇게 되면 구성 가능하게 된다. 

hfsm의 이전 구현을 찾아서 사용한다. 동적으로 만들기 보다는 정적으로 구성하는 게 좋을 듯 하다. 실제 동적으로 상태가 추가되고 삭제 되는 경우는 없기 때문이다.  한번에 전체가 구성되도록 한다. 

machine.define<CLS>( "")

​     .on(   "success",   CLS::id)

​     .on( )

​    .define<CLS>()  

​       .on() .. 

   .end() 

 .end();



위와 같이 fluent 스타일로 구현 가능하다. define에서 생성하고 현재 state를 push하고 end()에서 pop() 하면 동작한다. 



이동하면서 스킬을 시전한다던가 동시에 여러 가지 동작을 한다던가 하는 건 쉽지 않다. 그럴 경우 좀 복잡하게 되긴 한다.  



C# fluent BT 에 관한 설명. 이벤트 처리와 통합된 구조가 필요하다. BlackBoard 값과 연동하는데 조건이 MMORPG라면 너무 많아진다. 

http://www.what-could-possibly-go-wrong.com/fluent-behavior-trees-for-ai-and-game-logic/





