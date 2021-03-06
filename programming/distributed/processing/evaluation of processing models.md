# Evaluation of Processing Models

서버의 처리 모델은 대표적인 두 가지 방식이 있다. 하나는 IOCP 쓰레드에서 모든 걸 처리하는 방식과 IOCP 통신은 무한 대기를 하도록 하고 별도의 쓰레드들에서 처리를 하는 방식이다. 직접 비교하기가 쉽지 않다. 성능은 원래 측정의 영역인데 용도에 맞는 성능을  제공하면 된다. 그래도, 어느 정도 처리 성능을 비교해 둘 필요가 있다. 왜냐하면 두 모델의 성능 차이가 매우 클 수도 있기 때문이다. 



## 모델링

Discrete Event Simulation 

- Send / Recv Event 
- Time 
  - Processing Time 
  - Send / Recv Time 



IOCP 쓰레드 풀 모델 

분리된 애플리케이션 쓰레드 풀 모델 



### IOCP Thread Pool Model 

GQCS (GetQueuedCompletionStatus)로 IOCP 포트의 완료 여부를 검사하는 쓰레드에서 수신과 송신의 완료를 포함하여 애플리케이션 로직을 모두 처리하는 방법이다. GQCS의 호출은 바로 리턴 되게 하거나 일정 시간 대기하게 할 수 있다.  

송수신 때문에 커널 쓰레드와 경쟁은 피할 수 없어 보인다.  얼마나 발생할 것인가? IO 량에 비례한 발생이 예상된다. 

### Separate Application Thread Pool Model 

IOCP 쓰레드는 GQCS에서 무한 대기하고 별도의 쓰레드 풀에서 애플리케이션을 처리하는 방법이다.  

boost.asio는 여러 네트워크 API를 추상화하고 이런 방식으로 처리하도록 유도한다.  큐를 한번 더 사용하여 IO 쓰레드에서 처리한 내용을 받는다. 전송은 직접 처리하여 요청까지 하는 경우가 많다. 

#### Context Switching 제어 

IO 쓰레드와 앱 쓰레드의 개수를 생성 시 조절한다.  GQCS 대기 중 코어 수보다 실행 중인 쓰레드 개수가 작아진다.   GQCS 들어갈 때 앱 쓰레드 실행 개수를 늘린다 (어떻게??) . 바로 대응하기 보다는 실행 상태를 길게 보면서 조절한다.  

### 비교 

별도의 애플리케이션 쓰레드를 두는 방식은 GQCS가 대기하지 않는 방식과 동일하다.  

Context 스위칭이 별도 쓰레드 풀을 사용하는 모델의 단점으로 꼽힌다. 합쳐서 실행 중인 쓰레드의 개수를 코어 개수로 제한하면 IOCP 호출 후 처리하는 방식과 동일하다.  이를 어떻게 구현할 수 있는가? 

여러 가지 파라미터의 차이는 있다. 

IOCP 쓰레드 모델이 OS와 긴밀하게 연결되면서 GQCS를 0으로 하면 별도의 앱 쓰레드가 필요 없이 context switching 도 줄일 수 있는 모델이다. 

분리된 앱 쓰레드 모델을 사용하더라도 context switching을 줄일 수 있도록 구성해야 한다.  전체 쓰레드 개수가 코어 개수보다 적당히 많아야 한다. IO 부하가 크다면 앱 쓰레드를 줄이고 앱 부하가 크다면 IO 쓰레드를 줄인다. 

### Parameters  

- IO 쓰레드 개수 
- 앱 쓰레드 개수 
- 통신 부하 정도 



### Measurements 

테스트는 동일한 구조가 서로 마주보면서 서로에게 부하를 주도록 한다.  Send / Recv가 있는 구조라 가능하다. 

   A >> A'

   A << A'

그러면 양쪽의 파라미터를 조절하면서 특성을 살펴볼 수 있다.  

- 통신이 있어야 한다. 
- 파라미터 조절이 가능해야 한다. 



### 결론 

IOCP 쓰레드 풀 모델은 커널 쓰레드와 경쟁한다.  앱 쓰레드 모델은 앱 쓰레드, IOCP 쓰레드, 커널 쓰레드가 경쟁한다.  앱 쓰레드 모델이 쓰레드가 경쟁이 더 많으나 쓰레드 개수를 조절하여 앱 특성에 맞게 조절할 수 있다. 

IOCP 쓰레드 풀 모델이 문맥 전환 비용은 더 적다. 그렇다고 앱 쓰레드 모델이 비용이 대단히 크지는 않다.  수치는 다음과 같다. 

- TODO: 수치들 정리 





## 자료 

https://en.wikipedia.org/wiki/Context_switch#User_and_kernel_mode_switching

- L2 캐시 다시 채우기가 가장 큰 영향 







































