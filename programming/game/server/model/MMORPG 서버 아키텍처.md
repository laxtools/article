# MMORPG 서버 아키텍처 

시스템 아키텍처는 대략 다음과 같이 구성할 수 있다. 

- world master
  - user system
  - scene handler
  - guild handler
  - chat handler
  - party handler 
- 프론트 서버 
  - lobby service
  - scene service
    - scene
      - game system들 
- db 서버 
  - db service

시스템 아키텍처도 여러 가지 도전 과제들이 있다. 특히, scene service를 구성하고 scene 간의 전환을 부드럽게 구성하며 인접한 scene 간에 동기화를 구현하는 것이다. seamless 서버를 분리된 scene으로 구현하는 문제는 어렵다. 

# scene 서비스 설계 

- scene_handler
  - scene 생성과 관리 
  - 진입과 진출 
    - 규칙 처리
  - scene의 최종 소유자 
- scene_service
  - 여러 개 
  - scene (handler) 들을 실행 
- scene 
  - game 
    - options 
      - json
    - 게임별 생성 처리 
      - 시스템과 엔티티들  
- 흐름을 그림으로 그려야 함. 



## 메세지와 상태 변화 

- 종이에 꼼꼼히 그리면 좋다. 그렇게 검증하고 반복해서 개선한다. 
- 스펙을 명확하게 한다. 안 그러면 애매해서 잘 안 된다. 작은 스펙으로 진행하고 확장한다. 
  - 기능이 많아지면 핵심을 놓칠 수 있다. 
  - 파티 매칭 처리는? 
    - 파티를 위한 scene을 찾거나 만들어 준비해 두고 한명씩 들여보낸다. 
    - 이게 다이다. 
  - 심리스 scene은? 
    - 전환 지역에 들어오면 scene을 변경한다. 
    - 그게 다이다. 
- 역할을 단순하게 한다. scene_master는 사용자 인증이나 관리나 채팅을 처리하지 않는다. 
  - 단지, scene만 관리한다. 그게 다이다. 
  - 누가 물어보면 알려줄 수는 있다. 



# 파티 처리



















