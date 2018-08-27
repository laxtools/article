# learning sql server 

"뇌를 자극하는 SQL Server 2005" by 우재남으로 스터디를 진행한다. 전체를 다 연습하는 것을 목표로 한다.  



# SSMS 

Sql Server Management Studio는 이름을 잘못 지은 G예이다. 좀 더 짧게 사용 할 수 있는 이름이 더 낫다.  SSMS 17.8.1까지 나와 있고 사용성도 좋아 성공한 프로젝트임에는 틀림 없다.  SSMS에 익숙해지고 들어 있는 많은 기능을 이해한다. 데이터 기반의 게임 개발을 위한 툴 개발에도 많은 도움을 줄 수 있다. 쿼리 언어로 게임의 상태를 조회하고 변경할 수 있다면 얼마나 좋을 것인가? 



# 3장. 데이터베이스 구축의 전체과정 미리 실습하기 



- DB 생성 
- 테이블 생성 



## 테이블 생성 

- 타잎 
- 키 
- NULL 옵션 
- 기본 값



이름 규칙이 필요하다.  파스칼 케이스, 약자 대문자,  타잎 약어를 앞에 붙이기 (필드는 생략)을 사용한다. 약어는 되도록 사용하지 않는다. 

![db_table_spec](D:\laxtools\article\programming\database\db_table_spec.png)



인덱스는 Primary Key를 포함한다. 클러스터형과 비클러스터형의 차이는 무엇인가? 



### Clustered / Non-Clustered Index 

https://docs.microsoft.com/ko-kr/sql/relational-databases/indexes/clustered-and-nonclustered-indexes-described?view=sql-server-2017

SQL 서버의 인덱스는 B 트리에 기반한다. 

클러스터형 인덱스는 행의 저장 순서를 해당 키에 따른다.  물리적인 저장 순서가 해당 키에 의존한다.  따라서, 클러스터형 키는 테이블 당 하나만 있을 수 있다. 검색이 빠르고 데이터 로딩도 클러스터 테이블에 저장되지만 삭제 비용은 훨씬 높아 보인다. 실제 어떤 지는 공부를 더 해야 한다. 

클러스터 테이블이 아니라면 개별 행은 힙 페이지에 저장된다. 일반적이고 고전적인 방식의 테이블 페이지 관리를 따르는 것으로 보인다. 



### MySQL의 인덱스 처리 

http://12bme.tistory.com/138

DBMS 내부 처리를 이해하는데 도움이 된다. 자세히 정리해 두었는데 영어와 한글의 혼용을 어떻게 부드럽게 할까가 어려운 숙제라는 점을 잘 보여준다. 명확하게 정리했다. 



### B 트리 알고리즘  

B-tree는 Balanced n-ary tree이고 중간 노드의 병합과 분할이 일어날 수 있다.  대신 균형을 잡는 작업이 자주 발생하지는 않는다.  B+와 B* 트리에 대해서도 공부를 하면 좋을 듯.  



#### B+ 트리 

노드의 split / merge 로만 처리 가능한 트리이다.  순차적인 처리도 빠르게 가능하다. 

http://web.cs.ucdavis.edu/~green/courses/ecs165b-s10/Lecture6.pdf

- 그림 설명이 포함된 알고리즘 설명 (동적인 특성: 삽입 / 삭제) 



### 인덱스 업데이트와 성능 

- insert 와 index 업데이트 
- 검색을 위한 unique index와 수정을 통한 업데이트 

위의 두 가지 연산이 트랜잭션 성능에 어떤 영향을 미칠 수 있는가? 언제 어떻게 반영되는가? 

https://en.wikipedia.org/wiki/Index_locking

인덱스 잠금이란 주제이다. 



인덱스 잠금 프로토콜은 연관된 leaf 노드만 기본적으로 잠근다.  이는 DBMS의 특별한 트랜잭션으로 처리된다.  인덱스 잠금으로 인한 동시성 하락을 방지하기 위한 다양한 연구와 기법이 있다. 아직 많은 연구가 필요해 보인다. 

- B-Tree concurrency control 
- latch

http://vldb.org/conf/1985/P331.PDF

매우 오래된 고전적인 논문이다.  rebalancing이 일어나지 않도록 유지함으로써 락 범위를 최소화 한다? 맞는 지는 모르곘으나 방향은 그러하다. 

테이블의 키를 설계할 때, 게임에서는 오브젝트 DB처럼 처리하는 것이 좋을 듯 하다.  아이템과 연관된 테이블의 크기가 매우 커질 수 있다. 정규화가 필요한 이유이기도 하다.  연산을 효율적으로 처리할 수 있도록 하고, 개별 연산의 동작을 정확하게 정의하고 사용해야 한다. 인덱스 관련 영향도 검토해야 한다. 



### 테이블 스크립팅 

SSMS의 기능으로 테이블 명을 우클릭하면 스크립팅 기능이 나온다. 여기서 생성과 조회 등의 SQL 문을 생성해서 스크립트 창에 표시하는 기능이 있다.  UI 작업보다는 스크립트 작업을 빠르게 할 수 있어야 한다. 

```sql
USE [DbShop]
GO

/****** Object:  Table [dbo].[TblMember]    Script Date: 2018-08-21 오후 4:02:32 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TblMember](
	[MemberName] [nchar](5) NOT NULL,
	[JuminNo] [char](14) NOT NULL,
	[Address] [nvarchar](30) NOT NULL,
 CONSTRAINT [PK_TblMember_1] PRIMARY KEY CLUSTERED 
(
	[JuminNo] ASC
)
   WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
```

여기서는 세부 옵션들이 보인다.  DBA가 필요한 이유이기도 하다. 



## 백업 

백업과 복원은 DB 운영에서 가장 중요한 작업이다.  DB 감사도 통계 기반으로 진행할 필요가 있다. 앱 개발자가 DB를 충분히 고려해서 개발을 진행하지 않을 가능성이 높기 때문에 정기적인 감사를 통해 권한 설정, 동작 통계 기반의 튜닝 등의 작업이 필요하다. 

백업을 수행하는 방법으로 incremental 백업과 full 백업이 있다. Replication을 켜고 복제 DB에서 백업을 진행하는 방법도 있다. 



