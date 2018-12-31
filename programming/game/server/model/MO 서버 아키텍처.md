# MO 서버 아키텍처 

MMORPG를 제외하면 모든 온라인 게임은 MO이다. 광범위하게 사용되는 구조로 전략 게임을 포함하고 MOBA, FPS도 동일 구조이므로 가장 중요한 온라인 게임 분산구조이다. 게임마다 차이는 있으나 대다수 공유하는 개념과 구현이 있으므로 이를 정형화한 틀을 제공하면 게임들을 빠르게 만들 수 있다. 

c++ 11 이후의 발전은 c++을 c#이나 java 수준으로 만들 수 있는 어떤 것이 나올 수 있다는 점을 강하게 시사하고 있다. 그간 주로 어려운 문제였던 포인터, 템플릿 사용이 수월해지고 람다나 타잎 추론 관련 기능의 추가로 쉽게 서술한 언어로 바뀌고 있다. 대중적인 장르의 게임을 효율적으로 만들기위한 토대가 어떤 지점에서 만들어질 것으로 예상하고 있다. 이는 서버 아키텍처의 구현에서 중요한 역할을 하게 될 것으로 보인다. 

# 기본 개념들

- 서비스 
  - 처리와 메세지 핸들링 단위
  - 내부 handler들 관리 
- scene
  - 게임 인스턴스 
  - handler
    - 내부에 시스템들을 가짐 
    - task로 실행됨



서비스 단위 분산 처리 시스템을 갖추고 task를 실행할 수 있는 구조를 둔다. scene은 유니티에서 쓰는 게임 장면 단위인데 이를 빌려 쓴다. scene은 handler로 자체 메세지 채널을 갖고 여러 시스템으로 기능을 나눠 구현한다. 

너무 개략적이나 우선 내가 이해하고 있는 범위로 나중에 상세한 설명을 할 기회가 있을 듯 하다. 여기서는 이미 갖춰진 기반 하에서 MO 게임의 아키텍처를 살피는데 집중한다. 



# 기능

MO는 다음의 기능을 필요로 한다. 

- 인증
- 로비 
  - 다양한 준비 
  - 상점
- 매칭
- 인스턴스 
  - 게임 플레이 

그 외 게임에 필요한 친구, 파티, 길드 등의 기능이 필요하다. 각 기능별로 중계하고 조절할 서비스가 필요할 수도 있고 로비로 구현할 수도 있다. 이 부분은 MO에 한정되지 않는 기능으로 별도로 살핀다. 



## 인증

- 로그인 
- 인증 마스터 서비스 
- 서버 이동 인증
  - 로비 
  - 게임 진입 
- 빠른 재접속 
- 로그아웃 



로비 연결을 유지한다. 큰 선택이다. 옮겨 다닐 수도 있지만 한 곳에 있으면 연결 관리가 쉬워진다. 대신 조율과 제어를 위한 뒷단의 서비스들이 늘어날 수 있다. 선택은 항상 장단점이 함께 온다. 서비스로 기능을 확장하는 방향을 유지한다.

로비 연결을 유지하면 게임 진입의 인증 부담은 줄어든다. 로그인에서 로비로만 이동하면 된다. 게임 진입의 인증은 서버에서 전달된 정보에 고유한 진입 인증 정보를 제공함으로써 가능하다. scene token과 같은 개념으로 볼 수 있다. 또는 인스턴스 아이디를 고유하게 해서 전달하는 것만으로도 가능한데 추측을 할 수도 있으므로 고유한 토큰이 필요하다. 

뒷단에 인증 마스터 서비스를 두고 인증 정보를 파일에 저장한다. rocksdb와 같은 영속성을 지원하는 key-value db를 사용한다. 이렇게 정보를 저장하고 있으면 토큰 기반으로 인증하여 빠른 진입이 가능하다. 재진입은 게임 플레이에서도 고려해야 한다. 상태의 추가가 필요하고 단선 상태에서 로그아웃으로 전환하는 과정이 명확하게 구현되어야 한다. 



# 매칭

예전에는 인스턴스 목록과 상태를 보고 사용자가 선택하는 방식을 많이 썼는데 이는 상태 불일치, 진입 충돌 문제가 있다. 요즘은 재미있게 같이 플레이할만한 사용자를 알아서 찾아서 플레이 공간에 넣는 방식을 주로 쓴다. 사용자가 설정한 조건을 허용하고 대상을 조건에 포함하여 선택 가능하게 하는 것으로 조건 설정 기반 확장을 하면 대부분 괜찮다. 

