# Reading Math Fast

영어로 된 수학 교재를 읽으면서 공부해야 할 때가 많다.  영어를 읽다 보면 시간이 오래 걸린다. 빠르게 읽기 위한 방법들을 찾아보고 어떤 방법이 동작하는 지 알아본다.  



## 아이디어 I - Def, Theorem, Problem 

수학적인 정의는 경험과 직관을 배경으로 한다. 이를 이해하지 못 하면 정의를 이해하기 어렵다. 정의를 이해하지 못 하면 정리와 증명을 이해하지 못 한다. 그래서, 지금까지는 전체를 읽으면서 경험과 직관을 형성하려고 했다. 거꾸로 진행해 본다. 

정의는 외운다. 정리의 증명을 꼼꼼히 본다. 이 때 경험과 직관을 형성한다. 문제 풀기로 넘어간다. 문제를 풀면서 다시 살핀다. 그래도 이해가 안 되면 텍스트를 읽는다. 

$ Def \rightarrow Intuition $ 의 과정을 통해 이해한다. 

$ Theorem \rightarrow Intuition \rightarrow Proof $ 과정을 통해 성질을 풍부하게 만든다. 

정의와 직관이 전부이다.  대상이 되는 구조의 모양이 손에 잡힐 듯 생생해야 한다. 



## 연습. Diferential Forms 

**Def.** Differential 1-form on an open subset of $R^2$ is an expression $F(x,y)dx + G(x,y)dy$  . 

멍. 두 개의 함수, 두 개의 기호, 이의 결합.  dx, dy가 뭔지 모르지만 이의 함수를 계수로 하는 1차 결합. 

위를 n차원까지 확대할 수 있다. expression이라는 점이 일단 중요하다. 이 교재의 접근이 그렇다. 의미로 시작하지 않고 표현식 (형태)로 시작한다. 

뭔가 직관을 형성하려는 텍스트가 있다. 중요한 편미분으로 만들어진 1-form이 있고 그레디언트와 유사하다. 



**Def**. $Fdx + Gdy$ is exact if  there is $C^2$ function $f(x, y)$ with $df = Fdx + Gdy$ 

i.e., $F = \frac{\partial f}{\partial x} $ and $G = \frac{\partial f}{\partial y}$   in $R^2 $ case. 

closed when $\frac{\partial F}{\partial y} = \frac{\partial G}{\partial x}$ . 이는 exact일 조건이다. 



**Def.** Parameteric curves 

$C:[a, b] \rightarrow R^2$ 

orientation of trajectory. when $C$ is $C^1$  

$-C $  is $x=f(-u), y=g(-u), -b \le u \le a$ when $x=f(t), y=g(t), a \le t \le b $  



**Thm**. if $F(x, y)dx + G(x, y)dy$ is a closed form on all of $R^2$ with $C^1$ coefficients, then it is exact. 



**Def**. Line Integrals

$ \int_{C} F dx + G dy = \int_a^b [ F(x(t), y(t)) \frac{dx}{dy} + G(x(t), y(t)) \frac{dy}{dt}]dt$  

위의 실질적인 의미가 중요하다. 계산이 필요하다. 정의에 따라 계산할 수는 있겠다. 

구체적인 그림과 계산이 필요하다.  

https://brilliant.org/wiki/line-integral/

여기에 직관을 구성할만한 좋은 그림들이 있다. 이런 그림을 직접 그리고 계산도 직접할 수 있어야 한다. 수학은 계산이다. 프로그래밍은? 

Prop. if $\omega$ is exact anc $C_1$ and $C_2$ are two parameterized curves with the same starting and ending points, then $ \int_{C_1} \omega = \int_{C_2} \omega$ 



여기의 구성으로는 exact일 경우만 계산 가능하게 되어 있다. 왜 이렇게 진행하는가? 1-form이 무엇인지 아직 다 정의되지 않았기 때문이다. 

이제 못 따라간다.  왜 그런가?  좀 더 느린 연습이 많은 기초적인 흐름을 파악하지 못 했긴 때문이다. 외우고 응용하겠다는 의지가 있어야 한다. 천재들처럼 한번 보고 이해하면 해당 영역이 다 만들어지는 건 아니지 않은가. 



### 잘 안 됨 

충분한 연습이 있어야 한다. 그런 교재가 필요하다. 실제 수학은 어려운 건 맞다. 그냥 본다고 바로 풀리지도 않는다. 아주 많은 훈련과 연습이 필요하다. 



