# forgottenserver 분석 

게임 컨텐츠 구현이 충실해 보인다.  아키텍처는 단순하다. 분산이나 멀티쓰레드 처리가 없다. 그래서 게임에 더 집중하고 있다. 게임 내용을 구현하는 한 예로 살펴보면 도움이 될 듯 하다. 



# 준비 



## 분석 환경

github에서 받았다. theforgottenserver.sln이 있다. vc14니 vs 2015이다. vs2015 라이센스가 안 돼서 vs 2017로 실행한다. 빌드하는 것이 목적은 아니므로 일단 진행하면서 본다. 



162개 파일이 있다. 툴 성격과 통신, 컨텐츠로 나누어진다.  boost와 lua를 사용한다. 



## 한번 훑기 

훑어 봐야 뭘 봐야 할 지 알 수 있다. 파일별 내용을 본다. 

- account.h

  - ```c++
    struct Account {
    	std::vector<std::string> characters;
    	std::string name;
    	std::string key;
    	time_t lastDay = 0;
    	uint32_t id = 0;
    	uint16_t premiumDays = 0;
    	AccountType_t accountType = ACCOUNT_TYPE_NORMAL;
    
    	Account() = default;
    };
    ```

  - 이름, 키, 캐릭터 목록을 갖는다. 

- action.h / action.cpp

  - Action : Event 클래스 
  - Actions : BaseEvents 
  - pugi::xml_node와 pugi::xml_attribute로 구성된 이벤트이다. 
  - Thing이란 이름과 클래스도 흥미롭다.
    - 비트켄슈타인의 Thing인가? 
  - Event는 script를 갖는 이벤트이다. 
  - Actions의 인터페이스도 흥미롭다. 

- ban.h / ban.cpp

  - ```c++
    struct BanInfo {
    	std::string bannedBy;
    	std::string reason;
    	time_t expiresAt;
    };
    ```

  - 문자열로 처리했다. 

  - 데이터를 어떻게 구성하면 좋을까 생각하게 된다. 

    - enum 
    - type 
    - script / data
    - 옵션들 

  - IOBan 클래스 안에 static 함수들이 있다. 

    - 뭔가 전역적으로 물어볼 때가 필요할 경우 과감하게 쓴다. 

- baseevents.h 

  - 인터페이스를 제공한다. 
  - 게임에서는 아마도 Action과 Actions를 사용할 듯 
  - 게임 이벤트와 Action은 중요하고 필요하다. 
    - 컨텐츠를 모듈화 하고 시간과 조건에 따른 처리를 구조화 하려면 필요하다. 

- bed.h / bed.cpp

  - BedItem : Item 클래스 
  - Item을 보게 된다. 
    - 아이템의 속성 / 옵션 / 기능은 어떻게 구현할 지 생각하게 된다. 

- chat.h / chat.cpp

  - 채널 목록을 갖는 채팅 클래스와 채팅 채널 클래스로 구성
  - 16비트 채널 아이디를 사용한다. 

- combat.h / combat.cpp

  - 타일 상의 전투 처리
  - 플래그 값들로 되어 있다. 
  - 이는 event / condition + attribute / action / effect (비트, 값) 로 구조화 되어야 한다. 
  - 정리했던 문제나 다시 생각해 봐야 한다. 

- condition.h / condition.cpp

  - 시리얼라이즈 가능한 (통신에 사용) 조건에 따른 처리이다. 
  - Creature (몬스터) 들에 적용되는 조건 기반 효과이다. 
  - 이 부분도 효과를 적용하는 과정으로 생각할 수 있다. 

많다. 구현에서 배울 점들이 크게 많지는 않아 보인다. 기회될 때 더 본다. 

게임 컨텐츠에 대한 애정과 세세한 구현은 본받아야 한다. 



















