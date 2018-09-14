# differential forms 

df, dx를 벡터처럼 사용하여 직관적으로 계산하는 경우가 많다. 이런 방법은 일정한 조건 하에서 미적분 계산을 단순하게 하고 이해하게 쉽도록 만든다. 하지만, 처음에 이해하기가 쉽지 않다. 18살에 처음 미분소를 본 이후 계속 고민했던 부분이기도 하다. 이제 한달 정도 시간 투자를 하여 완전하게 하고자 한다. 물론 시작이다. 



# 1-forms 



## 1-forms

differential forms on an open subset of $R^2$ is an expression $F(x, y)dx + G(x, y)dy$. 여기서 F, G는 R-valued functions on the open set 이다. 

$f(x, y)$가 U 상의 $C^1 $ R-valued 함수라고 하면, total differential (전미분, 또는 외미분)은 다음과 같다. 

$ df = \frac{\partial f}{\partial x}dx + \frac{\partial f}{\partial y} dy$ 

위는 직관적으로 미분이 작용하는 공간 상의 (dx, dy)와 ($\frac{\partial f}{\partial x}$, $\frac{\partial f}{\partial y}$)의 내적값이다. 즉, 편미분으로 만들어진 벡터가 (dx, dy) 벡터 방향의 성분이다. 

$R^3$에서도 유사하게 전미분이 정의된다. 

$ df = \frac{\partial f}{\partial x}dx + \frac{\partial f}{\partial y} dy + \frac{\partial f}{\partial z} dz$

미분형식이 벡터 필드와 매우 비슷해 보인다. 다음과 같이 생각해 볼 수 있다. 

$F\vec{i} + G\vec{j} + H\vec{k} \longleftrightarrow Fdx + Gdy + Hdz$

위와 같은 관점에서 $\nabla f$  는 $df$에 해당한다. 표기만 바꾼 걸로 보이지만 최종적으로 매우 강력하다. 

$x, y, z$가 파라미터 $t$에 의존한다고 하면 (하나의 파라미터화 라고 보면), 연쇄 법칙은 다음을 보여준다. 

$ \frac{df}{dt} = \frac{\partial f}{\partial x}\frac{dx}{dt} + \frac{\partial f}{\partial y}\frac{dy}{dt} + \frac{\partial f}{\partial z} \frac{dz}{dt}$

여기서 dt를 양 쪽에 곱해서 (cancel out) 전미분 형식을 얻을 수 있다. 



## Exactness in $R^2 $

$Fdx + Gdy$가 $R^2$ 상의 $C^1$ 계수 (Coefficients)를 갖는 미분 형식이라고 하자. $C^2$ 함수 $f(x, y)$가 있어, $df = Fdx + Gdy$를 만족하면 미분 형식이 정확하다(Exact)고 한다. 

이는 $F = \frac{\partial f}{\partial x}$, $G = \frac{\partial f}{\partial y}$ 라고 하는 것과 동일하다. 

따라서, $\frac{\partial F}{\partial y} = \frac{\partial^2 f}{\partial y \partial x} = \frac {\partial^2 f}{\partial x \partial y}= \frac{\partial G}{\partial x}$ 이다. 

여기서 f의 이계 편미분이 같으려면 $C^2$ 이어야 한다. (왜 그런가?)

정확한 미분 형식은 $ydx$가 f를 찾을 수 없는 것처럼 드물다. 

**연습:** 

$ydx$ 의 정확한 함수 f를 찾으려면 $\int y dx$ = $\frac{\partial f}{\partial x} = yx + C$ 여기서 $\frac{\partial f}{\partial y} = x$가 된다. 따라서, 만족하는 함수가 없다. 

만약 $\frac{\partial F}{\partial y} =  \frac{\partial G}{\partial x}$ 이면 닫혀있다(closed)고 한다.  그래서, 정확하려면 닫혀있어야 한다. 