https://docs.microsoft.com/ko-kr/sql/relational-databases/backup-restore/back-up-and-restore-of-sql-server-databases?view=sql-server-2017

- 위에 SQL 서버의 백업, 차등 백업 (incremental backup), 트랜잭션 로그 백업에 대한 내용이 있다. 



http://gdbt.tistory.com/40

- 복제 구성 경험을 맛깔나게 표현 



작은 서비스라면 복제 DB를 구성하여 백업 겸용으로 활용하면 괜찮아 보인다. 



# 4장.  DBMS 개요와 데이터베이스 모델링 



## 모델링 

L 자형 테이블과 정규화. 



매우 짧게 설명하고 지나간다.  여러 가지 모델링 기법들이 있다.  별도로 내용을 찾는다. 중요하다. 



## 자료. 관계형 데이터 모델  

http://infolab.stanford.edu/~ullman/focs/ch08.pdf

- stanford 자료. 
- 간단한 기초이므로 보면서 정리 



### Intro 



Design of information structures using the relational model. 

- relations are a powerful and flexible way to represent information 
- selecting attributes or properties of the objects withoug redundancy (or minimizing redundancy
- knowing the key for a table 
- indexes 
  - index structures 
- relational algebra 
  - query 
- implementation of relational algebra
- optimization of relational algebra



### Relations 

Each row (tuple) represents a basic fact.

- The set of column names
- The rows containing the information



#### Database

A collection of relations is called a database. 

Navigating among relations. 



**Example.** 

{ Course, StudentId, Grade}

{StudentId, Name, Address, Phone}

{Couse, Prerequisite}

{Course, Day, Hour} 

{Course, Room}



#### Queries on a Database

- insert(t, R) 
- delete(X, R)
- lookup(X, R) 

X is spec. of some tuples. 

- A value or 
- The symbol * for column(s)

lookup( (*, "CS101"), Course-Prerequisites) 



함수로 본다면 insert, delete, lookup의 정의역과 치역은 무엇인가? 



### An Algebra of Relations 

- operand 
  - R(A, B, C) : Relation R with columns A, B, C
- union 
- intersection 
- difference 

scheme (스킴)은 relation의 컬럼에 대한 정의이다 (이름과 타잎). 

#### Selection Operator 

$\sigma_C(R)$ 

- C is a condition 
- R is a relation 

Extracts all tuples having condition C. 



**Example:** 

$\sigma_{Course="CS101"} (CSG)$

CS101 코스를 갖는 튜플들을 CSG relation에서 얻는다. 



#### Projection Operator 

$\pi_{B_1, B_2, ..., B_n}(R)$ 

- Relation R에서 
- 컬럼 $B_1, ..., B_n$만 가져옴 



**Example:** 

$\pi_{StudentId}(\sigma_{Course="CS101"}(CSG))$

CS101 코스에 있는 학생들 



#### Joining Relations 

$R \Join_{A_i, B_j} S$ 

- Join on $A_i$ of R and $B_j$ of S 
- $B_j$ omitted in the result relation 



This can be viewed as : 

$ \sigma_{A_i = B_j}(R \cdot S) $



#### Expression Trees

![db_expr_tree](D:\laxtools\article\programming\database\db_expr_tree.png)

SQL로 생각하지 않고 algebra로 생각하고, expression 트리를 그려보는 것도 괜찮은 방법이다. 



### SQL 

익숙한 부분이니 건너 뛴다. Algebra 관점에서 보는 연습도 중요하다. 



### Algebraic Laws for Relations 



####join

- commutative ignoring column order 
- not associative 



**Counter example of associativity:** 

R = {A, B}, S = {B, C}, T = {A, D}

$(R \Join S) \Join T$ has common column B on $R \Join S$ 

$R \Join (S \Join T)$ does not have common column on $S\Join T$ 



자주 사용하는 일반적인 경우는 결합법칙이 성립한다. 

![db_join_associativity](D:\laxtools\article\programming\database\db_join_associativity.png)



### Laws Involving Selection 

선택이 Expression Tree의 앞단으로 옮겨져도 동일하다. (proof?) 이를 사용하여 최적화 할 수 있다. 

**Example:** 

$\sigma_C(R \Join S) = \sigma_C(R) \Join S) $

or 

$\sigma_C(R \Join S) = R \Join \sigma_C(S)$



이를 selection pushing이라고 한다. "선택 밀기"

다른 중요한 규칙 중 하나는 선택 조건을 나누는 것이다. 

$\sigma_{C \, \mathbb{AND} \, D}(R) = \sigma_C(\sigma_D(R))$

이를 selection spliting이라고 한다. "선택 나누기"



선택은 교환 법칙이 성립한다. 

$ \sigma_C(\sigma_D(R)) = \sigma_D(\sigma_C(R))$

![db_ex_optimization](D:\laxtools\article\programming\database\db_ex_optimization.png)

선택을 Join 쪽으로 밀고 나눠서 최적화 할 수 있다.  좋은 연습 문제이다. 
$$
\sigma_C ( K \Join CR) 
$$
여기서 K는 조인의 아래 트리. $C = C_1 \, AND \, C_2 \, AND \, C_3$ 

selection split 적용하면 다음과 같이 된다. 
$$
\sigma_{C_1} ( \sigma_{C_2} ( \sigma_{C_3}(K \Join CR)))
$$
다음 $C_3$에 해당하는 컬럼을 갖는 Join 쪽으로 selection push를 한다. 이와 같이 계속 밀어서 먼저 추출하도록 한다. 



### Laws Involving Projection 

집합 연산들과 연관된 부분들은 trivial 하다. 

projection pushing이라고 불리는 다음이 중요하다. 

$\pi_L(R \Join S) = \pi_L(\pi_M(R) \Join \pi_N(S))$

위에서 $\pi_M$은 $\pi_L$ 중 R에 해당하는 컬럼들이다. $\pi_N$은 S에 해당하는 컬럼들이다. 

프로젝션을 미는 것도 데이터 입출력을 줄일 수 있으므로 최적화에 사용된다. 



### 연습문제 

Algebra 관련 연습문제는 별도로 풀어보는 것이 좋겠다. 한번 확고하게 해두고 증명할 수 있다면 해방이다. 자유다.   강력하다. 



### 정리 

