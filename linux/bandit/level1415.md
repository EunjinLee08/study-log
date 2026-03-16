# Bandit Level 14 → Level 15

## 🎯 목표

`localhost`의 포트 `30000`으로 `bandit14`의 비밀번호를 전송해서 다음 레벨 비밀번호를 얻는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit14` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- 이 레벨은 SSH가 아니라 **일반 TCP 소켓**으로 특정 포트에 접속해서 데이터를 주고받는 문제다.
- TCP 소켓 통신에 쓸 수 있는 도구는 여러 가지가 있다.

| 도구 | 특징 |
|------|------|
| `telnet` | 가장 간단한 텍스트 기반 TCP 클라이언트. 암호화 없음 |
| `nc` (netcat) | 범용 네트워크 도구. 연결·리슨·파일 전송 모두 가능 |
| `echo \| nc` | 파이프로 자동 입력해서 스크립트화 가능 |

- `authorized_keys`는 SSH 공개키 인증에서 **서버 측에 등록된 공개키 목록** 파일이다. 포트 30000은 SSH가 아닌 단순 TCP 서비스이므로 이 파일로는 접속할 수 없다.

### 명령어

```bash
# 방법 1: telnet으로 접속 후 비밀번호 수동 입력
telnet localhost 30000

# 방법 2: nc로 접속 후 비밀번호 수동 입력
nc localhost 30000

# 방법 3: echo + nc로 한 줄에 자동 전송
echo "bandit14 비밀번호" | nc localhost 30000
```

### 실행 결과

```bash
bandit14@bandit:~$ telnet localhost 30000
Trying 127.0.0.1...
Connected to localhost.
bandit14 비밀번호 입력
Correct!
비밀번호
```

## 📝 메모

- `telnet`은 암호화가 없어서 실제 서비스 접속에는 사용하지 않지만, 로컬에서 TCP 포트가 열려 있는지 확인하거나 간단한 텍스트 프로토콜(HTTP, SMTP 등)을 테스트할 때 유용하다.
- `nc`는 활용처가 다양하다.
  - 포트 스캔: `nc -zv localhost 30000`
  - 파일 전송: `nc -l 1234 > received.txt` / `nc localhost 1234 < file.txt`
  - 리버스 쉘: CTF에서 자주 등장하는 패턴
- `authorized_keys`는 `~/.ssh/` 디렉토리 안에 있는 SSH 공개키 목록 파일이다. 이 파일에 등록된 공개키를 가진 클라이언트는 비밀번호 없이 SSH 접속이 가능하다. SSH 프로토콜 전용이라 일반 TCP 포트에는 사용할 수 없다.
