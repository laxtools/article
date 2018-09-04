# heap corruption 

Windows Exception Code 0xc000374 를 디버깅 하는 과정을 적는다. 

# 사례1. 로컬 vector에서 크래시

- std::vector의 insert 중 vector의 기존 메모리 해제에서도 크래시 발생 
  - lock()을 호출하고 진행 
    - 쓰레드 관련 이슈 없음 
  - 함수 로컬 변수 vector 
- 다른 쓰레드들을 보면 대부분 대기 
  - IO 대기 (네트워크)
  - 열심히 실행 중인 다른 쓰레드는 없음 

다음과 같은 사실을 추정할 수 있다. 

- 자주 할당하고 해제하는 메모리에서 heap corruption이 발생 
  - 다른 사례에서도 STL의 deallocate에서만 발생 

- lock()이 있고 for 루프로 순회하므로 오래 걸릴 때가 있을 수 있음 
  - 이 때 해당 메모리를 침범하여 쓰는 경우 발생 가정 
  - 인접한 메모리를 할당한 곳에서 침범 

vector 메모리를 할당할 때 이전에 해당 메모리 영역을 갖고 있던 곳에서 overrun이 발생했을 가능성이 가장 높다. 



# 할당 / 해제 함수들 

- new / NEW /  delete 



# 잠재적인 위험 함수들 

- memcpy, memset, memmove
- 배열 인덱스 오류
- strcpy, sprintf

많이 쓰이고 있어 다음과 같은 개선이 필요하다. 
- 안전한 함수로 모두 변경 
 - memcpy_s, strcpy_s, snprintf_s, memmove_s
- memset 전수 조사  
 - 조건 체크 모두 추가 
- 배열 전수 조사 
 - 인덱스 범위 체크 전체 조사 
 - 포인터 + 위치 형태도 배열로 보고 전체 조사 

