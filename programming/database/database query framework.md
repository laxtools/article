# database query framework

DB를 처리하는 구조는 반복적이다.  

- 요청과 응답 메세지 
- 요청 코드 
  - 파라미터 바인딩 
  - 실행과 에러 처리 
- 응답 코드 
  - 결과 조회
  - 메세지 등록 
  - 응답 전송 
- 애플리케이션 트랜잭션 처리 
  - 공유 / 유일 (shared / exclusive)
  - 모델 
    - 앱 선처리 + 로그 
    - DB 선처리 후 앱 처리 



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

이를 지원하기 위해 정규화를 적절한 수준으로 할 필요가 있다. 캐릭터 테이블과 조인으로 빠르게 조회 가능한 것만 검증되면 아이템 관련 테이블 크기를 행과 열에서 모두 줄일 수 있도록 설계한다. 



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

쿼리 스트링과 데이터 문자열 필드에 대한 유니코드 처리를 확인한다. 

unicode in database and api.md 파일에 해당 내용을 간략하게 정리했다. 윈도우와 SQL 서버 조합은 UTF-16으로 언어 문자열 처리를 하면 된다. 



### Types 

익숙하지 않은 날짜, 시간, numeric 등의 처리에 대해 테스트로 정리한다.  메세지에서 지원하는 타잎으로 충분할 수도 있지만 날짜 필드의 경우 별도 처리가 필요하다. 메세지에도 추가한다. 

단위 테스트 형식으로 테이블 생성과 테스트를 진행하여 확인한다. 



## 언어 설계 



### 방향 

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



### 실행 

생성된 코드의 실행이 언어의 의미(Semantic)를 정의한다. 따라서, 실행 흐름을 정리해야 한다. 

- tx를 메세지로  db_service로 전달 
- tx_runner에 tx 전달 
  - tx의 키, 선택 알고리즘에 따라 tx_runner 선택 
- tx의 쿼리 처리
- tx의 결과를 전달 
- db_link에서 tx::id로 배포 
  - tx::id는 uuid를 사용 



### tx

요청과 응답으로 나눠서 처리해야 한다. 

tx_name : tx : zen_packet

- id : uuid 
- db : string
- key 
- execution policy 
  - key modulo 
  - uniform random
- application transaction 
  - group : string 
  - shared | exclusive
  - application first | db first 
  - target 
    - object type 
    - object id
- 디버깅 / 통계 
  - time of request
  - time of response 
  - execution time 
  - wait time 
  - call function : string 

- request 
  - struct 
  - query 바인딩 
- response
  - struct 
  - query 결과 바인딩 
  - fetch 결과 바인딩 



application transaction 처리를 위한 구조가 필요하다. 트랜잭션은 캐릭터 (Pc) 와 같은 오브젝트에 연결된다.  group 간에는 영향이 없고 그룹 내에서만 락 처리가 필요하다. 



아래는 로그 기반으로 앱에서 먼저 처리하는 shared 트랜잭션 요청의 한 예시이다. 

```c++
#define TXM(obj) (obj)->get_tx_manager()

auto rc = TXM(pc).lock_shared( "inven" );

if ( !rc )    
{
    // 에러 처리 
}

// tx 만들기 

TXM(pc).process_log( tx_use_item ); 
TXM(pc).request_db( tx_use_item, on_res_tx_use_item, timeout ); 
TXM(pc).process_app( tx_use_item ); 

TXM(pc).unlock_shared( "inven" );
```



앱 선처리 하는 트랜잭션들은 타임아웃으로도 에러 체크를 해야 한다. 타임아웃은 DB 에러 감지를 안전하게 할 정도로 길고, 타임아웃으로 에러 로그를 남기는데 너무 대기시간이 길지 않을 정도로 짧아야 한다. 60초 정도로 설정하면 적절해 보인다. 



DB 처리 후 처리하는 모델은 응답을 받아 완료해야 한다. 

```c++
auto rc = TXM(pc).lock_exclusive( "inven" ); 

// tx 만들기

if ( !rc )
{
	TXM(pc).push(tx); // 다음에 처리 
    return ...;
}

TXM(pc).request_db( tx, on_res_tx_loot_item ); 
```

아래는 DB 처리 후 처리 함수이다. 

