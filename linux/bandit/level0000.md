# Bandit Level 0

## 🎯 목표

SSH로 bandit 서버에 최초 접속한다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit0` |
| Password | `bandit0` |

## 💡 풀이

### 핵심 개념

- `ssh`는 원격 서버에 암호화된 연결로 접속하는 명령어다.
- 기본 포트는 22이지만, `-p` 옵션으로 다른 포트를 지정할 수 있다.

### 명령어

```bash
ssh bandit0@bandit.labs.overthewire.org -p 2220
```

### 실행 결과

- bandit 서버에 접속

## 📝 메모

- 처음 접속 시 호스트 신뢰 여부를 묻는데 `yes` 입력하면 된다.
- 기본 포트(22)가 아닌 **2220**을 사용한다는 점 주의.
