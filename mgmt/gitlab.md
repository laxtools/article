# gitlab

설치 가능한 git 개발 허브이다.  VM 밖에 없어 설치가 잘 되지 않았다. 제대로 장비를 구해서 설치를 하고 프로젝트를 진행한다. AD 연동까지 진행해야 하는데 프로젝트 진행은 작게 일단 한다. 

다른 기능보다 허브를 제공한다는 것이 가장 큰 강점이다. 



## gitlab flow 

git을 활용한 여러 가지 flow들이 있다. 기반은 다음과 같다. 

-  빠른 브랜치 전환 기능 
  - git pull
  - git checkout branch 
- 병합 요청, 리뷰, 병합 기능 
- Linux 커널 개발의 흐름 
  - 다수의 개발자들과 많은 변경에 대한 처리 흐름 

### 게임 개발에 적용 가능성 

- 브랜치 생성과 전환이 100GB 정도에 대해 빠른지 
- 바이너리에 대해 병합 시 충돌을 처리하는 방법 
  - 최신 버전을 사용하는 방법으로 가능할 지



### 흐름 

master, 로컬 (origin), production 브랜치를 사용한다. 로컬이나 자기 브랜치(기능 개발)에서 작업 후 master로 병합한다. 병합된 내용을 production에 merge 요청을 보낸다. master가 모든 변경을 보유하고 production은 릴리스되는 내용들을 갖게 된다. production으로 가기 전 pre-production을 갖고 안정화 작업을 진행한다. 

게임의 경우 production에서 지역 브랜치를 만들고 로컬라이제이션을 진행한다. 

master, origin, user-feature, rc 브랜치, release-version, release-version-kr, release-version-jp, ... 

user-feature 브랜치는 백업용에 가깝다. rc 브랜치로 병합 요청은 리뷰 후 병합된다. 여러 명의 협업이 필요할 경우 dev-feature 브랜치를 만든다. 이럴 경우 user-feature 브랜치는 없어도 된다. 















