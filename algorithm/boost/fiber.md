# fiber

work stealing 알고리즘도 구현되어 있다. coroutine은 앞으로 계속 만나게 될 주제이다. 자유롭게 쓰면 많은 곳에 활용할 수 있다. dispatch하고 연계해야 하니 바로 잘 되지는 않겠지만 연습해 볼 수 있다. 



## 느낌 

- go의 goroutine 느낌
  - channel 통신
  - work sharing / work stealing 구현 
  - 자체 쓰레드 풀이 있는 듯 
    - 맞는 지는 모르겠고

- 예제들은 주로 계산형
  - channel이 있어 그런 모델도 지원할 듯 
  - 게임은 덩치가 커서 잘 맞을 지 모르겠다. 

## cpu_relax.hpp

cpu_relax() 함수가 있다. 윈도우 용은 YieldProcessor() 함수이다. 

 _mm_pause()로 CPU에 스핀 중이라고 힌트를 주면 효율적이 된다고 한다. 스핀 도는 시간 낭비를 줄일 수 있다. 자료는 여기. https://yonmy.com/archives/99



## spinlock_ttas.hpp

lock() 함수가 스핀락을 구현한다. 2단계로 되어 있고, 스핀 횟수를 std::uniform_int_distribution을 사용하여 조절하는 점이 재미있다. 

### std::atomic 

- std::memory_order_relaxed
- std::memory_order_acquire

```c++
typedef enum memory_order {
    memory_order_relaxed,
    memory_order_consume,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst
} memory_order;
```

https://en.cppreference.com/w/cpp/atomic/memory_order

- 상당히 길게 설명한다. 꽤 난해해 보인다. 

https://preshing.com/20140709/the-purpose-of-memory_order_consume-in-cpp11/

- 항상 뛰어난 사람들이 있다. 
- acquire / release에 대해 자세히 설명하고 있다. 
- 그림과 어셈블리 코드로 보여준다. 
- 훌륭하다. 



### 용도 

spinlock을 쓸만한 곳이 있는가? session에서 플래그 체크에 recursive_mutex를 사용한다. 여기에 딱 쓰기 좋은 거 같다.  boost의 스핀락도 있지만 fiber에 있는 구현도 괜찮아 보인다. 세션의 트래픽이 많아지면 도움이 많이 될 듯. 



## work_stealing vs. work_sharing 

fiber 스케줄링 알고리즘으로 구현했다. task 스케줄링에 적용할 수 있어 자료를 찾고 이해한다. 

https://en.wikipedia.org/wiki/Work_stealing

- fork / join 중심으로 설명한다. 
- thread affinity를 어느 정도 지키면서 노는 CPU가 없도록 한다. 