지금 보기에는 기초적인 내용이 많다.  Key, Primary Key, Secondary Key가 필요한 이유와 구현에 대해 일반적인 관점에서 정리했다. 8.6까지의 내용이다. 

8.7 부터 relation (테이블)에 대한 연산을 정의한다. 이 부분은 DB의 쿼리 내용과 일치한다. 

algebra 관련 부분은 SQL 작성 시 최적화 경로를 예측하는데 도움이 된다. 실제로는 키 값 위주로만 검색하므로 쓸 일이 없는 게 게임 쪽에서는 더 낫다. 쿼리 최적화는 인덱스를 포함해야 한다. 





## ER Diagram 



### SQLDBM

https://sqldbm.com/en/Features/

- online 툴 

  ![db_sqldbm_tool](D:\laxtools\article\programming\database\db_sqldbm_tool.png)



T-SQL 생성 기능이 있고 예쁘게 볼 수 있어 괜찮다. SSMS나 Visual Studio에 내장된 기능이 있을 수도 있다. 



### Visual Studio 

https://www.jamesserra.com/archive/2013/12/entity-data-modeling-with-visual-studio/

https://stackoverflow.com/questions/36531682/generating-entity-relationship-diagram-in-visual-studio-2015



### 모델링 

https://cs.uwaterloo.ca/~tozsu/courses/CS338/lectures/10%20ER%20Model.pdf

- 프리젠테이션 스타일 
- 단순함



#### Outline 

- Conceptual Data Models 
- Entity Relationship (ER) Model 
- ER Diagrams



#### Steps in Database Design 

- Requirements collection and anlysis 
  - Data 
  - Functional 
- Conceptual or logical DB design 
  - DB schema 
- Physical DB design 
  - Internal storage sturctures, file organizations, indexes, access paths, physical design parameters 
- External or view design 



#### Sample 

- COMPANY 
  - Employees, departments, and projects



대신, RPG 게임의 아이템 관리를 예제로 한다. 



#### ER Model Overview 

- Entities and entity sets 
  - Objects
- Relationship and relationship sets
  - Connections between objects
- Attributes
  - Properties 



#### Entities and Attributes 

- $e_1$ = { Name, Address, Age, HomePhone }
- $c_1$ = { Name, Headquaters, President }



#### Entity Sets 

- Entity type or set
  - Collection of similar entities that have the same attributes 
  - Relation or table 
  - Separation of type and instances 
    - Instances are the entity set
- ER model defines **"entity sets"**
  - But entity sets described in terms of their attributes



#### Categories of Attributes 

- Simple (atomic) vs. composite 
- Single-valued vs. multivalued 
- Stored vs. derived 
- Key or unique 



#### Initial ER Diagram for Company 

![db_er_company](D:\laxtools\article\programming\database\db_er_company.png)

Types and its attributes are identified. 



#### Item 

- Inventory 
  - {CharacterId, Type, ItemId, Slot, StackCount, Bind, SealCount, ... }
  - 게임마다 달라질 수 있다. 
- Item 
  - 아이템의 동적인 속성 저장 
  - 게임마다 다름 
  - 분할 할 것인가? 
    - 몇 개의 시스템 속성으로 분할 하는 것이 좋다. 
    - TblItemBase
    - TblItemOption
    - TblItemMagic
    - 각 시스템별 기능으로 확장할 수 있다. 
- ItemOperationLog 
  - { ItemId, Operation, Date, Operator1, OperatorType1, Operator2, OperatorType2  }
  - 애플리케이션에서 로그 DB를 통해 처리하거나 로그로 처리할 수 있다. 
  - 데이터 모델로 중요하다. 
  - 내용은 많이 확장할 수 있다. 
  - 정형화되지 않을 수도 있다. 



64비트 uuid 생성 알고리즘인 Twitter SnowFlake에 대한 내용을 unique id in 64bits.md에 정리했다. 유사한 방식으로 게임에 적합하게 정리하면 된다. 



![db_er_item](D:\laxtools\article\programming\database\db_er_item.png)



그 동안 정규화를 사용하지 않은 게 어색할 정도로 깔끔하다. DB 쪽도 명명규칙부터 깔끔하게 하는 것이 좋다. 가독성을 높이려면 SQL 쪽 규약과 함께 정리해야 하나 파스칼 케이스가 좋아 보인다. 



#### Relationships 

- Relationship 
  - Interaction between entities
  - Indicator : 다른 엔티티 참조 
- Relationship type R among n entity type $E_1, E_2, ..., E_n$ 
- Relationship instance $r_i$ 
  - $r_i$ associates n individual entities $(e_1, e_2, ..., e_n)$
  - 각 엔티티 $e_j$ in $r_i$ is a member of entity set $E_j$ 
- Degree of a relationship type 
  - Number of participating entity types 



#### Relationships & Relationship Set 



![db_relationship_set](D:\laxtools\article\programming\database\db_relationship_set.png)



위는 Relationship Set Suppy = (Supplier, Supply, Part, Project) 를 보여준다. 

관계의 인스턴스는 $(s_1, r_1, p_1, j_1)$ 이 있다. 

Entity Set이 테이블에 해당하고 인스턴스는 하나의 행에 해당한다. 



#### Relationships with Repeated Entity Sets 

- 하나의 엔티티 집합에서 여러 개의 엔티티가 연관되는 관계가 있다. 
  - 예) 배우자 (두 사람), 게임 (두 팀) 
    - $Game = ( Team_1, Team_2)$
- Role name 
  - Signifies role that participating entity plays in relationship instance 
  - Required when entity type participates multiple times in a relationship 



#### Using Role Names

![db_relationship_roles](D:\laxtools\article\programming\database\db_relationship_roles.png)



Supervision 관계 = ( Employee, Supervision(of Employee))

인스턴스의 예로는 $(e_1, r_1), (e_3, r_3)$ 등이 있다. 



#### Relationship Constraints 

- Cardinality ratio 
  - 각 엔티티가 참여할 수 있는 Relationship Instance 내 횟수 
  - Types 1:1, 1:N, or M:N
- Participation constraint
  - Specifies whether existence of entity depends on its beging related to another entity 
  - Types : Total and partial 
  - 관계가 맺어져야 있을 수 있는 지 여부를 결정
  - 이런 방식은 잘 못 보고 아래를 주로 사용