게임 인스턴스 내에서 매칭이 끝난 경우 매칭 가능하게 하고 해당 인스턴스로 진입 시킬 수 있어야 한다. 보드 게임들에서 기본 기능으로 제공하는 방식이다. 

## 설계

분산 시스템의 설계는 의미의 명시가 필요하다. 이는 각 노드의 상태 변화를 메세지(패킷)에 따른 변화로 확인할 수 있다. 함수 호출에 따른 상태 변화와 다르지 않다. 단지, 서비스 상태나 연결 상태를 고려해야 한다는 점만 다르다. 이는 분산 처리의 근본 문제라 할 수 있고 별도로 정리해 두었고 제일 아래 포함했다. 

Lobby, Match, SceneMaster 세 가지 서비스가 연관된다. Lobby는 사용자 연결을 유지하고 매칭, 정보 조회, 상점 등의 기능을 제공한다. Match는 매칭 서비스이다. SceneMaster는 게임의 인스턴스인 Scene을 관리하는  서비스이다. 

서비스 간의 피어 관계는 다음과 같다.

- Lobby - Match
- Match - SceneMaster

Lobby가 SceneMaster를 알아야 하는가? 매칭만을 위해서는 필요 없어 보이므로 Scene 쪽 정리할 때 다시 본다. 

프로토콜은 다음과 같다.

- User.ReqMatch
- Lobby.ReqMatch
- Match.ReqCreateScene
- SceneMaster.ResCreateScene
  - SceneService.ReqCreate
  - SceneService.ResCreate
- Match.ResMatch
- User.ResMatch



Scene을 만들고 매칭응답을 보내는 이유는 인증을 위해서이다. 

매칭 요청은 Lobby, Scene에서 올 수 있다. 

Match는 도메인을 미리 설정해 두는 것이 확장성을 위해 좋다. 

## 흐름

- User.s(Lobby, ReqMatch)
- Lobby.r(User, ReqMatch) > Lobby.d(ReqMatch) > Lobby.s(Match, ReqMatch)
- Match.r(Lobby, ReqMatch) > Match.d(ReqMatch) > Match.s(SceneMaster, ReqCreateScene)
- SceneMaster.r(Match, ReqCreateScene) > SceneMaster.d(ReqCreateScene) > SceneMaster.s(SceneService, ReqCreateScene)
- SceneService.r(SceneMaster, ReqCreateScene) > SceneService.d(ReqCreateScene) > SceneService.s(SceneMaster, ResCreateScene)
- SceneMaster.r(SceneService, ResCreateScene) > SceneMaster.d(ResCreateScene) > SceneMaster.s(Match, ResCreateScene)
- Match.r(SceneMaster, ResCreateScene) > Match.d(ResCreateScene) > Match.s(Lobby, ResMatch) 
- Lobby.r(Match, ResMatch) > Lobby.d(ResMatch) > Lobby.s(User, ResMatch)
- User.r(Lobby, ResMatch) > User.d(ResMatch)

이후 scene 진입 과정을 밟는다. 



## 매칭 처리

Match.d(ReqMatch) 처리 과정이 매칭 서비스의 핵심 기능이다. 게임마다 알고리즘은 약간 씩 다를 듯 하다. 내부 구현의 선택을 정리한다.

매칭은 대상 풀이 커야 재밌게 함께 할 수 있는 사용자들을 모아줄 수 있다. 그리고 매칭은 서버 부담이 적은 작업이다. 따라서, 하나의 핸들러로 충분히 처리 가능하다. 핸들러들이 최상위 매칭 범위를 결정하는 도메인 하나씩을 맡아서 처리한다. 도메인은 게임 기획에 따라 결정한다. 

### 페어 매칭

두명을 매칭하는 경우가 가장 단순하다. ELO와 같은 점수 기반 매칭이 가장 많이 쓰이므로 이를 전제로 한다. 같은 사용자와 계속 매칭되면 재미가 덜 하므로 점수 범위 내 랜덤 매칭을 사용한다. 요청 순으로 해당 사용자 범위에 있는 사용자를 찾아준다. 

#### 수치 범위 검색

$(u_1, ..., u_n)$의 사용자들에서 대상 사용자 $u_t$가 갖는 수치 범위 내 사용자들을 찾는 문제이다. 

**아이디어 1. 범위 리스트** 

