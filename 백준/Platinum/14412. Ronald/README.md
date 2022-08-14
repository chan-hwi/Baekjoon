# [Platinum V] Ronald - 14412 

[문제 링크](https://www.acmicpc.net/problem/14412) 

### 성능 요약

메모리: 3016 KB, 시간: 52 ms

### 분류

애드 혹(ad_hoc), 구성적(constructive), 자료 구조(data_structures), 분리 집합(disjoint_set), 그래프 이론(graphs)

### 문제 설명

<p>There are N cities in one country that are connected with two-way air links. One crazy airline president, Ronald Krump, often changes the flight schedule. More precisely, every day he does the following:</p>

<ul>
	<li>chooses one of the cities,</li>
	<li>introduces flights from that city towards all other cities where these flights do not currently exist, and at the same time cancels all existing flights from that city</li>
</ul>

<p>For instance, if from city 5 flights exist towards cities 1 and 2, but not towards cities 3 and 4, after Krump’s change, there will exist flights from city 5 towards cities 3 and 4, but not towards cities 1 and 2.</p>

<p>The citizens of this country are wondering if a day could come when the flight schedule will be complete. In other words, when between each two different cities a (direct) flight will exist. Write a programme that will, based on the current flight schedule, determine whether it is possible to have a Complete Day, or whether this will never happen, no matter what moves Krump makes.</p>

### 입력 

 <p>The first line of input contains the integer N (2 ≤ N ≤ 1000), the number of cities. The cities are labeled with numbers from 1 to N.</p>

<p>The second line contains the integer M (0 ≤ M < N*(N-1)/2), the number of current flights.</p>

<p>Each of the following M lines contains two different numbers, the labels of the cities that are currently connected.</p>

### 출력 

 <p>The first and only line of output must contain DA (Croatian for “yes”) or NE (Croatian for “no”).</p>

