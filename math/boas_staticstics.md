# [Boas] Probability and Statistics 

Notes and Solutions to selected problems. Trying all problems takes really long time. 



# 1. Introduction 



$p = \frac{number \, of \, event \, E}{total \, number \, of \, events}$

$\implies p = \frac{m(E)}{m(U)}$, when U is the spac and E is the event set. 

m is a measure. Counting measure for discrete events and integral for continuous events. 



## Problems 



### 1 

- select three-digit number randomly. 
- probability of the unit digit is 7? 
- probability of the hundred digit is 7? 



**idea:** 

- imagine cards with numbers from 100 to 999
- what is m(U)? 
- what is m(E)? 



#### probability of the unit digit is 7? 

**solution 1:**

m(U) = 1000 

m(E = unit digit is 7) = **7 

from 0 to 9, it has one 7. 

from 00 to 99, it has ten of {0, ..., 9}

from 100 to 999, it has 9 of {00 ~ 99}s. 

therefore, cards have 10 * 9 = 90 of 7s on unit digit. 

m(E) = 90. 

P(E) = 90 / 1000 = 9/100



**solution 2:** 

Instead of thinking in cards, imagine a slot machine with three digits. 

if the machie has 7 fixed on unit digit, then only ten and hundred digit can change. 

one hundred digit = { 1, ..., 9 }

ten digit = { 0, ..., 9 }

10 * 9 = 90 = m(E) 



#### probability of the hundred digit is 7? 

Following slot machine approach, we fix hundred digit to 7. 

unit digit = { 0, ..., 9}

ten digit = { 0, ..., 9}

m(E) = 10 * 10 = 100 

p(E) = 100/1000 = 1/10



### 2

- three coins are tossed
- the probability of two heads and one tails ? 
- the probability of first two are heads and the thrid tails? 
- if at least two are heads, what is the probability that all are heads? 



####the probability of two heads and one tails ? 



**solution 1:**

p(heads) = 1/2 = p(tails) 

E = { (H, H, T), (H, T, H), (T, H, H)}

m(U) = 2 * 2 * 2 = 8 

p(E) = m(E)/m(U) = 3/8



**solution 2:** 

Consider any event E in U of tossing 3 coins, then $p(E) = (1/2)*(1/2)*(1/2) = 1/8$ . 

The case with 2 heads and one tail is to select one toss fixed to Tails, automatically selecting Heads from other tosses. 

Therefore, the p(E = 2 heads and 1 tails) = $3 * p(E)$. 



#### the probability of first two are heads and the thrid tails? 

E = { (H, H, T)}

p(E) = m(E)/m(U) = 1 / 8 



#### if at least two are heads, what is the probability that all are heads? 

$p( E | A ) = p(E \cap A ) / P(A) $, where A = { e | e has at least two heads } and E = { e | all are heads }

or 

U = { e | at least two are heads }

E = { e | all are heads }

U = { (H, H, T), (H, T, H), (H, H, H), (T, H, H)}

E = { (H, H, H)}

p(E) = m(E) / m(U) = 1/4 



### 3

- a box has 2 white, 3 black, and 4 red balls. 
- a ball drawn randomly 
- the probability of black ball drawn? 
- the probability of not red? 



####the probability of black ball drawn? 

**solution 1:** 

m(U) = 9 

m(E) = 3 

p(E) = m(E) / m(U) = 3/9 = 1/3 



**solution 2:** 

we can think of this as permutation of $U = \{ w_1, w_2, b_1, b_2, b_3, r_1, r_2, r_3, r_4 \}$, counting the cases of first one is black. 

total number of permutations = 9!

the cases with first one black = 3 * 8!

then the probability = 3 * 8! / 9! = 3 / 9 = 1/3



####the probability of not red? 

**solution 1:**

m(U) = 9 

m(E) = m(B) + m(W), where B is the events that black ball is drawn and W is for white. 

m(B) = 3, m(W) = 2 

p(E) = 5/9 



**solution 2:** 

m(E) = 9 - m(R) 

m(E) = 9 - 4 = 5

p(E) = 5/9 



### 4 

- A single card drawn at random from a shuffled deck. 
- the probability of red card? 
- the probability of the ace of hearts? 
- the probability of either a three or a five? 
- the probability of an ace or red or both? 



#### the probability of red card? 

**facts:** 

- poker cards are 52. 
- spade : black 
- heart : red
- club : black 
- diamond : red 
- 2 ~ 10, J, Q, K, A



**solution 1:** 

m(U) = 52 when drawing a card. 

m(E) = 13 * 2 = 26 

p(E) = 1/2 



**solution 2:** 

m(U) = 2 in terms of color  (red / black)

m(E) = 1 

p(E) = 1/2



How to formalize the above arguments? 



#### the probability of the ace of hearts? 

m(E) = 1 

