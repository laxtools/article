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



# 6장. 필수적인 Transact-SQL 문 



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



































