# Step 6 – Player 장비 시스템 리팩토링 정리

## 📌 작업 배경

이번 단계에서는 Player의 장비 착용 로직이 지나치게 많은 책임을 가지고 있다는 문제에서 시작.

- Player가 아이템 타입 판별, 효과 적용, 출력까지 모두 담당
- 문자열 기반 타입 판별 (`"Weapon"`, `"Armor"`)로 인한 구조 취약성
- EquipItemFromInventory 함수 하나에 로직이 과도하게 집중됨
- 장비 / 소모품의 동작 방식 차이가 코드에 명확히 드러나지 않음

---

## 🎯 리팩토링 목표

1. **아이템의 행동 책임을 Item 쪽으로 이동**
2. **Player는 상태 변경만 담당**
3. **장비 착용 / 교체 로직을 명확히 분리**
4. **스마트 포인터 기반 소유권 이동 구조 명확화**

---

## 🧱 Item 구조 변경 요약

### 1️⃣ Item::Use(Player&) 기반 구조

Item은 추상 클래스로 유지되며, 모든 아이템은 Use 함수를 통해 동작한다.

```cpp
class Item
{
public:
    virtual void Use(Player& player) = 0;
};
```

## 2️⃣ Weapon / Armor / Consumable 역할 분리
### 🔹 Weapon

장비 효과 적용 책임을 가짐

Player의 EquipWeapon을 호출

```cpp
void Weapon::Use(Player& player)
{
    player.EquipWeapon(AtkUP);
}
```

### 🔹 Armor

```cpp
void Armor::Use(Player& player)
{
    player.EquipArmor(HpUP);
}
```

### 🔹 Consumable

ConsumableType enum으로 세부 효과 관리

포션 타입이 늘어나도 함수 증식 없이 확장 가능

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

## 🧑 Player 장비 착용 구조 변경
### 1️⃣ EquipItemFromInventory 책임 재정의

EquipItemFromInventory는 다음 역할만 담당한다.

인덱스 검증

착용 가능 여부 판단

장비 슬롯 상태 확인

필요 시 교체 로직으로 분기

```cpp
if (auto weapon = dynamic_cast<Weapon*>(item))
{
    if (!equippedWeapon)
        UseItem(weapon);
    else
        TryEquipWeapon(weapon);
}
```

Armor 역시 동일한 구조로 처리된다.

### 2️⃣ TryEquipWeapon / TryEquipArmor

이미 장비가 착용된 경우에만 호출됨

교체 여부 UI 및 흐름만 담당

bool 반환 없이 내부에서 처리 후 종료

```cpp
void Player::TryEquipWeapon(Weapon* weapon)
{
    int menu;
    std::cin >> menu;

    if (menu == 1)
    {
        ATK = BaseATK;
        inventory.AddItem(std::move(equippedWeapon));
        UseItem(weapon);
    }
}
```

※ 이미 조건 분기가 끝난 상태이므로 bool 반환은 불필요하다고 판단

## 🔐 스마트 포인터 & 캐스팅 정리
### ✔ dynamic_cast

타입 확인용

실패 시 nullptr 반환

RTTI 기반 안전한 다운캐스팅

```cpp
if (auto weapon = dynamic_cast<Weapon*>(item))
```

### ✔ static_cast

이미 타입이 보장된 상황에서 형변환

unique_ptr 변환 시 사용

```cpp
equippedWeapon = std::unique_ptr<Weapon>(
    static_cast<Weapon*>(item.release())
);
```

### ✔ item.release()

unique_ptr의 소유권을 포기하고 raw pointer 반환

이후 소멸 책임은 새 unique_ptr로 이동

### 📦 Inventory Remove 구조 이해

```cpp
std::unique_ptr<Item> item = std::move(Items[index]);
Items.erase(Items.begin() + index);
```

move: 아이템 소유권을 지역 변수로 이동

erase: 벡터의 빈 슬롯 정리

반환된 unique_ptr이 새 소유자가 됨
