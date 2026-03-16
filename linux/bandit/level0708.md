# Bandit Level 7 → Level 8

## 🎯 목표

`data.txt` 파일 안에서 `millionth`라는 단어 옆에 적힌 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit7` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- `data.txt`는 수만 줄짜리 거대한 파일이라 `cat`으로 전체를 출력해서 눈으로 찾는 건 비현실적이다.
- `grep`은 파일(또는 입력 스트림)에서 **특정 패턴이 포함된 줄만** 필터링해서 출력하는 명령어다.
- `|`(파이프)는 앞 명령어의 출력(stdout)을 뒤 명령어의 입력(stdin)으로 넘긴다.

### 명령어

```bash
# 방법1: cat으로 조회한 내용을 |로 전달하여 필터링
cat data.txt | grep millionth

# 방법2: grep에 파일 직접 지정
grep millionth data.txt
```

### 실행 결과

```bash
bandit7@bandit:~$ grep millionth data.txt
millionth	비밀번호
```

## 📝 메모

- `cat data.txt | grep millionth`와 `grep millionth data.txt`는 결과가 동일하다. 파일을 직접 지정하는 방법이 `cat`을 거치지 않아 더 효율적이다.
- `grep`의 주요 옵션:
  - `-i` : 대소문자 구분 없이 검색
  - `-n` : 매칭된 줄 번호 함께 출력
  - `-r` : 디렉토리를 재귀적으로 탐색
  - `-v` : 패턴과 **일치하지 않는** 줄만 출력 (반전)
  - `-c` : 매칭된 줄 수만 출력
- `|` 파이프는 명령어를 체이닝할 때 핵심 도구다.
