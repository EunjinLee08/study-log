# Bandit Level 9 → Level 10

## 🎯 목표

`data.txt`는 바이너리가 섞인 파일이다. 그 안에서 **사람이 읽을 수 있는 문자열** 중 `=`로 시작하는 줄에서 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit9` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- `data.txt`는 바이너리 데이터가 섞여 있어서 `cat`으로 열면 터미널이 깨진 문자로 가득 찬다.
- `strings` 명령어는 바이너리 파일에서 **일정 길이 이상의 연속된 ASCII 문자열만** 추출해서 출력한다.
- `strings` 출력 결과에서 `grep`으로 `=`를 포함한 줄만 필터링하면 바로 비밀번호를 찾을 수 있다.

### 명령어

```bash
# strings로 ASCII 문자열만 추출 후 grep으로 = 포함 줄 필터링
strings data.txt | grep "="
```

### 실행 결과

```bash
bandit9@bandit:~$ strings data.txt | grep "="
========== the
========== password
========== is
========== 비밀번호
```

## 📝 메모

- `strings`의 기본 최소 문자열 길이는 **4자**다. 즉 4글자 미만의 ASCII 문자열은 출력되지 않는다. `-n` 옵션으로 변경할 수 있다.
- `strings`는 바이너리 파일에서 숨겨진 문자열을 찾을 때 사용되므로, 리버싱에서도 자주 쓰인다.
- `strings | grep` 조합은 바이너리가 섞인 파일에서 특정 패턴을 찾을 때 사용할 수 있다.
