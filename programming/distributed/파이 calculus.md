# pi calculus 

 names 

 - channel and / or variable 
 - P | Q 
 - c(x).P : input
 - c~<y> : output 

 - !P : copy (replication of P) 
 - (\nu x) P : x is local to P
 - nil 


http://courses.cs.vt.edu/cs5204/fall09-kafura/Papers/PICalculus/Pi-Calculus-Introduction.pdf

# Intro

 b#a.S | b(c).c#d.P -> S | a#d.P -> S | P

서버의 프린터 채널인 a를 전송하고 
채널 b를 통해 받은 a 채널로 d를 보내는 흐름 

채널 자체를 보낼 수 있는 것이 가장 큰 코너스톤이라고 함 


migrating local scopes 때문에 표현력이 좋다고 한다. 

(@a)(P|Q) P와 Q에 제한된 채널 a를 만든다. 
다른 계산과 다른 점은 a를 다른 프로세스로 보낼 수 있다는 점이다. 


nil, a#x.P, a(x).P, t(tau), P+Q (P or Q), P | Q (P and Q), 

if x = y then P, if x != y, then P

(:x) P

comment: # for bar, : for \nu 

bn(P) : bound names in P 
fn(P) : free names in P

fn(P, Q) = fn(P) \union fn(Q) 

substitution : { x / y } maps y to x. 
{ x_1 ... x_n / y_1 ... y_n } maps y_i to x_i. 

\sigma range over substitutions 

unary operators has precedence over binary operators. 

(:x)P | Q + R means (((:x)P) | Q) + R

# 정리 

간결한 언어로 증명이 필요한 중요한 프로토콜이나 흐름을 설계할 때 사용 가능하다. 
익숙해져야 할 부분이 많고 어려운 개념들을 포함한 전문 영역으로 훈련이 많이 필요하다. 




