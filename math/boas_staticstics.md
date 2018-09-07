# [Boas] Probability and Statistics 

Notes and Solutions to exercises. 



# Introduction 



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

















#### 











