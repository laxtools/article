# nana c++ 11 gui framework

새로운 C++을 사용한 간결한 GUI 프레임워크이다.
게임 쪽 IMGUI와 함께 사용할 만한 대안으로 보인다.
nanogui도 있으나 사용성 개선이 멈춰있어
nana를 사용해서 도구들을 만들어 본다.

## 연습

hierarchical csv
   - , as a main separator
   - : as a second separator
   - type specified
   - excel plugin to expand second separation

하위 과제:
 - 다국어 문자열 필드 처리  
   - std::string에서 std::wstring 변환
   - strtk 참고 : http://www.partow.net/programming/strtk/

## 계층적인 게임 데이터 (hcsv)

json으로 정의된 스키마를 읽어 hcsv 포맷을 엑셀과 DB로 읽어 오거나 hcsv 파일로
저장할 수 있다.

hcsv['row']['column']['subcolumn'] 으로 접근 가능하다.
외부 파일이나 내부 컬럼을 foreign 키 값으로 가질 수 있고 검증 가능하다.
의존 관계에 따라 파일 로딩 순서를 결정할 수 있다.

타잎:
 - 문자열
 - 숫자 (float, int8, int16, int32, int64, unsigned, float, double)
 - enum / keys

## 기능

- json으로 정의된 schema
- C++ 코드 생성 (로딩과 사용, 저장)
- 엑셀에서 로딩과 저장
- DB 테이블 생성과 import, db에서 로딩