- Alternative : Structural constraint 
  - (최소, 최대) 개수를 연관에 표시 





#### 최종 ER 다이어그램 

![db_final_er](D:\laxtools\article\programming\database\db_final_er.png)



관계는 삼각형이고 관계 인스턴스 항목의 집합이자 타입이다 (Extent을 통한 타잎화. 열거식 개념화). 



#### 정리 

ER은 개념 차원의 모델링이다. 기능을 만족하는 지가 중요하다. 실제 DB 설계에서는 물리적인 설계도 중요하다. 특히, 쿼리 (Stored Procedure와 트랜잭션 관계)의 효율적인 처리가 매우 중요하다. 특히, 게임에서는 더 그러하다. 



# 5장. SQL Server Management Studio 



## SSMS

- 서버 그룹 관리 

  - 보기 -> 등록된 서버 
  - 여기서 개체 탐색기 등 연결 가능 

개념과 기술은 거리가 매우 머니 연습을 많이 해야 재주가 생긴다. 



- 프로젝트 
  - DBMS
  - 쿼리 



- 쿼리 
  - 텍스트로 표시 
  - csv 내보내기 
  - 실행계획 표시



## SQLCMD

```sql
c:\> sqlcmd -S host\sqlexpress
1> use DbShop
2> select * from [TblMember]
3> go
데이터베이스 컨텍스트가 'DbShop'(으)로 변경되었습니다.
MemberName JuminNo        Address
---------- -------------- ------------------------------
KDLAP      330311-3134334 오산
Abcde      690302-1331217 서울

(2개 행 적용됨)
```

SSMS 대신 빠르게 뭔가를 해볼 때 좋다.  SSMS 설치가 없더라도 가능할 듯. 



**명령어들:** 

- ED 편집기 열기 
- !! 쉘 명령어
- QUIT 
- r 쿼리 파일 
- ServerList 
- Out <파일명> 
- Perftrace 성능 추적 
- Connect 새로운 인스턴스 연결 



## BCP 

벌크 복사. 파일 입출력. 



## 프로파일러 

성능 프로파일러. 

최적화는 따로 보도록 한다. 



# 6장. 필수로 알아야 하는 Transact-SQL 문 



## 데이터 준비 

T-SQL 연습을 하려면 데이터가 필요하다. 많아도 좋다. 



## 구문 

- Group by 
  - Having 
  - Rullup 
  - Cube 
- CTE (Common Table Expression)
  - SQL99 기능 
  - 임시 테이블이 있는 것처럼 동작 
  - 한 테이블에서 관계를 맺는 쿼리에 대해 재귀 허용을 위해 주로 사용할 듯 
    - 임시 테이블 사용보다는 효율적일 듯 함
- JOIN 
  - 명시적인 JOIN의 사용 
  - 최적화에 중요
    - 실수 없이 조인하도록 
  - Inner / outer join 구분 

- Union / Union All (모두 포함) 



### Join 

Inner Join이 일반적으로 DB 대수에 정의된 조인이다. outer join은 어느 쪽 테이블에 항목이 없더라도 포함하라는 뜻이다. LEFT / RIGHT 가 앞에 붙어서 항상 포함하도록 지정한다.



## SQL 프로그래밍 

Stored Procedure Programming이다.  2005 버전의 기능이긴 하나 게임에서 매우 복잡한 SP 사용은 좋지 않으므로 기본 기능을 충분히 잘 이해하는 걸 목표로 진행한다. 



### 마음 바꾸기 

DB와 SP를 데이터 관리 환경에서 데이터 프로그래밍 환경으로 넓혀서 생각한다.  SP를 DB 쿼리를 위한 언어에서 일반 프로그래밍 언어로 확장한다.  관점의 전환을 통한 전체적인 시야의 확장은 모든 일에 중요하다. 

```sql
SELECT 'Hello DB'
```

예시의 하나로 SELECT 문을 테이블과 연결된 데이터 조회 구문에서 데이터를 가져오는 일반 구문으로 생각한다. 

```sql 
DECLARE @Name VARCHAR(30)
SELECT @Name = 'Hello Variable' 
SELECT @Name

SET @Name = 'Hello2'
SELECT @Name
```

변수도 프로그래밍 언어의 변수처럼 생각한다.  

여기에 IF, WHILE 등의 구문과 expression이 있으면 원하는 작업들을 대부분 처리할 수 있다. 

```sql 
DECLARE @i1 int 
DECLARE @i2 int 

SET @i1 = 3
SET @i2 = 5 

PRINT 3 * 5
PRINT 3 / 5

DECLARE @f1 float
DECLARE @f2 float 

SET @f1 = 3.5
SET @f2 = 0.001

PRINT @f1 / @f2 

SET @i1 = 0 

WHILE @i1 < 5 
BEGIN 
  PRINT @i1 
  SET @i1 = @i1 + 1
END 


```

위 정도를 프로그래밍 할 수 있으면 대부분 프로그래밍 할 수 있다.  SQL이라는 강력한 데이터 관리 도구가 있으므로 더욱 그렇다.



### IF ELSE

```sql 
IF @Name = 'Hello' 
	BEGIN 
		PRINT '@Name is Hello'
	END
ELSE 
	BEGIN 
		PRINT '@Name is not Hello'
	END
```

PRINT 문은 "메세지" 창에 출력되고, 쿼리 내용은 결과에 출력된다. 

SQL bool 표현식은 일반 프로그래밍 언어, 논리적인 차원에서 가장 자연스러운 것들로 이루어진다. 타잎별 불 표현식을 이해하고 있으면 IF 문의 조건 등에 사용할 수 있다. 

중요한 타잎별 함수들을 알아야 한다. 이를 풍부하게 알면 작성이 쉬워진다. 



### CASE 

switch 문과 같다. 

```sql 
CASE 
	WHEN bool expr THEN expr
	WHEN bool expr THEN expr
	...
	ELSE expr
```

THEN 문이 값인 expression인가, 아니면 문장인 statement인가는 중요하다. CASE는 expression으로 SELECT 문에 사용할 수 있다. IF는 statement로 사용할 수 없다. 





### WHILE 

```sql 
WHILE bool expr 
BEGIN 
END
```

BREAK, CONSTINUE, RETURN과 함께 사용할 수 있다. 의미는 다른 언어와 같다. Statement이다. 



