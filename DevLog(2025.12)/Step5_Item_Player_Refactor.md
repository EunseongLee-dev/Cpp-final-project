# Step 5 – Item / Player 구조 수정 및 설계 정리

## 개요
이번 수정의 핵심 목표는 **Item–Player 상호작용 구조를 명확히 분리**하고,  
아이템 종류가 늘어나도 코드 수정 범위를 최소화하는 것이다.

특히 다음 문제를 해결하는 데 집중했다.

- Item에서 Player의 private 멤버 접근 문제
- 소비 아이템(포션) 타입별 처리 방식
- Item 추상 클래스 관련 컴파일 에러
- Inventory 출력 시 Value가 0으로만 출력되던 문제

---

## 1. Player Getter 함수 추가 이유

### 문제
Item에서 효과 적용 후 상태 출력이 필요했지만,
Player의 HP / MP / ATK는 `private` 이라 직접 접근 불가.

### 해결
- **상태 변경은 Player가 책임**
- Item은 “요청”만 하고 출력은 Player가 담당

### 추가된 함수
- `Heal(int)`
- `Mana(int)`
- `ATKUP(int)`
- `EquipWeapon(int)`
- `EquipArmor(int)`

👉 **캡슐화 유지 + 책임 분리**

---

## 2. Item::Use 설계 방향

### 공통 규칙
- Item은 Player의 내부 구조를 모른다
- Item은 Player의 인터페이스만 호출한다

```cpp
void Player::UseItem(Item* item)
{
    item->Use(*this);
}
```

👉 Item은 **행동 정의**, Player는 **상태 관리**

---

## 3. Consumable(소비 아이템) 처리 방식

### 고민 지점
- 포션 타입이 여러 개 (Heal / Mana / ATK)
- 타입마다 함수를 나눌 것인가?

### 선택한 방식
```cpp
void Consumable::Use(Player& player)
{
    switch (ctype)
    {
    case ConsumableType::Heal:
        player.Heal(value);
        break;
    case ConsumableType::Mana:
        player.Mana(value);
        break;
    case ConsumableType::Atk:
        player.ATKUP(value);
        break;
    }
}
```

### 이유
- 현재 프로젝트 규모에서는 **switch가 가독성과 유지보수 면에서 최적**
- 포션 수십 종으로 늘어날 경우 → 클래스 분리 고려

---

## 4. ItemType 컴파일 에러 원인

### 에러
```
ItemType : 알 수 없는 재정의 지정자
```

### 원인
- `Item.h`에서 `ItemType` enum 정의가 포함되지 않음

### 해결
- ItemType enum을 별도 헤더로 분리
- `Item.h`에서 해당 헤더 include

👉 **헤더 의존성 명확화**

---

## 5. Item 추상 클래스 인스턴스화 에러

### 에러
```
C2259: Item: 추상 클래스를 인스턴스화 할 수 없습니다
```

### 원인
- `Item`에 순수 가상 함수 존재
- Inventory / Factory 쪽에서 `Item` 직접 생성 시도

### 해결
- Item 직접 생성 코드 제거
- 항상 `Weapon`, `Armor`, `Consumable` 같은 **구현 클래스만 생성**

👉 Item은 **인터페이스 역할만 담당**

---

## 6. Inventory 출력 시 Value가 0으로 나오던 문제 (핵심)

### 현상
- 이름 / 타입 정상 출력
- Value만 항상 0

### 원인
```cpp
int Item::Value;  // 부모 클래스 값만 출력 중
```

실제 의미 있는 값은 자식 클래스에 있었음.

### 해결 방법 (최종 선택)
```cpp
class Item
{
public:
    virtual int GetValue() const = 0;
};
```

각 아이템이 자신의 의미에 맞게 override:

```cpp
int Consumable::GetValue() const { return value; }
int Weapon::GetValue() const { return AtkUP; }
int Armor::GetValue() const { return HpUP; }
```

👉 **다형성 기반 설계로 전환**

---

## 7. 출력 책임 분리

### 변경 전
- Item과 Player에서 출력이 섞여 있음

### 변경 후
- Item: 행동 메시지
- Player: 상태 출력

```cpp
std::cout << " (Hp: " << Hp << " / " << MaxHp << ")\n";
```

👉 출력 중복 제거 + 유지보수 용이

---

## 결론

이번 수정으로 얻은 구조적 이점:

- Item ↔ Player 결합도 감소
- Inventory / GameManager 수정 최소화
- 아이템 추가 시 기존 코드 수정 거의 없음
- 다형성 기반 확장 가능 구조 완성

이 단계 이후:
- 장비 교체 로직
- 버프/디버프 아이템
- 효과 지속형 아이템

을 자연스럽게 확장 가능.

---

📌 **이번 Step의 핵심 키워드**
- 캡슐화
- 책임 분리
- 다형성
- 추상 클래스는 인터페이스다