p(E) = 1/52



#### the probability of either a three or a five? 

$m(E) = m(E_1) + m(E_2)$, where $E_1$ : three drawn, $E_2$ : five drawn. and $E_1 \cap E_2$ is empty. 

m(E) = 4 + 4 

p(E) = 8 / 52 = 4 / 13 = 0.3076



#### the probability of an ace or red or both? 

m(Ace) = 4

m(Red) = 26 

m(Both) = 2

m(E = Ace or Red or Both) = m(Ace) + m(Red) - m(Both) = 28 since Ace and Red are counted "Both times" more. 

p(E) = 28/52 = 7/13



#### poker quiz 

lots more complex calculations are in poker game. 

add my own problems when proper. 



### 9

- trying to find instrument A in a laboratory 
- someone put both A and B into identical boxes mixed at random on a shelf
- lab has 3 A's and 7 B's. 
- the probability that you get an A from a box? 
- the probability that you get an A from a box after taking out B from a box 



#### the probability that you get an A from a box? 

**clear:** 

- only A and B are in boxes. 
- 10 instruments are all. 



**solution:** 

m(U) = 10 

m(E) = 3

p(E) = 3/10 



#### the probability that you get an A from a box after taking out B from a box 

m(U) = 9 

m(E) = 3 

p(E) = 3/9 = 1/3



# 2. Sample Space

a set of all possible mutually exclusive outcomes is a sample space. 

- uniform / non-uniform sample space



**Probability:** 

- sample space
- probabilities associated with the points (elements of the space) 
- probability = sum of the probability of points in the event
  - event is a subset of the sample space

샘플 공간은 확률의 합이 1인 서로 소인 집합들로 나눠지면 된다. 



## Problems 

### 11

- nonuniform sample spaces for three tosses 

**solution:** 

ttt, tth, tht, thh, htt, hth, hht, hhh

we can split this set into mutually exclusive ones. 

{ ttt }, {tth, tht, thh, htt, hth, hht, hhh}

what is the rule of this sample space? 

### 14

- two dice are thrown. 
- a) the probability of forming a two-digit number greater than 33? 
- b) the probability of forming a two-digit number greaer than or equal to 42? 
- c) can you find a two-digit number (or numbers) s.t. the probability of being able to form a larger number is the same as the probability of being able to form a smaller number? 

Following the note, the order of numbers does not matter to form a two-digit number. We can change the sample space reflecting this fact. 

s(a, b) = { a:b, b:a}. For example, s(1, 2) = { 1:2, 2:1 }

Then, the sample space is: 

s(1, 1), s(1, 2), s(1, 3), s(1, 4), s(1, 5), s(1, 6), 

s(2, 2), s(2, 3), s(2, 4), s(2, 5), s(2, 6) 

s(3, 3), s(3, 4), s(3, 5), s(3, 6)

s(4, 4), s(4, 5), s(4, 6)

s(5, 5), s(5, 6)

s(6, 6)

#### the probability of forming a two-digit number greater than 33? 

Two form a number great that 33

ten digit can be { 3, 4, 5, 6} 

unit digit can be for each ten digit: 

unit( 3 ) = { 4, 5, 6}

unit( 4 ) = { 1, 2, 3, 4, 5, 6 } = unit( 5 ) = unit( 6 )

The changed sample space does not help since the probabilities are all different. uniform sample space is easier to calculate by counting in this example (discrete case?). 

Since the order can be reversed, the set is extended. 

E(uint(3)) = { 3:4, 3:5, 3:6, 4:3, 5:3, 6: 3 }

E(uint(4)) = { 4:1, 4:2, 4:3, 4:4, 4:5, 4:6, 1:4, 2:4, 3:4, 5:4, 6:4 }

E(uint(5)) = { 5:1, 5:2, 5:3, 5:4, 5:5, 5:6, 1:5, 2:5, 3:5, 4:5, 6:5 }

E(uint(6)) = { 6:1, 6:2, 6:3, 6:4, 6:5, 6:6, 1:6, 2:6, 3:6, 4:6, 5:6 }

$\cup$ E = { 3:4, 3:5, 3:6, 4:3, 5:3, 6:3 }

$\cup$ { 4:1, 4:2, 4:4, 4:5, 4:6, 1:4, 2:4, 5:4, 6:4 }

$\cup$  { 5:1, 5:2, 5:5, 5:6, 1:5, 2:5, 6:5 }

$\cup$  { 6:1, 6:2, 6:6, 1:6, 2:6 }

m(E) = 6 + 9 + 7 + 5 = 27 

p(E) = 27 / 36 = 3/4

Is it easier to calculate $E^c$ ? Since the set is smaller, it would be eaiser. 

Is there a algebraic formula to calculate the probability in general? 



#### the probability of forming a two-digit number greaer than or equal to 42? 

