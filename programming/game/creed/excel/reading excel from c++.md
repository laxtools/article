# Reading excel from c++ 

To manipulate game data in excel and export into final format (csv), we need to have c++ library that can access excel data including color information for schema definition. 



# excel 게임 데이터 스키마 

- 컬러 정보 
  - 헤더 
  - 타잎 
  - 주석 
  - 제약 사항 
    - 키 / 외부 키 / 유니크 키 
- C++ 코드 생성
  - csv / 바이너리 export 
  - csv / 바이너리 로딩 



xlnt 라이브러리로 PoC를 진행하고 최종 설계에 반영한다.  작업하는 원본에서 항상 최종 데이터를 출력할 수 있도록 한다.  



## 스펙 

- 기본 타잎
- csv 의미 유지 
  - 관계형 데이터 모델
- toc 
- typedefs 
  - enum 
  - range restricted values



질문: is this the right way to go?  how about database? excel은 data ide이다. 현재까지 그렇다. 앞으로도 그래야 할까? 



# 라이브러리 

http://libxl.com/

https://www.easyxls.com/

- not free

https://docs.microsoft.com/en-us/office/open-xml/open-xml-sdk

- microsoft support for excel XML 

https://github.com/tfussell/xlnt

- open source 
- MIT license

http://www.sqlforexcel.com/

- 다른 접근 
- excel에서 sqlserver 데이터 편집 

https://omnidb.org/en/

- database 데이터 관리 툴 
- 여기에 기반하여 툴을 제공할 수 있을 듯 

https://www.sqlalchemy.org/



Kivy GUI + Python + SQL Server as Data IDE































