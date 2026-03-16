# Bandit Level 13 → Level 14

## 🎯 목표

비밀번호 대신 **SSH 개인키**가 주어진다. 이 키로 `bandit14` 계정에 접속한 뒤, `/etc/bandit_pass/bandit14` 파일에서 비밀번호를 읽는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit13` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- SSH 인증 방식은 크게 두 가지다.
  - **비밀번호 인증**: 지금까지 해온 방식. 접속 시 비밀번호 입력.
  - **공개키 인증(Public Key Authentication)**: 개인키(private key)와 공개키(public key) 쌍을 이용. 서버에 공개키를 등록해두면, 클라이언트는 개인키로 인증한다.
- **RSA**는 대표적인 비대칭 암호 알고리즘이다.
  - 공개키로 암호화 → 개인키로만 복호화 가능
  - SSH에서는 서버가 공개키로 챌린지를 암호화하고, 클라이언트가 개인키로 복호화해서 신원을 증명한다.
- `ssh -i` 옵션으로 인증에 사용할 개인키 파일을 지정할 수 있다.

### 명령어

```bash
# bandit13으로 접속 후 개인키 확인
cat sshkey.private

# 개인키로 localhost의 bandit14 계정에 접속
ssh -i sshkey.private bandit14@localhost -p 2220

# bandit14로 접속 후 비밀번호 파일 읽기
cat /etc/bandit_pass/bandit14
```

### 실행 결과

```bash
bandit13@bandit:~$ ls
sshkey.private

bandit13@bandit:~$ ssh -i sshkey.private bandit14@localhost -p 2220
...
bandit14@bandit:~$          ← bandit14로 접속 성공

bandit14@bandit:~$ cat /etc/bandit_pass/bandit14
비밀번호
```

## 📝 메모

- 개인키 파일은 **권한이 너무 열려 있으면 SSH가 거부**한다. 실제 환경에서 개인키를 쓸 때는 `chmod 600 sshkey.private`으로 소유자만 읽을 수 있도록 설정해야 한다.
- `localhost`는 현재 접속 중인 서버 자신을 가리키는 주소다. 즉 bandit 서버 안에서 bandit 서버로 다시 SSH 접속하는 것이다.
- `/etc/bandit_pass/` 디렉토리에는 각 레벨의 비밀번호가 저장되어 있다. 해당 유저만 읽을 수 있도록 권한이 설정되어 있어서, `bandit14`로 접속해야만 `bandit14`의 비밀번호를 읽을 수 있다.
- SSH 공개키 인증은 비밀번호 없이 서버에 접속할 수 있어서, 서버 자동화(스크립트, CI/CD)나 보안 강화 목적으로 널리 쓰인다.
