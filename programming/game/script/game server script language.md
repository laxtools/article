# Game Server Script Language 

C++ 쉽게 잘 연동되는 언어가 필요하다. 성능이 중요할 수도 아닐 수도 있다. 개선이 쉬운 언어에서 시작해서 LLVM까지 붙이는 작업이 가능하면 더 좋다. 매우 빠르면 좋지만 셋업만으로도 충분할 수 있다. 

- 스크립트로 작업하다가 C나 C++로 빌드할 수 있는 언어 
  - 빠르게 작업하고 최종적인 건 빌드로 처리 
- 문법이 데이터 중심으로 if 문 등은 적게 사용할 수 있는 언어 
  - 선언적인 스타일이면 더 좋을 듯 

## 방향 

오가며 이것 저것 다 생각해 볼 수도 있겠지만 여기 정도에서 멈추는 게 게임 개발자에게 맞다. 다음과 같이 방향을 확정한다. 

- lua를 사용한다 
  - 필요한 곳에서 사용하고 빠르게 해 본 후 해당 도메인 언어나 데이터 정의, C++ 구현을 사용할 수 있다. 
  - 충분한 성능을 제공하면 교체하지 않는다. 게임에 따라 다르다. 
  - 기본 사용성을 충분히 갖춘 스크립트 연동과 실행 환경을 구비한다. 
    - 디버깅 
    - 스크립트 빌드 및 관리 
    - 연동 인터페이스의 개선
      - sol2 정도의 좋은 인터페이스나 sol2 자체의 정복
- ReoGrid와 데이터 편집 툴 개발 
  - ReoGrid는 소스도 괜찮고 기능도 훌륭하고 충분하다 
  - ReoGrid 자체를 수정할 수도 있지만 툴 구현에 집중한다. 
  - 편리한 인터페이스를 추가한다. 

아래는 지금까지 고민한 내용들이다. 


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
- nim 
  - ferret 처럼 타겟 언어 백엔드로 컴파일 
  - C/C++, Objective-C, Javascript 지원
  - 언어는 lua나 파이썬과 유사
  - 6,266 star on github (엄청나다)
- cling 
  - c++ interpreter with c++ code 
  - 이 길이 가장 적합 
- behavior
  - boolean expression with c++ functions 
  - behavior tree
  - signal (message)
  - how to interpret it? 
    - reflection
  - 여전히 cling이 가장 매력적이다



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



##Nim 

C++ 백엔드를 사용하는 개발 흐름을 본다. 바인딩이 쉽고 컴파일된 코드 성능이 괜찮고 멀티 쓰레드 사용이 가능하다면 게임에 적용할 수 있다. 

Github의 star가 6천을 넘었고 Unreal 4 통합도 있으며 C++ 함수와 직접 매핑되므로 디버깅이 쉽다. 실제 사용해 봐야 얼마나 유용한 지 알 수 있겠으나 방향 자체는 내가 찾던 것과 같다. 인터프리터로 실행되어 빠르게 개발할 수 있고 C++로 빌드할 수 있어 빠르게 실행할 수 있다. 



### 설치 

https://nim-lang.org/install_windows.html

- windows binary 
- mingw 설치 함께 진행 



### Hello World!

```python
# This is a comment
echo "What's your name? "
var name: string = readLine(stdin)
echo "Hi, ", name, "!"
```

아직 메인스트림 언어는 아니다. C로 컴파일해서 처리한다. 