### GOTO 

그 goto.  



### TRY, CATCH 

그 try, catch

DB 처리에서 유용한 부분들이 있다. 에러 처리 스킴을 어떻게 할 지에 따라 사용 여부를 결정해야 한다.  DB 쿼리의 에러 처리는 중요한 주제이다.  별도로 정리해야 한다 (이 책은 11장에서 다룬다).



# 7장. 데이터베이스 생성과 관리 



## 데이터베이스 기본구조와 시스템 테이터베이스



### 데이터와 로그 파일 

8KByte 페이지와 8개의 페이지로 구성된 extent로 분할하여 데이터 파일을 관리한다. 

로그 파일은 LSN (로그 시퀀스 번호)와 트랜잭션 ID, 트랜잭션 정보를 기록한다. 

로그 파일은 DB 복구에 사용한다.  (복제 등 다른 많은 용도로 사용한다. )



### 트랜잭션 

Auto commit은 각 쿼리 문 단위로 트랜잭션화 하여 처리하는 방법으로 기본 동작 모드이다. BEGIN TRANSACTION, COMMIT / ROLLBACK 단위로 명시적으로 묶어 주어야 범위 생성이 가능하다. 

실험을 통해 확인하는 과정이 있다. 좋은 아이디어이자 무엇인가를 이해하는 좋은 방법이다. 이렇게 개념이 아닌 현실 속에서 파악하는 방법, 이해가 아닌 연습을 통한 훈련이 반드시 필요하다. 

- 쿼리 한 줄씩 실행 
- 테이블 상태 조회 
- 크래시 발생 시키기 (강제 종료) 
- 복구 확인 



### 시스템 데이터베이스 

- master
- model 
- msdb
  - 백업 / 복제 등 예약 작업 
- tempdb 
  - 시스템, 사용자 임시 테이블 
- 복제 
  - publication 
  - distribution 
  - subscription 



## 데이터베이스 생성 및 관리 



### SSMS 이용 

- DB 이름 
- 논리적 이름 
- 파일 유형 
- 파일 그룹 
- 처음 크기 
- 증분 크기 
- 경로 
- 파일이름 



### T-SQL로 생성 

ODBC에서 쿼리로 만들 수 있는 지 나중에 확인한다.  가능하다면 단위 테스트 구성에 좋다. 



### 파일 그룹

IO 성능 향상을 위해 물리적인 파일들을 분산. 



### 파일 줄이기 

- DBCC SHRINKDATABASE
- DBCC SHRINKFILE



### 데이터베이스 수정 

- ALTER DATABASE

예전에 오라클 명령어로 봤던 기억이.... 



### 데이터 파일 늘리기 

AKTER DATABASE [db] MODIFY FILE ( ... )



### 데이터베이스 이름 바꾸기 

- ALTER DATABASE [db] SET SINGLE_USER
- ALTER DATABASE [db] MODIFY NAME = [name]
- ALTER DATABASE [db] SET MULTI_USER

위는 논리적인 이름 변경이다. 

sp_helpdb와 같은 많은 sp 들이 있다. 이들을 잘 알면 도움이 많이 된다. 프로그래머에게는 약간 과도한 지식인 듯 하다. 



## 데이터베이스 옵션

자동 축소, 멀티 유저 / 싱글 유저 등의 기본 옵션들이다. 



# 8장. 테이블과 뷰

13장 트리거까지 테이블, 인덱스, 트랜잭션, 커서 등 쿼리 처리 관련한 중요 개념들과 사용법에 대해 설명한다. 익숙한 듯 익숙하지 않은 것들을 돌아보면서 확실하게 정리한다. 



## 테이블 



### 테이블 만들기 

T-SQL이 매우 편하다. 

`EXEC sp_help TblMember` 

관리 sp 중 하나인 sp_help는 다양한 오브젝트를 대상으로 실행된다. 테이블 속성을 한번에 볼 때 좋다. 



### 제약 조건 

```sql
ALTER TABLE [table] 
ADD CONSTRAINT [name] PRIMARY KEY( column1, ... )
```



FOREIGN KEY, UNIQUE, CHECK 



### DEFAULT 정의 

```sql
ALTER TABLE [table] 
ADD CONTRAINT [name] DEFAULT [value] FOR [column]
```

위와 같이 DEFAULT도 제약 조건 중 하나로 지정할 수 있다. 



### 임시 테이블 

\#을 붙이면 로컬 임시 테이블, \##이면 전역 임시 테이블이다.  게임용 DB에서는 안 쓰는 게 좋다.  



### 테이블 삭제 

DROP TABLE [name] 

외래키의 경우 참조가 있을 경우 지울 수 없다. 



### 테이블 수정 

컬럼 이름등 다양하게 ALTER TABLE로 변경 가능하다. 



### 데이터베이스 개체의 이름과 외부 서버에 있는 개체로의 접근 



#### 데이터베이스 개체 

서버이름.데이터베이스이름.스키마이름.개체이름 

```sql 
SELECT * FROM BRAIN.tableDB.dbo.userTbl
```

기본 스키마 이름이 dbo이다.  오브젝트 생성시 스키마 이름을 주면 해당 스키마에 오브젝트가 생성된다. 



#### 외부 서버에 있는 개체로의 접근 

```sql 
EXEC sp_addlinkedserver 
	@server = 'SECOND',  -- 사용할 이름 
    @srvproduct = 'SQLServer', 
    @provider='SQLNCLI', 
    @datasrc='BRAIN\SECOND'  --- 접속할 인스턴스 
```

위와 같이 서버 연결을 하나 만들고 SQL로 접근 가능하다. 

```SQL 
SELECT * FROM SECOND.tableDB2.dbo.userTbl2
```



## 뷰 

게임 개발 시 필요할까? 꼭 필요한 부분은 없다. 



## 분할 테이블과 분할 뷰



### 분할 테이블

- 파티션 함수를 정의 
- 파티션 구성표를 정의 
- 테이블 정의 시에 파티션 구성표를 적용
- 테이터 입력 



먼저 DB를 만들 때, 파일 그룹을 만들어 둔다. 꼭 필요한 지는 모르겠다.  하나의 파일에 넣더라도 파티션 자체로 이득이 있을 듯 하다. 

