# ���� ������ ����ȭ 

 - delay 
   - propagation 
   - processing 
     - server / client 

 - information 
   - event 
   - state


## A very simple synchronization scenario 

 2 body simulation in 3d with force event 

 2���� ��ü�� ���� �̺�Ʈ�� �޾Ƽ� 3���� �󿡼� ������ �� 

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

����ġ�� �ʿ��ϴ�. ���� ���ӵ鿡�� ����� ����ȭ ����� ���ʷ� 
���̵� ���ϰ� ��Ʋ�鼭 ���캻��. 

�ý��� A �󿡼� �ð� t�� �߻��� �̺�Ʈ, $e_t$, �� �ý��� B�� ���ĵȴ�. �̴� ������ ������ ���� �����Ѵ�. 

$e_{t+delay}$ �� ������ ��� �̹� $delay$ �ð� ��ŭ �� �ý��� ���� ���� ���̰� �߻��Ѵ�.  RTS���� ����ϴ� ����� ���� �ð� �̺�Ʈ�� ��Ƽ� �ѹ��� ���ÿ� ó���ϴ� ����̴�. 










## extension to n-body 

 still two nodes. 

 add more solid sphere bodies up to N. 

 analyze algorithms with N body. 

 
