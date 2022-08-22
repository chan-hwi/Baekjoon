# [Platinum IV] XORanges - 17627 

[문제 링크](https://www.acmicpc.net/problem/17627) 

### 성능 요약

메모리: 9052 KB, 시간: 156 ms

### 분류

자료 구조(data_structures), 세그먼트 트리(segtree)

### 문제 설명

<p>Janez loves oranges! So he made a scanner for oranges. With a cameras and a Raspberry Pi 3b+ computer, he started creating 3D images of oranges. His image processor is not a very good one, so the only output he gets is a 32-bit integer, which holds information about the holes on the peel. A 32- bit integer <em>D</em> is represented as a sequence of 32 digits (bits) each of which is one or zero. If we start from 0 we can obtain <em>D</em> by adding 2<em><sup>i</sup></em> for every <em>i</em>-th bit that is equal to one. More formally the number <em>D</em> is represented by the sequence <em>d</em><sub>31</sub>, <em>d</em><sub>30</sub>, ..., <em>d</em><sub>0</sub> when D = <em>d</em><sub>31</sub>·2<sup>31</sup> + <em>d</em><sub>30</sub>·2<sup>30</sup> + ... + <em>d</em><sub>1</sub>·2<sup>1</sup> + <em>d</em><sub>0</sub>·2<sup>0</sup>. For example, 13 is represented as 0, ..., 0, 1, 1, 0, 1.</p>

<p>Janez scanned <em>n</em> oranges; however, sometimes he decides to rescan one of the oranges (<em>i</em>-th orange) during the execution of your program. This means that from this scan on, he uses the updated value for the <em>i</em>-th orange.</p>

<p>Janez wants to analyse those oranges. He finds exclusive or (XOR) operation very interesting, so he decides to make some calculations. He selects a range of oranges from <em>l</em> to <em>u</em> (where <em>l</em> ≤ <em>u</em>) and wants to find out the value of XOR of all elements in that range, all pairs of consecutive elements in that range, all sequences 3 of consecutive elements and so on up to the sequence of <em>u</em> - <em>l</em> + 1consecutive elements (all elements in the range).</p>

<p>I.e. If <em>l</em> = 2 and <em>u</em> = 4 and there is an array of scanned values <em>A</em>, program should return the value of <em>a</em><sub>2</sub> ⊕ <em>a</em><sub>3</sub> ⊕ <em>a</em><sub>4</sub> ⊕ (<em>a</em><sub>2</sub> ⊕ <em>a</em><sub>3</sub>) ⊕ (<em>a</em><sub>3</sub> ⊕ <em>a</em><sub>4</sub>) ⊕ (<em>a</em><sub>2</sub> ⊕ <em>a</em><sub>3</sub> ⊕ <em>a</em><sub>4</sub>), where ⊕ represents the XOR and <em>a<sub>i</sub></em> represents the <em>i</em>-th element in array <em>A</em>.</p>

<p>Let XOR operation be defined as:</p>

<p>If the <em>i</em>-th bit of the first value is the same as the <em>i</em>-th bit of the second value, the <em>i</em>-th bit of the result is 0; If the <em>i</em>-th bit of the first value is different as the <em>i</em>-th bit of the second value, the <em>i</em>-th bit of the result is 1.</p>

### 입력 

 <p>In the first line of the input there are 2 positive integers <em>n</em> and <em>q</em> (total number of rescans and queries - actions).</p>

<p>In the next line, there are <em>n</em> space-separated non-negative integers, which represent values of the array <em>A</em> (scan results for oranges). Element <em>a<sub>i</sub></em> contains the value for <em>i</em>-th orange. Index <em>i</em> starts with 1.</p>

<p>Actions are described in the next <em>q</em> lines with three space-separated positive integers.</p>

<p>If the action type is 1 (rescan), the first integer equals 1 and is followed by <em>i</em> (index of an orange that Janez wants to rescan) and <em>j</em> (the result of the rescan of the <em>i</em>-th orange).</p>

<p>If the action type is 2 (query), the first integer equals 2 and is followed by <em>l</em> and <em>u</em>.</p>

### 출력 

 <p>You should print exactly one integer for each query with the matching result for the query. You should print every value in a new line. Note that the <em>i</em>-th line of the output should match the result of the <em>i</em>-th query.</p>

