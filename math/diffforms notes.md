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

따라서, $\frac{\partial F}{\partial y} = \frac{\partial^2 f}{\partial y \partial x} = \frac {\partial^2 f}{\partial x \partial y}= \frac{\partial G}{\partial y}$ 이다. 

여기서 f의 이계 편미분이 같으려면 $C^2$ 이어야 한다. (왜 그런가?)

정확한 미분 형식은 $ydx$가 f를 찾을 수 없는 것처럼 드물다. 

**연습:** 

$ydx$ 의 정확한 함수 f를 찾으려면 $\int y dx$ = $\frac{\partial f}{\partial x} = yx + C$ 여기서 $\frac{\partial f}{\partial y} = x$가 된다. 따라서, 만족하는 함수가 없다. 

만약 $\frac{\partial F}{\partial y} =  \frac{\partial G}{\partial y}$ 이면 닫혀있다(closed)고 한다.  그래서, 정확하려면 닫혀있어야 한다. 

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

비약은 없으나 비약이 있다. $\omega$ 표시에 비약이 있는가? $\omega = Fdx + Gdy$ 라고 보면 비약은 없다. $df = \omega$ 일 때 $\int_{C_1} df = \int_{a}^{b} \frac{df}{dt}dt$ 을 열심히 생각해 봐야 한다. 여기가 핵심이다. 



더 보기 전에 연습이 필요하다. 

### Corollary 1.4.6 if $\omega$ is exact and C is closed, then $\int_C \omega$ = 0 

이건 복소해석에서 본 것과 같다. C를 C1, C2로 나눠서 시점과 종점이 같도록 하면 둘의 값이 갖고 방향만 다르기 때문에 합친 건 0이 된다. 



### Proof of Theorem 1.4.1 



















