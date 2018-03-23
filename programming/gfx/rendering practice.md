
# Rendering Library 

- libcinder.org
- magnum 
  - c++ 11 opengl wrapper 
- urho3d.github.io
  - engine



공부를 겸하고 프로토타이핑 프레임워크로 사용하므로 magnum 정도가 적합해 보인다. magnum에서 시작하고 urho3d의 기능을 갖추는 방향으로 진행한다. 특히, skeletal animation이 가능한 모델 형식을 정의하고 fbx에서 import하여 렌더링할 수 있도록 한다. 

magnum으로 시작했는데 덩치가 커서 cinder로 교체한다. math, gl, shader 를 지원한다. 간결해 보이고 이전 버전의 Visual C++에서도 지원이 된다 (2008까지 있음). 여기에서 시작한다. 

## cinder install

prebuilt 버전이 Visual C++ 2013 버전까지 제공된다. Visual C++ 2017로 진행할 예정이라 git 에서 받아서 빌드한다.  외부 의존 라이브러리를 포함하고 있다. boost를 사용하고 있다. 지금은 놀랍지 않지만 예전 같으면 엄청 싫어했을 듯 하다. 

visual studio 2015용 솔루션을 갖고 있다. 여기 옵션을 일부 조정하여 쉽게 샘플을 만들 수 있도록 한다. 

괜찮게 진행되었다. 항상 이런 부분들이 좀 괴롭기는 하다. C++의 단점 중 하나이다. 



## nsight 설치 

쉐이더 지원이나 디버깅 등을 위해 설치. glsl syntax highlighting 지원되고 디버깅도 바로 가능하다. 

![nsight_example](D:\laxtools\article\algorithm\gfx\nsight_example.png)



## Understanding 

기초 가이드 문서가 잘 되어 있다. 이를 따라서 진행한다. 이후에는 개별 영역에 대한 깊이 있는 이해가 필요하다. 게임에 사용하는 shader와 그래픽 알고리즘들을 이해하는 것이 목표이다. 

### Tutorials







# Practice

- Modern OpenGL을 잘 설명
  - https://learnopengl.com/
  - 예제들도 괜찮고 Cinder와 같이 glm을 사용
- 위 사이트의 흑백으로 잘 보이는 버전
  - https://learnopengl.com/book/learnopengl_book_bw.pdf
  - 폰트가 별로라 온라인 버전이 낫다. 



LearnOpenGL in Cinder로 코드를 변경한다.  처음 부분들은 Cinder Tutorials로 가볍게 넘어갈 수 있다. 











## magnum install 

**덩치가 크고 의존하는 라이브러리가 너무 많다**



vcpkg가 C++ 라이브러리에 제공된다.  https://github.com/Microsoft/vcpkg

### 패키지를 사용 

매그넘 개발에 참여하는 게 아니므로 라이브러리로 사용한다. 

http://doc.magnum.graphics/magnum/building.html#building-packages-vcpkg

sdl2 빌드 중 실패. 귀찮으니 더 귀찮은 개별 프로젝트 빌드 진행. 







