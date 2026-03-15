# Bandit Level 2 → Level 3

## 🎯 목표

홈 디렉토리에 있는 `spaces in this filename`이라는 이름의 파일에서 다음 레벨의 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit2` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

- 쉘은 공백(` `)을 **인수 구분자**로 해석한다.
  - 즉 `cat spaces in this filename`은 `spaces`, `in`, `this`, `filename` 네 개의 파일을 읽으라는 명령으로 해석된다.
- 공백이 포함된 파일 이름을 다루는 방법은 두 가지다.
  1. **따옴표로 감싸기**: `cat "spaces in this filename"`
  2. **백슬래시(`\`)로 공백 이스케이프**: `cat spaces\ in\ this\ filename`
- 탭(Tab) 키로 자동완성하면 쉘이 자동으로 이스케이프 처리해준다.

### 명령어

```bash
# 방법 1: 따옴표로 감싸기
cat "spaces in this filename"

# 방법 2: 백슬래시로 이스케이프
cat spaces\ in\ this\ filename

# 방법 3: Tab 자동완성 활용 (추천)
cat sp[Tab]  # 쉘이 나머지를 자동 완성해줌
```

### 실행 결과

```bash
bandit2@bandit:~$ ls
spaces in this filename

bandit2@bandit:~$ cat "spaces in this filename"
```

## 📝 메모

- Tab 자동완성은 공백 파일 이름뿐 아니라 특수문자가 포함된 파일 이름 전반에 걸쳐 유용하다. 쉘이 알아서 이스케이프 처리를 해주기 때문에 가장 실수가 적은 방법이다.
- 작은따옴표(`'`)와 큰따옴표(`"`) 모두 사용 가능하지만, 큰따옴표 안에서는 `$`, `` ` ``, `\` 같은 특수문자가 여전히 해석된다는 차이가 있다. 단순한 파일명에는 둘 다 동일하게 작동한다.
