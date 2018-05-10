# IDL Specification 

코드 생성과 별개로 IDL 스펙을 정의한다. 코드 생성과 Serialization은 각 프로젝트마다 요구 사항이 다르므로 별도로 처리하는 것이 맞다. 



## BNF



### 주석 

//와 /* */의 c++과 같은 주석 라인은 무시한다. 

```pascal
comment := "//.\n" | "/*.*/"   
```

### include 

```pascal
Include: 
	tok_include '\"'  IncludePath tok_identifier '\"'

IncludePath: 
	IncludePath tok_identifier '/' 
```

path는 identifier로 구분된 '/'를 경로 구분자로 하는 현재 파일 부터의 하위 경로만 지원한다. 

### identifier 

```
identifier := ([a-zA-Z_](\.[a-zA-Z_0-9]|[a-zA-Z_0-9])*)
```

영문, _, 숫자를 포함한다.  중간에 .이 나올 수 있다. 









