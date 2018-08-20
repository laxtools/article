# Learning database internals

DB를 사용하긴 했으나 많지는 않았다. 특히, 코딩은 매우 적게 했다. 데이터가 중요한데 그간 등한시 했다. 옳지 않다. 가장 소중한 것이 데이터이다. 결국 기록이고 지식이고 전부이다.  관계형 DB가 ACID를 제공할 수 있어 가장 광범위하게 사용한다. 분산에 제약이 있고 잘못 쓰면 느리지만 강력하다. 내부를 잘 알아야 잘 쓸 수 있다. 현재까지 인터페이스는 SQL과 개별 DBMS의 프로그래밍 언어 (Stored Procedure)가 중요하다. 개별 도메인에 맞는 언어를 찾을 수 있을 듯 하다. Tableau 시스템과 쿼리 언어는 참고할만 하다. 



# 교과서. Relational DBMS Internals  

피사, 파리, 베네치아 대학에서 함께 만든 교재로 200페이지 정도로 짧다. 빠르게 정리하는데 도움이 될 것으로 보여 다 읽기로 결심하고 시작한다. 



## 1.2 A DBMS Architecture 

- Storage Engine 
  - Permanent Memory Manager
    - manages page allocation and deallocation on disk storage
  - Buffer Manager
    - manages the data transfer of data between permanent memory and the main memory
  - Storage Structures Manager
    - Index, hash, tree, ...
  - Access Methods Manager
    - create and destroy databases, files, indexes, and the data access methods for table scan and index scan.
  - Transaction and Recovery Manager 
  - Concurrency Manager
- Relational Engine
  - Data Definition Language Manager 
  - Query Manager 
    - transforming queries into equivalent, but more efficient form, thus finding a good strategy for its execution
  - Catalog Manager 
    - metadata, about the schemas of the existing databases (views, storage structures and indexes), and security and authorization ifnormation



## 1.3 The JRS System 

A reference implementation of relational DBMS in java by the author and students. 



## 9.1 Transactions 

- static integrity constraints 
- dynamic integrity contraints



#### Definition 9.1 Consistent State 

A consistent state of the database is a state in which all contraints are satisfied. 



### 9.1.1 Transactions from the programmer's point of view

transaction, which groups a set of instructions that read and write data. 



#### Definition 9.2 A transaction:  

 is a sequence of operations on the database and on temporary data, with the following properties:

- Atomicity 
  - Only committed transactions change the database
- Isolation 
  - When a transaction is executed concurrently with others, the final effect must be the same as if it was executed alone. 
- Durability 
  - The effects of committed transactions on the database survive system and media failures.

AID of ACID. C is consistency. 

The isolation property is called the serializability property: when a transaction is executed concurrently with others, the final effect must be the same as a serial execution of committed transactions. 

**Transaction and Recovery Manager** is responsible of supporting the properties of atomicity and durability.  The isolation property is guaranteed by the **Concurrency Manager**. 



### 9.1.2 Transactions from the DBMS's point of view

DBMS only "**sees**" the read and write operations on its data. A write operation updates a page in the buffer, but does not cause an immediate transfer of the page to the permanent memory. If for some kind of failure the content of the buffer is lost, the updates might not have been written to the database. To correct this situation, the DBMS will have to take special preventive measures. 

#### Definition 9.3 

A transaction for the DBMS is a sequence of read and write operations which start and end with the following transaction operations: 

- **beginTransaction**, signals the beginning of the transaction
- **commit**, signals the successful termination of the transaction, and requires the system to make its updates durable
-  **abort**, signals the abonormal termination of the transaction, and requires the system to undo its updates



![db_fig_transaction_state](D:\laxtools\article\programming\database\db_fig_transaction_state.png)

위에서 commit 이후에도 실패할 수 있다는 점에 주목해야 한다. DB를 구현할 때는 그런 상황이 있을 수 밖에 없다. 



## 9.2 Types of Failures

- transaction failure 
- system failure
- media failure 

#### Definition 9.5 Transaction Failure 

is an interruption of a transaction which does not damage the content of either the buffer or the permanent memory. 



- 프로그램에서 abort를 호출 하는 경우 
- DBMS에서 integrity constraint 위반을 발견하는 경우 
- concurrency manager가 deadlock을 발경하여 종료해야 하는 경우 



## 9.3 Database System Model 

![db_fig_dbms_model](D:\laxtools\article\programming\database\db_fig_dbms_model.png)

트랜잭션의 atomicity와 durability를 제공하기 위해 permanent 메모리는 세 가지 구성 요소를 갖는다. 

- database
- Log 
- DB Backup

로그파일들 페이지는 데이터베이스 페이지와 다른 알고리즘으로 관리되므로 다른 버퍼를 사용한다. 



Transaction and Recovery Manager는 다음과 같은 일을 한다. 

- the execution of a read, write, commit and abort operation 
- the management of the log 
- the execution of a restart command after a system failure, that guarantees that the database only contains the updates of the successfully terminated transactions



단순화하기 위해 다음을 가정한다. 

- the database is just a set of pages 
- each udpate operation affects a single page
- the operation of transferring a page from the buffer to the permanent memory is an atomic operation
- if different transactions are concurrently in execution, they read and write different pages. 



## 9.4 Data Protection 

Redundancy를 기본 스킴으로 한다. 

#### Definition 9.8 Recovery 

is the process that restores the database to the consistent state that existed before the failure. 



**Database Backup.**  

**Log**  During the normal use, the history of the operations performed on the database from the last backup is stored in the log. For each transaction $T_i$, the following information is written to the log: 

