# Bandit Level 6 → Level 7

## 🎯 목표

**서버 어딘가에** 아래 세 조건을 모두 만족하는 파일에서 비밀번호를 찾는다.

- 소유 유저(owner): `bandit7`
- 소유 그룹(group): `bandit6`
- 크기: 33 bytes

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit6` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- 이전 레벨은 `inhere` 디렉토리 안에서만 찾으면 됐지만, 이번엔 **서버 전체(`/`)** 를 탐색해야 한다.
- `find /`로 루트부터 탐색하면 접근 권한이 없는 수많은 디렉토리에서 `Permission denied` 에러가 쏟아진다.
- `2>/dev/null`로 표준 에러(stderr)를 버리면 에러 메시지를 제거하고 실제 결과만 깔끔하게 볼 수 있다.

| 옵션 | 의미 |
|------|------|
| `-user bandit7` | 소유 유저가 `bandit7`인 파일 |
| `-group bandit6` | 소유 그룹이 `bandit6`인 파일 |
| `-size 33c` | 크기가 정확히 33 bytes인 파일 |
| `2>/dev/null` | 표준 에러(Permission denied 등)를 `/dev/null`로 버림 |

### 명령어

```bash
# Permission denied 에러를 숨기고 조건에 맞는 파일만 출력
find / -user bandit7 -group bandit6 -size 33c 2>/dev/null

# 찾은 파일 내용 출력
cat /var/lib/dpkg/info/bandit7.password
```

### 실행 결과

```bash
bandit6@bandit:~$ find / -user bandit7 -group bandit6 -size 33c 2>/dev/null
/var/lib/dpkg/info/bandit7.password

bandit6@bandit:~$ cat /var/lib/dpkg/info/bandit7.password
```

## 📝 메모

- `2>/dev/null`은 매우 자주 쓰이는 패턴이다. 의미를 분해하면 다음과 같다.
  - `2` : 표준 에러(stderr)를 가리키는 파일 디스크립터 번호
  - `>` : 리디렉션 연산자
  - `/dev/null` : 데이터를 버리는 특수 파일
  - 즉, "에러 출력을 `/dev/null`에 버려라"는 의미다.
- 참고로 표준 출력(stdout)은 `1`, 표준 에러(stderr)는 `2`다. `>/dev/null`은 `1>/dev/null`의 축약이다.
- `2>/dev/null` 없이 실행하면 `Permission denied`가 수백 줄 쏟아져서 정작 원하는 결과를 찾기 어렵다.
