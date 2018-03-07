# 물리 현상의 동기화 

 - delay 
   - propagation 
   - processing 
     - server / client 

 - information 
   - event 
   - state


## A very simple synchronization scenario 

 2 body simulation in 3d with force event 

 2개의 강체가 힘을 이벤트로 받아서 3차원 상에서 움직일 때 

 initial condition: 
  - shape of body 
    - sphere for simplicity 
  - mass   
  - collision objects 
    - none for simplicity 
	- add walls later

 event: 
  - force (3d vector) 
    - input 
	- collision

 input event can be generated any time.

 state: 
  - position 
  - velocity 

 simulation difference
   - state (position and velocity) differences of two simuation nodes at a given time

Q1. find sync algorithms. 


Q2. analyze those algorithms in terms of simulation differences over time, delay and force. 


Q3. determine durable sync algorithms for human recognition. 


Q4. find proper game design under limitations of sync algorithms. 


### sync algorithms - sketch 

스케치가 필요하다. 기존 게임들에서 사용한 동기화 방식을 기초로 
아이디어를 더하고 비틀면서 살펴본다. 

시스템 A 상에서 시간 t에 발생한 이벤트, $e_t$, 가 시스템 B로 전파된다. 이는 일정한 지연을 갖고 도착한다. 

$e_{t+delay}$ 를 적용할 경우 이미 $delay$ 시간 만큼 두 시스템 간의 상태 차이가 발생한다.  RTS에서 사용하는 방식은 일정 시간 이벤트를 모아서 한번에 동시에 처리하는 방식이다. 










## extension to n-body 

 still two nodes. 

 add more solid sphere bodies up to N. 

 analyze algorithms with N body. 

 
