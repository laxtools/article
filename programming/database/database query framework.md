# database query framework

DB를 처리하는 구조는 반복적이다.  

- 요청과 응답 메세지 
- 요청 코드 
  - 파라미터 바인딩 
  - 실행과 에러 처리 
- 응답 코드 
  - 결과 초회 
  - 메세지 등록 
  - 응답 전송 



stored procedure(SP)를 포함한 쿼리 문의 생성까지 자동화하는 건 프로그래머의 선택을 너무 많이 제약한다. 따라서, 이 부분은 별도로 놔둔다.  SP나 쿼리를 파싱해서 전체 코드를 생성하는 건 유지보수가 어렵고 안정적인 언어로 만들기가 쉽지 않다. 따라서, 이 부분도 제외한다. 

목표는 C++로 처리되는 부분의 자동화이이다.  프로그래머에게 자유를 줄 수 있는 부분이 있다면 그렇게 해야 한다.  자동화는 사람에게 시간을 더 주기위해 필요하다. 



# 방향 

C++에서 SqlServer Native Client 인터페이스를 사용하여 편하고 안전하게 구현한 하나의 모델이 있다.  이를 C++에 맞게 변경하고 이에 맞추어 코드를 생성한다. 

코드 생성은 메세지 IDL과 유사하게 C++ 문법에 가까운 구조에서 각종 코드를 생성하도록 한다. 

코드 생성과 처리 프레임워크를 오가면서 개선하여 완전해지도록 한다. 테스트를 자동화 하는 것도 중요하다. 테스트만 별도로 광범위하게 실행할 수 있도록 한다. 



# 구현 



## 연습 

연습용 DB를 하나 만들고, 생성할 수 있도록 스크립트를 준비한다. 여기에서 C++과 Stored Procedure로 다양한 연습을 한다. 

- IMDB 데이터베이스 
  - 비디오 가계 DB 
  - SP와 쿼리 연습 
  - 프로그램 작성해서 스키마, SP 생성, DB 업로드 

https://data.world/craigkelly/steam-game-data

kaggle, where data gathers. 



- object relational model에 대한 정리 
  - 모델 설계 
  - 정규화 (게임에 적합한 정규화)
  - 쿼리 언어 
  - 쿼리 API



- sqlserver mgmt studio 연습 
  - SP 개발 
    - 작성 / 실행 / 디버깅 
  - 테이블 관리 
    - 게임 스키마 리뷰





### SqlServer Mgmt Studio 연습 

- SP 개발 
- 테이블 관리 
  - 스키마 리뷰 



아이템 관련된 테이블들을 잘 설계해야 한다.  

- 정규화가 필요하다. 
  - 기능별로 나누는 게 좋다. 
  - DB 조작에 대한 부하가 크가
  - 인벤토리 테이블은 분리하는 게 낫다? 
    - 그렇다. 
    - 실제 해보면 나을 수 있다. 
- DB 연산 
  - insert / delete / update로 처리하더라도 update는 세분화 해야 한다. 
    - 대부분 일부만 처리한다. 
    - 전체 처리는 네트워크, DBMS 모두에 부담을 크게 준다. 



SQL Server 공부를 별도로 진행한다. 



T-SQL (Transact SQL)에 익숙해질 필요가 있다.  개발하다 보면 자연스럽게 그렇게 될 것이다. 먼저, 캐릭터, 아이템, 스킬, 메일, 길드의 Object Relational 구조에 대해 정리한다. 



### Object Relational Model 













## 프레임워크 

ODBC를 사용한다.  



## ODBC 스펙 

https://github.com/Microsoft/ODBC-Specification/blob/master/ODBC%204.0.md

마이크로소프트의 스펙 정의. ODBC 4.0. 

ODBC는 API 정의라 실제 동작을 확정하지 않는다. 실제 동작은 드라이버에서 발생한다.  따라서, DB 마다 동작이 다르다. API와 함께 DB별 프로토콜을 알아야 정확한 동작을 파악할 수 있다. 

기본 흐름인 Prepare / Bind / Execute / Fetch 흐름을 API와 TDS 관점, 각 row의 처리, 각 column의 타잎 처리에 대해 상세하게 파악해야 한다. 