```SQL
CREATE PARTITION FUNCTION [functionName] (args) 
AS RANGE LEFT FOR VALUES ( 1975, 1981)
```

아래에 파티션 함수를 RANGE로 만드는 방법에 대한 설명이 있다. 모든 데이터를 다 사용하지 않아도 된다. 

https://docs.microsoft.com/ko-kr/sql/t-sql/statements/create-partition-function-transact-sql?view=sql-server-2017

Computed Column을 사용할 수 있다면 거의 모든 수식을 사용할 수 있다. 확인이 필요하다. 

https://docs.microsoft.com/ko-kr/sql/relational-databases/tables/specify-computed-columns-in-a-table?view=sql-server-2017



#### 확인. Partition function on Computed Column 

```SQL 
CREATE TABLE dbo.Products   
(  
    ProductID int IDENTITY (1,1) NOT NULL  
  , QtyAvailable smallint  
  , UnitPrice money  
  , PartitionID AS ProductID % 5
);  
```

https://www.sqlshack.com/database-table-partitioning-sql-server/

Sql Server 2016 버전부터 모든 버전에서 지원한다.  성능 관련 개선 기능은 엔터프라이즈 버전에서만 사용 가능하다는 얘기가 있는데 확인해야 한다. 

- https://social.msdn.microsoft.com/Forums/sqlserver/en-US/07984e8c-aa46-45e4-ab34-c5fbe1e2a9f9/table-partitioning-in-sql-2016-standard-edition?forum=sqldatabaseengine
- Partitioned Table Parallelism not supported in Standard Edition 
  - 하지만, 여전히 성능 개선이 있다. 
  - 인덱스와 파일 분리로도 상당할 수 있다. 



# 9장. 인덱스 

트랜잭션 이해와 함께 가장 중요한 장이다.  커서는 사용하지 않는다. 트리거는 특수한 경우 사용을 고려해 볼 수 있다.  이제 인덱스, 트랜잭션, 스토어드 프러시져, 백업과 복구, 레플리케이션/미러링 남았다. 



## 인덱스 개요와 활용 

### 인덱스의 종류 

클러스터형과 비클러스터형이 있다. 클러스터 형은 사전과 같이 인덱스로 데이터가 정렬된 인덱스이다.  따라서, 클러스터형 인덱스는 테이블 당 하나만 있다. 물리적인 정렬도 같이 일어나므로 성능 영향이 있을 수 있다. 게임은 오브젝트 키 단위로 접근이 주로 발생하고 일정 범위를 검색하는 일이 적다. 따라서, 클러스터 인덱스의 데이터 정렬 기능이 필요하지 않을 수 있다. 

https://www.mssqltips.com/sqlservertip/3041/when-sql-server-nonclustered-indexes-are-faster-than-clustered-indexes/

- key 값의 range scan은 클러스터 인덱스가 빠르다. 
- key 값 조회나 count(*) 같은 조회는 nonclustered가 더 빠르다. 

게임은 nonclustered 를 기본으로 하는 것이 괜찮아 보이나 더 살핀 후 확정해야 한다. 



### 인덱스의 내부 작동 

B 트리를 기준으로 설명한다. 리프와 중간 노드의 분할이 일어난다. 더 자세한 내용은 좀 더 전문적인 문서를 참조해야 한다. 

http://pages.di.unipi.it/ghelli/bd2/DBMS-Internals.pdf 의 5장. Dynamic Tree-Structure Organizations에서 상세하게 다룬다. 

클러스터형은 데이터 페이지를 정렬하여 리프 노드로 바로 사용한다. 비클러스터형은 페이지와 데이터를 가리키는 포인터를 사용한다.  데이터 위치 포인터는 RID (Row ID)라고 한다. 

비클러스터와 클러스터 인덱스가 함께 있을 경우 비클러스터 인덱스는 클러스터 인덱스에 대한 참조를 갖고 검색하게 된다. 이는 클러스터 인덱스 변경 시 데이터 페이지 번호 변경으로 RID가 바뀌게 되어 비클러스터 인덱스의 전체 재구성이 일어나기 때문이다. 



### 인덱스 생성, 변경, 삭제 

CREATE, ALTER, DROP으로 처리. 옵션들이 있으나 게임 개발에서 실질적으로 중요하지는 않아 보인다.  긴급하게 대처해야 할 경우 필요할 수도 있다. 

- 생성 
  - ONLINE : 인덱스 생성 중에도 테이블 접근 허용 
  - SORT_IN_TEMPDB : 임시 DB에서 인덱스 생성을 위한 정렬 수행 
- 변경 
  - REORGANIZE : 인덱스 재구성만 한다. 



`sp_helpindex` 로 인덱스 내용을 볼 수 있다. 



범위 검색이 넓은 범위에 걸쳐 일어나면 비클러스터형 인덱스의 경우 사용하지 않을 수 있다. 범위 검색은 클러스터 인덱스가  매우 빠르다. 

포괄열을 갖는 인덱스는 유용한 부분이 있겠으나 제약이 많아 실제 사용 가능한 지 모르곘다. 특수한 경우의 최적화로 사용 가능해 보인다. 



### 테이터베이스 엔진 튜닝 관리자 

자동화된 튜닝 기능은 의존하지 않는 게 좋다. 항상 확인하고 검증해서 사용해야 한다.  어떤 자동화가 있는 지 알면 튜닝에 참고하는 용도로 좋을 듯 하다. 



## 분할 인덱스와 인덱싱된 뷰



### 분할 인덱스 

분할 테이블에 인덱스를 생성하면 자동으로 분할 인덱스가 된다. 

```sql 
SELECT * FROM userTbl 
WHERE $PARTITION.birthYearRangePF(birthYear) = 1; 
```

위와 같이 파티션 함수를 통해 조회할 수 있다. 분할 테이블 지원 기능 중 하나이다. 

분할 테이블의 경우 범위 스캔이나 여러 열 조회시 인덱스는 분할 인덱스이고 분할 파티션에 파일들이 있으므로 더 느릴 수 있다. 따라서, 키 단위로 단일 파티션에서 조회가 주로 일어날 경우에 유용하다. 



### 인덱싱된 뷰

뷰에 인덱스를 생성할 수 있다. 인덱스를 갖는 뷰를 인덱싱된 뷰라고 부른다. 





