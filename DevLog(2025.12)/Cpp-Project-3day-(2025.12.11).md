# 프로젝트 진행 정리 (2025-12-11)

## ✔ 1:1 전투(GameManager) 구조 변경

-   기존에는 여러 몬스터와 전투가 한꺼번에 이뤄지는 구조였으나, **항상
    첫 번째 몬스터와 1:1 전투**하도록 구조 개선.
-   전투 종료 후:
    -   사망한 몬스터 삭제 및 벡터에서 제거
    -   `GiveRandomItem()` 호출
    -   `SpawnMonster()` 로 다음 몬스터 생성

### 변경된 핵심 로직

``` cpp
if (!Monsterr[0]->IsAlives())
{
    delete Monsterr[0];
    Monsterr.erase(Monsterr.begin());

    GiveRandomItem();   // 아이템 지급
    SpawnMonster();     // 새로운 몬스터 생성
}
```

### GameLoop 조건 수정

-   `isGameover` bool 조건 판별 실수로 인해 while문이 바로 종료되는 현상
    발견.
-   `while(!isGameover)` 형태로 수정하여 정상 동작 확인.

------------------------------------------------------------------------

## ✔ Item 클래스 기본 구현 (3단계)

### 구현 내용

-   Item은 **이름 / 타입 / 수치**만 가진 단순 데이터 클래스.
-   현재의 3단계 목표는 "Player가 아이템을 받을 수 있다" 수준

### Item 구조

``` cpp
Item::Item(std::string _name, std::string _type, int _value)
    : Name(_name), Type(_type), Value(_value)
{}
```

------------------------------------------------------------------------

## ✔ Player 아이템 사용 기능 추가

-   현재는 **Heal 아이템**만 실제 스탯에 반영.
-   Type에 따른 분기 처리:

``` cpp
void Player::UseItem(Item* item)
{
    std::string Type = item->GetType();

    if (Type == "Heal") {
        Hp += item->GetValue();
        ...
    }
    else if (Type == "Mana") { ... }
    else if (Type == "Atk") { ... }
}
```

------------------------------------------------------------------------

## ✔ GameManager 아이템 지급 임시 구현

-   몬스터 사망 시 체력 포션을 지급하고 바로 사용함.
-   아직:
    -   50% 확률 지급\
    -   여러 아이템 중 랜덤 선택\
    -   Monster에서 드랍 여부 결정\
        등은 구현하지 않음.

``` cpp
void GameManager::GiveRandomItem()
{
    Item* potion = new Item("체력 포션", "Heal", 30);
    Playerr->UseItem(potion);
    delete potion;
}
```

------------------------------------------------------------------------

## ▶ 다음 단계 계획 (4단계: Inventory)

-   Player가 아이템을 소유하는 구조 도입
-   예상 구현 기능:
    -   아이템 추가
    -   아이템 제거
    -   아이템 목록 출력
    -   소유권/메모리 관리 개념 체감
-   이후 Monster에서 드랍 → GameManager가 받아 플레이어에게 전달 구조
    가능

------------------------------------------------------------------------
