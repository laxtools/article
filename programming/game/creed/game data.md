# 계층적인 게임 데이터 (hcsv)

json으로 정의된 스키마를 읽어 hcsv 포맷을 엑셀과 DB로 읽어 오거나 hcsv 파일로
저장할 수 있다.

hcsv['row']['column']['subcolumn'] 으로 접근 가능하다.
외부 파일이나 내부 컬럼을 foreign 키 값으로 가질 수 있고 검증 가능하다.
의존 관계에 따라 파일 로딩 순서를 결정할 수 있다.

타잎:
 - 문자열 (std::string, utf8)
 - 숫자 (int8, int16, int32, int64, unsigned types, float, double)
 - enum 
 - pair 

## 기능

- json으로 정의된 schema
- C++ 코드 생성 (로딩과 사용, 저장)
- 엑셀에서 로딩과 저장
- DB 테이블 생성과 import, db에서 로딩


## library 

https://haptork.github.io/easyLambda/

훨씬 크지만 참고할 수 있는 훌륭한 구현으로 보인다. 
개념들을 익히고 게임의 개념들을 추가하고 통합해서 
멋진 틀로 만들도록 한다. 

## excel 

https://github.com/tfussell/xlnt

excel 포맷이 공개되었다고 들었는데 좋은 라이브러리들이 많이 나왔다. 
C++에서도 많은 라이브러리들이 나오고 있다. 

hcsv 대신 excel을 DB로 하는 도구를 만들 수 있고 이 쪽 방향으로 진행해도 좋아 보인다. 

스키마 정의와 변환 / 통합 기능이 있어야 한다. 

## 확장 

데이터 언어일 뿐만 아니라 메세지 정의 언어로 동작할 수 있다.  json으로 정의하면 IDL 파서를 만들 필요가 없다. json으로 구성해서 코드 생성을 하는 구조로 만들 수 있다. 

### 스키마 

```json
{

 include: [ file1, file2, ... ], 

 namespace: game, 

  enum : {

    fields : [ ]

   } , 

  struct : { 

    name: position, 

    fields: []

   }, 

   message : {

    name: req_move,

    topic:  game.req_move, 

    fields: {  position: pos, int32: id, ...   }  

 }

}

```



### csv 

```javascript
{

  table: { 

    name: skill, 

    fields : { int32 : index, float32: range, category: kind }
  }

 enum : { 

   name: category, 

   fields : [

      ....

   ]

  }

}

```





## 정리 

간단한 아이디어 확장으로 게임 데이터, 메세지, DB 스키마를 포괄하는 구조를 확보했다. 키 값을 추가하고 기능을 만들면 자동으로 전체 기능이 확장된다. 이와 같이 의미를 갖는 스키마와 코드 생성은 개발 효율을 올리는데 매우 중요하다. 



