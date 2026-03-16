# Bandit Level 10 → Level 11

## 🎯 목표

`data.txt`에 Base64로 인코딩된 데이터가 담겨 있다. 디코딩해서 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit10` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- **Base64**는 바이너리 데이터를 ASCII 문자열로 표현하는 인코딩 방식이다.
  - 64개의 문자(`A-Z`, `a-z`, `0-9`, `+`, `/`)만 사용하고, 끝에 `=` 패딩이 붙는 것이 특징이다.
  - 암호화가 아닌 **인코딩**이므로 키 없이 누구나 디코딩할 수 있다.
- `base64` 명령어로 인코딩/디코딩을 모두 수행할 수 있다.
  - 기본 실행: 인코딩
  - `-d` 옵션: 디코딩

### 명령어

```bash
# 방법 1: 파일 직접 디코딩
base64 -d data.txt

# 방법 2: 파이프 사용
cat data.txt | base64 -d
```

### 실행 결과

```bash
bandit10@bandit:~$ cat data.txt
원문

bandit10@bandit:~$ base64 -d data.txt
The password is 비밀번호
```

## 📝 메모

- Base64 인코딩된 문자열은 끝에 `=` 또는 `==` 패딩이 붙는 경우가 많아서 육안으로도 어느 정도 식별이 가능하다.
- Base64는 암호화가 아니라는 점이 중요하다. 이메일 첨부파일, JWT 토큰, 웹에서 이미지를 텍스트로 전송할 때 등 **데이터 전송 형식**으로 주로 쓰인다.
- 터미널에서 문자열을 직접 디코딩하고 싶을 때는 `echo`와 파이프를 조합할 수 있다.
  ```bash
  echo "VGhlIHBhc3N3b3Jk" | base64 -d
  ```
- 반대로 인코딩할 때는 `-d` 없이 사용한다.
  ```bash
  echo "hello" | base64
  # aGVsbG8K
  ```
