# Bandit Level 3 → Level 4

## 🎯 목표

`inhere` 디렉토리 안에 숨겨진 파일에서 다음 레벨의 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit3` |
| Password | 이전 스테이지 |

## 💡 풀이

### 핵심 개념

- Linux에서 `.`(점)으로 시작하는 파일/디렉토리는 **숨김 파일**로 취급된다.
  - `ls`만 입력하면 숨김 파일은 표시되지 않는다.
  - `-a` 옵션(`--all`)을 추가해야 숨김 파일까지 모두 표시된다.
- `cd`로 디렉토리를 이동한 뒤 작업하거나, 경로를 직접 지정해서 접근할 수 있다.

### 명령어

```bash
# inhere 디렉토리로 이동
cd inhere

# 숨김 파일 포함 전체 목록 확인
ls -al

# 숨김 파일 내용 출력
cat .hidden
```

### 실행 결과

```bash
bandit3@bandit:~$ ls
inhere

bandit3@bandit:~$ cd inhere

bandit3@bandit:~/inhere$ ls
# 아무것도 출력되지 않음

bandit3@bandit:~/inhere$ ls -al
total 12
drwxr-xr-x 2 root    root    4096 Apr 23  2023 .
drwxr-xr-x 3 root    root    4096 Apr 23  2023 ..
-rw-r----- 1 bandit4 bandit3   33 Apr 23  2023 .hidden

bandit3@bandit:~/inhere$ cat .hidden
```

## 📝 메모

- `ls -al` 결과에서 `.`은 현재 디렉토리, `..`은 상위 디렉토리를 의미한다. 둘 다 숨김 항목으로 분류되어 `-a` 없이는 보이지 않는다.
- 숨김 파일 여부는 파일 시스템 속성이 아니라 순전히 **파일 이름이 `.`으로 시작하는지** 여부로만 결정된다. 즉 보안 기능이 아니라 단순한 컨벤션이다.
