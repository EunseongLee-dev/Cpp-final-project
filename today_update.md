
# 오늘 구현한 내용 정리 (Skill 함수, Attack 로직, IsAlive 활용)

## 1. Skill 함수 구현
- 여러 스킬을 사용하는 구조로 확장 가능하도록 Skill 클래스를 설계.
- 스킬은 다음 요소로 구성:
  - 스킬 이름
  - 데미지 수치
  - 마나 소모량
  - 추가 효과(선택)

예시 형태:
```cpp
struct Skill {
    string name;
    int damage;
    int manaCost;

    Skill(string n, int d, int m) : name(n), damage(d), manaCost(m) {}
};
```

## 2. Attack 함수에 Skill 적용
- Attack 함수 내에서 일반 공격 / 스킬 공격을 구분하도록 변경.
- 스킬 선택 여부는 입력 또는 AI 로직에 따라 분기.
- 스킬 사용 시:
  - 마나가 충분한지 확인
  - 스킬 데미지를 적용
  - 마나 감소 처리
- 일반 공격 시 기존 damage 로직 그대로 사용.

변경된 Attack 개념:
```cpp
void Character::Attack(Character& target, Skill* skill) {
    if (skill != nullptr) {
        if (mp >= skill->manaCost) {
            mp -= skill->manaCost;
            target.hp -= skill->damage;
        }
    } else {
        target.hp -= this->damage;
    }
}
```

## 3. IsAlive 활용
- 각 공격 후 대상의 생존 여부를 판단하는 데 사용.
- 전투 루프에서 계속 체크하여 사망 시 턴 종료 또는 게임 종료 처리.
예시:
```cpp
if (!target.IsAlive()) {
    cout << target.name << "은(는) 쓰러졌다!" << endl;
}
```

## 4. Random 함수 오류 해결
- seed 문제 및 범위 이슈를 해결.
- C++11 random 사용 또는 기존 rand() 보정 완성.

---

업로드 용으로 정리되었으며, 이 파일은 그대로 GitHub에 push 가능함.
