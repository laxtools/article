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

������ ������ ä���� a�� �����ϰ� 
ä�� b�� ���� ���� a ä�η� d�� ������ �帧 

ä�� ��ü�� ���� �� �ִ� ���� ���� ū �ڳʽ����̶�� �� 


migrating local scopes ������ ǥ������ ���ٰ� �Ѵ�. 

(@a)(P|Q) P�� Q�� ���ѵ� ä�� a�� �����. 
�ٸ� ���� �ٸ� ���� a�� �ٸ� ���μ����� ���� �� �ִٴ� ���̴�. 


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

# ���� 

������ ���� ������ �ʿ��� �߿��� ���������̳� �帧�� ������ �� ��� �����ϴ�. 
�ͼ������� �� �κ��� ���� ����� ������� ������ ���� �������� �Ʒ��� ���� �ʿ��ϴ�. 