정확성은 매우 중요한 개념이다.  미분 방정식에서 이미 만난적이 있을 것이다. 방정식이 다음과 같이 주어지면, $\frac{dy}{dx} = \frac{F(x,y)}{G(x, y)}$ 다시 써서 $Fdx - Gdy$ = 0 으로 할 수 있다. 

만약 $Fdx - Gdy$가 정확하다면 df가 있고 f(x, y) = c 가 위 식의 해가 된다. 

물리에도 이런 개념이 있다. 벡터 필드 $\vec{F} = F_1 \vec{i} + F_2\vec{j}$ 가 힘을 나타낼 때, $P(x, y)$ 로 표시되는 포텐셜 에너지가 있어 $\vec{F} = -\nabla P$ 를 만족하는 함수를 찾길 원할 때가 있다. 포턴셜 에너지 함수를 갖는 힘을 보존력 (Conservative)이라고 한다. 미분형식의 용어로는, $\vec{F}$ 의 미분 형식 $F_1dx + F_2dy$가 정확할 때 보존력이 된다. 

**노트:** 

$dx, dy$ 가 벡터 형식이 아닌데 벡터와 함께 쓰이는 점이 아직 잘 이해가 안 된다. 이를 이해하는 과정이 핵심으로 보인다. 벡터와 스칼라를 넘어서 자유롭게 쓸 수 있어야 한다. 



## Parameteric curves 

매개변수 곡선은 실수 구간의 함수로 공간의 특성을 파악할 때 기본으로 사용한다. 복소해석에서 선적분을 다룰 때도 매개변수화한 곡선 상의 적분에서 시작했다. 이와 같이 선적분을 시작하기 전에 매개변수화된 곡선에 대한 기본 개념을 정리한다. 

Parametric curve in a plane is  vector valued function $C : [a, b] \rightarrow R^2$ . 

이는$\vec{C}(t) = (x(t), y(t))$, where t $\in$ [a, b] 와 같은 얘기이다. 실수 구간을 사용하면 순서가 있고, 이에따른 벡터들이므로 궤적이 된다. 

$C$가 $C^1$이라고 가정하면 속도 벡터 또는 접벡터 $\vec{v} = (\frac{dx}{dt}, \frac{dy}{dt})$를 정의할 수 있다. 

$-C$는 $(x(-t), y(-t))$ 로 주어지는 곡선으로 $-t \in [-b, -a]$가 된다. 

$-C$는 재매개화의 한 예로 일반적으로는 다음과 같다. 

$t=h(u)$ 이고 $\frac{dt}{dh} \ne 0$ 라고 하면 x = f(h(u)), y=g(h(u))와 같이 재매개화가 이루어진다. (시작과 종점 관련 구간이 일치해야 한다) 



## Line Integrals 

이제 진짜 질문에 이르렀다. $Fdx + Gdy$ 미분형식이 언제 정확한가? 동일하게 힘이 보존력인지 아닌 지 어떻게 알까? 닫혀있는 지를 체크하는 건 간단하다. 그리고 닫혀있지 않으면 정확하지 않다. 거꾸로도 자주 참이다. (놀라운가? 왜 그런가?)



### Theorem 1.4.1 If $F(x, y)dx + G(x, y)dy$ is a closed form on all of $R^2$ with $C^1$ coefficients, then it is exact. 



위를 증명하려면 $df = Fdx + Gdy$ 를 풀어야 하고 이 식에 있는 $d$ 의 효과를 undo 해야 한다. 이는 어떤 형태의 적분을 필요로 한다. 



### Definition 1.4.2 

$$
\int_C Fdx + Gdy = \int_{a}^{b} \big[F(x(t), y(t))\frac{dx}{dt} + G(x(t), y(t))\frac{dy}{dt}\big] dt
$$

**노트** 

위는 직관적으로도 이해해야 한다. 계산이 쉬울 수도 있고 아닐 수도 있다. 수치적분으로도 생각할 수 있다. 그림을 그려 생각해 보는 것도 좋다. 



**연습:**

