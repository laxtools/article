# unicode of database and api

캐릭터 인코딩은 사람 참 불편하게 만든다. 플래폼마다 달라서 귀찮다. database는 정렬에 언어를 반영해야 하기 때문에 로케일 설정이 필요하다. 이를 정의하고 사용할 수 있어야 한다. 



# unicode 



## 개요 

유니코드는 코드 포인트를 문자에 매핑하기 위한 표준이다. 유니코드는 다음과 같은 함수이다. 

$ unicode : code point \rightarrow character $



## Datatbase

### nchar, nvarchar

nchar, nvarchar는 UTF-16으로 인코딩한다.  버전, OS, 클라이언트에 따라 다양한 세부 사항 차이가 있다. 소프트웨어의 어려운 점이 이런 부분이다. 

대략 클라에서 인코딩만 맞춰주면 UTF-16으로 저장되고 사용할 수 있다고 생각하면 된다. 클라로 UTF-16은 UTF-16으로 오는가? 

### Collation

collation이 대조 (다른 것을 같이 봐서 차이를 안다)의 뜻이다. 이는 문자열을 서로 비교 (대조) 한다는 의미이다.  대조하는 방식이 DB에서 collation이다. 

비유니코드일 경우 코드 페이지와 문자열을 지정해야 대조가 가능하다. 유니코드의 경우 유니코드 정렬을 하면 된다.  유니코드를 따로 이해해야 한다. 

확립된 방법은 유니코드를 언어 데이터에 사용하는 것이다. UTF-16이므로 API를 통해 클라이언트에서 처리하는 방법을 이해하면 된다. 



## API 

ODBC와 같은 C++ DB API에서 바인딩하고 사용하는 방법을 정리하면 된다.  자료 항목에 있는 "Understanding Unicode and ODBC Data Access" 문서에 필요한 내용이 다 있다. 

자료 / Understanding Unicode and ODBC Data Access 를 참고하는 것으로 대신한다. 

Windows / SQL Server 조합에서는 UTF-16을 문자열 기본 형식으로 생각하면 된다. 쿼리 문자열도 UTF-16으로 해야 문자열 리터열을 UTF-16으로 넘길 수 있으니 합리적으로 보인다. 



# 자료 



https://docs.microsoft.com/ko-kr/sql/relational-databases/collations/collation-and-unicode-support?view=sql-server-2017

- Unicode 기본 설명 



https://www.progress.com/tutorials/odbc/unicode

- Understanding Unicode and ODBC Data Access 



## Understanding Unicode and ODBC Data Access 



### Character Encoding - Background 

Unicode는 이름처럼 간단하지 않다. 역사와 플래폼이 섞여 있다. 



#### Background 

ASCII에서 시작했다. 7비트, 영어 지원에 문제가 없었다. 8비트, 유럽 언어 지원이 가능했다. 이제 아시아권 언어 지원이 불가능하여 DBCS (Double Byte Character Set)를 지원한다. DBCS는 한 바이트로 지원하거나 아니면 아시아 문자를 위해 2바이트를 사용했다. 그래서, OS 차원의 코드 페이지가 도입되었다. DBCS는 setlocal( LC_ALL,""); 로 지정하거나 LANG 환경 변수로 지정된다. 

더 나은 방법이 있다고 판단되어 Unicode Consorium이 시작 되었다. 처음에 두 바이트로 코드 페이지 없이 전체 문자를 표현할 수 있게 고안 되었다. 95,000 자 정도를 지원한다. 

하지만 기존 소프트웨어들이 모두 변경되어야 해서 이를 수용하기 위한 변경이 진행되었다. UTF-8, UCS-2, UTF-16이 그것들이다. 

UTF-8은 ASCII를 수용하는 가변 바이트 인코딩 형식이다. 전송을 위해 사용되고 대다수 Unix 플래폼의 기본 인코딩으로 사용된다.

UCS-2는 2바이트 고정 길이를 사용하고 유니코드 값을 바이트 열로 변환한다. Windows 95에서 시작하여 Windows NT까지 사용된다. 

UTF-16은 UCS-2를 포함하고 surrogate pairs 안에 있는 특수 문자를 지원한다. UTF-16은 Windows 2000, Windows XP, Windows Server 2003, Windows Vista의 인코딩 형식이다. 



#### Unicode Support in Databases

SQL 서버 2000은 UTF-16을 사용하고, Oracle은 UTF-8과 UTF-16을 지원한다. 일관된 Unicode 구현과 사용은 OS와 database 자체에 의존한다. 



#### Unicode Support in ODBC

ODBC 3.5 표준 이전에는 ANSI(ANSI 또는 DBCS)를 사용했다. API와 드라이버는 모두 ANSI 기반이었다.  ODBC 3.5 표준은 ODBC Driver Manager가 ANSI를 최대한 투명하게 지원할 것을 요구했다. 

ODBC 3.5와 이후 버전은 다음과 같은 구성을 지원한다. 

- ANSI application with an ANSI driver 
- ANSI application with a Unicode driver 
- Unicode application with a Unicode driver
- Unicode application with an ANSI driver 



### Unicode and Non-Unicode ODBC drivers

드라이버에서 유니코드 애플리케이션의 함수 호출을 처리하는 방식이 드라이버가 유니코드 드라이버인지를 결정한다. 

#### Function Calls

"W" 가 붙은 함수를 호출할 때 유니코드 드라이버는 ANSI 버전으로 변환하지 않고 처리한다. 

SQL_ATTR_APP_UNICODE_TYPE 속성을 조회하여 드라이버 지원을 확인할 수 있다. 



#### Unicode Application with a Unicode Driver 



#### Data

Unicode 애플리케이션은 C 타잎인 SQL_C_WCHAR로 바인딩하고 해당 값을 받는다. ODBC 3.5 호환 드라이버는 SQL_C_CHAR와 SQL_C_WCHAR를 모두 지원해야 한다. 

ODBC가 DB와 통신할 때는 DB 타잎인 SQL_WCHAR나 SQL_CHAR 타잎을 사용해야 한다. ANSI 데이터와 ANSI 데이터베이스의 경우 SQL_C_CHAR와 SQL_CHAR를 사용한다. 유니코드 데이터와 유니코드 데이터베이스는 SQL_WCHAR를 사용한다. 



##### Default Unicode Mapping 

Windows는 UCS-2/UTF-16이고 다른 유닉스 계열은 UTF-8이다. 



##### Connection Attribute For Unicode 

SQL_C_WCHAR의 자동 변환을 원치 않으면 설정할 수 있다. 

```c++
rc = SQLSetConnectAttr (hdbc, SQL_ATTR_APP_WCHAR_TYPE, (void *)SQL_DD_CP_UTF16, SQL_IS_INTEGER);
```



### Summary 

SQLServer와 Windows 조합에서는 UTF-16을 SQL_C_WCHAR / SQL_WCHAR에 사용한다. Unix의 경우 UTF-8을 기본 포맷으로 하는 DB와 변환이 없으므로 잘 조화를 이룬다. 







