# Cloud Service 

아직 사용해 본 적이 거의 없다. AWS에 Linux instance를 만들어 본 적만 있고 이런 저런 얘기는 들었다. 

google은 compute engine이란 이름으로 VM 서비스를 제공한다. 분단위 과금으로 무료 범위 안에서 쓸 수 있다면 사용을 시작해 보는 것도 좋을 듯 하다. 최종적인 서비스 환경을 갖추고 설치하고 관리하기 위한 인프라를 선택해야 한다. windows를 굳이 고집할 필요는 없어 보인다. 그런데 Linux 가 더 편리한가? 플래폼 호환을 유지하는 것이 필요하다. Linux와 Windows 모두에서 동작하고 양쪽에서 성능을 골고루 제공하는 서버. c++를 주 언어로 사용하는 이유이기도 하다. 

## Compute Engine 

https://cloud.google.com/compute/

무료 평가판 서비스가 있으므로 사용해 본다. 



## Cloud SQL 

MySQL 서비스를 제공한다. 인프라 관리 비용을 줄이기 위해선 이쪽이 나을 듯 하다. OS는 Linux, DB는 Cloud SQL(MySQL)을 사용한다. 서버들은 container를 갖고 확장 및 축소를 처리한다 (켜고 끄고도 진행)



## Linux 환경 

VirtualBox로 Linux 환경을 갖춘다.  Linux도 점점 나아지고 있다. 좀 많이 느리다. Server 로 실행하고 desktop은 사용하지 않고 작은 크기로 딱 서버 개발에만 사용할 정도로 사용한다. 

Visual Studio로 서버 개발을 할 수 있도록 환경을 정리하고 빌드 / 디버깅 등을 Visual Studio로 진행한다. 어려움은 있겠지만 양쪽으로 개발하고 주기적인 빌드와 테스트만 가끔 실행하는 방식으로 하면 효율은 유지될 것으로 보인다. 























