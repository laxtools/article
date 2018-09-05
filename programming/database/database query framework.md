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



## 쿼리 기능 

- transaction 지정 
- stored procedure / sql query
- binding of input / output parameters
- row fetch into result message
- support transaction processing in application 



### Binding / Fetch 

- Input / output binding from / to struct fields
- Fetch to struct fields 



struct를 기준으로 처리해야 유연하다.  (더 적은 의존이 된다) 





# 애플리케이션 트랜잭션 모델 

게임 서버는 상태를 갖고 있다. DB 처리는 암묵적인 애플리케이션과 DB 간 트랜잭션 모델을 갖고 처리한다. 이를 명확하게 하여 모델로 만들고 고려하여 구현해야 한다. 



## 처리의 예 (Example of Transactions)

몇 가지 전형적인 예를 들어본다. 

- 사용자 캐릭터(이하, 캐릭터)가 특정 지역에 진입할 때 데이터를 DB에서 얻어 온다. 
  - 캐릭터 정보 
  - 인벤토리 
  - 스킬 
  - 버프 상태 등
- 캐릭터가 아이템을 처리한다. 
  - 루팅
  - 거래 
  - 판매 
  - 사용 
  - 선물 주기 
  - 선물 받기 

캐릭터 로딩 Op = ( 캐릭터 정보 조회, 인벤토리 조회, 스킬 조회, 버프 조회, ..., Op_n )

위의 작업이 진행 중에 인벤토리가 수정되면 이후 캐릭터 정보와 게임 상태는 불일치가 발생한다. 따라서, 대부분의 게임 서버에서 캐릭터 단위의 DB 처리는 Serialize 한다. 

아이템을 루팅으로 획득할 경우 바로 게임에서 사용 가능하게 할 지, 아니면 DB에 정상적으로 저장되면 사용 가능하게 할 지 결정해야 한다. 심리적으로 드랍된 아이템은 이미 회득한 것이나 마찬가지다. 이럴 경우 낙관적으로 보고 사용 가능하게 할 수도 있으나 DB 저장이 안 되는 경우 문제가 심각할 수 있다. 이를 보완하려면 트랜잭션 로그와 같은 Persistent Log가 있어야 한다. 이를 로컬 트랜잭션 로그와 선처리 방식이라고 하자.  

RDBMS를 사용하는 대부분의 게임은 DB 처리 후 애플리케이션에 반영하는 구조를 갖는다. 이를 후처리 방식이라고 한다. 대부분의 경우 안전하지만 serialize와 맞물리면 느릴 수 있다.  대표적인 예가 물약, 화살과 같이 자주 사용하는 아이템들이 있다. 이럴 경우에도 선처리가 필요하다. 



## 애플리케이션 락과 Serialize

캐릭터, 인벤토리, 아이템 등 DB 처리에 연관되는 곳에 DbLock을 갖도록 한다. 락 종류는 다음과 같다. 

- IX (Exclusive)

- IS (Shared)

IS는 IS를 허용하고 IX를 허용하지 않는다. IX는 IS / IX를 허용하지 않는다. 이를 통해 Serialize 한다. 

IX는 로딩 시,  거래와 같이 DB 완료 후 처리하는 경우에 잡는다.  IS는 선처리가 가능하거나 여러 번 동시에 처리되어도 될 경우 잡는다. 



## 애플리케이션 선처리 

게임서버의 상태 변경을 DB 처리가 정상적으로 수행될 것이라는 가정하에 진행한다. 만약 DB 에러가 발생하면 해당 트랜잭션을 다시 실행하는 것으로 표시한다. 선처리 트랜잭션이 실패한 경우는 DB 자체에 장애가 발생한 경우이다. 

DB 복구 후 트랜잭션 로그를 통해 시뮬레이션 결과를 반영하는 과정을 밟는다. 이는 DB의 리커버리와 유사하거나 동일한 알고리즘과 구현 수준을 갖도록 한다. 



## 처리 예시 



### 물약,  화살 등 

자주 사용될 수 있고 단일 오브젝트의 변경을 처리하는 경우 선처리로 한다. 

- IS 락을 잡는다. 
- 트랜잭션 처리가 가능한 지 확인한다. (수량 등)
- 트랜잭션 로그에 시작과 데이터를 적는다. 
  - 비동기로 처리한다. 
- DB에 요청한다. 
- 애플리케이션 로직을 처리한다. 
- IS 락을 푼다. 
- DB 응답이 오면 트랜잭션 완료 표시를 한다. 
  - 실패하면 기록하지 않거나 실패로 기록한다. 



### 거래 / 아이템 루팅 / 조합 / 분해 등 

