# navi+  

navigation mesh with collision shapes. 

- 직관적인 논리로는 완벽 
- 관건 
  - 충돌 처리의 성능 
  - 동적인 충돌체와 네비매시의 연동 
  - 빈 네비 공간의 높이 포함 속성 태깅 

# 목표 

- 충돌과 네비매시의 통합 
- 동적인 충돌체
  - 네비매시의 통합 
- 길찾기 
  - 에이전트 크기 반영 
  - 충돌 정보의 반영 
  - 이동 형태의 반영 
    - Walking
    - Flying 
    - Jump    
    - 복합 충돌체와 애님
- 충돌 
  - AABB / OBB 
  - Sphere 
  - Cast
    - Ray 
    - Sphere
    - Disk 
- 공유
  - 정적인 충돌 정보 
  - 네비 매시 정보
  - 동적인 정보만 분리
- 툴 
  - Unity Exporter / Visualizer 
  - UE4 Exporter / Visualizer


# 기반 

- Recast / Detour 
  - Height Value 
  - Property (Tag)
- Sparse Octree 
  - Collision Shapes 
    - Bullet


# 진행 

- PoC 
  - UE4 
  - 알고리즘 클라이언트 내 구현
  - Visualizer 

- 테스트와 함께 반복 진행 
  - Iterative 
  - performance 


# 아이디어 

- 충돌과 길찾기 분리 
  -	길 찾은 후 이동 하면서 충돌하면 다시 찾기 
  		Avoidance / Group 이동을 이 방법으로 구현 
  		충돌 공간만 동적으로 다루면 됨 
    - 매시 정보는 충돌 처리에만 통합 
  
위의 아이디어로 진행하면서 세부 아이디어를 만든다. 



# 자료 



https://accu.org/index.php/journals/1838

- 네비게이션 매시 생성 알고리즘
- 좋은 논문. 좋은 연습문제들을 포함 
- 미코노켄 (Recast) 방법을 개선하는 게 좋을 듯 하다. 

Voxel Flood Fill이 생각난다. 2D 채우기처럼 3D 빈공간 채우기를 하는 것. 그러고 나서 걷어내고 찬 공간을 처리하는 방법. 같은 개념인가? 메모리를 효율적으로 사용하기위해 Sparse Voxel Tree와 같은 구조를 생각해 볼 수 있다. 
























