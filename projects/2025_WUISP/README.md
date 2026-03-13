# Wazuh 기반 웹 공격 패턴 분석 및 실시간 대응 시스템

> 웹 서버를 대상으로 한 공격을 **실시간으로 탐지**하고, 사람의 개입 없이 **공격자 IP를 자동 차단**하는 보안 파이프라인 구축 프로젝트

**기간:** 2025.08 ~ 2026.01 (약 6개월)  
**역할:** 팀장(PM) — 전체 아키텍처 설계, Wazuh Rule/Active Response 구현, 실습 환경 구축 주도

---

## 프로젝트 배경

일반적인 보안 실습은 공격 성공/실패 여부 확인에 그치며, 실제 **탐지 → 분석 → 자동 대응**으로 이어지는 구조를 다루지 않는다. 본 프로젝트는 실제 운영 환경에 가까운 보안 파이프라인을 직접 설계·구현하여, 공격 발생 시 시스템이 즉시 탐지하고 자동 차단되도록 하는 것을 목표로 한다.

---

## 시스템 아키텍처

```
[Attacker: Kali Linux]
        |
        | SQL Injection / Brute Force 공격
        ↓
[Victim: Rocky Linux]
  - DVWA (취약한 웹 서버)
  - ModSecurity2 + OWASP CRS  → Injection-based Attack 탐지
  - Suricata (IDS)             → Brute Force 트래픽 탐지
  - Wazuh Agent               → 로그 수집 및 서버로 전달
        |
        | 보안 로그 전달
        ↓
[Wazuh Server: Rocky Linux]
  - Wazuh Manager / Dashboard / Indexer
  - 로그 분석 및 Rule 매칭
  - Active Response → Agent에 차단 명령 전송
        |
        | 차단 명령 (wazuh-nft-block.sh)
        ↓
[Victim: nftables]
  - 커널 레벨에서 공격자 IP 즉시 차단
```

**핵심 플로우:** 공격 → 탐지(ModSecurity/Suricata) → 분석(Wazuh Rule 매칭) → 자동 차단(nftables IP 차단)

---

## 탐지 대상 및 대응 전략

### Injection-based Attack (ModSecurity + OWASP CRS)
- SQL Injection, XSS 등 웹 애플리케이션 레이어 공격 탐지
- OWASP CRS 룰셋 기반 누적 점수 방식 적용 (단순 룰 매칭 + 임계값 초과 시 차단)
- 탐지 룰: OWASP CRS (`REQUEST-941-APPLICATION-ATTACK-XSS.conf`, `REQUEST-942-APPLICATION-ATTACK-SQLI.conf` 조정)
- Wazuh Rule 30411 매칭 → Active Response 트리거

### Brute Force Attack (Suricata)
- 60초 내 동일 IP의 POST 요청이 10회 이상 발생 시 탐지
- 커스텀 Suricata 룰 직접 작성 (`/var/lib/suricata/rules/local.rules`)
- Suricata JSON 로그를 Wazuh가 인식할 수 있도록 Custom Decoder 작성
- Wazuh Rule 100301 매칭 → Active Response 트리거

---

## 핵심 구현 내용

### 1. Wazuh Active Response 설정 (`/var/ossec/etc/ossec.conf`)
탐지된 룰 ID에 따라 Agent에서 `wazuh-nft-block.sh` 스크립트를 실행하도록 설정.  
공격자 IP를 JSON 데이터에서 추출하여 nftables `wazuh_block` Set에 추가, 커널 레벨 패킷 drop 수행.

### 2. Suricata Custom Decoder 작성 (`/var/ossec/etc/decoders/local_decoder.xml`)
Suricata가 생성한 JSON 로그의 `src_ip` 필드를 Wazuh firewall-drop Active Response에서 사용하는 `srcip` 필드로 매핑.

### 3. nftables 기반 차단 구조
`wazuh_block` Set에 등록된 IP를 chain input에서 drop 처리.  
timeout 600초 설정으로 실습 환경에서 자동 해제.

---

## 실습 결과

| 공격 유형 | 탐지 도구 | 탐지 결과 | 차단 결과 |
|---|---|---|---|
| SQL Injection | ModSecurity + Wazuh | HTTP 403 Forbidden 반환 | nftables IP 차단 성공 |
| Brute Force | Suricata + Wazuh | 로그 수집 및 Rule 매칭 | nftables IP 차단 성공 |

---

## 기술 스택

| 구분 | 기술 |
|---|---|
| SIEM | Wazuh (Manager / Agent / Dashboard) |
| WAF | ModSecurity2 + OWASP CRS |
| IDS | Suricata |
| 방화벽 | nftables |
| OS | Rocky Linux 9, Kali Linux |
| 취약한 웹 환경 | DVWA (Damn Vulnerable Web Application) |

---

## 참고 블로그

구현 과정의 단계별 기록은 아래 Velog 시리즈에서 확인할 수 있습니다.  
[WUISP 25 시리즈 보기](https://velog.io/@eunjinlee24/series/WUISP-25)