가끔 처리되고 DB 반영이 중요한 경우들에 해당한다. 선처리를 하려면 나중에 복구할 수 있어야 하는데 구현이 많아지면 어려우므로 빠르게 처리해야 하는 경우에만 사용한다. 

- IX 락을 잡는다. 
- 트랜잭션 처리가 가능한 지 확인한다. 
- DB에 요청한다. 
- DB 응답이 오면 애플리케이션 로직을 처리한다. 
- IX 락을 푼다. 



## 클래스 설계 

tx 으로 추상화 한다. tx는 어딘가 빠르게 찾을 수 있도록 보관하고 DB에 요청한다. 응답이 오면 처리한다. 

자동화된 처리를 하려면 위의 클래스도 함께 만들 수 있으면 좋겠다. 행동이 포함되어야 하므로 동작 코드를 분리해야 한다. 

```c++
struct tx_use_item : public tx
{
    lock = exclusive;
    process = log;
	u32 item_id; 
    u32 count; 
    
    /// create a log for recovery
    tx_log::ptr log(); 
    
    /// recover db transaction from log
    int recover(const tx_log* log); 
}
```

좀 더 고민을 많이 해야 하나 대략 위와 같은 내용을 DB 처리 코드 생성 시 만들어야 한다. 

process는 log와 db를 둔다. log는 log 후 애플리케이션 반영 및 db 처리 방식이고, db는 db 처리 후 애플리케이션 반영 방식이다. 

생성된 코드로 처리와 복구가 단위 테스트로 검증이 쉬워야 한다. 



## 아이템 처리 

다른 고려 사항도 많겠으나 가장 중요한 건 처리 단위로 Stored Procedure와 트랜잭션 세트를 만드는 것이다.   아이템 분해나 합성, 거래도 그렇게 처리해야 한다. 한꺼번에 데이터를 바인딩해서 넘기는 방법이 쉽도록 코드 생성이 되어야 한다. 

이를 지원하기 위해 정규화를 적절한 수준으로 할 필요가 있다. 캐릭터 테이블과 적절한 조인으로 빠르게 조회 가능하는 것만 검증되면 아이템 관련 테이블 크기를 행과 열에서 모두 줄일 수 있도록 설계한다. 





# 구현 

구현은 반복적으로 개선하는 과정이다. 



## PoC 

- nanodbc 
- Binding / Fetch 코드를 생성된 것처럼 만들고 진행 
- 언어를 추출
- 다시 언어의 개선과 생성 고려 
- 위의 반복 

여기도 디버깅, 예외 처리를 가장 중요하게 생각한다. 보고 싶으면 진행 과정을 볼 수 있게 한다. 

### ODBC Connection String 

별도 ODBC 구성을 통해 DSN을 얻지 않고 연결 문자열로 처리한다. DB 비번을 구성파일에서 암호화된 문자열로 얻는 건 별도 구성을 통해 결정한다.  

https://kb.globalscape.com/KnowledgebaseArticle10063.aspx

```
Provider=MSDASQL;DRIVER={MySQL ODBC 3.51 Driver};SERVER=10.10.10.1;DATABASE=Example;UID=myusername;PWD=mypassword;
```

SqlServer의 연결 문자열은 다음과 같다. 

```
Driver={ODBC Driver 13 for SQL Server};server=localhost;database=WideWorldImporters
```

```
Driver={SQL Server Native Client 11.0};Server=SqlHostName:Port;Database=SomeSqlDatabase;UID=YourUserName;PWD=YourPassword
```

Example: 

```
Driver={SQL Server Native Client 11.0};Server=localhost:1433;Database=DBShop;UID=Hello;PWD=DONTLOOKATME
```

### Unicode 

쿼리 스트링과 데이터 문자열 필드에 대한 유니코드 처리를 확인한다. 유니코드는 이번에 꼭 정리하고 간다. 

### Types 

익숙하지 않은 날짜, 시간, numeric 등의 처리에 대해 테스트로 정리한다.  메세지에서 지원하는 타잎으로 충분할 수도 있지만 날짜 필드의 경우 별도 처리가 필요하다. 메세지에도 추가한다. 

단위 테스트 형식으로 테이블 생성과 테스트를 진행하여 확인한다. 



## 언어 설계 

- 제약 
  - BeginTransaction 사용 없음 
  - Stored Procedure로만 처리 
  - ODBC (Generic)
    - No database specific features 
    - Use Stored Procedure!
- 게으름 
  - 최대한 편하고 쉽게 처리
  - Stored Procedure와 테이블 설계에 공을 들이고 처리는 쉽게 한다. 
- struct 기반 처리 
  - 메세지는 마지막 
- 직관적일 것 
- 단위 테스트 
  - 기능별 상세 테스트 
  - fail 테스트 포함
  - 외부 의존 최소화 
    - 별도 실행 가능하도록 함 

