# Using CDB

windows command line debugger인 cdb 사용법을 익힌다. CDB로 자유롭게 어셈블리 코드와 메모리를 살피면서 디버깅을 하는 수준까지 가려 한다. 



WinDBG가 어셈블리를 한번에 보기가 편하고 여러 창을 동시에 사용할 수 있어 CDB보다 낫다. 경로에 있으면 CDB처럼 실행할 수 있다. 



cf) 문장은 형용사, 동사로 끝내도록 한다. "것"은 사용하지 말자. 간단하고 명확하게 문장을 끝맺자. 



## 기본 명령어 



- [.sympath (Set Symbol Path)](http://go.microsoft.com/fwlink/p?linkid=399238)
- [.reload (Reload Module)](http://go.microsoft.com/fwlink/p?linkid=399239)
- [x (Examine Symbols)](http://go.microsoft.com/fwlink/p?linkid=399240)
- [g (Go)](http://go.microsoft.com/fwlink/p?linkid=399388)
- **Break** command on the **Debug** menu
- [lm (List Loaded Modules)](http://go.microsoft.com/fwlink/p?linkid=399237)
- [k (Display Stack Backtrace)](http://go.microsoft.com/fwlink/p?linkid=399389)
- [bu (Set Breakpoint)](http://go.microsoft.com/fwlink/p?linkid=399390)
- [bl (Breakpoint List)](http://go.microsoft.com/fwlink/p?linkid=399390)
- [~ (Thread Status)](http://go.microsoft.com/fwlink/p?linkid=399392)
- [~s (Set Current Thread)](http://go.microsoft.com/fwlink/p?linkid=399393)
- [.sympath+ (Set Symbol Path) append to existing symbol path](http://go.microsoft.com/fwlink/p?linkid=399238)
- [.srcpath (Set Source Path)](http://go.microsoft.com/fwlink/p?linkid=399395)
- **Step Into** command on the **Debug** menu (**F11**)
- [!analyze -v](http://go.microsoft.com/fwlink/p?linkid=399396)
- [qd (Quit and Detach)](http://go.microsoft.com/fwlink/p?linkid=399394)



# 어셈블리 이해 

masm으로 진행한다. 좋은 튜토리얼이 있다.  외울 건 외워야 한다. 

## 레지스터들 

eax, ebx, ecx, edx ==> a, b, c, d에 x가 붙은 다음 다시 e가 붙었다. a, c, d만 사용. EBX는 DS 세그먼트 내 데이터 포인터로 사용됨. 

source index, destination index (SI, DI)의 확장. ESI, EDI

stack pointer, base pointer (SP, BP)의 확장. ESP, EBP

여기까지 32비트 레지스터. 

CS (코드), DS, ES, FS, GS (데이터), SS (스택). 세그먼트들은 뭘 하지? 이들은 16비트. 

EFLAGS (상태, 제어, 플래그), EIP (명령. 포인터 류 아님?)



| **eax** | Accumulator                |
| ------- | -------------------------- |
| **ebx** | Base register              |
| **ecx** | Count register             |
| **edx** | Double-precision register  |
| **esi** | Source index register      |
| **edi** | Destination index register |
| **ebp** | Base pointer register      |
| **esp** | Stack pointer              |





## 명령어 

- ADD, SUB, AND, OR, XOR
- MUL, DIV 
  - EAX (Accumulator 레지스터)
- INC, DEC, NEG 
- NOT (논리)
- PUSH, POP
  - 스택
-  MOV 
- CMP 
  - op1 - op2 의 결과로 플래그 세팅 
  - JMP, REP와 사용 
- JMP label
- LEA reg, memory 
  - memory의 오프셋을 reg에 저장 
- RET 
  - 리턴 
- INT constant 
  - 인터럽트 



invoke SendMessage, [hWnd], WM_CLOSE, 0, 0 := 

```
push 0
push 0
push WM_CLOSE
push [hWnd]
call [SendMessage]
```



### 예제 

1에서 6까지 더하고 7을 곱해서 스택에 넣고 이를 변수에 지정. 



## 기본 윈도우 



### 매크로 

.if, .else, .endif 

.while, .break, .endw

### 함수 

<name> proc <var1>:<var1 type>, <var2>:<type>, ... 

​	<function code> 

 	ret 

<name> endp

invoke <name>, p1, p2, ... 

mov RetVal, eax 로 eax에서 RetVal로 이동? 

### 변수 

.data 또는 .data? (초기화 안 된 변수들)

<name> <type> <value or ?> 

local <name>:<type> 



### 간단 위도우 

특별히 관심이 가는 부분은 아니다. 좀 더 이해했고 디버깅 공부로 일찍 전환한다. 



## 더 많은 윈도우 



### 문자열 다루기 



## C++ 어셈블리 이해 

C++ 컴파일러로 빌드한 어셈블리들을 이해한다. 

### 초간단 

```assembly
#include "stdafx.h"


int main()
{
00211650  push        ebp     	   ; 
00211651  mov         ebp,esp  	   ; ebp = esp 
00211653  sub         esp,0C0h     ; esp = 0C0h  (13)
00211659  push        ebx          ; stack[ ebx, ebp ] 
0021165A  push        esi          ; stack[ esi, ebx, ebp ]
0021165B  push        edi          ; stack[ edi, esi, ebx, ebp ]
0021165C  lea         edi,[ebp-0C0h]  ; edi = ebp - 0X0h  
00211662  mov         ecx,30h         ; ecx = 30h	
00211667  mov         eax,0CCCCCCCCh  ; eax = 0CCCCCCCCh 
0021166C  rep stos    dword ptr es:[edi]     ; 
    return 0;
0021166E  xor         eax,eax   	 ; eax = 0 => 리턴 값
}
00211670  pop         edi             ; stack [ esi, ebx, ebp ]
00211671  pop         esi             ; stack [ ebx, ebp]
00211672  pop         ebx             ;  스택 복구
00211673  mov         esp,ebp         ; 스택 포인터 복구 
00211675  pop         ebp             ; 마저 
00211676  ret                         ; 리턴 
```

위는 디버그 모드의 어셈블리 코드이다. 

```
lea : 소스 레지스터의 값에 인덱스만큼 더해서 데스티네이션 레지스터에 넣으라는 뜻
edi = ebp - 0C0h 
```

원래 lea는 Load Effective Address로 주소 계산에 사용. 효과 때문에 계산 용도로 많이 사용.

예시 

- `LEA EAX, [ EAX + EBX + 1234567 ]` calculates `EAX + EBX + 1234567` (that's three operands)
- `LEA EAX, [ EBX + ECX ]` calculates `EBX + ECX` without overriding either with the result.
- multiplication by constant (by two, three, five or nine), if you use it like `LEA EAX, [ EBX + N * EBX ]` (N can be 1,2,4,8).

rep stos 는 문자열 처리 관련. 

es:[edi] 등은 주소 모드에 관한 것이다. 

```assembly

int main()
{
00007FF6C52B1670  push        rbp                     ; stack[rbp]
00007FF6C52B1672  push        rdi                     ; stack[rdi, rbp]
00007FF6C52B1673  sub         rsp,0C8h                ; rsp = 0C8h
00007FF6C52B167A  mov         rbp,rsp                 ; rbp = rsp 
00007FF6C52B167D  mov         rdi,rsp                 ; rdi = rsp  
00007FF6C52B1680  mov         ecx,32h                 ; ecx = 32h 
00007FF6C52B1685  mov         eax,0CCCCCCCCh          ; eax = 0CCCCCCCCh
00007FF6C52B168A  rep stos    dword ptr [rdi]         ; 
    return 0;
00007FF6C52B168C  xor         eax,eax                 ; eax = 0
}
00007FF6C52B168E  lea         rsp,[rbp+0C8h]          ; rsp = rbp + 0xC8
00007FF6C52B1695  pop         rdi                     ; stack [ rbp ]
00007FF6C52B1696  pop         rbp                     ; 
00007FF6C52B1697  ret  
```

위는 64비트 디버그 모드 어셈블리이다. 

```assembly
    return 0;
00007FF606EE1000  xor         eax,eax  

```

위의 내용으로 끝. 엄청난 취적화다. C++이 그래서 쓰이는 것. 

### 단계 2

```c++

void print_vector(std::vector<int>& vs)
{
	for (auto& v : vs)
	{
		std::cout << v << std::endl;
	}
}

int main()
{
	std::vector<int> vs{ 1, 2, 3, 4, 5 };

	print_vector(vs);

    return 0;
}

```



```assembly
void print_vector(std::vector<int>& vs)
{
00007FF62FC85BE0  mov         qword ptr [rsp+8],rcx  
00007FF62FC85BE5  push        rbp  
00007FF62FC85BE6  push        rdi  
00007FF62FC85BE7  sub         rsp,1A8h  
00007FF62FC85BEE  lea         rbp,[rsp+20h]  
00007FF62FC85BF3  mov         rdi,rsp  
00007FF62FC85BF6  mov         ecx,6Ah  
00007FF62FC85BFB  mov         eax,0CCCCCCCCh  
00007FF62FC85C00  rep stos    dword ptr [rdi]  
00007FF62FC85C02  mov         rcx,qword ptr [rsp+1C8h]  
00007FF62FC85C0A  mov         qword ptr [rbp+168h],0FFFFFFFFFFFFFFFEh  
00007FF62FC85C15  mov         rax,qword ptr [__security_cookie (07FF62FC93010h)]  
00007FF62FC85C1C  xor         rax,rbp  
00007FF62FC85C1F  mov         qword ptr [rbp+178h],rax  
	for (auto& v : vs)
00007FF62FC85C26  mov         rax,qword ptr [vs]  
00007FF62FC85C2D  mov         qword ptr [rbp+8],rax  
00007FF62FC85C31  mov         edx,18h  
00007FF62FC85C36  lea         rcx,[rbp+28h]  
00007FF62FC85C3A  call        std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int> > >::__autoclassinit2 (07FF62FC81456h)  
00007FF62FC85C3F  lea         rdx,[rbp+28h]  
00007FF62FC85C43  mov         rcx,qword ptr [rbp+8]  
00007FF62FC85C47  call        std::vector<int,std::allocator<int> >::begin (07FF62FC810FFh)  
00007FF62FC85C4C  nop  
00007FF62FC85C4D  mov         edx,18h  
00007FF62FC85C52  lea         rcx,[rbp+58h]  
00007FF62FC85C56  call        std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int> > >::__autoclassinit2 (07FF62FC81456h)  
00007FF62FC85C5B  lea         rdx,[rbp+58h]  
00007FF62FC85C5F  mov         rcx,qword ptr [rbp+8]  
00007FF62FC85C63  call        std::vector<int,std::allocator<int> >::end (07FF62FC8101Eh)  
00007FF62FC85C68  nop  
00007FF62FC85C69  jmp         print_vector+94h (07FF62FC85C74h)  
00007FF62FC85C6B  lea         rcx,[rbp+28h]  
00007FF62FC85C6F  call        std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int> > >::operator++ (07FF62FC8137Fh)  
00007FF62FC85C74  lea         rdx,[rbp+58h]  
00007FF62FC85C78  lea         rcx,[rbp+28h]  
00007FF62FC85C7C  call        std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<int> > >::operator!= (07FF62FC815FFh)  
00007FF62FC85C81  movzx       eax,al  
00007FF62FC85C84  test        eax,eax  
00007FF62FC85C86  je          print_vector+0E0h (07FF62FC85CC0h)  
00007FF62FC85C88  lea         rcx,[rbp+28h]  
	for (auto& v : vs)
00007FF62FC85C8C  call        std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int> > >::operator* (07FF62FC81154h)  
00007FF62FC85C91  mov         qword ptr [rbp+88h],rax  
	{
		std::cout << v << std::endl;
00007FF62FC85C98  mov         rax,qword ptr [rbp+88h]  
00007FF62FC85C9F  mov         edx,dword ptr [rax]  
00007FF62FC85CA1  mov         rcx,qword ptr [__imp_std::cout (07FF62FC97150h)]  
00007FF62FC85CA8  call        qword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (07FF62FC97168h)]  
00007FF62FC85CAE  lea         rdx,[std::endl<char,std::char_traits<char> > (07FF62FC810EBh)]  
00007FF62FC85CB5  mov         rcx,rax  
00007FF62FC85CB8  call        qword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (07FF62FC97170h)]  
00007FF62FC85CBE  jmp         print_vector+8Bh (07FF62FC85C6Bh)  
	}
00007FF62FC85CC0  lea         rcx,[rbp+58h]  
00007FF62FC85CC4  call        std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int> > >::~_Vector_iterator<std::_Vector_val<std::_Simple_types<int> > > (07FF62FC815DCh)  
00007FF62FC85CC9  nop  
00007FF62FC85CCA  lea         rcx,[rbp+28h]  
00007FF62FC85CCE  call        std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int> > >::~_Vector_iterator<std::_Vector_val<std::_Simple_types<int> > > (07FF62FC815DCh)  
}
00007FF62FC85CD3  lea         rcx,[rbp-20h]  
00007FF62FC85CD7  lea         rdx,[__xt_z+400h (07FF62FC8EEA0h)]  
00007FF62FC85CDE  call        _RTC_CheckStackVars (07FF62FC8122Bh)  
00007FF62FC85CE3  mov         rcx,qword ptr [rbp+178h]  
00007FF62FC85CEA  xor         rcx,rbp  
00007FF62FC85CED  call        __security_check_cookie (07FF62FC8153Ch)  
00007FF62FC85CF2  lea         rsp,[rbp+188h]  
00007FF62FC85CF9  pop         rdi  
00007FF62FC85CFA  pop         rbp  
00007FF62FC85CFB  ret  
```



x64 최적화 빌드의 print_vector inline 된 부분. 

```c++
	print_vector(vs);
00007FF7CDB2105E  mov         rdi,qword ptr [vs]  
00007FF7CDB21063  mov         rbx,rdi  
00007FF7CDB21066  mov         rsi,qword ptr [rsp+48h]  
00007FF7CDB2106B  cmp         rdi,rsi  
00007FF7CDB2106E  je          main+98h (07FF7CDB21098h)  
00007FF7CDB21070  mov         edx,dword ptr [rbx]  
00007FF7CDB21072  mov         rcx,qword ptr [__imp_std::cout (07FF7CDB230B8h)]  
00007FF7CDB21079  call        qword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (07FF7CDB23088h)]  
00007FF7CDB2107F  mov         rcx,rax  
00007FF7CDB21082  lea         rdx,[std::endl<char,std::char_traits<char> > (07FF7CDB211E0h)]  
00007FF7CDB21089  call        qword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (07FF7CDB23090h)]  
00007FF7CDB2108F  add         rbx,4  
00007FF7CDB21093  cmp         rbx,rsi  
00007FF7CDB21096  jne         main+70h (07FF7CDB21070h)  

```

스택이나 힙에 있는 값들을 dt 명령어로 변환해서 볼 수 있어야 한다. 

맹글링된 심벌을 자유롭게 다루어야 한다. 



## More Assembly 

IA32 와 x64 아키텍처 관련 기본 문서.  기본기가 더 있어야 한다. 

### 함수 호출 

- 스택은 큰 주소에서 작은 주소로 올라감 
- ebp가 스택 프레임 포인터 



### x64

rcx, rdx, r8, r9을 사용하여 처음 4개 파라미터 전달 

나머지는 스택을 사용 

호출자는 32바이트의 그림자 공간을 스택에 만듦



## 로그 

### 도구  

튜토리얼즈포인트에 있는 nasm과 gcc 기반의 튜토리얼을 사용한다.  윈도우즈 콘솔 프로그램도 여러 영향이 있어 간단한 예제로 먼저 시작한다.  

nasm 튜토리얼이 리눅스와 gcc 를 사용한다. 윈도우즈에서 사용법을 찾기 어렵다. masm sdk가 라이브러리를 포함하고 있어 그 쪽으로 시도한다. 

- masm 
  - ml 
  - link 
  - 라이브러리 포함 