```c++
void on_res_tx_loot_item( tx::ptr tr )
{
    tx_scoped_ix_unlock unlock( TXM(pc) ); // 응답이 오면 무조건 풀어야 한다.   
    
    auto tx_loot = static_cast<tx_loot>(tr);
    
    pc->process_app( tx_loot );   // 결과 적용을 진행한다. 	    
}
```



루팅 할 때 획득하는 아이템이 수십개라면 대기하게 된다. 따라서, 위의 exclusive 처리는 느릴 수 있다. 이를 개선하기 위해 아이템 획득 (루팅 시에만) 처리를 shared로 변경할 수 있다. 

실패했을 경우 처리가 어렵다.  shared, db first 처리가  유용해 보인다.  로그 부담은 줄이고 동시성도 올릴 수 있다. 루팅에 적용할 수 있는가?  그럴 것으로 보인다. 

exclusive, db first는 거래나 구매와 같이 중요한 작업에 사용할 수 있다. 슬롯 변경은 exclusive, app first를 적용할 수 있다. 빠르게 사용 가능하지만 동시에 다른 요청을 처리하지는 않는다. 

tx manager에 push하고 처리하는 걸 기본으로 해야 할 것으로 보인다. deque을 사용하고 뽑아서 처리 불가능하면 다시 덱에 넣어서 다음에 처리한다.  

```c++
void on_loot_item( message::ptr m )
{
    // [1] check conditions 
    
    // [2] make a tx 
    
    // [3] push into tx_manager 
    
    // [4] call tx_manager::execute()    
}

void pc_tx_manager::execute() 
{
    auto tx = peek_tx(); 
    
    if ( tx->lock(this) )
    {
        pop_tx();
        
        // .... 조건에 따라 처리 함수들 
	}	
}
```

tx_manager는 필요한 오브젝트 마다 상속해서 구현한다.  guild_tx_manager, pc_tx_manager가 대표적이고 아마도 이 두 개 밖에 없을 듯 하다. 



# Log and Recovery 

트랜잭션 로그와 리커버리 알고리즘과 실제 구현을 살펴서 게임에서 DB 처리 전 애플리케이션 처리를 먼저 할 수 있는 구조를 만든다. 



## 파일 처리 

트랜잭션에 사용하는 로그는 중요하다. 메모리 맵 파일이 가장 안정적인 쓰기를 보장한다. DBMS들이 트랜잭션 로그 작성에 사용한다. 

3개의 파일을 사용하고 하나가 일정 크기를 넘어가면 다음 파일로 순환한다.  



## 처리 흐름 



### 로그 

- tx 시작 
  - tx begin 
    - uuid 
    - time
  - tx content block begin
    - tx content 
  - tx content block end
- tx 결과 
  - tx end
    - tx uuid 
    - error | success  
    - time



log.tx 파일에 요청 순으로 한번에 쓴다.  빠른 처리를 위해 최근의 tx의 uuid와 파일 offset을 메모리에 보관한다.  일정 크기를 넘어가면 logs.tx.1으로 이름을 변경하고 logs.tx는 빈 파일에서 다시 시작한다. 에러가 발생하면 error.tx에 기록한다. 서버 종료 시 완료되지 않은 트랜잭션이 있다면 완료 되거나 타임아웃으로 모두 처리될 때까지 대기한다. 



### 에러 복구 

DB 처리가 실패한 원인에 따라 복구가 불가능할 수도 있다. 나중에 적용하는 것이 적절하지 않을 수도 있다. 이미 상태가 변경되었다면 적용이 안 된다. 

복구 가능한 에러는 다음과 같다. 

- DBMS 장애 
- db_service 장애 



앱 선처리하는 경우는 DB 장애 외에는 장애가 발생할 수 없는 트랜잭션에 대해 사용해야 한다.  그리고 이는 대부분의 트랜잭션에 대한 요구 조건이기도 하다. 

에러가 발생한 트랜잭션들은 errors.tx 파일에 순서대로 보관한다. 

db_service 장애가 발생할 경우 DB에서는 처리되고 응답이 없어 실패가 되는 경우가 있다. 이럴 경우를 포함하여 처리 가능하게 하려면 db_service의 트랜잭션 로그 정보를 비교해서 처리해야 한다. 그렇게 하더라도 DB 처리가 확실히 되었다는 보장은 없다. 



