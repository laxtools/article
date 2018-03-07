
# Rendering Library 

- libcinder.org
- magnum 
  - c++ 11 opengl wrapper 
- urho3d.github.io
  - engine



공부를 겸하고 프로토타이핑 프레임워크로 사용하므로 magnum 정도가 적합해 보인다. magnum에서 시작하고 urho3d의 기능을 갖추는 방향으로 진행한다. 특히, skeletal animation이 가능한 모델 형식을 정의하고 fbx에서 import하여 렌더링할 수 있도록 한다. 

magnum으로 시작했는데 덩치가 커서 cinder로 교체한다. math, gl, shader 를 지원한다. 간결해 보이고 이전 버전의 Visual C++에서도 지원이 된다 (2008까지 있음). 여기에서 시작한다. 

## cinder install

prebuilt 버전이 Visual C++ 2013 버전까지 제공된다. Visual C++ 2017로 진행할 예정이라 git 에서 받아서 빌드한다.  외부 의존 라이브러리를 포함하고 있다. 





## Understanding 

기초 가이드 문서가 잘 되어 있다. 이를 따라서 진행한다. 이후에는 개별 영역에 대한 깊이 있는 이해가 필요하다. 게임에 사용하는 shader와 그래픽 알고리즘들을 이해하는 것이 목표이다. 





## magnum install 

**덩치가 크고 의존하는 라이브러리가 너무 많다**



vcpkg가 C++ 라이브러리에 제공된다.  https://github.com/Microsoft/vcpkg

### 패키지를 사용 

매그넘 개발에 참여하는 게 아니므로 라이브러리로 사용한다. 

http://doc.magnum.graphics/magnum/building.html#building-packages-vcpkg

sdl2 빌드 중 실패. 귀찮으니 더 귀찮은 개별 프로젝트 빌드 진행. 







