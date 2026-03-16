# Bandit Level 11 → Level 12

## 🎯 목표

`data.txt`의 내용은 **ROT13**으로 인코딩되어 있다. 복원해서 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit11` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- **ROT13(Rotate 13)** 은 알파벳을 13칸씩 밀어서 치환하는 고전 암호다.
  - `a → n`, `b → o`, ..., `m → z`, `n → a`, ..., `z → m`
  - 알파벳이 26자이므로 ROT13을 두 번 적용하면 원문으로 돌아온다. 즉 **인코딩과 디코딩이 동일한 연산**이다.
  - 숫자와 특수문자는 변환하지 않는다.
- `tr` 명령어는 문자를 **1대1 대응으로 치환**하는 명령어다.
  - `tr 'abc' 'xyz'`는 `a→x`, `b→y`, `c→z`로 각 문자를 대응된 문자로 바꾼다.
  - 범위 표기(`a-z`)를 지원해서 알파벳 전체를 간결하게 표현할 수 있다.

### ROT13 치환 규칙 시각화

```
원문:  a b c d e f g h i j k l m  n o p q r s t u v w x y z
ROT13: n o p q r s t u v w x y z  a b c d e f g h i j k l m
```

### 명령어

```bash
cat data.txt | tr 'a-zA-Z' 'n-za-mN-ZA-M'
```

### `tr` 인수 해석

| 인수 | 풀어쓰면 | 의미 |
|------|----------|------|
| `a-z` | a b c ... m n o ... z | 소문자 원문 |
| `n-za-m` | n o p ... z a b ... m | 소문자를 13칸 밀어서 대응 |
| `A-Z` | A B C ... M N O ... Z | 대문자 원문 |
| `N-ZA-M` | N O P ... Z A B ... M | 대문자를 13칸 밀어서 대응 |

### 실행 결과

```bash
bandit11@bandit:~$ cat data.txt
원문

bandit11@bandit:~$ cat data.txt | tr 'a-zA-Z' 'n-za-mN-ZA-M'
비밀번호
```

## 📝 메모

- ROT13은 보안성이 전혀 없는 인코딩이지만, 스포일러 방지나 가벼운 난독화 목적으로 인터넷 게시판 등에서 쓰이기도 한다.
- `tr`은 치환 외에도 문자 **삭제(`-d`)** 와 **압축(`-s`)** 기능도 있다.
  ```bash
  # 숫자 모두 삭제
  echo "abc123" | tr -d '0-9'   # abc

  # 연속된 공백을 하나로 압축
  echo "a   b   c" | tr -s ' '  # a b c
  ```
- ROT13과 달리 ROT47은 ASCII 출력 가능 문자(33~126) 전체를 47칸씩 밀어서 치환한다. 숫자와 특수문자도 변환된다.
