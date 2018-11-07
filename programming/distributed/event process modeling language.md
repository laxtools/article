# event process modeling language

 text denotation

 function : <name>
 flow     : >> (async) . (sync)
 connector: select / when / parallel
 service  : [name]
 event    : name
 state     : c++ expression including function call that returns value
 flow block   : { }
 assignment : p1 = flow block 

object and state.


GOAL: 
	develop to the level that it can be converted to an implementation.

## login

```
 login = 
 {
 		<req_login> 
			>> <login> . send_load_account >> req_load_account 
			>> [db] . <load_account> 
			>> res_load_account 
			>> [login] .  <authenticate>  
			. select {
				 user.login_failed() : p1, 
				user.login_succeeded() : p2 
			}
}

p1 = 
{
}

p2 = 
{
}
```







# languages 

## EPC

https://www.ariscommunity.com/event-driven-process-chain

behavior tree와 매우 비슷하다. 



## BPEL

de-facto standard for web-service-based and IT systems supported enactment and execution of business processes.    



## BPMN 

거의 완벽하다. OMG에서 정리한 모델로 툴 지원이 있다.