- When it starts, the record (begin, $T_i$)
- when it commits, the record (commit $T_i$)
- when it aborts, the record (abort, $T_i$)
- when it modifies the page $P_j$ the record $(W, T_i, P_j, BI, AI)$, where BI is the old value of the page (before image) and AI is the new version of the page (after image)

![db_fig_transaction_log](D:\laxtools\article\programming\database\db_fig_transaction_log.png)

각 로그는 LSN (Log Sequence Nubmer)로 구분된다. 



**Undo and Redo Algorithms**  Recovery algorithms differ in the time when the system transfers the pages updated by a transaction to the permanent memory. undo와 redo를 필요로 하는 알고리즘이 있다. 미리 쓰면 undo가 필요하고, 늦게 쓰면 redo가 필요하다. 이는 트랜잭션 로그를 통해 진행한다. undo / redo 중에 실패할 경우에도 트랜잭션 로그 재시작이 가능해야 한다. 이를 idempotency property라고 한다. 



**Checkpoint**  To reduce the work performed by a recovery procedure in the case of system failure, another information is written to the log, the so called **checkpoint (CKP) event**.

- **commit consistent checkpoint**
  - The activation of new transaction is suspended
  - The systems waits for the completion of all active transactions 
  - All pages present in the buffer which have been modified are written to the permanent memory and the relevant records are written to the log  (flush operation)
  - The CKP record is written to the log 
  - A pointer to the CKP record is stored in a special file, called restart file 
  - The system allows the activation of new transactions

완전히 정확한 상태를 남기기 위해 시스템이 멈추는 것 같다. 



- **bufffer consistent checkpoint - Version 1**
  - The activation of new transactions is suspended
  - The execution of database operation of the active trnasactions is suspended 
  - All pages present in the buffer which have been modified are written to the permanent memory and the relevant records are written to the log (flush operation) 
  - The CKP record, containing the list of the identifiers of the active transactions, is written to the log. 
  - A pointer to the CKP record is stored in a special file, called restart file
  - The system allows the activation of new transactions and continues the execution of the active transactions. 



여전히 버퍼를 다 써야 하기 때문에 느리다. ARIES 알고리즘이 이를 보완하는 한 예이다. 



## 9.5 Recovery Algorithms 





## 9.8 The ARIES Algorithm 

ARIES (Algorithm to Recovery and Isolation Exploitation Semantics) is a general recovery algorithm of the type Undo-Redo to reduce logging overhead, and minimize recovery time from transaction, system and media failures. 

### Write in the log only the description of the operation 



### Store a part of the log in the buffer



### A new type of checkpoint 

fuzzy checkpoint (트랜잭션을 허용하면서 비동기로 진행) 

- Write a beginCKP record, to signal the beginning of the checkpoint procudure 
- Build a endCKP record, by inserting in it the content of the transaction table and the dirty pages table
- When the endCKP record is written to the permanent memory, the LSN of the beginCKP record is stored in a file used in the restart procedure, called the master record. 



## 10.1 Introduction 

![db_fig_concurrency_violation](D:\laxtools\article\programming\database\db_fig_concurrency_violation.png)

흔히 볼 수 있는 serialization issue이다. 



#### Definition 10.1 Serial Execution 

An execution of a set of transactions $ T = \{ T_1, ..., T_n\} $ is serial if, for every pair of transactions $T_i$ and $T_j$, all the operations of $T_i$ are executed before any of the operations of $T_j$ or vice versa. 



#### Definition 10.2 Serializable Execution 

An execution of a set of transactions is serializable if it has the same effect on the database as some serial execution of the transaction that commit. 



Serializable Execution으로 만들어 주는 역할을 Concurrency Manager 또는 Scheculer 에서 수행한다. 



## 10.2 Histories 











# 연습문제 



## TDS 프로토콜 스펙의 이해와 정리 

http://www.rfc-editor.org/rfc/rfc4234.txt



## Tableau 연습 

trial 신청하고 해당 기간 동안 사용하면서 데이터 중심의 게임 제작 시스템을 구상한다.  게임 데이터 IDE가 될 수 있다. 



## MMORPG 데이터 스키마 설계 

https://github.com/jgoodman/MySQL-RPG-Schema

위와 같은 시도가 있다. 기획 데이터를 포함하는 스키마이다. DB에 함께 두는 방식도 괜찮을 수 있다.  DB를 중심으로 하는 데이터 흐름을 구성하는 것도 괜찮을 수 있다. 



### 자료 

https://people.eng.unimelb.edu.au/gwadley/pubs/wadley-database-mmorpg.pdf

https://eprints.qut.edu.au/10160/1/10160.pdf



## MMORPG 데이터 언어 

DB, 쿼리, 메세지, 엔티티의 속성을 포함하는 구조를 생각할 수 있다. DB와 섞어 전체 작업 흐름을 Tableau처럼 구성한다. 이를 목표로 한다. 시뮬레이션 게임을 이 위에 구성할 수 있다면 MMORPG 데이터 게임을 완결지을 수 있다. 나머지는 시간, 입력에 따른 변환과 표현이다. 

http://pc.gamespy.com/pc/world-of-warcraft/567731p1.html

- Quest designer의 몇 가지 측면에 대한 인터뷰



https://www.codesynthesis.com/products/odb/

- C++ precompiler로 persistency를 RDBMS 통해 제공 



## RDBMS as Object DB







## Object Cache 

(key, value) store. value has serialized object or attribute. Modelling can be different from RDBMS. Object based database development can boost efficiency of writing data management in c++. 



































