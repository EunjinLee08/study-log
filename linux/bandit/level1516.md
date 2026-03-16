# Bandit Level 15 → Level 16

## 🎯 목표

이전 레벨과 동일하게 `localhost`의 특정 포트로 비밀번호를 전송하되, 이번엔 **SSL/TLS 암호화** 연결을 사용해야 한다. 포트는 `30001`.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit15` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- **SSL/TLS**는 네트워크 통신을 암호화하는 프로토콜이다.
  - SSL(Secure Sockets Layer)은 구버전, TLS(Transport Layer Security)는 현재 표준이다. 통상적으로 SSL이라고 불러도 실제로는 TLS를 사용한다.
  - HTTPS, SMTPS, FTPS 등 "S"가 붙은 프로토콜은 모두 TLS로 암호화된 버전이다.
- 이전 레벨에서 쓴 `telnet`이나 `nc`는 평문 통신만 가능하다. SSL/TLS 연결에는 `openssl s_client`를 사용한다.
- `openssl s_client -connect <host>:<port>`로 SSL/TLS 서버에 클라이언트로 접속할 수 있다.

### 명령어

```bash
# 방법 1: openssl s_client로 접속 후 비밀번호 수동 입력
openssl s_client -connect localhost:30001

# 방법 2: echo + openssl로 한 줄에 자동 전송
echo "jN2kgmIXJ6fShzhT2avhotn4Zcka6tnt" | openssl s_client -connect localhost:30001 -quiet
```

### 실행 결과

```bash
bandit15@bandit:~$ openssl s_client -connect localhost:30001
CONNECTED(00000003)
...
(인증서 정보 출력)
...
---
bandit15 비밀번호 입력
Correct!
비밀번호
```

## 📝 메모

- `openssl s_client` 접속 시 인증서 정보가 길게 출력된다. `---` 구분선 아래에 입력창이 나오면 비밀번호를 입력하면 된다.
- `-quiet` 옵션을 붙이면 인증서 정보 출력을 억제해서 결과만 깔끔하게 볼 수 있다. `echo | openssl`로 자동화할 때 유용하다.
- `openssl`은 SSL/TLS 관련 작업 외에도 다양한 암호화 기능을 제공한다.
  - 대칭키 암호화: `openssl enc -aes-256-cbc ...`
  - 해시 생성: `openssl dgst -sha256 파일`
  - 인증서 생성/확인: `openssl x509 ...`
  - RSA 키 생성: `openssl genrsa ...`