unit(4) = { 2, 3, 4, 5, 6 }

uint(5) = { 1, 2, ..., 6 }

uint(6) = { 1, 2, .., 6}

E(uint(4)) = { 4:2, 4:3, 4:4, 4:5, 4:6, 2:4, 3:4, 5:4, 6:4}

E(uint(5)) = { 5:1, 5:2, 5:3, 5:4, 5:5, 5:6, 1:5, 2:5, 3:5, 4:5, 6:5 }

E(uint(6)) = { 6:1, 6:2, 6:3, 6:4, 6:5, 6:6, 1:6, 2:6, 3:6, 4:6, 5:6 }

$\cup$ E = { 4:2, 4:3, 4:4, 4:5, 4:6, 2:4, 3:4, 5:4, 6:4}

$\cup$ { 5:1, 5:2, 5:3, 5:5, 5:6, 1:5, 2:5, 3:5, 6:5 }

$\cup$ { 6:1, 6:2, 6:3, 6:6, 1:6, 2:6, 3:6 }

m(E) = 9 + 9 + 7 = 25 

p(E) = 25 / 36 

Constructing E with (2.4) is a lot simple. 



#### c) 

The number splits the sample space of (2.4) into two sets with equal numbers. 

The order of digit does not matter, since we can change the position. For example, 

2:4 is equal to 4:2. This means the number needs to cut (2.4) around diagonal. 

Let's pick 51 as the number, then below two lines of 5:1 are in E. Then $m(E) \ge 12$ . We need to find 6 more elements, but are 7 more elements that are $\ge$ 51. 

Let's pick 52 as the number, then below two lines from 5:2 are in E.  Then $m(E) \ge 11$. We need to find 7 more elements. 4:5, 4:6, 3:5, 3:6, 2:5, 2:6, 1:6 are those elements. If larger includes the same number, 52 is that number.



#### Finding a sample space

The process is tedious. There must be a clear sample space for each solutions. 

Instead of looking at sample space, we can think about domain, the number. 

domain is a set of (Toss1, Toss2). 

range is a set of numbers with Max(Toss1, Toss2) Min( Toss1, Toss2): 

C1  C2  C3 C4 C5 C6

11  21  31 41 51 61

​      22  32 42 52 62

​            33 43 53 63 

​                 44 54 64

​                       55 65

​                             66

$ f : \{(t1, t2)\} \rightarrow N$, where N is the above numbers. 

The inverse image is a set of tosses that maps to the number. For example, 

$f^{-1}(\{21\}) = \{ (1, 2), (2, 1) \}$

C1, ..., C6 are column sets. C1 = {11}, C2={21, 22}, and so on.

$|f^{-1}(C6)| = 11$, and $|f^{-1}(C5) = 9|$ 

If there is a splitting number, then it must be in C5. 

Since the size of inverse image decreases by 2 when the number is increased by 1 up to 54, we can increase to 52. 

$|f^{-1}(C5 - \{51\})| = 18$ 



Above function constructs a sample space. 



### 17

- Two dice thrown
- The first die is even
- the number on the second is $\lt 4$



#### Finding a sample space

possible samples under the conditions:

2:1, 2:2, 2:3

4:1, 4:2, 4:3

6:1, 6:2, 6:3



#### a) possible sums and probabilities

sums = { 3,       4,     5,      6,    7,     8,    9 }

probs = { 1/9, 1/9, 2/9, 1/9, 2/9, 1/9, 1/9}



#### b) the most probable sum

5 and 7



#### c) the probability that the sum is even

p(4) + p(6) + p(8) = 1/3



# 3. Probability Theorems

$P(AB) = P(A) \cdot P_A(B) $ means $P(A \cap B) = P(A) \cdot P(B | A) $

The proof uses uniform probability. 
$$
P(AB) = \frac{N(AB)}{N}
\\
P(A) = \frac{N(A)}{N}
\\
P_A(B) = \frac{N(AB)}{N(A)}
$$
The independence condition is $P(B) = P_A(B)$, which is 
$$
\frac{N(B)}{N} = \frac{N(AB)}{N(A)}
$$
This is surprising.

When throwing two dice, the events A = first die is 3 and B = second die is 2 are known as independent. The calculation shows that the above ratio is same. (why??)

This is a definition. Can it be constructed from other definitions? 

The definition is saying that the probability of B does not change under its confinement into A if they are independent. 

This seems to be related to the core concept of probability. It must be an advanced theory. But some more arguments can be made with uniform probability.

First dice events $f_1, f_2, ..., f_6$ splits the space of the second dice events $s_1, s_2, ..., s_6$, meaning $m(f_1 \cap s_1) = m(f_2 \cap s_1) = ...$. This is one case. 



Another property:
$$
P(A+B) = P(A) + P(B) - P(AB)
$$


























#### 