- $r_1$ : 0 ~ 100, $r_2$ : 101  ~ 200, ... 
- 각 범위에 사용자들 배치 

**아이디어 2. 정렬과 바이너리 서치**

- list를 사용하여 정렬 상태 유지 
  - 삽입할 때 위치를 찾아서 넣기 
- 알고리즘을 직접 구현?
  - STL로 가능한가?

아이디어 2로 충분해 보인다. stl의 lower_bound, upper_bound 등을 사용하면 충분히 가능해 보인다. 성능을 확인하면서 구현하면 된다.  같은 값을 갖는 사용자들도 고려한다. 버그가 없어야 하고 정확해야 한다.

lower_bound로 얻은 iterator로 삽입하면 정렬이 유지된다. lower_bound, upper_bound로 찾은 iterator 주변을 검색하면 사용자들을 추출할 수 있다.

#### 조건 검색

ELO와 같은 포인트 외에 조건이 추가될 수 있다. 조건은 대상 집합을 분리한다. 공간이 나뉘므로 매칭이 어려워진다. 조건 검색은 기획에서 많은 고려가 필요하다. 될 수 있으면 이렇게 기획하지 않는 것이 좋다. 그래도 한번 생각해 본다. 

핑이 서로 좋은 사용자를 연결해주는 기능을 추가한다고 생각해보자. 사용자 간의 핑 값을 저장할 수는 없으므로 지역을 갖고 있다. 지역 간의 핑 값은 한벌만 갖고 있는다. <kr, us> 값을 인덱스로 두 사용자 간의 핑 값을 빠르게 검색할 수 있다. 

먼저 ELO로 대상 사용자를 검색한다. 그 다음 핑 값이 일정 범위 안에 있는 사용자를 찾는다. 없으면 실패로 처리하고 대기 큐에 넣는다. 너무 오래 걸리지 않도록 ELO 범위 확장을 사용한다. 핑 범위 확장은 플레이 경험을 나쁘게 할 수 있다. 

핑은 생각보다 단순한 조검 검색이다. 



### 그룹 매칭

여러 명의 사용자 간의 대전 게임은 그룹 매칭이 필요하다. 그룹 매칭은 쉬워 보이지 않는다. 몸 값이 비슷한 티믕ㄹ 구성하는 것처럼 ELO 합산 범위에 따라 다르게 할 수도 있고 역할에 따른 수치값으로 역할별로 뽑을 수도 있다. 

팀 매칭은 더 어려운 과제로 보인다. 팀을 형성하면서 적절한 대전이 가능한 팀을 만들어야 하므로 깊게 생각해야 한다. 별도 주제로 다루기로 한다. 흥미로운 주제이다. 

대부분의 게임은 단순한 그룹 매칭이 더 잘 동작하고 괜찮을 수 있다. 일정 수준이 되는 사용자들을 빠르게 묶어서 함께 플레이 할 수 있도록 하는 그룹을 묶는 작업은 팀 매칭보다는 간단하다. 또한 간단하게 구현하는 게 게임 개발 효율과 실질적인 플레이 경험에 더 좋을 수 있다. ELO와 같은 단계를 두고 단순한 정렬과 검색 기반의 페어 매칭과 유사한 기법이 충분해 보인다. 



# scene (게임 인스턴스)

게임 인스턴스를 씬으로 부르기로 했다. instance란 용어를 쓰면 필드, 채널 등과 혼선을 불러와 이를 포함하는 상위 개념으로 유니티에서 사용하는 게임 장면 단위를 차용한다. 

scene은 생성과 소멸, 진입과 진출이 모든 게임에 공통적으로 필요한 처리이다.  게임 플레이는 게임마다 다르고 이는 게임으로 별도 프로토콜에 따라 구성해야 한다. 생성, 진입, 진출, 소멸도 게임마다 다른 부분들이 있어 일반화하기 어렵다. 특수성의 일반성이라고 할 수도 있는 공통적인 처리 부분들이 있으므로 하나의 방법으로 정리한다. 

## 설계

### 서비스들

서비스 분산 구조에서 다음과 같은 서비스를 상정한다. 

- scene_service
  - scene의 생성과 실행
  - scene 진입과 진출 
  - scene의 소멸 
  - scene으로 메세지 전달 
- scene_master
  - 도메인별 scene 전체 관리 
  - match 서비스 등 다른 서비스와 처리 조율
  - scene의 수명 관련 처리 담당
    - 결정을 담당하는 유일한 권위