```c

N_LIB_PRIVATE N_NIMCALL(void, deinit_WHgd5C59bkXWDz3vnAxfzXQ_2)(tyObject_CellSet_jG87P0AI9aZtss9ccTYBIISQ* s) {
	tyObject_PageDesc_fublkgIY4LG3mT51LU2WHg* it;
	nimfr_("deinit", "cellsets.nim");
	nimln_(85, "cellsets.nim");
	it = (*s).head;
	{
		nimln_(86, "cellsets.nim");
		while (1) {
			tyObject_PageDesc_fublkgIY4LG3mT51LU2WHg* n;
			nimln_(414, "system.nim");
			if (!!((it == NIM_NIL))) goto LA2;
			nimln_(87, "cellsets.nim");
			n = (*it).next;
			nimln_(88, "cellsets.nim");
			dealloc_RCjNtRnHdRYntrcE7YtwWw(((void*) (it)));
			nimln_(89, "cellsets.nim");
			it = n;
		} LA2: ;
	}
	nimln_(90, "cellsets.nim");
	(*s).head = NIM_NIL;
	nimln_(91, "cellsets.nim");
	dealloc_RCjNtRnHdRYntrcE7YtwWw(((void*) ((*s).data)));
	nimln_(92, "cellsets.nim");
	(*s).data = NIM_NIL;
	nimln_(93, "cellsets.nim");
	(*s).counter = ((NI) 0);
	popFrame();
}
```

stdlib를 wrapping한 함수 중 하나이다. nim이 어떻게 다른 언어로 만들어지고 실행되는 지 볼 수 있다. 

sol2와 같은 빠른 lua wrapper를 사용한 처리가 더 나을 수 있다. 디버깅만 잘 되면 문제가 없을 듯. 

### Macros

lisp 처럼 언어 자체를 확장할 수 있는 매크로 기능을 제공한다.  



# lua 



## 디버깅 

dev-cat에서 만든 것. 다른 것들도 있다. 디버깅 가능하도록 C++에서 옵션으로 설정할 수 있도록 한다. 실행 시 선택해서 개발 중에는 언제라도 디버깅 가능하게 한다. 

## 활용 

AI, 퀘스트, 맵 처리 모두 가능하다. 빠른 호출 인터페이스를 사용하면 순수 C++ 함수 호출에 근접한 성능을 낼 수 있다. sol2가 그러하다. 그래도 잦은 호출 보다는 설정 방식이 좋다. 



# Tiny Expression Language

C++ 함수 호출이 가능한 매우 작은 expression 언어를 만들고 이를 데이터에 포함하여 사용한다. 예를 들어, 아이템 사용 조건 같은 곳, AI의 특정 행동 실행 조건으로 사용한다. 

lua를 사용해서 같은 효과를 만들 수 있다. tag를 주면 된다. 

```
lua: self.HasTargetItem(10031) and self.IsAlive()
```

csv 테이블에서 위와 같은 효과를 줄 수 있다. 



## 자료 

https://github.com/codeplea/tinyexpr

- 작은 expression 파서와 실행기 
- C 함수 호출 기능 



# 데이터 

관계형 모델은 오래 사용되었다. 정규화가 많으면 편집과 조회가 불편한데 이 부분만 해결하면 관계형 모델로 게임 데이터는 모두 서술 가능하다. Verbosity를 낮추고 사용이 편한 구조를 csv와 바이너리로 만들 수 있다. DBMS에 넣어 일관되게 관리할 수도 있다. 편리한 편집 도구만 있으면 된다. 

엑셀 형식의 편집 기능을 직접 구현하여 빠르게 보고 편집 가능하게 한다. 몇 가지 매크로 기능을 쓸 수 있게 한다. 

## 라이브러리 

https://archive.codeplex.com/?p=wpfsheet



https://reogrid.net/

- MIT 라이센스 
- 방대한 소스 코드 
- WPF 지원 

소스를 수정하기 보다는 사용하는 형태로 정리한다. 

유료화 도구가 상당히 많이 있다. 



## 다른 접근 



## 텍스트 편집 

텍스트 형식으로 편집한다. GUI이긴 하다.  EmEditor에 텍스트 기반 편집 기능이 포함되어 있다. 에디터는 그 나름의 방대한 경험이 축적되어 있다. 



## Excel Application 

엑셀 자체를 스키마 정의와 편집에 사용하는 방법이다. 

http://datalogicauto.com/

- 서비스를 제공하는 곳



