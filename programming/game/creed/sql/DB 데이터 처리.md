# DB 데이터 처리 



## 개요 

김호성 TD님의 GEN 엔진에서  SQL 주석을 통해 분석하여 쿼리 처리와 메세지 코드 생성 기능을 보고 게임의 중요 데이터 처리 영역인 DB 처리를 자동화 하는 방법에 대해 고민하게 되었다. 

SQL문 자체에 전체 의미가 포함 되어 있으므로 파싱만으로 프로시저 호출과 결과 처리 코드를 생성할 수 있다. 파싱 이외에 다른 더 수월한 방법이 있다면 활용할 수 있겠으나 현재까지 살펴본 바로는 없어 보인다. 

완전한 방법이란 측면에서 SQL 문 파싱 방법이 정공법이고 한번 완성되면 모든 개발 영역 (C#을 포함)에서 사용 가능하다. 



## 목표 

- C++ 오브젝트 정의 

  - 테이블에서 정의 

- 쿼리를 통해 메세지 생성

  - 호출 인터페이스 분석 
  - 실행 후 결과 값 분석 
  - 코드 생성 






## 쿼리를 통한 메세지 생성 

### 아이디어 

CREATE PROCEDURE 부분 파싱. 코드 생성 코드 생성.  테이블 데이터 추가 후 쿼리 실행. 결과 값 로딩 후 코드 생성.  (가능???) 

아니면 전체 파싱 후 생성. 이 방법이 정확하다. 하지만, 어렵다.  어려워도 맞는 방향으로 가야 한다. 아니면 중간 쯤 애매한 상태가 된다. 

once and for all, better forever. 





# 자료 

https://github.com/xo/xo

- go 언어로 개발한 처리 스크립트 생성 도구 
- 스키마와 템플릿 엔진에 기반 
- 쿼리 코드 생성기 

DB 데이터 처리의 목표는 이보다 훨씬 크다. 그래도 참고할만 하다. 

실행이나 reflection 기반으로 프러시저 분석이 가능하면 많은 도움이 될 것 같다. 



https://github.com/hyrise/sql-parser

- c++ sql parser 



http://www.cybergarage.org/oss/cloud/%C2%B5sql-for-c/

-  another sql parser (ANTLR)



https://msdn.microsoft.com/ko-kr/library/microsoft.sqlserver.management.sqlparser.parser.parser.aspx

- 자체 파서를 제공한다. 
- 어느 정도 기능이 있는 지 확인 필요 



https://social.msdn.microsoft.com/Forums/sqlserver/en-US/0105834a-7d10-4686-8b30-1a1362572b3f/microsoft-sql-parser-support?forum=sqlgetstarted

- 위의 내용에 따르면 
- SQL 서버 Feature Pack 중 SqlDom.msi를 설치하면 
- TransactSql.ScriptDom을 사용할 수 있다. 
- ScriptDom은 완전한 파서를 제공한다. 
- https://gist.github.com/philippwiddra/2ee47ac4f8a0248c3a0e
  - 여기에 간단한 SELECT 문 파싱 예제가 있다. 
  - Visitor 기반인데 완전한 AST 접근이 가능해야 한다. 
  - https://liuzy163.wordpress.com/2016/03/07/use-scriptdom-to-parse-sql-script/
    - 여기에 더 상세한 정보가 있다. 



http://www.sqlparser.com/tsql-sql-parser.php

- 상용 툴 


































