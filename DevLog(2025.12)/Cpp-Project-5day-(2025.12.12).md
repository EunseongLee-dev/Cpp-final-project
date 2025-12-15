# 프로젝트 정리: 인벤토리 · 몬스터 · 플레이어 · 게임매니저 구현

## 1. 전체 구조 개요

이번 단계에서는 몬스터 드랍 아이템을 플레이어 인벤토리에 넣고,
플레이어가 아이템을 사용하도록 전체 시스템을 완성함.\
동시에 **메모리 관리 문제**, **raw pointer → 스마트 포인터 적용**,
**인벤토리 책임 분리**, **게임 턴 처리 개선** 등을 수행함.

구성된 주요 클래스: - `Item` - `Inventory` - `Player` - `Monster` -
`GameManager`

------------------------------------------------------------------------

## 2. 스마트 포인터 적용 (`std::unique_ptr<Item>`)

### 왜 적용했는가?

-   몬스터가 드랍한 아이템을 `new` 로 만들고 넘길 경우 누가 `delete`
    해야 하는지 책임이 불분명해짐.
-   인벤토리 내부에서 아이템을 보관하므로, **인벤토리가 소유권을
    가진다**는 개념이 맞음.
-   따라서 인벤토리 내부 컨테이너는 `std::vector<std::unique_ptr<Item>>`
    로 결정.

### `.get()` 의 의미

-   `unique_ptr` → 내부의 raw pointer를 반환하는 함수.
-   벡터 기능이 아니라 **스마트 포인터 기능**임.

------------------------------------------------------------------------

## 3. Inventory 구현 요약

### 주요 변경점

-   `vector<Item*>` → `vector<unique_ptr<Item>>` 변경
-   AddItem → `std::move` 사용
-   GetItem → raw pointer 반환 (`.get()`)
-   RemoveItem → `erase()` 호출 시 자동으로 소멸자 호출됨

### Inventory 핵심 메서드 흐름

``` cpp
void AddItem(std::unique_ptr<Item> item);
Item* GetItem(int index) const;   // 소유권은 넘기지 않음
void RemoveItem(int index);       // erase 시 unique_ptr 자동 delete
void PrintInventory() const;
int Count() const;
```

------------------------------------------------------------------------

## 4. Monster::DropItem() 구현 요약

### 역할

-   아이템을 생성해 `unique_ptr<Item>` 로 반환.

``` cpp
std::unique_ptr<Item> Monster::DropItem()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> ch(0, 2);

    switch (ch(mt)) {
        case 0: return std::make_unique<Item>("체력 포션", "Heal", 30);
        case 1: return std::make_unique<Item>("마나 포션", "Mana", 20);
        case 2: return std::make_unique<Item>("공격력 증가 포션", "Atk", 10);
    }
}
```

------------------------------------------------------------------------

## 5. Player 구현 요약

### 1) 인벤토리 삽입

``` cpp
void Player::AddItem(std::unique_ptr<Item> item)
{
    inventory.AddItem(std::move(item));
}
```

### 2) 인벤토리에서 아이템 사용 흐름

``` cpp
void Player::UseItemFromInventory(int index)
{
    if (index 범위 검사 실패)
        return;

    Item* item = inventory.GetItem(index);  // raw pointer
    UseItem(item);                           // 효과 적용
    inventory.RemoveItem(index);             // 자동 delete
}
```

### 3) 아이템 효과 처리

-   Heal → HP 회복
-   Mana → MP 회복
-   Atk → 공격력 증가

------------------------------------------------------------------------

## 6. GameManager 구현 요약

### 1) 아이템 드랍 처리

``` cpp
void GameManager::GiveRandomItem()
{
    auto drop = Monsterr[0]->DropItem();

    if (50% 확률 아이템 획득)
        Playerr->AddItem(std::move(drop));
}
```

### 2) 전투 턴 처리

``` cpp
전투 메뉴
1. 공격
2. 인벤토리 사용
```

-   인벤토리에서 아이템 번호 입력받고 사용
-   아이템 사용 후 턴 종료
-   취소 시 공격으로 전환

------------------------------------------------------------------------

## 7. 이번 단계 주요 성과 정리

### ✔ 독립적인 인벤토리 시스템 완성

-   소유권 명확\
-   아이템 관리 안전하게 구현

### ✔ Monster → GameManager → Player → Inventory 흐름 완성

전투 중 아이템 획득 → 인벤토리 저장 → 플레이어가 직접 사용까지
자연스러운 구조.

### ✔ raw pointer 삭제 문제 해결

스마트 포인터 적용으로 메모리 누수·double delete 모두 제거됨.

### ✔ 코드 구조 안정화

-   Player, Monster, Inventory 의 책임 명확
-   GameManager 가 전투 흐름만 담당하며 역할 분리됨

------------------------------------------------------------------------

## 8. 다음 단계 제안

-   전투 로그 클래스 분리
-   아이템 등급/확률표 분리
-   장비(Equipment) 시스템 추가
-   몬스터 다중 스폰 구현
-   전투 UI 개선(반복 턴 구조)

------------------------------------------------------------------------

