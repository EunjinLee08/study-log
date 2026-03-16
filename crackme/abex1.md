# [crackme] abex1 by abex

## 🎯 목표

하드 디스크를 CD-ROM으로 인식하도록 프로그램을 패치한다.

## 🛠️ 사용 도구

| 도구 | 용도 |
|------|------|
| Ghidra | 디컴파일 및 어셈블리 분석 |

---

## 🔍 문제 분석

### 실행 시 동작

프로그램을 실행하면 메시지 박스가 나타나고, 확인을 누르면 아래 메시지가 출력된다.

```
Nah... This is not a CD-ROM Drive!
```

### `GetDriveTypeA` 반환값 (첨부 html 파일 기준)

| 반환값 | 드라이브 타입 |
|--------|--------------|
| 0 | 알 수 없음 (DRIVE_UNKNOWN) |
| 1 | 유효하지 않은 경로 (DRIVE_NO_ROOT_DIR) |
| 2 | 이동식 디스크 (DRIVE_REMOVABLE) |
| 3 | 하드 디스크 (DRIVE_FIXED) |
| 4 | 네트워크 드라이브 (DRIVE_REMOTE) |
| **5** | **CD-ROM (DRIVE_CDROM)** ← 목표 |
| 6 | RAM 디스크 (DRIVE_RAMDISK) |

- 현재 하드디스크를 파라미터로 넘기면 `3`이 반환됨
- 이 값이 `5`로 반환되도록 하면 프로그램을 속일 수 있음

---

## 💡 풀이

### 디컴파일 분석 (Ghidra)

Ghidra로 디컴파일한 결과, `GetDriveTypeA` 호출 이후 반환값을 비교하는 분기 구조가 있다.
```c
UVar1 = GetDriveTypeA(&DAT_00402094);
if (UVar1 - 2 == unaff_ESI + 3) {
  MessageBoxA( (HWND) 0x0, s_Ok,_I_really_think_that_your_Hd_i_0042064,s_YEAH!_0040205e,0);
}
else {
  MessageBoxA( (HWND) 0x0, s_Nah..._This_is_not_a_CD-ROM_Driv_0040203b,s_Error_00402035,0);
}
```

```asm
; 반환값 비교
CMP   EAX, ESI         ; CD-ROM인지 확인 (5 == DRIVE_CDROM)
JZ    LAB_0040103d     ; 같으면 성공 메시지로 점프
PUSH  s_Nah...         ; 다르면 그대로 진행하여 "Not a CD-ROM" 메시지 출력
```

- **현재 동작**: `GetDriveTypeA`가 하드디스크에 대해 `3`을 반환 → `CMP EAX, ESI`가 달라서 실패 → 실패 메시지 출력
- **문제**: `GetDriveTypeA`는 Windows API로, 본 프로그램 내에서 해당 함수의 코드를 직접 수정하는 방법은 확인되지 않음

### 패치 전략

`GetDriveTypeA`의 반환값을 바꾸는 대신, **조건 점프(JZ)를 무조건 점프(JMP)로 패치**한다.

```asm
; 패치 전 (조건부 점프)
JZ    LAB_0040103d     ; EAX == 5 일 때만 성공으로 점프

; 패치 후 (무조건 점프)
JMP   LAB_0040103d     ; 항상 성공 메시지로 점프
```

### 패치 방법 (Ghidra)

1. Ghidra에서 해당 `JZ` 명령어 위치로 이동
2. 우클릭 → **Patch Instruction** 선택
3. `JZ`를 `JMP`로 수정
4. **File → Export Program** 으로 패치된 실행 파일을 내보냄

---

## ✅ 결과

패치 후 프로그램 실행 시:

```
Ok, I really think that your HD is a CD-ROM! :p
```

---

## 📝 메모

- **`JZ` vs `JMP` 차이**:
  - `JZ` (Jump if Zero): 직전 `CMP` 결과가 0(equal)일 때만 점프
  - `JMP`: 조건 없이 무조건 점프 → 비교 결과와 무관하게 성공 분기로 진입
- `GetDriveTypeA`는 Windows API로, 드라이브 루트 경로(ex: `C:\`)를 인자로 받아 드라이브 타입을 정수로 반환한다.
  - 굳이 이쪽을 건드린다면 IAT를 후킹해서 `GetDriveTypeA` 대신 가짜 판별기 프로그램으로 갈아끼우면 된다.
