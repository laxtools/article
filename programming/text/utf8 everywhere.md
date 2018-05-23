# UTF8 Everywhere 

http://utf8everywhere.org/

의견일 수도 있고 가야할 방향일 수도 있다. 윈도우를 제외한 다른 플래폼은 이 방향으로 이미 전환했다. 언리얼 4의 경우 UTF16LE를 사용하고 있다. 마음에 걸리는 부분이다. 그래도 로그, 다국어 지원 등 여러 이슈를 해결하려면 이 방향이 맞아 보인다. 자료를 정리하고 결론을 내야 한다. 



## 현재  

윈도우 서버일 경우 wstring, wchar_t를 그대로 사용한다.  DB도 이를 전달한다. 일반 문자열은 string을 사용한다. 로그 파일은 시스템 인코딩을 사용한다. 다른 선택들이 다양하게 있겠지만 현재 많이 본 방식은 이렇다. 

다른 인코딩을 사용할 경우 변환한다. 로그, DB, 클라이언트 (플래폼 별?) 모두 변환이 필요하다. 



### 다국어 처리 디버깅 







# 자료 



## 언리얼 4 

http://api.unrealengine.com/KOR/Programming/UnrealArchitecture/StringHandling/CharacterEncoding/

소스 코드에 버그가 발생하는 예를 설명한다.  정확하게 알 필요가 있다. 