## 키 값 저장소 사용 

persistent key / value 데이터베이스들이 있다. RocksDB는 페북에서 지원하는 DB이다.  완전한 Key / Value Store로 파일에 저장되고 트랜잭션도 지원한다. 

트랜잭션 로그 시스템을 구현하는 대신에 Key / Value Store를 내장하고 처리하도록 하는 방법이 더 나은 옵션으로 보인다. 완료된 트랜잰션들은 일정 시간이 지나면 지울 수 있다.  좀 덩치가 큰 라이브러리이긴 하나 구현하지 않는 것이 가장 깔끔한 구현일 수 있다. 

https://db-engines.com/en/ranking/key-value+store

여기에 key value store들이 있는데 영속성을 제공하고 c++ 로 구현된 상용이나 GPL이 아닌 DB는 많지 않다. 버클리 DB는 좀 오래 되었다. RocksDB가 Apache 2.0 License에 persistency를 지원한다. 페북에서 만들고 있다는 점도 믿을만 하다. 



### RocksDB 사용예

```c++
DB* db;
Options options;
// Optimize RocksDB. This is the easiest way to get RocksDB to perform well
options.IncreaseParallelism();
options.OptimizeLevelStyleCompaction();
// create the DB if it's not already present
options.create_if_missing = true;

// open DB
Status s = DB::Open(options, kDBPath, &db);
assert(s.ok());

// Put key-value
s = db->Put(WriteOptions(), "key1", "value");
assert(s.ok());
std::string value;
// get value
s = db->Get(ReadOptions(), "key1", &value);
assert(s.ok());
assert(value == "value");

// atomically apply a set of updates
{
    WriteBatch batch;
    batch.Delete("key1");
    batch.Put("key2", value);
    s = db->Write(WriteOptions(), &batch);
}

s = db->Get(ReadOptions(), "key1", &value);
assert(s.IsNotFound());

db->Get(ReadOptions(), "key2", &value);
assert(value == "value");

```

사용 인터페이스는 단순하다. 바이너리 값으로 저장한다. tx들은 serialize 가능하다 (메세지). 



Iterator 인터페이스를 통해 snapshot을 순회할 수 있다. 

```c++
Iterator* iter = GetSnapShot(); 

while ( iter->Valid() )
{
    auto current = iter->Value(); 
    iter->Next();
}
```

대략 위와 같이 사용할 수 있다. 복구를 위해 전체 트랜잭션 로그를 순회할 때 사용할 수 있다. 



# db_service의 분산 처리 리뷰 

db 처리를 전담하는 서버를 두고 사용하는 방식은 네트워크 연결이나 프로세스 관련 장애가 추가된다. 문제는 DB 처리 요청을 한 프로세스와 DB 처리를 하는 프로세스의 장애가 분리될 수 있다는 점이다. 여기에 DB 장애까지 나누어지면 안정성 이슈가 추가된다. 

따라서, DB 처리가 필요한 서버들의 경우 해당 서버 내에 로컬 db_service를 두는 게 처리가 더 안정적이다.  이런 모델을 강제하기 보다는 선택할 수 있도록 한다. 

분리된 전용 db_service가 있는 경우 복구에 대해 생각해 본다. 



## 복구에 미치는 영향

DB 요청을 보내고 응답을 받았다면 확실히 처리된 것으로 안다. 문제는 DB 요청을 보내고 연결이 끊어지면 처리 여부를 알 수 없다는 문제가 있다.  확실히 알러면 DB에 기록을 남기는 방법 밖에 없다. 확실한 것이 좋다. 

모든 Stored Procedure가 tx::id를 아규먼트로 받도록 하고 이를 tx_log 테이블에 기록하도록 한다. 일정 시간 이전의 로그들은 주기적으로 지운다.  

복구 할 때 db_service의 로그를 참조하는 것이 아니라 이 로그 테이블의 내용을 참조하여 처리한다.  이 방법이 가장 확실하다. 



# 정리 

아이디어는 괜찮다. 구현할 내용이 많다. 아이디어 수준의 문서로 남기고 구현을 진행한 결과를 다른 문서로 정리한다. 사용 설명서가 되면 좋겠다. 