# 10장. 트랜잭션과 잠금 



## 트랜잭션 



### 트랜잭션의 개념

논리적 작업 단위. 

- Atomicity  (원자성)
- Consistency (일관성)
- Isolation  (격리성)
- Durability (영속성)

그 ACID. 



### 트랜잭션의 문법과 종류

BEGIN TRAN[SACTION]

... 

COMMIT | ROLLBACK TRAN[SACTION] 



종류 

- Autocommit Transaction 
  - 쿼리마다 자동으로 트랜잭션화
- Explicit Transaction 
  - BEGIN TRAN으로 명시적으로 시작 
- Implicit Transaction  
  - 암시적 트랜잭션
  - 오라클 호환 모드 
  - 권장하지 않음 



### 트랜잭션 트래킹 

Trigger와 @@trancount를 사용한 트랜잭션 트래킹 에제가 있다. 

```sql
SELECT @@trancount
```

위 명령으로 현재 트랜잭션 개수를 볼 수 있다. 



`SAVE TRAN [name]` 으로 롤백 지점을 지정할 수 있다. `ROLLBACK TRAN [name]` 으로 해당 지점까지의 작업만 롤백 한다.  



## 잠금 

잠금은 데이터베이스의 일관성을 유지하기 위해 필요하다.  일관성은 데이터 모델에서 나온 논리적인 의미를 유지하기 위한 방법이다. 트랜잭션의 분리 실행으로 유지한다. 



### 트랜잭션 격리 수준

- READ UNCOMMITTED 
- READ COMMITTED 
- REPEATABLE READ 
- SNAPSHOT 
- SERIALIZABLE

격리 수준이 많은 이유는 데이터 모델과 의미에 따라 일관성을 요구하는 수준과 방식이 달라지기 때문이다. DBMS에서 모든 것을 결정하기 않고 사용자가 선택할 수 있도록 하는 수단이다. 

`SET TRNASACTION ISOLATION LEVEL`로 지정한다. 



여러 사용자가 동시에 하나의 데이터에 접근할 때 발생되는 문제는 다음과 같다. 

- Dirty Read (커밋되지 않은 데이터 읽기)
- Unrepeatable Read (반복되지 않은 읽기)
- Phantom Read (팬텀읽기, 가상 릭기)



#### 더티 리드 

더티 페이지는 메모리(데이터 캐시)에서는 변경되었지만 디스크에는 반영되지 않은 데이터(페이지)를 말한다. 더티 리드는 이런 더티 페이지를 읽는 것을 말한다. 

READ UNCOMMITTED는 이 더티 리드를 허용한다. 

```sql 
DBCC USEROPTIONS 

textsize	2147483647
language	한국어
dateformat	ymd
datefirst	7
lock_timeout	-1
quoted_identifier	SET
arithabort	SET
ansi_null_dflt_on	SET
ansi_warnings	SET
ansi_padding	SET
ansi_nulls	SET
concat_null_yields_null	SET
isolation level	read committed
```

위의 명령어로 현재 세션의 격리 수준을 확인할 수 있다. 

게임은 오브젝트 단위로 한번에 하나의 트랜잭션만 진행되는 경우가 상당히 많다. 이를 전제로 두고 READ UNCOMMITTED로 격리 수준을 둘 수 있다. 



#### Unrepatable Read 

반복되지 않은 읽기란 트랜잭션 내에서 한번 읽은 데이터가 트랜잭션이 끝나기 전에 변경되었다면, 다시 읽었ㅇ르 경우에 새로운 값이 읽어지는 것을 말한다. 

실습에서 다음을 설명한다. 

- READ COMMITTED는 더티 리드를 막아준다. 
- READ COMMITTED 만으로는 Unrepatable Read를 막을 수 없다. 

**SESSION 1:** 

```sql 
BEGIN TRAN 
 SELECT * FROM isoTbl; 
```

**SESSION 2:** 

```sql 
BEGIN TRAN 
  UPDATE isoTbl SET money = money - 500 WHERE name = 'AAA';
  UPDATE isoTbl SET money = money + 500 WHERE name = 'BBB';
COMMIT TRAN  
```

**SESSION 1:** 

```sql 
  SELECT * from isoTbl; 
COMMIT TRAN  
```

SELECT에 의해 공유 잠금이 걸린 경우에도 다른 사용자의 "읽기" 접근을 막아야 하는 경우가 있다. 이런 경우 REPEATABLE READ로 격리수준을 올린다.  REPEATABLE READ란 트랜잭션 진행 중 동일 데이터에 대한 반복 읽기는 트랜잭션 내의 변경이 없다면 동일한 값을 계속 읽는다는 뜻이다.  

트랜잭션의 대상이 되는 행들에 대해 읽기도 막는 효고가 있다. 정확한 구현은 DBMS 내부 알고리즘들을 더 살펴야 한다. 



#### Phantom Read 

REPEATBLE READ는 공유잠금을 설정한다.  가상 읽기는 새로운 데이터의 입력도 막는다.  이를 SERIALIZABLE 또는 SNAPSHOT 격리 수준에서 지원한다. 

잠금의 대상이 중요하다. 테이블인가?  



### 잠금이 걸리는 리소스와 잠금의 종류



#### 잠금이 걸리는 리소스 

- RID 
- KEY 
- PAGE 
- EXTENT 
- HOBT 
- TABLE 
- FILE
- APPLICATION
- METADATA
- ALLOCATION UNIT 
- DATABASE



#### 잠금 모드 

- Shared Lock 
- Exclusive Lock 
- Update Lock 
- Intent Lock 
  - 잠금 계층 구조를 만드는 데 사용된다. (의미?)
  - 의도 공유 (IS), 의도 배타 (IX), 의도 배타 공유 (ISX) 
- Schema Lock 
  - 스키마 수정 (Sch-M)과 스키마 안정성(Sch-S) 잠금이 있다. 
- 대량 업데이트 잠금 
- 키 범위 잠금 
  - SERIALIZABLE 격리 수준을 사용할 때, 쿼리가 읽는 행 범위를 보호한다. 



잠금 리소스와 잠금 모드의 동작은 DBMS 별로 세밀한 부분에서는 차이가 많을 것으로 보인다. 



### 잠금의 정보 확인과 힌트 

