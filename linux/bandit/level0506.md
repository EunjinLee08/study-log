# Bandit Level 5 → Level 6

## 🎯 목표

`inhere` 디렉토리 안 어딘가에 있는 파일 중 아래 세 조건을 모두 만족하는 파일에서 비밀번호를 찾는다.

- 사람이 읽을 수 있음
- 크기가 정확히 1033 bytes
- 실행 파일이 아님

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit5` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- `inhere` 안에는 `maybehere00` ~ `maybehere19`까지 20개의 디렉토리가 있고, 각 디렉토리마다 여러 파일이 존재한다. 일일이 들어가서 확인하는 건 비현실적이다.
- `find` 명령어를 사용하면 **조건을 조합해서** 원하는 파일을 한 번에 찾을 수 있다.

| 옵션 | 의미 |
|------|------|
| `-size 1033c` | 크기가 정확히 1033 bytes인 파일 (`c` = bytes) |
| `! -executable` | 실행 권한이 없는 파일 |
| `-type f` | 일반 파일만 (디렉토리 제외) |

### 명령어

```bash
cd inhere

# 세 조건을 모두 적용한 find
find . -type f -size 1033c ! -executable

# 찾은 파일 내용 출력 (파일명에 공백이 있으므로 따옴표 처리)
cat "./maybehere07/.file2"
```

### 실행 결과

```bash
bandit5@bandit:~/inhere$ find . -type f -size 1033c ! -executable
./maybehere07/.file2

bandit5@bandit:~/inhere$ cat "./maybehere07/.file2"
```

## 📝 메모

- `find`의 `-size` 옵션에서 단위 표기에 주의해야 한다.
  - `c` : bytes
  - `k` : kilobytes
  - `M` : megabytes
  - `G` : gigabytes
- `!`는 조건을 반전(NOT)시키는 연산자다. `! -executable`은 "실행 권한이 없는" 파일을 의미한다.
- `find`는 조건을 여러 개 나열하면 기본적으로 AND로 결합된다. OR 조건이 필요할 때는 `-o` 옵션을 사용한다.
- 이 레벨은 `-size 1033c` 하나만으로도 파일이 유일하게 특정되기 때문에 나머지 조건은 사실상 필터 역할을 하지 않는다.
