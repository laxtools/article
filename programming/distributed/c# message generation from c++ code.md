# C# message generated from C++ code

예전의 서버들은 memcpy를 serialization / deserialization에 사용하는 극단적인 경우도 있었다. 장점은 매우 빠르다는 것이고 단점은 endian과 문자열 encoding 때문에 여러 언어와 플래폼을 지원하지 못 한다는 것이다. 이런 단점이 해소된다면 여전히 가장 빠르다. 

C++에서 메세지를 struct 로 정의하고 memcpy를 쓸 수는 없지만 serialization/deserialization을 수행하는 코드를 template을 통해 만들 수 있다. 이 부분을 C#에서 그대로 맞춰서 처리하는 것 자체는 문제가 안 된다. 어려운 문제는 C# 코드를 수동으로 만들면 작업 부담이 매우 커진다는 점이다. 

이를 위해 clang의 C++ 파싱 기능을 활용하여 C++ 소스를 파악한 후 사용하는 여러 클래스들을 C#으로 생성하고 serialization / deserialization 코드도 함께 생성해 준다면 기존의 서버들을 유니티와 같은 C# 언어를 사용하는 환경에 적용 가능하다. 

## clang

clang은 라이브러리 형태로 사용 가능하다. 파스 트리를 사용할 수 있다. meta 정보 생성에도 유용하게 쓸 수 있으므로 내부가 아닌 외부의 MPL을 위해 활용 가능하다. 한번은 정복하고 가야할 부분이기도 하고 필요한 부분이니 이번 기회에 동작하는데까지 진행한다. 

## 목표 

이미 동작하고 있는 온라인 게임 서버의 이벤트 / 메시지 관련 파일을 대상으로 한다. 보통 클라이언트와 서버가 공유하기 때문에 별도의 폴더로 나와 있는 경우가 대부분이므로 해당 정보를 활용한다. 

# clang 라이브러리 사용하기 

- LLVM prebuilt download 
- https://shaharmike.com/cpp/libclang/

libclang 101이라고 불리는 위 문서를 기준으로 visual studio에서 libclang으로 파싱된 정보를 조회하고 이를 통해 C# 코드를 생성하는 데까지 진행한다. 만약 빠르게 성공한다면 기존 게임들의 Unity 포팅 속도를 획기적으로 높일 수 있다. 

https://github.com/chakaz/reflang

위 프로젝트를 진행하면서 얻은 경험을 공유하는 것이라 위에 보면 많은 예제들이 있다. 

## Step 1. Parse a very simple C++ header 

대부분의 경우 헤더에만 정의 되어 있다. serialization 코드까지 대상으로 할 수는 없기 때문에 헤더만 사용한다고 가정한다.  



## Step 2. Parse a real world example 







# 과제들 























