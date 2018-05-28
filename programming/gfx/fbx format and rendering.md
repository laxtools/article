# FBX format and rendering 

FBX를 대부분의 아트 툴에서 제공하고 오토데스크 제품들을 대부분 많이 쓰고 있어 성공한 애셋 교환 포맷이 되었다. Mesh, Animation에서 시작하여 쉐이더까지 살펴보고 기초적인 렌더링에 활용한다. 



## FBX spec and rendering

http://docs.autodesk.com/FBX/2014/ENU/FBX-SDK-Documentation/index.html

프로그래밍 가이드는 오토데스크의 용어로 설명하기 때문에 처음에 잘 이해가 안 될 수 있다. 소스가 공개된 FBX converter나 importer들을 살펴보면서 용어와 개념들을 이해하고 직접 갖고 놀아 보는 것이 좋다. 



## Play w/ FBX 

- import mesh and render 
  - texture 
  - vertex 
  - face 
  - normal 
  - normal map 
- import anim and render 
  - skeletal debug 
  - shader 

DX의 sdkmesh 변환 도구를 참조하면 기본적인 흐름은 이해할 수 있다. 렌더링은 매시와 애니메이션이 시작이고 라이트와 재질이 끝이다. 

## Adding Material  

shader를 선택하고 파라미터 값들을 지정하여 다양한 효과를 낼 수 있는 구조를 여러 가지로 실험해 본다. 



## 자료 

- Autodesk의 FBX 프로그래밍 가이드 
  - http://docs.autodesk.com/FBX/2014/ENU/FBX-SDK-Documentation/index.html
- FBX 사용 한글 반말 번역 
  - http://ozlael.egloos.com/4041764
  - 즐~
- DX에서 직접 Fbx API를 사용하여 로딩 
  - http://www.walkerb.net/blog/dx-4/
- DX의 sdkmesh 형식으로 변환하는 프로그램 
  - https://github.com/walbourn/contentexporter
  - mesh, animation을 포함하고 있음 
  - sdkmesh 형식에 대한 정의 
    - https://github.com/walbourn/contentexporter/wiki/SDKMESH
- Unity의 FBX 지원 영상 
  - 메뉴를 연동해서 자동으로 갱신 처리 
  - http://bbs.ruliweb.com/news/read/99898

- C# SDK wrapper 
  - https://github.com/ArcaneDreams/ArcManagedFbx









