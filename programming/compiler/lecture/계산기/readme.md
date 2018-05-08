# 파일들 

 example02.ll 

  - lex 파일
  - 토큰들 정의 

 example02.yy 

  - bison (yacc) 파일 
  - 계산기 문법 정의 

# 프로그램 생성 

 flex --wincompat -o example_lexer.cpp examle02.ll  

 bison -d --verbose  -o example_parser.cpp example02.yy 

 -d 옵션을 사용하면 헤더 파일을 생성함. 

 flex 디버깅을 위해서는 -d 옵션 추가 

 주의: 가장 마지막에 각 .ll, .yy 파일이 와야 함

# 생성된 파일 포함 

 프로젝트에 example_lexer.cpp, example_parser.cpp, example_parser.hpp를 추가

 추가한 .cpp 파일들에 미리 컴파일된 헤더 사용 안함 옵션 설정

  
# 사용법 

 example02.ll 파일에 main 함수 있음 
 
 ./parser.exe 계산파일
 
 위와 같이 실행하면 계산 결과를 print 문으로 확인 가능 
 
     


