# Stochastic Model

시공간 상의 확률 분포를 갖는 값들에 대한 분석과 시뮬레이션을 다룬다.  



# 2장. Essentials of random variables and vectors 

sample space $\Omega$. $X(\omega)$ for $\omega \in \Omega$ . 확률 변수 $X$는 실수값 함수. 



## 2.1 Random Variables 



### 2.1.1 Distribution and density 

$F(x) = Pr(X \le x), -\infty \lt x \lt \infty$ (누적 확률 분포 함수. CDF) 

- F is a right countinuous, non-decreasing function of x with range [0, 1]
- $lim_{x \rightarrow \infty} F(x) = 1$
- $lim_{x \rightarrow -\infty}F(x) = 0$ 
- $Pr(a \lt X \le b) = F(b) - F(a) \ge 0$ for $a \le b$ 

연속 분포 함수를 가정한다. 

If $F(x)$ is differentiable, $f(x) = dF(x) / d(x) $ 를 확률 밀도 함수 (probability density function. PDF)라고 한다. 

- $f(x) \ge 0$ since $F(x)$ is non-decreasing 
- $\int_{a}^{b} f(x) dx = F(b) - F(a) = Pr(a \lt X \le b)$ 
- $\int_{-\infty}^{\infty} f(x) dx = 1$ 

CDF 대신 PDF를 사용하여 확률 분포를 정의하는 게 일반적이다. PDF는 확률 값이 아니다. (확률의 변화율. dF로 본다.). 

#### Example 2.1: Cauchy random variable 

$f(c) = a/[\pi(c^2 + a^2)], a > 0, -\infty < c < \infty$ 

$dF = f(c)dc$ 

$F(x) = \int _{-\infty}^{x} f(c) dc $

$F(x) = \int_{-\infty}^{x} f(c) dc$

$f(c)$의 부정적분을 구하면 된다. $1/(x^2 + a^2)dx$ 형식의 부정적분이다. 



#### Example 2.2  Exponential random variable 

$f(x) = \lambda e^{-\lambda x}, \lambda > 0, x \ge 0$ 

$dF = \lambda e^{-\lambda x}dx$ 

$F(x) = \int_{0}^{x} f(x) dx  = 1 - e^{-\lambda x}$ 



#### Example 2.3 Uniform random variable 

$f(u) = 1 / (\beta - \alpha)$, $\alpha \le u \le \beta$ 

F(u)의 계산은 연습 문제. 



### 2.1.2 Moments 





















 



















