# Communicating Sequential Processes

channel 기반 메세지 교환으로 병렬 / 분산 프로그래밍을 하는 구조에 대한 초기 노력들 중의 하나로 파이 계산과 같은 이후 발전에도 살아남은 모델이며 go 언어 등에 기본으로 내장된 기능이기도 하다. 

분산 처리의 견고한 모델 중 하나로 채널 교환과 상태 처리를 세션 관리와 함께 구현하면 완전한 모델이 될  가능성이 높다. 게임 서버의 중요한 기반이 될 수 있어 보고 있다. 



## 논문 - C.A.R Hoare / Queens University 

### Concepts and Notations 

```c++
<command> ::= <simple command> | <structured command> 

<simple command> ::= <null command> 
 	| <assignment command> 
    | <input command> 
    | <output command> 
    
<structured command> ::= <alternative command> 
	| <repetitive command> 
	| <parallel command> 

<null command> ::= skip

<command list> := {<declaration>; | <command>;} <command>

```



#### Parallel Commands

```c++
<parallel command> 	::= [<process> {||<process>}]
<process> 			::= <process label> <command list> 
<process label> 	::= <empty> 
	| <identifier> :: 
	| <identifier> (<label subscript>{,<label sbuscript>})::
<label subscript> 	::= <integer constant> | <bound variable> 
<bound variable> 	::=  <identifier> 
<range> 			::= <bound variable>:<lower bound>..<upper bound> 
<lower bound> 		::= <integer constant> 
<upper command> 	::= <integer constant> 
```

$X(i:1..n) :: CL $ 은 $$ X(1)::CL_1 || X(2)::CL_2 || ... || X(n)::CL_n$$ 을 뜻한다. 

예졔로 : 

[west::DISASSEMBLE || X::SQUASH || east::ASSEMBLE ]의 형태가 있다. west, X, east는 이름 (lable)이고 뒤에는 명령이다. 

#### Assignment Commands 

```c++
<assignment command> ::= <target variable> := <expression> 
<expression> ::= <simple expression> | <structured expression> 
<structured expression> ::= <constructor>(<expression list>)
<constructor> ::= <identifier> | <empty> 
<expression list> ::= <empty> | <epxression> {(, <epxression> )}
<target variable> ::= <simple variable> | <structured variable> 
<structured target> ::= <constructor> (<target variable list>)
<target variable list> ::= <empty> | <target variable> {, <target variable>}

```

#### Input and Output Commands 

```c++
<input command> ::= <source> ? <target variable> 
<output command> ::= <destination> ! <expression> 
<source> ::= <process name> 
<destination> ::= <process name> 
<process name> ::= <identifier> | <identifier>(<subscripts>)
```

X?(x,y) : from process X, read a pair of values and assign them to x, y. 

console(j-1) ! "A" : to console j-1, output "A" 



input --> recv, output --> send. 

#### Alternative and Repetitive Commands

```c++
<repetitive command> ::= *<alternative command> 
<alternative command> ::= [<guarded command>] {  }
<guarded command> ::= <guard> --> <command list> 
| (<range>{, <range>})<guard> --> <command list> 
<guard> ::= <guard list> | <guard list>; <input command> 
 | <input command> 
<guard list> ::= <guard element>{;<guard element>}
<guard element> ::= <boolean expression> | <declaration> 
```