$-\frac{y}{x^2 + y^2}dx + \frac{x}{x^2 + y^2}dy$의 적분을  $x=cos\theta, y=sin\theta$ where $\theta \in [0, 2\pi]$ 따라 구하라. 



동일한 과정을 $R^3$에 대해서도 정의할 수 있다. 



### Proposition 1.4.5 If $\omega$ is exact and $C_1$ and $C_2$ are two parameterized curves with the same endpoints,then $\int_{C_1}\omega = \int_{C_2} \omega$



$\omega = df$ 라면 $\int df$ = $f |^b_{a}$ 가 된다. 따라서, 중간의 점들에는 의존하지 않는다. 

**노트**

비약이 있다. $\omega$ 표시에 비약이 있는가? $\omega = Fdx + Gdy$ 라고 보면 비약은 없다. $df = \omega$ 일 때 $\int_{C_1} df = \int_{a}^{b} \frac{df}{dt}dt$ 을 열심히 생각해 봐야 한다. 여기가 핵심이다. 

좀 더 생각해 보면 다음과 같이 따라갈 수 있다. 
$$
df = Fdx + Gdy 
\\
\int df = \int \frac{df}{dt}dt = \int (F\frac{dx}{dt} + G\frac{dy}{dt})dt
$$
위의 적분은 선적분 정의와 같다. x, y가 곡선을 따라 매개변수화 되므로 적분이 가능하다. 위는 스칼라 함수인데 나중에 벡터 함수도 다뤄야 한다. 



### Corollary 1.4.6 if $\omega$ is exact and C is closed, then $\int_C \omega$ = 0 

이건 복소해석에서 본 것과 같다. C를 C1, C2로 나눠서 시점과 종점이 같도록 하면 둘의 값이 갖고 방향만 다르기 때문에 합친 건 0이 된다. 



### Proof of Theorem 1.4.1 

$Fdx + Gdy$가 $R^2$ 상의 닫힌 형식이다. $f(x,y) = \int_C Fdx + Gdy$ 이고 곡선이 (0, 0)에서 (x, 0) 다시 (x,y)로 이어지는 선분들로 이루어져 있다고 하자. 

$f(x, y) = \int_{0}^{x} F(t, 0)dt + \int_{0}^{y}G(x, t)dt$

이 때, $df = Fdx + Gdy$임을 보이려고 한다. 

Fundamental theorem of calculus로 미분을 하면 

$\frac{\partial f}{\partial y} = \frac{\partial}{\partial y} \int_{0}^{y} G(x, t)dt$ = $G(x, y)$ 이다. 

**note:**

위에서 G의 primitive가 GG라고 하면 $\int G(x, t)dt = GG |^{y}_{0}$ = GG(x, y) - GG(x, 0)가 된다. 이를 다시 y에 대해 편미분하면 G(x, y)가 된다. 

구체적인 예를 들어서 계산해도 괜찮다. $G(x, y) = x^2 + y^3$ 이라고 하면 더 명확하다. Boas 책으로 연습을 많이 하는 게 좋다. 

$\frac{\partial f}{\partial x}$ 를 계산하는 부분에서 closed 성질을 이용한다. $R^2$ 전체에서 닫힌 성질은 곡선을 작업하기 편하게 선분으로 선택하는 과정에서 사용되었다.  이와 같은 작업이 가능한 오픈 집합이면 동일한 증명이 가능한데 예외적인 경우도 있다. 이를 확정하기 위한 방법이 de Rham cohomology이다. 

증명에서 $df = Fdx + Gdy$ 형태의 f가 있다는 걸 증명했는데 그 f(x, y) 가 $\int_C Fdx + Gdy$ 임에 주목해야 한다. 아직 잘 모르겠지만 dxdy 또는 dxdydz 와 같은 것, 벡터에 대해서도 미분 형식을 사용하는 것 등도 이 쪽과 연관이 있어 보인다. 



## Work 

$\vec{d} = (dx, dy, dz)$ , $\vec{F} = (F_1, F_2, F_3)$ 