이 책의 가장 큰 장점은 실습을 통해 개념을 확인하는 과정에 있다. 

sys.dm_tran_locks에서 정보를 가져오면서 어떤 잠금들이 생기는 지를 설명한다.  격리 수준에 따라 락들이 다양하게 발생한다. 



### 블로킹과 교착상태 



#### 블로킹

락에 따라 다른 트랜잭션의 오브젝트 접근을 막는다. 타임아웃을 설정할 수 있다. 

`SELECT @@lock_timeout`으로 현재 설정을 조회한다. `SET LOCK_TIMEOUT 15000`으로 설정한다. 값은 밀리초이다. 

#### 데드락 

트랜잭션의 실행 순서에 관계가 있다. 잠금이 발생하는 모든 자원에서 생길 수 있다. 

SQL 서버 프로파일러에서 확인 가능하다. 



## 분산 트랜잭션 

생략. 



# 11장. 저장 프로시저와 사용자 정의 함수 



## 저장 프로시저

- CREATE / ALTER  / DROP
- EXECUTE [@retval = ] 이름 값1, 값2, ..., 값N [OUTPUT] 
  - @retval은 선언되어야 하고 리턴 값이 있을 경우만 동작 
  - ODBC는 ? = proc ( ?, ?, ... ) 로 하고 binding해서 사용
- 파라미터의 기본값을 SP 정의 시 지정 가능 
  - @birthday INT = 1900,  
- TRY / CATCH 사용성 확인 
  - 좋은 습관일 지, 아닐 지



### 시스템 저장 프러시저 

- sp_databases, sp_tables 
- sp_who, sp_helptext, sp_lock
- ......



## 저장 프로시저의 작동 



### WITH RECOMPILE 옵션과 저장 프러시져의 문제 

컴파일 시 최적화를 하므로 변경된 데이터에 대해 최적화가 이루어지지 않을 수 있다.  몇 가지 방법으로 해결한다. 

- DBCC FREEPROCCACHE 
  - SP 캐시 지우기 
  - 가장 간단해 보여 하나만 적음 





## 사용자 정의 함수 

SELECT 문 등에서 간단한 유틸리티로 사용할 수 있다. 지금까지 사용해 본 적은 없다. SQL 서버의 VM 성능이 충분할까?  되도록 부담을 줄이는 게 나을 수도 있다. 



# 12장 커서, 13장 트리거 

게임 서버에서 커서는 사용하지 않아야 한다.  운영 DB 등에는 사용할 수도 있다. 

트리거는 특수한 경우만 사용한다. 편하기는 하나 관리가 잘 안 되면 위험할 수 있다. 





# 17장. 데이터의 고가용성 (로그 전달, 데이터베이스 미러링, 복제)



## 고가용성을 위한 방법 및 개념



### 서버 클러스터링 개요 

클러스터링은 엔터프라이즈 이상에서 지원한다. 하드웨어 지원이 필요하고 구성이 복잡하다. 게임에서 사용하기에는 크다. 



### 로그 전달 개요 

보조 서버로 트랜잭션 로그를 전달하여 반영하고 수작업으로 서비스를 복구 가능하게 한다. 



### 데이터베이스 미러링 개요 

주서버, 미러 서버, 모니터 서버로 구성된다. 복제하다가 주서버에 문제가 있으면 전환한다. 



### 복제 개요 

주서버 (게시 서버), 전달 서버(배포서버), 구독 서버로 구성된다. 복제도 트랜잭션 로그 기반으로 동작한다.  서비스를 여러 곳에서 동일한 데이터에 대해 접근 가능하다. 활용도가 높아 보인다. 



## 로그 전달 



### 작동 방식 

- 주 서버의 로그 백업 파일 (*.TRN)이 주서버의 지정된 폴더에 일정한 주기 (기본 15분) 로 백업된다. 
- 일정한 주기마다 백업 로그 파일이 보조 서버의 지정된 폴더로 전달된다. 
- 보조 서버로 복사된 트랜잭션 로그가 복제 DB에 반영된다. 



### 설정 

꽤 많다. 유실 간격이 길기 때문에 실제 사용할 일은 없어 보인다.  



## 미러링 



### 개요 

- 원본 DB에서 작업한다. 
- 작업 내용은 복제 DB로 실시간 전달된다. 
- 원본 DB가 장애가 발생하면 자동 전환 기능은 프로그램에서 구현해야 한다. 
  - 다른 방법은 없는가? 장애 확인은 어떻게 하지? 



자동 전환 문제를 해결해야 하는데, 이 문제가 미러링 자체에서 해결되지 않은 건 클러스터링의 하위 기능으로 미러링이 사용되기 때문으로 보인다.  분산 시스템의 장애 탐지 및 전환 (failover) 알고리즘을 프로그램 상에서 구현해야 한다. 



### 실습 

여러 가지 세부 사항이 있다.  실제 사용할 때 보면 된다. 용도가 있는가?



## 복제 



### 복제의 방법 

- 스냅숏
- 트랜잭션 
- 병합 복제 
  - 구독 서버의 변경 사항이 게시 서버로 전달된다. 
  - 즉시 또는 지연 병합 



###복제의 구성 

- P2P 
- 중앙 게시자 모델
- 중앙 구독자 모델 

게임에서는 백업과 운영을 위해 중앙 게시자 모델을 사용할 수 있다.  





### 실습 

양이 가장 많다.  



## 서비스의 데이터 보호 방법에 관해 

DBMS의 전체 백업은 정기적인 유지 보수가 있어야 가능한데 모바일 게임들은 점점 더 점검 시간을 갖기 어려워지고 있다. 이런 환경에서 데이터를 보호를 위한 가장 적절한 방법이 복제로 보인다. 

서비스 DB와 가까운 곳에 (동일 IDC) 복제 DB를 구성하고 원본 DB에서 구독자로 백업을 받는다.  여기에 증분 백업 등을 설정하여 정기적인 백업을 함꼐 받도록 구성한다. 서비스 DB 만큼 좋은 장비일 필요는 없으나 IO 성능은 비슷한 정도라야 한다. 

다른 방법들도 있을 수 있으나 조건에 따라 달라질 것이다. 복제를 중요한 수단으로 활용해야 한다는 점은 명확하다. 

































































































