- scene
  - handler로 게임 플레이 패킷의 처리 
  - 진출과 상태에 따른 소멸 의뢰 
    - 반드시 scene_master에 결정을 받아 소멸 



scene의 생명 주기 (life cycle)는 단일한 책임 원칙에 맞게 scene_master가 결정해야 한다. 분산 시스템에서 메세지 (이벤트)의 흐름은 파악하지 못 한 곳에서 발생할 수 있고 비동기로 흘러 시차가 발생한다. 이를 코드에서 모두 고려하기 어렵고 변경을 예상하기는 더욱 어렵다. 따라서, 한 곳에서 정확하게 상태를 처리하는 것이 매우 중요하다. 

### 피어들

서비스 간의 피어 관계는 다음과 같다. 

- lobby - scene_master
  - 검색 / 참관 등을 위해 필요할 때가 있다
- scene_service - scene_master
- scene_master - match 
- scene_master - 다른 서비스들
  - 이를 가정해야 더 확고해진다. 



### 프로토콜

이 쪽은 게임을 만들다 보면 예상치 못한 프로토콜이 추가될 가능성이 높다. 여기서는 전형적인 예상 흐름에 대해 정리한다. 

- Match.s(SceneMaster, ReqCreateScene) 
- SceneMaster.r(Match, ReqCreateScene) > SceneMaster.d(ReqCreateScene) > SceneMaster.s(SceneService, ReqCreateScene) 
- SceneService.r(ReqCreateScene) > SceneService.d(ReqCreateScene) > Scene.d(ReqCreateScene) > Scene.s(SceneMaster, ResCreateScene) 
- SceneMaster.r(ResCreateScene) > SceneMaster.d(ResCreateScene) > SceneMaster.s(Match, ResCreateScene) 
- Match.r(SceneMaster, ResCreateScene) > Match.d(ResCreateScene) > Match.s(Lobby, ResMatch)
- Lobby.r(Match, ResMatch) > Lobby.d(ResMatch) > Lobby.s(User, ResMatch)
- User.r(Lobby, ResMatch) > User.d(ResMatch) > User.d(ConnectSceneService) > User.r(OnConnected) > User.s(SceneService, ReqJoinScene)
- SceneService.r(ReqJoinService) > Scene.r(ReqJoinService) > Scene.d(ReqJoinService) > Scene.s(SceneMaster, SynUserJoined)
  - Scene.s(User, ResJoinScene)
- User.r(Scene, ResJoinScene) > User.d(ResJoinScene) 

게임 진행의 시작은 Scene과 User간 통신으로 이루어진다. 



### 소멸 과정

- SceneMaster.s(SceneSerivce, ReqDestroyScene)
- SceneService.r(SceneMaster, ReqDestroyScene) > SceneService.d(ReqDestroyScene) > SceneService.s(SceneMaster, ResDestroyScene) 
- SceneMaster.r(SceneService, ResDestroyScene) > SceneMaster.d(ResDestroyScene)

시작이 SeneMaster에서 되도록 프로토콜을 짜야 한다. 매칭으로 진입 중인 사용자가 있는 경우처럼 Scene 단위나 SceneService에서는 모르는 상황이 있을 수 있다. ReqAskDestroyScene과 같은 약간 작위적인 메세지가 있는 것처럼 생각하더라도 꼭 이렇게 해야 한다. 나중에 메세지들이 비동기로 흘러다니고 상태가 꼬이면 매우 민감한 버그들이 나올 수 있다. 

중요하다. 

### 차이를 다루기

몇 가지 문제들을 생각해 본다. Scene은 여러 종류가 있다. 게임 종류도 다를 수 있다.  이들을 어떻게 다르게 관리할 것인가? 

scene은 생성과 진입 / 진출만 다룬다. 진입 조건 등 처리 등은 별도로 처리한다. 











# 분산 처리의 근본 문제 

분산처리의 근본 문제는 요청에 이어 응답 처리를 하는 것이다. 함수 호출과 비슷하지만 다음과 같은 점이 다르다 

- I. 요청과 응답 처리 코드의 분리
- II. 요청이나 응답이 전달되지 않을 가능성에 대한 처리

I)은 coroutine으로 결합하려는 시도가 있으나 오랫동안 사용한 콜백 함수로도 충분하다. 적절히 흐름을 설정할 수 있는 방법만 있으면 된다. 