돌을 들어올리는 간단한 경우로 보면, 다음과 같이 일을 계산할 수 있다. 

$\vec{F} \cdot \vec{d} = -(F_1 dx + F_2dy + F_3dz)$ 

위의 값을 벡터 필드 상의 곡선에 따라 적분할 수 있어 보인다. 

$$ -\int_C F_1dx + F_2dy + F_3dz$$

위의 식은 $-\int_C \vec{F} \cdot \vec{d}$ 와 같이 나타낼 수도 있다. 여기서 $\vec{d}$는 매개변수가 되는 곡선에서 변위 벡터가 된다. 따라서 $\vec{d} = \vec{dC}$ 이고 매개변수화 한 형태에서 연쇄 법칙을 사용하여 $\vec{d}C = \frac{\vec{d}C}{dt}dt$ 가 된다. $\vec{F}$도 C의 함수로 보면 $\vec{F} = \vec{F}(C)$ 이다. 

좀 더 접근해 가고 있다. 계산 연습이 필요하다. 구체적인 공간 상의 구체적인 함수 형태로 만들어서 계산할 수 있어야 한다. 

위를 벡터처럼 적는 방법으로 $-\int_C \vec{F} \cdot d\vec{s}$ 를 사용한다. 



## Green's theorem for a rectangle 

$R$을 (0, 0), (0, a), (a, b), (0, b)로 둘러싸인 사각형이라고 하자.  $C$를 이 사각형을 둘러싸는 반시계 방향 경계 곡선으로 둔다. $C^1$ 인 함수 $P(x, y), Q(x,y)$ 가 사각형 R에 주어질 때, 미적분 기본 정리에서 다음 결과가 나온다. 
$$
\int\int_D\frac{\partial Q}{\partial x}dxdy = \int_a^b[Q(a, y) - Q(0, y)]dy = \int_CQ(x, y)dy
$$
다변수 함수의 미적분 계산에 좀 더 익숙해질 필요가 있다. 

- Fubini 정리의 증명 이해 
- Jacobian으로 변수 변환 이해 
  - 다변수 체인룰? 

그리고 $\int_C Pdx + Qdy$ 가 $\int_a^b [P(x(t), y(t))\frac{dx}{dt} + Q(x(t), y(t))\frac{dy}{dt} ]dt $ 임을 기억한다. 마법은 없고 정의와 논리만 있을 뿐이다. 



## Exercise Set 1









# 2-forms



## Wedge product

$\vec{u}, \vec{v} \in \mathbb{R}^n$, define the matrix $\vec{u} \wedge \vec{v} = \frac{1}{2} (\vec{u}^T\vec{v} - \vec{v}^T\vec{u})$ 

여기서 가장 중요한 건 웨지곱이 행렬이라는 점이다. 계산을 하면 skew symmetric 행렬이 된다. $\vec{u} \wedge \vec{v} = -\vec{v} \wedge \vec{u}$ 가 된다. $\wedge^2 \mathbb{R}^2$는 skew symmetric 행렬 집합이다. 웨지곱은 이 집합의 원소이다. 

이는 일반적으로 다음에서 알 수 있다. 
$$
(\vec{u}^T\vec{v} - \vec{v}^T\vec{u})^T = 
(\vec{v}^T)\vec{u}^{TT} - \vec{u}^T\vec{v}^{TT}
\\
= \vec{v}^T \vec{u} - \vec{u}^T\vec{v} 
\\
= -2(\vec{v}\wedge\vec{u})
$$
정의에서 바로 계산하기 보다 계산 규칙을 만들면 편하다. 
$$
v \wedge u = - u \wedge v
\\
u \wedge u = 0 
\\
c(u \wedge v) = (cu) \wedge v = u \wedge (cv)
\\
u\wedge v + u \wedge w = u \wedge ( v + w) 
$$


### Theorem 2.1.2 $u \wedge v$는 u와 v로 생성된 (span) 평행다면체의 면적을 결정한다. 

