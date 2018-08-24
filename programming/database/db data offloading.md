# db data offloading

시간이 지나면 데이터가 증가한다. 쿼리도 느려질 가능성이 매우 높다. MMORPG에서는 월드 통합에 따라 데이터가 급격하게 늘어날 수 있다. 따라서, 오래 접근하지 않은 데이터를 보관용 테이블에 넣고 접근 시 꺼내 오는 방법을 생각해 본다. 

예시로 item 테이블을 살핀다. 게임에서 가장 데이터가 많은 테이블이다. 



## 알고리즘 

두 가지 연산이 있다. 하나는 offloading, 하나는 loading이다. 

offloading은 캐릭터 테이블 접근 시간을 기준으로 일정 기간 이상 접근하지 않은 캐릭터의 아이템들에 대해 ItemOffload 테이블로 옮긴다.  주기적인 작업이다. 서비스 영향을 줄이기 위해 조금씩 단게적으로 반복해서 작업한다. 

loading은 캐릭터 테이블에 접근 시 발생한다. 오프로딩 된 데이터를 Item 테이블로 옮겨오는 작업이다. insert into .. select from으로 진행된다.  트랜잭션 부하를 최소화하여 진행한다. 그래도 인덱스 테이블 등의 작업은 피할 수 없다. 

offloading의 시간이 가장 중요한 파라미터이다. loading이 발생하는 횟수도 중요하다.  이를 평가할 수 있으려면 마지막 접속 시간과 재방문 주기의 분포를 알아야 한다. 게임에 따라 다르겠으나 적절한 offloading 시간 설정으로 전체적인 이득은 얻을 수 있어 보인다. 

이 항목들의 수치화와 각 연산의 비용에 따른 이익을 측정할 수 있어야 한다.  알고리즘이 의존하는 테이블 내 항목의 개수 분포도 영향을 미친다. 



## 데이터 분석 

실제 운영 중인 게임을 대상으로 offloading 대상 캐릭터 수와 비율을 측정한다. 재접속 기간과 비율은 기록이 없을 가능성이 높은데 확인해야 한다. 만약 이 비율이 적합하다면 오프로딩 알고리즘을 적용할 수 있다. 



## 관련 자료 

https://blogs.oracle.com/datawarehousing/big-data-sql-quick-start-offloading-part2

- 오라클에서 Hadoop을 사용한 offloading 기법과 쿼리에 대한 설명이다. 

https://www.ibm.com/developerworks/library/ba-offloading-informix-data-spark/index.html

- Informix에서 Spark을 사용한 offloading과 로딩 기법에 대한 설명이다. 















