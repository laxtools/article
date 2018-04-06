# wise model 

분산 처리 모델을 만들려 한다. 채널과 채널 전송에 기반한다. 물리적인 연결을 encapsulate 한 채널과 채널의 공유, 채널 내 타잎과 필드 값 기반의 두 개의 send / receive 기능, 비동기 처리와 continuation, 장애와 장애 콜백을 포함하는 게임 서버에 실질적으로 사용된 개념들에 기초하여 정리한다. 

- 물리 연결 encapsulation 
  - 세션 기반의 채널 생성과 사용
- 채널 공유 기능
  - 생성된 채널에 대한 관리 
  - 수신된 채널에 대한 라이프타임 / 상태 관리 
- 타잎과 필드 값 기반의 send / receive operation 
  - 비동기 처리 
  - operator <<, >>
    - channel << send; 
    - channel >> recv;
    - channel << msg 
    - channel >> {msg, action}
    - channel >> {topic, action}
- continuation 
  - send에 포함된 특성에 따라 처리 
  - 장애 시 처리를 포함 

pi calculus 를 통해 분산 처리의 semantic 모델 구성에 필수적인 요소를 파악하면서 정리해 나간다. fact들을 찾아 나가고 증명해 나간다. 필요한 개념들을 추가한다. 수학으로 모델을 잡고 코드로 완성하는 형태로 나아간다.  



# 대략의 스케치 

go 언어의 채널은 하나의 타잎에 대해 동작한다.   postfix, prefix operator로 <- 를 갖는다.  

```go
ch := make(chan string, 1)
ch <- "message"
rc <- ch
```

위와 같이 채널 오브젝트에 접근 가능하면 채널을 통한 통신이 가능하다. 언어적으로 같은 모델을 사용할 수 있다. 타잎이 하나인 것은 너무 제한적으로 보이며 비동기 처리를 가능하게 하는 것이 좋다. 

```c++
auto ch = make_channel("channel1"); 

auto msg = std::make_shared<msg_req_login>(); 
// initialize message 
msg->id = "user1"; 
msg->pw = "abc"; 

ch << msg;
```

```c++
auto ch = get_channel("channel1"); 
ch >> {"topic" : msg_req_login::topic, on_req_login}; 
```

대략의 개념은 위와 같다. 어려운 점들은 다음과 같다. 

- 채널의 상태 전파 

  - 생성
  - 소멸 
  - 장애 

- 메세지 전송 중 장애 발생 시 처리

  - ```c++
    ch << {msg, on_login_channel_error }
    ```

  - 위와 같이 원래 메세지를 에러 처리 함수와 연결해서 처리 가능

  - 타임 아웃 설정 등을 할 수 있다. 

  - 편하게 사용 가능해야 한다 

- 필드 기반 등록 

  - subscription과 포스팅이 다양하게 이루어진다. 
  - 예를 들어, 특정 게임 인스턴스로 메세지를 보낸다고 할 때 해당 인스턴스의 채널을 알아야 한다.





# 채널의 생성과 관리 

shared_ptr로 하고 이름과 다양한 키로 얻어 올 수 있게 한다. channel_service와 같은 단일한 지점에서 관리한다. 생성하면 여기에 등록된다. 

단일 지점에서 관리하면 생성 / 소멸 시 락 충돌이 있을 수 있다.  많은 채널을 사용하는 경우에도 대부분 채널 포인터를 얻어서 통신하게 되므로 실질적으로는 괜찮을 것이다. 중앙의 단일한 채널 서비스 외에 쓰레드 별, 기능별로 두는 방법도 있다. 적절한 선택이 가능하도록 지원하면 되는데 일단은 깔끔한 인터페이스가 중요하니 중앙에 두는 것으로 한다. 

다른 장비나 원격 시스템에서 생성된 채널 

# 메세지의 전파 

subscribe / publish 모델을 사용한다.  reflection 기능을 사용하고 필드 값 기반으로 전파 가능하게 한다. 토픽과 타잎을 맞추고 필드 값으로 전파 가능하다.  reflection 없이도 가능할 수 있다. 함수를 제공해서 맞춘 다음에 받는 방법도 있다.  채널 간의 연결로도 처리할 수 있다. 

## 채널 연결 

ch1.set_pipe { topic{game.play.*}, function to find channel and pass } 

ch1.get_pipe(topic{game.play.*}).add( new_ch ); 

ch1.get_pipe().remove("channel..."); 



# 수학 모델 

파이 모델에서는 채널과 채널 전송 외에 특별히 얻을 게 없어 보인다. CSP는 서버 프로그래머에게 좀 더 익숙한 언어를 사용한다. 채널은 CSP도 갖고 있다. CSP를 모델링 언어로 삼고 전체 구조를 이에 맞춰서 설계하고 증명 한 후에 구현을 진행하는 것도 괜찮아 보인다. 이미 아이디어들은 있지만 정교하게 만들기 위해 필요하다. 

만세! Tony Hoare의 CSP 작업은 Robin Milner의 파이 모델에 기초한다. 

- $c.v$ : 채널 c로 v 전송
- $l.c$ : l의 채널 c 
- $\alpha P$ : P의 알파벳 (이벤트) 
- $a \rightarrow P$ : a then P

235 pages book, a csp book. 

Read chapter 1, chapter 2, chapter 4. Then, decide to read more or not. 

## Processes

자판기: 

- coin, choc event 
- in1p, in2p, small, large, out1p 
- event class
- alphabet 
  - 이벤트들 
- 이벤트는 즉시 발생한다. 
  - 긴 사건은 시작과 종료로 표시 
- 시간 요소 배제 (응답 시간 / 처리 시간 등)
  - 논리와 별도로 고려할 것을 제안 



- prefix 
  - ​





















































