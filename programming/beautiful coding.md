# Beautiful coding 

아름다운 코드를 추구한다. 명확하고 정확한 코드, 이해하기 쉽고 간결한 코드가 아름답다. 작고 예쁜 코드를 쌓아 위대하고 복잡한 시스템을 만든다. 아직 많이 부족하지만 그런 경지를 찾아가는 여정을 시작한다. 



# 언어 차원의 확장과 기법  

매크로와 템플릿 기능, 연산자, 함수를 통한 DSL의 정의와 사용은 코드를 예쁘게 한다.  함수형 언어의 알고리즘들, 개념들의 사용은 코드를 간결하게 만든다. 



## 포인터 관련 매크로 

```c++
if ( nullptr != mTimerValidChecker )
{
    delete mTimerValidChecker; 
    mTimerValidChecker = nullptr;
}
```

위의 코드는 소멸자에서 지울 경우이다. 위는 매크로로 해제 연산을 만드는 것이 좋다. 

```c++
DELETE_CLEAR(mTimerValidChecker); 
```



## 점검 관련 매크로 

VERIFY, RETURN_IF, EXPECT, ENSURE는 필수적이다. 

THROW_IF도 가능할 수 있는데 별도로 처리하는 것이 나을 수 있다. 

```c++
int ResetTimerValidChecker()
{
    int cnt = 0;
	if ( nullptr != mTimerValidChecker ) 
	{
    	cnt = mTimerValidChecker->ResetTimerValidChecker(this); 
	}
	return cnt;
}
```

위는 작고 간단한 함수이다. 매크로로 간결하게 할 수 있다. 의미도 명확해지고 더 견고해진다. 

```c++
int ResetTimerValidChecker()
{
    VERIFY( mTimerValidChecker );     
    RETURN_IF( nullptr == mTimverValidChecker, 0 );    
    return mTimerValidChecker->ResetTimerValidChecker(this); 
}
```



## 작은 단위 클래스와 함수  

게임에서 HP, MP 등 리소스가 있는데 이를 가벼운 범위를 갖는 클래스로 만들면 일일이 체크하는 코드를 제거할 수 있다. 직접 구현해 본 적은 없지만 유용할 듯 하다. 

julia 언어가 멀티 함수를 사용한다. 아규먼트의 타잎별로 계속 override 가능하다. c++ 도 기본 기능으로 갖고 있다.  단지, 클래스를 변경할 수는 없다. 이런 관점을 따라 유틸리티 함수들을 동일 이름이라도 타잎이 다르면 다른 함수를 선택하도록 구성할 수 있다. 



## 이벤트를 통한 인터페이스 

퀘스트 / 업적 / 미션 / 스킬 / AI에 모두 잘 동작한다.  게임에서 상당히 잘 동작하는 방법이다. 작은 이벤트 단위 실행 함수나 클래스 분리와 함께 사용하게 된다. 의미가 잘게 나눠지므로 코드 파악이 수월해진다. 



두 가지 형태가 가능하다. 

- Command 패턴 방식 
  - 이벤트를 명령으로 만들어 호출하면 이벤트에 따른 실행을 하는 방식
- Observer 패턴 방식 
  - 등록하고 퍼블리싱 하면 콜백으로 호출되는 방식 



근본적인 차이는 없는데 각 영역별로 구현할 때 적합한 방법을 선택한다. 



# 함수 



## 변수가 아닌 함수로 동작하게 한다 

모든 모듈화 / 관심 분리 / 간결한 구조의 기반이다.  순수한 값 클래스가 있다면 이는 어떤 다른 동작 클래스의 변수가 되어야 한다. 



































