# Bandit Level 0 → Level 1

## 🎯 목표

홈 디렉토리에 저장된 `readme` 파일에서 다음 레벨의 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit0` |
| Password | `bandit0` |

## 💡 풀이

### 핵심 개념

- `ls`는 현재 디렉토리의 파일 목록을 보여주는 명령어다.
  - `-a` 옵션: 숨김 파일(`.`으로 시작하는 파일)도 표시
  - `-l` 옵션: 파일 권한, 소유자, 크기, 날짜 등 상세 정보 표시
- `cat`은 파일의 내용을 터미널에 출력하는 명령어다.

### 명령어

```bash
# 현재 디렉토리 파일 목록 확인
ls -al

# readme 파일 내용 출력
cat readme
```

### 실행 결과

```
bandit0@bandit:~$ ls -al
total 24
drwxr-xr-x  2 root    root    4096 Apr 23  2023 .
drwxr-xr-x 70 root    root    4096 Apr 23  2023 ..
-rw-r--r--  1 root    root     220 Jan  6  2022 .bash_logout
-rw-r--r--  1 root    root    3526 Jan  6  2022 .bashrc
-rw-r--r--  1 root    root     807 Jan  6  2022 .profile
-rw-r-----  1 bandit1 bandit0   33 Apr 23  2023 readme

bandit0@bandit:~$ cat readme
```

## 📝 메모

- `readme` 파일의 소유자는 `bandit1`, 그룹은 `bandit0`이다. 즉 다음 레벨 유저만 소유하고, 현재 유저는 그룹 권한으로 읽을 수 있다.