II)는 좀 더 복잡하다. 비동기 처리가 내부 흐름에 있는 경우가 많고 네트워크 자체가 비동기로 동작하므로 응답이 전달되지 않는 경우 확인이 불가능하다. TCP의 경우 타임아웃으로 재전송을 시도하고 지속적으로 재전송이 실패할 경우 연결이 끊어진다. 이는 타임아웃 없이 전달 여부를 확인할 방법이 없다는 사실을 보여준다.  왜냐하면 동작하지 않는 장비나 구성 요소가 있다면 응답을 줄 수 없기 때문이다. 

전달이 실패할 경우는 결국 TCP의 연결 오류로 전달된다. 연결이 있는 모든 프로토콜은 그럴 것이고 UDP와 같은 경우는 자체적으로 구현해야 한다. 

- User.s(Game, SaveItem) > Game.r(User, SaveItem) > Game.d(SaveItem) > 
- Game.s(Db, SaveItem) > 

- Db.r(Game, SaveItem) > Db.d(SaveItem) > Db.s(Game, SaveItemResult) 
- Game.r(Db, SaveItemResult) > Game.d(SaveItemResult) > Game.s(User, SaveItemResult)

사용자 입력을 받아 아이템 저장을 Db 서비스를 통해 처리하는 전형적인 흐름이다. s, r, d는 각각, send, recv, do 함수이다. 

사용자 연결과 Db 서비스 연결 두 가지가 관여한다. 사용자 입장에서 서버는 하나로 보여야 하므로 Game과 Db간의 전달 오류 처리가 필요하다. 단일 서버라면 고민하지 않아도 되니 구현 난이도의 차이가 여기에 있다. 

서버 내의 분산 서비스 요청에 대한 타임아웃 처리를 어떻게 구성할 지를 정리하면 된다. 하나는 개별 전송에 대해 타임아웃 설정을 하면 된다. 하지만, 이는 서버 간 응답이 있는 모든 전송에 대해 설정해야 하므로 과도하다.  전통적으로 다른 서버와 연결이 끊어지면 해당 서버 기능의 중요도에 따라 전체 사용자나 게임 상태에 대해 정해진 처리를 한번에 적용하는 방법을 사용해 왔다. 

의존하는 서비스 장애시 처리 정책을 명시적으로 선택하고 적용하면 대부분의 경우 해결된다.  이 과정이 쉽다는 뜻은 아니고 반드시 서비스 별로 사용 형태와 프로토콜을 충분히 고려해서 결정해야 한다. 각 서비스 별 정책 결정 과정을 정리할 때 고려해야 할 요소를 정리하고 서비스 별로 확정하면 된다. 



## 서비스 장애 처리

게임 서버의 서비스들은 서로 의존하는 경우들이 많다. 분산하는 이유가 기능을 나누기위한 것이니 당연하다. 그리고 사용자의 요청과 연결된다. 전형적인 의존 관계는 User.s(Game, Action) > Game.r(User, Action) > Game.s(ServiceA, Request) > ServiceA.r(Game, Request) > ServiceA.d(Request) > ServiceA.s(Game, Response) > Game.r(ServiceA, Response) > Game.d(Response) > Game.s(User, Response)이다. 

이 긴 과정의 시작은 User.s(Game, Action)이고 끝은 Game.s(User, Response)이다. 중간의 처리 흐름에 분산된 서비스가 있다면 서비스 장애 처리에 대한 고려가 반드시 필요하다. 위의 예는 Game, ServiceA가 관여하므로 분산 처리이다. 

만약 ServiceA.Down 이 발생했다고 하면 해당 Game을 종료하는 것이 가장 강력하며 단순한 방법이다. 종료하지 않는다면 Down 상태일 경우 항상 오류로 처리하거나 Up 될 때까지 대기하는 구현도 필요하다. r(User, *)를 갖는 모든 코드에 넣어야 한다. 

서비스는 up / down 상태이거나 up / down 이벤트가 발생한다. 서비스 상태와 이벤트를 사용하여 의존 관계를 처리하는 코드를 모두 작성할 수 있다. s(ServiceA, *) 코드에서 처리하거나 r(User, *) 코드에서 ServiceA의 상태를 확인하여 s(User, Response)를 바로 처리한다. 요청을 받는 지점이나 ServiceA 전송 지점에서 확인한다. s(ServiceA, *) 이후에 ServiceA.Down 이벤트가 발생할 경우의 처리가 핵심이다. 

