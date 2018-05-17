# Game Server Script Language 

C++ 쉽게 잘 연동되는 언어가 필요하다. 성능이 중요할 수도 아닐 수도 있다. 개선이 쉬운 언어에서 시작해서 LLVM까지 붙이는 작업이 가능하면 더 좋다. 매우 빠르면 좋지만 셋업만으로도 충분할 수 있다. 

- 스크립트로 작업하다가 C나 C++로 빌드할 수 있는 언어 
  - 빠르게 작업하고 최종적인 건 빌드로 처리 
- 문법이 데이터 중심으로 if 문 등은 적게 사용할 수 있는 언어 
  - 선언적인 스타일이면 더 좋을 듯 



## 언어들 

- lua 
  - Ravi 
    - 루아의 개선 버전 
    - 특히, 로컬 변수의 기본 스코프가 로컬이고 클래스 타잎, 타잎 지정이 가능 
    - LLVM JIT 
  - 루아도 tranpiler가 있긴 하다.  
- chaiscript 
  - 문법이 깔끔하고 C++ 연동이 쉽다. 
  - C++로 transpiler를 구현해 볼 만하다. 
- scheme 
  - chicken이 c로 변환하는 기능이 있다. 
  - interpreter와 transpiler를 함께 사용할 수 있다. 
  - C++ 연동이 쉬워야 하는데 이 부분 확인이 필요 
  - 문법이 익숙하지 않을 듯 
- ferret
  - clojure c++ transpiler 
  - java에 의존한다. 
  - https://ferret-lang.org/
  - c, c++ FFI 

chaiscript 또는 이와 유사한 언어로 transpiler 작성을 한다.  ferret을 선택할 수도 있다.  clojure 파서부터 구현?? 



## chaiscript

```c++
class Rectangle {
  attr height
  attr width
  def Rectangle() { this.height = 10; this.width = 20 }
  def area() { this.height * this.width }
}
var rect = Rectangle()
rect.height = 30
print(rect.area())
```

거의 c++로 그대로 변환 가능한 문법을 갖고 있다. C++ 11 header only 이기도 해서 쉽게 처리가 가능하다.  어떻게 할 것인가? 코드를 살펴보고 이해하면 되겠다. 

fork 하고 이 방향으로 간다. 타잎이 없는 언어라는 점이 좀 어려울 듯 하다. 타잎 추론을 넣어야 한다. 



### C++에서 스크립트 호출 

eval 함수 외에 다른 방법이 있는가?  1282 likes 로 꽤 높긴 하지만 lua 만큼은 아니다.  ravi는 439 정도에 있다. Likes만 믿을 수는 없다만. 

함수를 가져와서 호출 할 수 있다. 이를 사용하면 양쪽의 연동이 가능하다. eval 후 사용한다.  함수만으로 호출 가능하면 기능이 제한적이 된다. 파일 모두를 실행하고 연결하는 방식이 좀 어려워진다. 

VM은 여러 개 만들 수 있고 서로 다른 메모리를 사용할 것으로 보인다. 이것도 확인해야 한다. 

### Transpiler 

코드 자체는 C++로 잘 변경할 수 있어 보인다. 하지만 사용 인터페이스가 달라지므로 두 가지를 모두 지원해야 한다. 

on_find_enemy = chai.eval(); 



## C++ 스크립트 

RCC++ (Runtime Compiled C++)은 C++을 실행 시간에 컴파일하고 로딩해서 기능을 변경하는 방법이다.  프로젝트를 잘게 쪼개서 처리하는 것과 비슷한 아이디어로 DLL에 기반한다.  스크립팅은 이 정도로도 가능해 보인다. 

https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus/wiki

뭔가를 만들기 좋아하고 규칙이 만들어지면 좋은 사람들은 이 쪽을 선택해도 될 것 같다. 나는 아니다. 언어가 좋다. 



RCC++와 같은 기능을 찾기 전에 C++ 코드 자체가 깔끔한 스크립트가 되도록 할 방법을 찾아야 한다.  null 포인터가 없는 깔끔한 환경 안에서 데이터와 메세지 중심으로 제한된 공개 인터페이스로 동작하도록 한다. 

컴포넌트 단위의 내부는 최대한 감추고 인터페이스가 명확하고 간결하도록 한다. 그게 먼저다. 

MPL과 C++의 개선된 기능들을 활용하면 C++가 영역별로 마치 스크립트인 것처럼 만들 수 있다. 이 부분이 가장 중요하다. 



## Expression Template Library 

MPL의 기법 활용 중 하나로 봐도 된다. DSL의 일종이다. 컴파일 시간 부담은 있다. 



























