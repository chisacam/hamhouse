# hamhouse
햄버거집 시뮬레이션, 2019년 운영체제 프로젝트

## 목표
햄버거집 시뮬레이션

1. 계산, 요리, 배달 직원(CPU스케쥴링, RR)
2. 햄버거집 냉장고(Main Memory 스케쥴링, page_replacement)
3. 햄버거집 창고(Disk 스케쥴링, SSTF)

이상을 각각 구현하고 조합해 햄버거집을 구현합니다.
아래 제시사항을 만족해야합니다.

* 프로세스의 기준은 각각의 손님입니다.
* 메뉴는 하나일수도, 여러개일수 있습니다.
* 주문시간은 00:00~24:00까지 입니다.(하루이내)
* 한 손님에게 입력파일에 주어지는 Q만큼 서비스하면 다른 손님에게 서비스를 해줘야 합니다.
* 냉장고의 크기는 재료 50개를 수용가능하고, 창고는 무한대라고 가정합니다.
* 냉장고와 창고에서 가져오는 재료는 한번에 하나씩만 가져올 수 있습니다.
* 창고에서 재료를 가져올때는 냉장고에서 가장 오래전에 사용한 재료를 내보내야합니다.
* 창고에서 재료를 전달해주는 특수기계는 재료를 전달해주는데 0.1초가 소요되며, 마지막으로 재료를 꺼낸곳에서 대기합니다.
* 햄버거 메뉴는 새우, 닭고기 두가지 이고 각각 만드는데 110초, 100초가 소요됩니다.
* 새우 햄버거는 빵, 새우, 피클, 상추, 토마토가 각 1개씩, 닭고기 햄버거는 새우와 토마토대신 닭고기와 치즈를 사용합니다.(총 7가지 재료)
* 주문시 주문시간은 방문손님 5초, 전화주문 3초이고 금액계산 시간은 5초입니다. 이것 또한 Q에 따라 서비스해야합니다.
* 만약 손님이 전화주문을 했다면, 배달시간 200초가 필요합니다.
* 입력파일은 프로그램 실행시 이름을 전달하면 해당 이름의 파일을 읽을 수 있어야 합니다.

## 사용언어
C언어

## 입력양식
RR을 위한 퀀텀(Q)제시
번호<tab>주문시간<tab>주문방법<tab>주문메뉴
  
<pre>
Q=30
1    09:00    전화    새우,닭고기
2    05:10    방문    새우
3    10:10    방문    닭고기
...(생략)
</pre>

## 출력양식
번호<tab>주문시간<tab>주문방법<tab>요구 서비스시간(burst time)<tab>실제 서비스시간(turnaround time)

<pre>
2    05:10    방문    110    (T)
1    09:00    전화    210    (T)
3    10:10    방문    100    (T)
...(생략)
현재 냉장고 상태
빵 : n
상추 : n
피클 : n
새우 : n
토마토 : n
닭고기 : n
치즈 : n
</pre>