### 전송 후 장애 이벤트 처리 

 요청의 시작 지점이 되는 Game.r(User, Action)에 대해 Game.d(ServiceA.Down) > Game.s(User, Response)를 처리해야 한다. 두 가지 방법이 가능하다. 

- Game.r(ServiceA, ResponseError)  실행 
- User에 대해 장애 처리 후 Game.s(User, ServiceA.Down) 전송
  - 이를 처리하려면 상태 값들이 필요

일반화가 가능한 방법은 첫 번째로 보인다. 어떤 경우는 두 번째가 구현도 쉽고 처리도 괜찮을 수 있다. 첫 번째 방법을 전송 맵과 장애처리 알고리즘으로 살펴본다. 두 번째는 상태와 장애 처리로 살핀다. 

### 전송 맵과 장애 처리

<ServiceA, [s1, s2, ...]> 를 맵으로 관리한다. 각 서비스에 전송한 전송 이벤트들을 모두 둔다. ServiceA의 장애 이벤트가 발생하면 s1, ... 에 대한 처리 코드를 호출한다. 아이디어는 간단하지만 실질적이지 않다. 엄청 많은 이벤트가 발생할 수 있기 때문이다.

### 상태와 장애 처리

개별 전송에 대한 장애 처리 대신 개별 엔티티와 오브젝트에 상태를 기록하고 장애 시 처리하는 방법이 있다. 이 방법이 현실적으로 보인다. 개별 전송에 대한 기록도 상태라고 본다면 더 포괄적인 개념이다.

아이템 저장을 예로 든다면 WAIT_SAVE 상태를 둔다. Db.Down 이벤트에서 이런 상태에 있는 아이템에 대한 장애 처리를 진행한다. 사용자에게 응답을 보낸다. 

## 선택

근간이 되는 이론을 확립하는 것도 중요하지만 게임을 안정적이고 효율적으로 만들 수 있는 실질적인 수준을 얻는데 집중해야 한다. 다음과 같이 선택한다.

- 상태와 장애처리를 사용한다
- 장애 시 서비스 의존 기능들을 종료한다
  - 서비스 영향에 따라 수준을 결정한다
  - 사용자가 알도록 한다
- 수신 시 또는 전송 전 서비스 상태 처리를 한다

### 예시. 매칭 서비스 장애

User.MATCH_REQUESTED 상태를 갖는다. 해당 서비스 장애 이벤트에서 오류를 전송하고 상태를 변경한다. Lobby.r(User, RequestMatch)의 진입 지점에서 해당 서비스의 상태가 다운이라면 오류를 전송한다. 

사용자가 계속 요청하고 실패하게 하는 "잠시 후 다시 시도해주세요" 대신 "매칭 서비스를 사용할 수 있습니다" 라고 알려주면 좋다. 연결된 사용자들에게 매칭 서비스의 Down > Up 상태를 전파해주면 좋다. 클라이언트는 의존 서비스를 Up 상태로 가정하고 요청을 보낸다. 만약 오류 메세지를 받으면 Down 상태로 표시한다. 다시 Up 메세지를 받으면 사용 가능 상태로 표시한다. 

### 예시. Db 서비스 장애 

Db 서비스는 게임 플레이에서 가장 중요한 부분이다. 아이템 저장이 실패하는 상황에서 게임을 계속 유지하는 건 의미가 없다. 따라서, 이런 중요한 장애가 발생할 경우 사용자에게 알리고 게임을 종료하는 것이 좋다. 서비스에 큰 영향을 미치는 경우 의존하는 기능들을 종료하는 단순한 접근을 사용한다.

경험 상 네트워크 단선을 포함하여 시스템 상의 장애는 극히 드물기 때문에 견고한 Db 서비스 구현이 된다면 실질적인 장애는 거의 발생하지 않는다. 따라서, 안정적인 Db 서비스 구현에 집중한다면 의존 기능 종료가 실질적인 선택으로 충분하다.

### 예시. 인스턴스 관리 서비스 장애

게임 인스턴스 또는 공간을 관리하는 서비스에 장애가 있을 경우 이미 만들어진 인스턴스들은 게임을 계속 진행할 수 있다. 해당 서비스의 Up 이벤트가 발생 시 기존 인스턴스들이 다시 상태를 알려서 조정하면 된다. 

## 정리

선택에 잘 정리되어 있다. 매우 중요한 선택이므로 잘 기억하고 가끔 다시 살핀다. 



























