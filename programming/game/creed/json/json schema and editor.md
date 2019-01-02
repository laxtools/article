# json schema and editor 



# 개요

게임 데이터는 XML이나 csv, DB를 주로 사용해 왔다. XML은 verbosity가 높은 편이고, csv와 DB는 관계형 모델을 사용하여 제약이 일부 있다.  

가장 많이 사용되는 흐름은 Excel에서 관계형 모델을 정의하고 csv로 export 하고 이를 처리하는 코드를 Excel이나 별도 스키마 정의에서 파악하여 생성하는 방식이다. 엑셀이 기획자들이 많이 사용하는 툴이기 때문에 편한 면이 있다. 

관계형 모델은 좋지만 유연하지 못 하다. 앞으로도 그래야 할까? 스킬 작업을 클라이언트와 서버 모두에서 진행한 경험이 있다. 이 때 서버는 CSV를 사용했다. 유연하지 못 한 면이 매우 번거로우며 클라이언트와 데이터 호환이 잘 안 된다.  json은 매우 유연하다. 

json을 사용할 때 단점은 편집이 어렵다는 점이다. 트리 형태의 데이터 편집을 쉽게 할 편집 도구가 아직 없다. 스키마가 있다면 여기에 맞춰 UI를 자동으로 만들고 빠르게 편집하게 할 수 있다. 

편집기가 사용하기 편하고 매우 강력해야 한다. 그리고 나머지는 간단하게 구현할 수 있다. 나머지는 다음과 같다. 

- 스키마 구성 
- 스키마에 따른 코드 생성 
- 스키마에 따른 검증 코드 
- 바이너리 변환 
- 바이너리 로딩과 검증 



# 사용성 

스키마를 정의한다. 이 부분은 json으로 구성한다. 그리고 툴을 실행한다. 스키마를 열거나 이미 있는 데이터 파일을 열면 해당 스키마에 따라 화면을 구성한다. 

화면은 CSV이나 엑셀처럼 한 줄 씩 보인다. 폴딩 기능이 있으므로 전체를 줄이거나 전체를 늘리거나 현재 라인만 늘리거나 줄일 수 있다. 

방향키, CTRL 조합으로 옮겨다닌다. F2를 누르면 해당 항목을 편집할 수 있다. 텍스트, 셀 , 노드 단위의 복사와 붙이기가 가능하다. 필터링 기능으로 특정 항목들만 볼 수 있다. 예를 들면, 'id : regex or ...' 와 같은 형식으로 찾을 수 있다. 엑셀과 같은 기능을 구현하기는 쉽지 않으므로 lua 스크립트를 사용할 수 있도록 한다.  

이와 같은 마법은 많은 노력을 필요로 한다. UI 작업을 많이 해서 잘 정리해야 한다. 

엑셀과 액세스 등 다른 편집기의 사용 경험도 그렇게 좋은 편은 아니다. UE3의 속성 편집기와 같이 스크립트의 데이터를 자유롭게 바로 편집하는 구조는 매우 강력하다. 이를 코드 생성을 통해 강력한 도구를 만든다. 



# 스키마



## 타잎 



### 구조 타잎

- struct
  - nesting
- enum 



### 필드 타잎 

- int 
  - i 8 / 16 / 32 / 64 
  - u 8 / 16 / 32 / 64
- float / double 
- string / ustring



### 컨테이너 

- vec 
- map 



### constraint 

- key 
  - primary key 
  - unique key 
  - foreign key 
- range 
  - min / max 



## 스키마 정의 

###Inception

```json 
{
  "User": {
    "Id": "String KEY",
    "MyCharacter": "Character"
  },

  "Character": {
    "Name": "String Key",
    "Exp": "Integer",
    "Level": "Integer",
    "Hp": "Integer",
    "Mp": "Integer",

    "Inventory": "[Item]",

    "QuickSlot": "<Integer, Item>",
    "EquippedItem": "<String, Item>"
  },

  "Item": {
    "Type": "String"
  }
}
```

ifun 엔진의 ORM 예시인데 간결하고 괜찮다. 위 정도면 충분해 보인다. Range는 나중에 추가할 수 있다. C++ 코드에서 사용되므로 Integer 대신 i8 / i32 등 타잎 구분을 세분화 한다. 

MMORPG는 100~200개 정도의 테이블을 사용한다. 따라서, struct 기준으로는 2~500개 정도 될 것으로 보인다. 

위에서 몇 가지 개선해야 할 점은 다음과 같다. 

- 포함되는 타잎 여부 
- 값 범위 지정 
- 타잎 참조 순서 고려
  - DB와 코드의 차이에 기인



## c# / c++ 코드 

```c++
struct User
{
    std::string Id; 
    Character MyCharacter; 
}; 

bool LoadUser(); 

result<bool, User*> FindUser(const std::string& Id) const; 

struct Character
{
    
};
```

대략 위와 같이 키로 검색하고 로딩하는 코드를 포함하여 생성한다.  Default 값은 타잎별로 적절하게 설정되도록 한다. 



# 자료 



http://json-schema.org

- json 스키마 
- validation과 문서화에 집중 



https://www.ifunfactory.com/engine/documents/reference/ko/object2.html

- ifunfactory의 ORM 정의 예시 



