# unique id in 64 bits 

- 50년간 고유한 밀리초 단위를 위해 36비트가 필요
- 4천대의 서버를 위해 12비트 필요 
- 남는 16비트를 순서로 사용 



이런 제약이 없으려면 uuid가 필요하다.  uuid는 매력적이다. 



## uuid 사용 시 단점들 

장점은 명확하다. 아이디 생성에 신경 쓰지 않아도 거의 영원히 고유한 아이디 생성이 보장된다.  단점은 하나다. 늘어난 길이로 인해 메모리 사용과 트래픽이 증가한다. 



### 트래픽 줄이기 

코드가 복잡해진다.  일대일 대응 (bijective) 함수 $sid_{charid} :  uuid   \rightarrow  shortid$  가 필요하다. 역함수는 shortid 에서 uuid로 변환한다.  버그가 발생할 가능성이 많아진다. 



### 메모리 

시스템 전체에 누적된 아이템의 캐수가 $I_n$ 이라고 하면, 메모리 증가량은 $64I_n$ 만큼 증가한다.  1억 개 정도의 아이템이라고 하면 증가분은 6GB 정도이다.  차이는 꽤 된다. 



### API와 C++ 관리 

128 바이트를 효율적으로 지원하기 어렵다.  C++에서 자연스럽지 않다. 



## 알고리즘 

20년 이상 서비스 되는 게임들이 이미 나왔다. 시간에 제약을 두기는 어렵다. 한 서버에서 밀리초당 4천개의 아이템이 동시에 생성되기는 어렵다. 따라서, 고유한 시간은 늘리고 (40비트), 서버 대수는 유지하면 된다. 

- 시간 : 40비트 
- 서버 : 12비트 
- 순서 : 12비트 



이와 같이 하면 Twitter Snowflake와 거의 동일하다. 비트 수만 약간의 차이가 있다.  서버 아이디로 하지 않고 고유 아이디 생성기의 데이터 값으로 설정한다. 

```scala

protected[snowflake] def nextId(): Long = synchronized {
    var timestamp = timeGen()

    if (timestamp < lastTimestamp) {
        exceptionCounter.incr(1)
        log.error("Rejecting requests until %d.", lastTimestamp);
        throw new InvalidSystemClock(
            "Refusing to generate id for %d milliseconds".
            format(lastTimestamp - timestamp)
        )
    }

    if (lastTimestamp == timestamp) {
        sequence = (sequence + 1) & sequenceMask
        if (sequence == 0) {
            timestamp = tilNextMillis(lastTimestamp)
        }
    } else {
        sequence = 0
    }

    lastTimestamp = timestamp
    ((timestamp - twepoch) << timestampLeftShift) |
    (datacenterId << datacenterIdShift) |
    (workerId << workerIdShift) | 
    sequence
}

```

알고리즘 자체는 간단하다. 마지막에 밀리초를 에포크에서 차이 값으로 구하고, 서버 아이디와 순서를 반영한다. 









