# Bandit Level 4 → Level 5

## 🎯 목표

`inhere` 디렉토리 안의 여러 파일 중 **사람이 읽을 수 있는(human-readable)** 파일에서 다음 레벨의 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit4` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- `inhere` 디렉토리에는 `-file00` ~ `-file09`까지 10개의 파일이 있다.
- 대부분은 바이너리(binary) 파일이고, 하나만 ASCII 텍스트(사람이 읽을 수 있는) 파일이다.
- 파일 이름이 `-`로 시작하므로 Level 2에서처럼 그냥 `cat`으로는 읽을 수 없다.
  - `cat ./-file00` 형태로 경로를 명시하거나 `cat < -file00` 형태로 읽어야 한다.
- `file` 명령어로 파일 타입을 미리 확인하면 일일이 열어볼 필요 없이 텍스트 파일을 빠르게 찾을 수 있다.

### 명령어

```bash
# inhere 디렉토리로 이동
cd inhere

# 방법 1: file 명령어로 파일 타입 한번에 확인 (추천)
file ./*

# 방법 2: 파일을 하나씩 직접 열어서 확인
cat ./-file00
cat ./-file01
# ... 반복
```

### 실행 결과

```bash
bandit4@bandit:~$ cd inhere
bandit4@bandit:~/inhere$ file ./*
./-file00: data
./-file01: data
./-file02: data
./-file03: data
./-file04: data
./-file05: data
./-file06: data
./-file07: ASCII text          ← 이 파일이 정답
./-file08: data
./-file09: data

bandit4@bandit:~/inhere$ cat ./-file07
lrIWWI6bB37kxfiCQZqUdOIYfr6eEeqR
```

## 📝 메모

- `file` 명령어는 파일의 확장자가 아닌 **파일 내용의 매직 바이트(magic bytes)** 를 분석해서 타입을 판별한다. 확장자가 없거나 잘못된 경우에도 정확히 동작한다.
- `file ./*`에서 `*`는 글로브(glob) 패턴으로, 현재 디렉토리의 모든 파일에 `file` 명령어를 한꺼번에 적용한다.
- 바이너리 파일을 `cat`으로 열면 터미널이 깨진 문자로 도배되는 경우가 있다. 이때는 `reset` 명령어로 터미널을 초기화할 수 있다.
