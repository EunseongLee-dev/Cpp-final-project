# Console RPG Project 정리

## 프로젝트 목적
이 프로젝트는 **C++ 객체지향 설계와 스마트 포인터(unique_ptr) 기반 소유권 관리**를 학습하기 위한 콘솔 기반 RPG 프로젝트이다.  
Player / Monster / Item / Inventory / GameManager 간의 **책임 분리와 흐름 설계**를 중심으로 구현하였다.

---

## 전체 구조 개요

### 핵심 클래스 구성
- **Player**: 전투, 아이템 사용, 장비 착용을 담당
- **Monster**: 전투 대상 및 아이템 드랍 테이블 제공
- **Item (추상 클래스)**: 모든 아이템의 공통 인터페이스
- **Consumable / Weapon / Armor**: Item 파생 클래스
- **Inventory**: 아이템 소유 및 관리
- **GameManager**: 게임 루프, 전투 흐름, 드랍 처리 담당

---

## 전투 시스템 흐름

### 공격 구조 (Player / Monster 공통)
- **Attack**
  - 랜덤으로 일반 공격 또는 스킬 사용
- **NormalAttack**
  - 타겟을 참조로 받아 ATK 기반 데미지 적용
- **Skill**
  - 마나 소모 체크 후 스킬 적용
  - 마나 부족 시 일반 공격으로 대체
- **TakeDamage**
  - 데미지 적용 및 생존 여부 체크

---

## 아이템 시스템 설계

### Item 계층 구조
- `Item` (추상 클래스)
  - GetItemTypeName()
  - virtual Use(Player&)
- `Consumable`
  - 체력 / 마나 / 공격력 증가 효과
- `Weapon`
  - 공격력 증가 장비
- `Armor`
  - 최대 체력 증가 장비

### Item 설계 의도
- **Use 함수는 Item이 스스로 자신의 효과를 적용**
- Player는 아이템의 구체 타입을 몰라도 됨 (다형성)

---

## Inventory 설계

### 주요 함수
- **AddItem**
  - 아이템 소유권을 inventory로 이전
- **GetItem**
  - 아이템 접근용 (소유권 유지)
- **RemoveItem**
  - 아이템 소유권을 외부로 이동 후 vector에서 제거
  - 장비일 경우 반환값 사용
  - 소모품일 경우 스마트 포인터 자동 소멸
- **PrintInventory**
  - 보유 아이템 목록 출력

### 설계 핵심
- Inventory가 **아이템의 유일한 소유자**
- 장비 착용 시 소유권 이동을 명확히 표현

---

## Player 아이템 처리 흐름

### 소모품 사용
- **UseItemFromInventory**
  - GetItem → UseItem 호출
  - 효과 적용 후 RemoveItem

### 장비 착용
- **EquipItemFromInventory**
  - dynamic_cast로 Weapon / Armor 분기
  - 장비 슬롯 상태에 따라 Equip 또는 TryEquip 호출

### 장비 관련 함수
- **EquipWeapon / EquipArmor**
  - 장비 슬롯이 비어 있을 경우 바로 착용
- **TryEquipWeapon / TryEquipArmor**
  - 이미 장착 중인 장비가 있을 경우
  - 교체 여부를 입력받아 처리
  - 기존 장비는 Inventory로 반환

### 설계 포인트
- 장비는 **소모되지 않음**
- 소유권 이동으로 장착 상태 표현
- 장비 교체 시 Inventory ↔ Player 간 소유권 이동

---

## Monster 드랍 시스템

### 드랍 테이블
- **DropItem**
  - 소모품 1개 랜덤 생성
- **DropEq**
  - 장비 1개 랜덤 생성

Monster는 항상 아이템을 생성하고,
**실제 획득 여부는 GameManager가 결정**

---

## GameManager 역할

### 주요 함수
- **GameLoop**
  - 전체 게임 흐름 관리
- **ProcessTurn**
  - 전투 및 아이템 선택 처리
- **CheckBattleResult**
  - 사망 판정 및 후처리
- **SpawnMonster**
  - 새로운 몬스터 생성
- **GiveRandomItem**
  - 드랍 테이블 호출 후
  - 확률에 따라 Player에게 지급

### 설계 의도
- GameManager는 **규칙과 흐름만 담당**
- 객체 내부 로직에는 직접 개입하지 않음

---

## 프로젝트 마무리 정리

- 객체 간 책임 분리
- 스마트 포인터 기반 소유권 이동
- 장비 vs 소모품 개념 구분
- 게임 루프 구조 이해

다음 단계의 더 복잡한 프로젝트를 진행하기 위한
**기초 설계 경험 축적**을 목표로 한다.