벡터곱의 성질인데 지금 바로 증명하지는 않고 개념을 추가해 나가면서 필요한 시점에 증명한다. 

벡터공간 V가 있을 때, 2-vector의 벡터 공간을 만들 수 있다. 
$$
\wedge^2V = \{ \sum_iu_i \wedge v_i | u_i, v_i \in V\}
$$
재미있다. 원래 벡터공간과 같은 필드 (실수나 복소수)를 사용한다. 바로 이해되지 않을 때는 계산이 도움이 된다. $\mathbb{R}^n$ 의 2-벡터 공간을 표준 기저로 살펴본다. 
$$
\vec{a} = (a_1, a_2, ..., a_n) = a_1e_1 + a_2e_2 + ... + a_ne_n
\\
$$
위와 같이 놓고 $\wedge^2V$ 의 임의의 2-벡터가 어떻게 표현될 지를 계산한다. **연습!!!**



## 2-forms 

2-form은 1-form의 웨지곱을 갖는 식이다. $\mathbb{R}^3$에서는 다음과 같다. 

$ F dx \wedge dy + G dy \wedge dz + H dz \wedge dx$ 

예제 계산을 다음과 같이 한다. 

$(3dx + dy) \wedge (e^x dx + 2dy) = ? $ 

A 2-from will be an expression that can be integrated over a surface in the same way that a 1-form can be integrated over a curve. 

1-form이 주어졌을 때 미분 형식을 만들기 위해 $d\omega$ 를 정의한다. 
$$
d(\alpha + \beta) = d\alpha + d\beta 
\\
d(f\alpha) = df \wedge \alpha + f \wedge d\alpha 
\\
d(dx) = d(dy) = d(dz) = 0
$$
위에서 f는 함수이고 $\alpha, \beta$는 1-form이다. 

$df = f_x dx + f_y dy + f_z dz$  (여기서 $f_x$는 x에 대한 편미분)

$d(Fdx + Gdy + Hdz) = d(Fdx) + d(Gdy) + d(Hdz) = $

$dF \wedge dx + F \wedge d(dx) + ... $ 

$d(dx) = 0$ 

$dF \wedge dx = (F_xdx + F_ydy + F_zdz) \wedge dx = $

$ F_ydy \wedge dx + F_z dz \wedge dx$ 

G, H도 비슷하게 계산하여 결과가 다음과 같다. 

$(G_x - F_y)dx \wedge dy + (H_y - G_z)dy \wedge dz + (F_z - H_x) dz \wedge dx$ 

벡터에서 웨지로 오가는 형태로 보면 위는 벡터 필드의 Curl 과 같다. 



## Exactness in $\mathbb{R}^3$ and conservation of energy 

 $C^1$ 1-form $\omega = Fdx + Gdy + Hdz$가  $C^2$ 함수 f가 $\omega = df$일 경우, 정확하다고 한다. 

$dw = 0$이면 닫혀있다고 하고 $G_x = F_y, H_y = G_z, F_z = H_x$를 만족해야 한다. 



Theorem 2.3.2는 매우 중요해 보인다. 계산을 해보는 게 좋겠다. 간단한 곡선들로 정확한 함수들을 찾는다. 

 if $f(x0; y0; z0) = \int_C \omega$, where C is any
piecewise C1 curve connecting (0; 0; 0) to (x0; y0; z0), then $df = \omega$

위는 df의 정의는 아니지만 정의처럼 생각할 수도 있다. 지금까지 df의 실제 의미를 준 경우가 없어서 더욱 그렇다. 



## Derivative of a 2-form and divergence

3-vector로 확장한다. $u \wedge v \wedge w$ . 3-vector는 2-vector의 웨지곱이 아니고 다른 오브젝트로 볼륨을 나타낸다. 

같은 벡터가 있으면 0, 순서가 바뀌면 -, 배분 법칙이 성립한다. 

2-vector는 행렬로 계산했는데 3-vector에 대한 행렬 표현은 없다. 















































