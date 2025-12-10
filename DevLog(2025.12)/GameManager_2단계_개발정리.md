
# C++ 콘솔 RPG 파이널 프로젝트 개발 로그 (2단계 초반)

## 📌 오늘 작업 범위 요약
- GameManager 클래스 최초 도입
- 전투 흐름 제어 책임을 main → GameManager로 이전
- Player / Monster에서 생존 판정(IsAlive) 역할 재정의
- 턴 처리 / 전투 종료 판정 구조 설계 및 구현 시도

---

## ✅ 변경 및 구현된 내용

### 1️⃣ Player / Monster 변경 사항

#### 🔹 IsAlive 체크 구조 변경
- 기존:
  - Player::Attack / Monster::Attack 내부에서 IsAlive 조건 검사
- 변경 후:
  - **공격 함수는 “공격 행위만 담당”**
  - 생존 여부 판단은 GameManager에서 일괄 관리

```cpp
bool Player::IsAlives() const
{
    return IsAlive;
}
```

```cpp
void Player::TakeDamage(int damage)
{
    Hp -= damage;

    if (Hp <= 0)
    {
        Hp = 0;
        IsAlive = false;
    }
}
```

📌 의미  
- Player / Monster는 “자기 상태만 관리”
- **게임 종료 판단, 전투 진행 여부는 GameManager 책임**

---

### 2️⃣ GameManager 설계 의도

#### 🔹 책임 분리
| 항목 | 담당 클래스 |
|----|----|
| 객체 생성 | GameManager |
| 전투 루프 | GameManager |
| 생존 판정 | Player / Monster |
| 게임 종료 결정 | GameManager |

---

### 3️⃣ GameManager 구현 내용

#### 🔹 멤버 구조
```cpp
class GameManager
{
private:
    Player* Playerr;
    std::vector<Monster*> Monsterr;
    bool isGameover;
    int turnCount;
};
```

- Player: 단일 객체
- Monster: 확장(웨이브)을 고려해 vector 사용

---

#### 🔹 게임 루프 구조

```cpp
void GameManager::GameLoop()
{
    while (!isGameover)
    {
        CheckBattleResult();
        if (isGameover)
            break;

        ProcessTurn();
    }
}
```

📌 흐름  
1. 전투 종료 판정
2. 종료 아니면 턴 진행

---

#### 🔹 턴 처리

```cpp
void GameManager::ProcessTurn()
{
    for (auto it : Monsterr)
        Playerr->Attack(*it);

    for (auto it : Monsterr)
        it->Attack(*Playerr);
}
```

📌 **현재 상태의 문제점**
- 모든 몬스터와 동시에 전투하는 구조
- 향후 “1 vs 1 전투”로 수정 예정

---

#### 🔹 전투 종료 판정

```cpp
void GameManager::CheckBattleResult()
{
    if (!Playerr->IsAlives())
    {
        isGameover = true;
        return;
    }

    bool anyMonsterAlive = false;

    for (auto it : Monsterr)
    {
        if (it->IsAlives())
        {
            anyMonsterAlive = true;
            break;
        }
    }

    if (!anyMonsterAlive)
        isGameover = true;
}
```

📌 핵심 포인트
- Player 사망 → 즉시 게임 종료
- 모든 몬스터 사망 시 전투 종료

---

### 4️⃣ SpawnMonster 함수 (현재 미구현)

```cpp
void GameManager::SpawnMonster()
{
    // 추후 구현 예정
}
```

#### 설계 의도
- 몬스터 생성 책임을 GameManager에 집중
- 이후 확장:
  - 몬스터 웨이브
  - 드랍 시스템
  - 전투 자동 연계

---

## ⚠️ 현재 구조의 핵심 문제 인식

### 문제 1️⃣
```text
플레이어가 모든 몬스터와 동시에 전투함
```
→ 의도와 다름

### 문제 2️⃣
```text
vector를 쓰지만 항상 전체 순회 구조
```
→ 사실상 단일 전투 개념이 깨짐

---

## 🛠️ 다음 단계에서 수정할 내용 (TODO)

### ✅ 전투 구조 수정
- Monster vector는 유지
- **항상 `Monsterr[0]`만 전투**
- 현재 몬스터 사망 시:
  - erase or pop_back
  - SpawnMonster() 호출

### ✅ SpawnMonster 구현 방향
- 새로운 Monster 객체 생성
- vector에 push_back
- 전투 대상 자동 교체

### ✅ GameManager 역할 명확화
- Player / Monster에서 전투 종료 로직 완전 제거
- GameManager만 게임 상태 판단

### ✅ 메모리 관리 점검
- Monster 제거 시 delete 여부 명확화
- 추후 unique_ptr 전환 고려 (4단계)

---

## 📌 오늘의 설계 핵심 요약

> **객체는 “상태 관리만” 하고,  
게임 흐름과 판단은 GameManager가 전담한다.**

---

✅ 상태:  
- 구조는 올바른 방향  
- 전투 방식만 1 vs 1로 다듬으면 다음 단계 진입 가능
