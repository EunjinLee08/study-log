# 🖥️ LeetCode Q1. Concatenation of Array 🔥 Easy

## 📌 문제 설명
길이가 n인 정수 배열이 주어졌을 때, `ans[i] == nums[i]`. `ans[i + n] == nums[i]`인 배열 ans를 return 하라.

## ⌨️ 입력 예시
```plaintext
nums = [1, 2, 1]
```

## ⌨️ 출력 예시
```plaintext
ans = [1, 2, 1, 1, 2, 1]
```

## 🖥️ 풀이 코드
```c
#include <stdio.h>
#include <stdlib.h>

int* getConcatenation(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize * 2;
    int* ans = (int*)malloc(sizeof(int) * numsSize * 2);

    for (int i = 0; i < numsSize; i++) {
        ans[i] = nums[i];
        ans[i + numsSize] = nums[i];
    }
```

## 💡 풀이 포인트
- malloc을 사용하여 주어진 배열 길이의 2배 길이를 갖는 배열 생성
- LeetCode의 문제 풀이 특성상 정답 배열의 길이를 함께 설정해야 LeetCode 채점 프로그램에서 정답을 어디까지 읽을 것인지를 파악할 수 있음

## 📝 배운 점
- 국제 코테 사이트인 LeetCode의 사용법
- 정답 제출 시 returnSize를 반드시 설정해야 정상적으로 답이 제출되는 특이사항

## 📚 참고
https://leetcode.com/problems/concatenation-of-array/?envType=problem-list-v2&envId=dsa-linear-shoal-array-i
