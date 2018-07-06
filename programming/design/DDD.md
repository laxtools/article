# DDD (Domain Driven Design) 

복잡도를 정복하기 위한 설계 방법론.  이해가 필요하다. 



# DDD Quickly by InfoQ 

http://carfield.com.hk/document/software%2Bdesign/dddquickly.pdf

OOP in enterprise scale. Software design is an art. (아. 다익스트라!) 

Abstraction of domain. The beginning. Blueprints transformed from domain. Then, a model of the domain. 

Dig concepts and relations. 


## 언어 

Extract terminology. 
Find relations. 
Build concepts. 

## Model Driven 

- 서비스 
- 엔티티 
- 값 오브젝트 (Value Object)
- 팩토리 
- 집합 (Aggregates) 
- 리포지토리 

레이어를 얘기하지만 파티션이 더 중요하다. 

### 모듈 

게임에서 Item 모듈이 가능한가? 
ItemModule::CreateItem() 
ItemModule::AcquireItem()
컴포넌트가 더 맞다. 

### Value Object 

컴포넌트 단위, 클래스 단위로 내부에 변수를 포함하므로 큰 영향은 없다. 컴포넌트와 내부 클래스를 갖추는 것이 중요하다. 

값 타잎 추가는 생각해 볼 수 있다. 복잡도만 올라갈 수도 있다. 연산이 필요하다면 이런 클래스도 유용하다. 

### Repository 

서버에서 리포는 Scene(맵)가 같은 공간, 오브젝트 풀이 있다. DB 자체는 Repository라기 보다는 영속성만 제공한다. (DB를 직접 검색하는 일은 게임에서 없다)


## 리팩터링 

반복적인 설계 개선 과정에 가깝다. 


## 정리 

Lessons learned: 
- 일정 기간 명확한 설계 단계를 밟는다. 하루라도 좋고 한달이라도 좋다. 
- 핵심 개념들을 추출한다. 엔티티 (오브젝트 / 액터)와 컴포넌트 (와 내부 타잎들)이 핵심 
- 데이터, 이벤트, 시그널을 분리한다 
- 로깅, 네트워크, 메모리 트래킹, 타이머, 시그널, 오브젝트, 리플렉션, 데이터, DB 처리를 견고하게 한다. 
- 어려운 문제 (공간 처리)를 확실하게 해 둔다. 
- 서비스, 액터, 컴포넌트 중심으로 나누어 설계하고 구현한다. 




# 아이디어 

How to make software design a science? 

- correctness proof 
- minimum complexity 

최소 복잡도를 갖는 정확한 코드를 게임 서버 구현으로 확보한다. 

Agile preproduction with prototyping

Waterfall design phase with feedback

설계 기간이 필요하다. 시간을 갖고 정리할 시간. 게임은 반복되는 패턴이 많아 회사 단위, 개인 단위로 정리된 모델과 설계가 있어야 한다. 우리는 게임을 만들지 않는가? 

개별 패턴은 기술 발전에 따라 개선될 수 있지만 없으면 문제다. 
























































