# TDS protocol 

SQL Server의 프로토콜이다. ODBC를 사용해도 TDS를 쓴다. 그래서, 특성을 정리해 둔다. 



# MS-TDS 스펙 

https://winprotocoldoc.blob.core.windows.net/productionwindowsarchives/MS-TDS/[MS-TDS].pdf

- 300 페이지 
- 2008년부터 2018년까지 내용 
- 챕터들 
  - Introduction 
  - Messages
  - Protocol Details
  - Protocol Examples 



Introduction, Protocol Details 두 가지를 중심으로 보면서 필요할 때 Messages 를 참조한다. 



# Introduction 

TDS (Tabular Data Stream)은 요청 / 응답 프로토콜로 DB 서버와 사용 작용하며 다음 기능을 제공한다. 

- 인증과 암호화 협상 
- SQL 요청 스펙 
- SP 호출, 사용자 함수 호출 (RPC) 
- 데이터 전달 (The return of data) 
- 트랜잭션 관리자 요청 



## 용어 

- enclave 
  - A protected region of memory that is used only on the server side. SQL 서버의 주소 공간에 있으며 신뢰할 수 있는 실행 환경으로 동작한다. 하나의 enclave에서 실행되는 코드만 해당 enclave의 데이터를 접근할 수 있다. 
- SSPI (Security Support Provider Interface) 
  - 윈도우 API로 인증된 연결을 맺고 안전한 데이터 전송을 보장한다. 
- SMP (Session Multiplex Protocol) 
  - 하나의 Transport 연결을 여러 클라이언트에서 공유하는 프로토콜. 



## Overview

Example: 

- Client: SQL statement 
- Server; COLMETADATAdata stream 
- ROWdata stream 
- ... 
- ROWdata stream 
- DONEdata stream 

응답 데이터는 stream으로 나눠서 전달된다. 이를 data stream이라 한다. 



## Versioning and Capability Negotiation 

- Supported TDS transports
- protocol Versions 
- Security and Authentication Methods
  - SQL Server User Authentication (SQLAUTH)
  - SSPI가 지원하는 인증 방법들 
- Localization 
- Capability Negotiation 
  - 각 버전에서 기능이 고정되어 있음 



# Protocol Details 



## Common Details 

- Abstract Data Model 
- Timers (클라이언트)
- High layer triggered events 
- Message Processing Events and Seqeuencing Rules 
  - PRELOGIN 
  - LOGIN7 
  - SQL COMMAND
  - SQL COMMAND with BINARY DATA (Bulk Load Data)
  - ATTENTION
  - REMOTE PROCEDURE CALL 
  - Transaction Manager Request 

Attention이 각 명령의 취소를 위해 쓰인다.  응답은 TABLE RESPONSE이다. 대부분 요청 / 응답 흐름으로 정의되어 있다. 



- Timer Events 
- Other Local Events 



## Client Details 



![tds_client_state_diagram](D:\laxtools\article\programming\database\image\tds_client_state_diagram.png)

인증 부분이 상태를 많이 차지한다. Logged In 이후는 상위 레이어 요청과 서버 응답으로 이루어진다. Attention은 요청에 대한 취소다. 



### Timers 

다음 세 개의 타이머를 구현해야 한다. 

- Connection Timer 
- Client Request Timer 
- Cancel Timer 



TCP에 keep-alive를 사용하도록 하고 있다. 



### Higher Layer Triggered Events 

- Connection Open Request 
- Client Request 
- Cancel Request 



### Message Processing Events and Sequencing Rules

내용이 많지만 사실 인증을 빼면 많지 않다. TDS 구현을 위해 자세한 설명이 있다. 사용할 때 아주 중요한 부분은 없어 보인다. 



## Server Details 

 상태를 보여주는 그림 하나로 충분할 것 같다. 

![tds_server_state_diagram](D:\laxtools\article\programming\database\image\tds_server_state_diagram.png)







# Protocol Examples

XML로 필드를 정의해서 설명하는 방식은 좋아 보인다. 프로그램을 작성해 둔 것으로 보인다. 



몇 가지 잘 모르는 부분이 있다. 

- Bulk Load 
- RPC call 

SQL Query 요청과 다른 점은 무엇인가?  ODBC 사용할 때 문법과 실제 프로토콜이 어떻게 매칭되는가? 

























