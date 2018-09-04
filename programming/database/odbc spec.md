# ODBC Spec 

https://cdn.simba.com/wp-content/uploads/2016/03/ODBC_specification.pdf



익숙해서 스펙을 잘 안 보고 그냥 사용했다. 몇 가지 궁금한 점도 있고 해서 다시 한번 읽어 본다.  스펙문서가 천 페이지가 넘으므로 최대한 간략하게 본다. 



# The ODBC Solution 

- ODBC is a call-level interface
- ODBC defines a standard SQL grammar 
- ODBC provides a Driver Manager to manage simultaneous access to multiple DBMSs
- ODBC exposes a significant number of DBMS features



# ODBC Architecture 

- Application 
- Driver Manager 
- Driver 
- Data Source



# Developing Applications 



## ODBC Fundamentals 

- Handles
- Buffers 
- Data Types 
- Conformance Levels
- Environment, Connection, and Statement Attributes 
- Tables and Views



### Handles 

SQLAllocHandle 

- Environment Handles 
- Connection Handles 
- Statement Handles 
- Descriptor Handles 
- State Transitions



### Buffers

- Deferred Buffers
- Allocating and Freeing Buffers
- Using Data Buffers



#### Deferrred Buffers

나중에 사용되는 버퍼들 

- SQLBindParameter
- SQLBindCol 



#### Allocating and Freeing Buffers

앱에서 할당하고 해제한다. 따라서, 주의해야 한다. 



#### Using Data Buffers

- Data Buffer Type 
- Data Buffer Address
- Data Buffer Length 

```c++
SQL_DATE_STRUCT	Date;
SQLINTEGER		DateInd;
SQLBindCol(hstmt,	1,	SQL_C_TYPE_DATE,	&Date,	0,	&DateInd);
```



## Basic ODBC Application Steps

![odbc_app_steps](D:\laxtools\article\programming\database\image\odbc_app_steps.png)



# 확인해야 할 내용

- Driver Manager Connection Pooling 
  - 자체 풀링을 사용할 경우 이슈들 잘 처리해야 함 
  - 특히, 예외나 연결의 상태 관련 처리 





# 정리 

스펙 문서이고 함수가 많아 정리하기 어렵다. 사례 중심으로 정리한 문서를 보도록 한다. 이 문서는 참고 자료로 좋다. 









