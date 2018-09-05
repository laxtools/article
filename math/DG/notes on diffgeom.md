# Notes on differential geometry 

From what I failed to mater, I begin again. Differential geometry for physicist has more concrete feelings as its target audiences are physicists. To have more concrete applications seems to be easier to follow. Calculations or concrete applications are the best way to practice to master a subject. 



# 1.2 Metric Spaces 



## 1.2.1 Simple idea of convergence

- "가깝다"는 판단 
- 일련의 점이 수렴한다는 뜻 
- 수렴한다는 의미가 공간을 결정한다
- 복소 공간의 수렴
  - $\epsilon$ 원판에 점들을 몰아 넣을 수 있다
  - "trap" sequence 



$\forall \epsilon \gt 0 \, \exist n \gt n_0 \, s.t. \, z_n \in B_{\epsilon}(z)$

$tail(z_n) \in B_{\epsilon}(z)$ 

$\implies z_n \rightarrow z$

$tail(z_n) = \{z_k | k > n\}$



거리가 있는 아무 공간이나 수렴의 의미를 가질 수 있다. 

$d(\vec{x}, \vec{y} ) = \sqrt{ {(\vec{x} - \vec{y})}^2 \cdot {(\vec{x} - \vec{y})}^2}$









## 1.2.2 The idea of a metric space

정의: 

- $d(x, y) = d(y, x)$
- $d(x, y) \ge 0$, $d(x, y) = 0$  iff $x=y$ 
- $d(x, y) \le d(x, z) + d(z, y)$ 



tail 집합으로 수렴을 정의하는 건 일반 위상 공간으로 넘어가기위해 필요하다. 



### Exercise. 사람들 간의 거리를 정의할 수 있는 지 확인한다. 

$d(p_1, p_2) = $ 365*24 - 최근 일년간 만난 시간

$d(p_1, p_1) = $ 365 * 24 - 365 * 24 = 0

자기와 만나는 시간이 최소이다. 거리가 작을수록 가깝다. 이는 거리의 의미를 만족한다. 

$d(p_1, p_3) \le d(p_1, p_2) + d(p_2, p_3)$

이를 만족할 수 없다. 

이렇게 두 점간의 거리가 일정하지 않은 공간이 있다.  



### Exercise. 수렴하면 한 점으로 수렴한다. 

if $p_n \rightarrow p_1$ and $p_n \rightarrow p_2$, then $p_1 = p_2$ 를 보여야 한다. 

$p_n$의 꼬리가 모두 $p_1$의 $\epsilon$ 공과 $p_2$의 $\epsilon$ 공 안에 들어와야 한다. 양 쪽 공에 들어있는 한 점을 생각하면 양쪽 공에 모두 속해야 한다. 따라서, $p_1$과 $p_2$는 $2\epsilon$ 보다 작다. $\epsilon$이 임의의 양수이므로 둘은 같은 점이다. 



### Def 1.2 stronger metric 

하나의 거리의 공에 대해 이에 속하는 공을 항상 찾을 수 있는 거리를 더 강하다고 한다. (더 강한 제약 조건이다)



### Exercise. 더 강한 쪽의 수렴하는 수열은 더 약한 쪽의 거리에서 항상 수렴한다. 



## 1.2.3 Examples of metric spaces

수 많은 거리가 정의될 수 있다. norm에서 정의될 수도 있고, 적분이나 합으로 정의되기도 한다. 





















































