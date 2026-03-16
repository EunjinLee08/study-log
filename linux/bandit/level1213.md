# Bandit Level 12 → Level 13

## 🎯 목표

`data.txt`는 hexdump 형태로 저장된 파일이다. 이를 바이너리로 복원한 뒤, **여러 겹으로 압축된** 파일을 모두 해제해서 비밀번호를 찾는다.

## 🔑 접속 정보

| 항목 | 값 |
|------|----|
| Host | `bandit.labs.overthewire.org` |
| Port | `2220` |
| Username | `bandit12` |
| Password | 이전 스테이지에서 확인 |

## 💡 풀이

### 핵심 개념

| 명령어 | 용도 |
|--------|------|
| `xxd -r` | hexdump → 바이너리 파일로 역변환 |
| `file` | 파일 타입(압축 형식) 확인 |
| `gzip -d` / `gunzip` | gzip(`.gz`) 압축 해제 |
| `bunzip2` | bzip2(`.bz2`) 압축 해제 |
| `tar -xzvf` | tar+gzip(`.tar.gz`) 압축 해제 |
| `tar -xvf` | tar+bzip2(`.tar.bz2`) 압축 해제 |

- `gzip`, `bzip2`는 파일 이름에 올바른 확장자가 붙어 있어야 압축 해제가 된다. 확장자가 없으면 직접 붙여줘야 한다.
- `/tmp` 아래에 작업 디렉토리를 만들어서 진행한다. 홈 디렉토리는 쓰기 권한이 없을 수 있다.

### 명령어 흐름

```bash
# 1. /tmp 아래에 작업 디렉토리 생성 후 파일 복사
mkdir /tmp/mywork
cp ~/data.txt /tmp/mywork/
cd /tmp/mywork

# 2. hexdump → 바이너리 역변환
xxd -r data.txt > data.bin

# 3. 이후 file로 타입 확인 → 해당 방식으로 압축 해제 반복
file data.bin
```

### 압축 해제 반복 과정

```bash
# gzip으로 압축된 경우
mv data.bin data.bin.gz
gzip -d data.bin.gz          # → data.bin 생성

# bzip2로 압축된 경우
mv data.bin data.bin.bz2
bunzip2 data.bin.bz2         # → data.bin 생성

# tar(gzip)으로 압축된 경우
mv data.bin data.bin.tar.gz
tar -xzvf data.bin.tar.gz

# tar(bzip2)으로 압축된 경우
mv data.bin data.bin.tar.bz2
tar -xvf data.bin.tar.bz2
```

### 최종 결과

```bash
# file 명령어로 ASCII text가 나올 때까지 반복
# 최종적으로 data8.bin이 ASCII text 파일로 나옴

bandit12@bandit:/tmp/mywork$ file data8.bin
data8.bin: ASCII text

bandit12@bandit:/tmp/mywork$ cat data8.bin
The password is 비밀번호
```

## 📝 메모

- 이 레벨의 핵심은 **`file` 명령어를 압축 해제 전마다 반복 실행**해서 현재 어떤 형식인지 확인하는 습관이다. 확장자가 없어도 `file`은 내용을 분석해서 정확한 타입을 알려준다.
- `xxd`는 hexdump 생성(`xxd 파일`)과 역변환(`xxd -r 파일`) 모두 가능하다. hexdump 형식을 보면 왼쪽에 오프셋, 가운데에 hex 값, 오른쪽에 ASCII 미리보기가 표시된다.
- `tar` 주요 옵션 정리:
  - `x` : 압축 해제(extract)
  - `z` : gzip 형식
  - `j` : bzip2 형식
  - `v` : 처리 과정 출력(verbose)
  - `f` : 파일 이름 지정 (항상 마지막에 위치)
- 현대 `tar`는 `-z`, `-j` 없이 `tar -xvf 파일명`만 입력해도 형식을 자동 감지해서 압축 해제해준다.
