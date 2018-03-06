# Reflection 

다양한 C++ 리플렉션 라이브러리들이 있다. 이들을 조사하고 적합한 것을 찾아 사용하면 매우 많은 기능들이 쉽게 구현될 수 있다. 



## Manual Reflection 

- https://github.com/rttrorg/rttr
- https://billyquith.github.io/ponder/docs/index.html

둘 다 깔끔한 인터페이스를 갖고 비슷한 스펙을 갖는다.  둘 다 MIT 라이센스이다. rttr이 문서가 더 깔끔하다. 기능이 비슷하다면 rttr을 쓰면 될 것 같다. 





## C# 메세지 생성  

응용의 하나로 IDL 없이 C++로 구현된 메세지들에 대해 C# 코드를 생성한다.  bitsery와 rttr을 쉽게 구성할 수 있는 Macro들을 찾아 본다. 여전히 잘 모르는 Macro의 다양한 기법들이 있다. 

IDL을 두는 것이 좋겠다. enum 같은 경우 다시 타이핑을 모두 해주어야 한다. 단순한 IDL에서 코드 생성은 쉽다. IDL 컴파일 후 코드 생성 시 디버깅을 위해 reflection 코드를 추가하는 건 좋은 시도로 보인다.  













