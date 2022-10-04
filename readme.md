# 리소스 활용 창작 API 포트폴리오

![](/assets/images/2022/2022-10-04-21-06-15.png)

- 기간: 2021. 02. 24 ~ 2021. 03. 12
- 언어: C++
- 환경: Win 32 API
- 세부: 

    싱글톤 패턴 (Singleton)  
    추상 팩토리 패턴 (Abstract Factory)  
    스크롤링 카메라  
    FMOD  

<hr/>

<h2>목차</h2>

<a href='#1'>1. 조작법</a><br/>
<a href='#2'>2. 씬 전환 방법</a><br/>
<a href='#3'>3. 씬</a><br/>
<a href='#4'>4. NPC 상호작용</a><br/>
<a href='#5'>5. NPC 상호작용</a><br/>
<a href='#6'>6. 전투 스테이지</a><br/>
<a href='#7'>7. 기타</a><br/>

<hr/>
<br/>

<h2 id='1'>조작법</h2>

![](/assets/images/2022/2022-10-04-21-11-31.png)


<hr/>
<br/>

<h2 id='2'>씬 전환 방법</h2>

```C++
void CSceneMgr::SceneChange(SCENEID eID)
{
	m_eCurScene = eID;

	// 씬이 전환되었을때
	if (m_ePreScene != m_eCurScene)
	{
		// 이전 씬 할당 해제합니다
		Release();

		switch (m_eCurScene)
		{
			// 로딩 씬
			case CSceneMgr::SCENE_LOADING:
			{
				m_pScene = new CSLoading;
			}
			break;

			// 캐릭터 선택 씬
			case CSceneMgr::SCENE_SELECTCHARACTER:
			{
				m_pScene = new CSSelectCharacter;
			}
			break;

			// 튜토리얼 씬
			case CSceneMgr::SCENE_TUTORIAL:
			{
				m_pScene = new CSTutorial;
			}
			break;
            //중략...
```

```C++
void CSSelectCharacter::Init()
{
	// 캐릭터 선택 창의 배경이미지를 추가합니다
	CBMPMgr::GetInstance()->InsertImg(L"../경로/BackGround_CharSelect2.bmp",
    L"BackGround_CharSelect");

	// 추상팩토리 방식으로 씬 오브젝트 추가합니다
	pSellect_SelectCharacter = AbstractFactory<COSelectCharacter>::CreateObj();
	CObjMgr::GetInstance()->AddObject(pSellect_SelectCharacter, 
    ObjID::OBJ_SELECTCHARACTER);

	// 캐릭터 재선택으로 인한 사운드 겹침현상 방지
	if (SelectCharBGMOnOff == false)
	{
		CSoundMgr::GetInstance()->PlaySoundW(L"Moonlight_BGM.mp3", 
        CSoundMgr::CHANNEL_ID::BGM);
		CSoundMgr::GetInstance()->SoundLoudControl(CSoundMgr::CHANNEL_ID::BGM, 0.3);

		SelectCharBGMOnOff = true;
	}
}
``` 
```C++
void CObjMgr::AddObject(CObj * pObj, ObjID::ID eID)
{
	// 오브젝트 리스트에 추가합니다
	m_Objlist[eID].push_back(pObj);
}
```
```C++
void COSelectCharacter::Init()
{
	LoadingShadow = true;

	//알파블렌딩 이펙트
	if (BACKtoReturn == false)
	{
		pSellect_AlphaEffect = AbstractFactory<COAlphaEffect>::CreateObj();
		CObjMgr::GetInstance()->AddObject(pSellect_AlphaEffect, 
        ObjID::OBJ_ALPHAEFFECT);
		pSellect_AlphaEffect->SetFadeinout(0);
	}

	//알폰소
	pSellect_Alponso = AbstractFactory<COAlponso>::CreateObj(-50, 700, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Alponso, ObjID::OBJ_CHARACTER);
	
	//레오
	pSellect_Leo = AbstractFactory<COLeo>::CreateObj(-300, 700, false);
	CObjMgr::GetInstance()->AddObject(pSellect_Leo, ObjID::OBJ_CHARACTER);
}
```

- 씬들은 씬매니저(SceneMgr)에서 관리
1. 씬이 변경되었을 경우 Scene 객체를 생성
2. Scene객체는 배경이미지, BGM을 Init함수를 통해 설정
3. ObjMgr에게 씬 오브젝트 정보를 생성하라 요청
4. 오브젝트 매니저(ObjMgr)에서 씬객체 추가
5. 생성된 오브젝트의 Init함수에서 사용할 객체 추가

<hr/>
<br/>

<h2 id='3'>씬</h2>

![](/assets/images/2022/2022-10-04-23-51-13.png)
<hr/>
<br/>

- <h2 id = '4'>일반 씬 (NPC 상호 작용)</h2>

![](/assets/images/2022/2022-10-04-23-55-42.png)

```C++
if (TextBoxOnOff == true)
{
    pSellect_TextBox->SetTextBoxTF(TextBoxOnOff);
    pSellect_TextBox->SetChapterNumber(1);
    pSellect_TextBox->SetTextNumber(m_TextNumber);

    switch (WhoIsTeller)
    {
    case eChar_Num::ALPONSO:
        pSellect_TextBox->SetWhoIsTeller(eChar_Num::ALPONSO);
        break;
    case eChar_Num::LEO:
        pSellect_TextBox->SetWhoIsTeller(eChar_Num::LEO);
        break;
    }
}
```
1. NPC와 캐릭터가 접촉한 상황에서 Space Bar를 누르면 상호작용이 시작
2. 상호 작용시 Text를 관리하는 TextBox에게 현 챕터의 번호, 텍스트 번호를 전달
3. 대화의 주체가 누구인지 전달
<br/>
<hr/>

- <h2 id = '5'>일반 씬 (상점 상호 작용)</h2>

![](/assets/images/2022/2022-10-04-23-57-17.png)

```C++
//포션구입
if (PtInRect(&BuyPotionRect, pt))
{
    if (CKeyMgr::GetInstance()->KeyDown(MK_LBUTTON))
    {
        pSellect_Player->SetPlayerPotion();
        pSellect_Player->SetPlayerMoney(10);

        CSoundMgr::GetInstance()->PlaySoundW(L"MarketBuy.mp3",
        CSoundMgr::CHANNEL_ID::SOUNDEFFECT1);
        CSoundMgr::GetInstance()->SoundLoudControl
        (CSoundMgr::CHANNEL_ID::SOUNDEFFECT1, 0.3);
    }
}
```
1. 상점 NPC와 상호작용을 하면 Status UI와 상점 UI가 생성
2. 각 아이템들의 가격 버튼 좌클릭시 아이템 구매
<br/>
<br/>
<hr/>

- <h2 id = '6'>전투 씬</h2>

![](/assets/images/2022/2022-10-05-00-08-35.png)

```C++
if (Monster_Map.empty() == true && MonsterCnt >= 1)
{
    // 스테이지당 설정된 최대 몬스터의 개채수만큼 소환
    for (MonsterCnt; MonsterCnt <= MaxMonsterCnt; MonsterCnt++)
    {
        CObj* pSellect_Monster = new COMonster_Practice;

        // 몬스터의 종류 랜덤으로 설정
        int RandMob = rand() % 2;

        // 몬스터의 스폰 XY좌표 설정
        int SpawnX = rand() % 700 + pSellect_Player->GetInfo().FX;
        int SpawnY = rand() % 20;

        if (RandMob == 0)
        {
            pSellect_Monster = AbstractFactory<COMonster_Practice>::CreateObj
            (SpawnX, pSellect_Player->GetInfo().FY + SpawnY);

            CObjMgr::GetInstance()->AddObject(pSellect_Monster, ObjID::OBJ_MONSTER);

            Monster_Map.insert(pair<int, CObj*>(MonsterCnt, pSellect_Monster));
        }
        else if (RandMob == 1)
        {
            pSellect_Monster = AbstractFactory<COMonster_Beach>::CreateObj
            (SpawnX, pSellect_Player->GetInfo().FY + SpawnY);

            CObjMgr::GetInstance()->AddObject(pSellect_Monster, ObjID::OBJ_MONSTER);

            Monster_Map.insert(pair<int, CObj*>(MonsterCnt, pSellect_Monster));
        }
```

```C++
if (pTarget == NULL || pTarget == 0)
{
    // 타겟이 없을경우 랜덤한 패턴으로 움직입니다
    isMoving = true;
    isAttack = false;
    if (MoveSwitch == false)
        RandMove = rand() % 3;

    switch (RandMove)
    {
    case 0:
        Move_Left();
        break;

    case 1:
        Move_Right();
        break;
    }
```
```C++
// 몬스터의 반경 내에 플레이어가 존재하면 타겟 지정
if (abs(Monster_Iter->second->GetInfo().FX - pSellect_Player->GetInfo().FX) <= 500)
{
    if (pSellect_Player->GetStatus().Cur_HP > 0)
    {
        Monster_Iter->second->SetTarget(pSellect_Player);
    }
}
```
```C++
// 공격 범위 내에 타겟이 들어오면 전투태세 돌입
if(abs(m_tInfo.FX = pTarget->GetInfo().FX <= pTarget->GetGroundX())
{
	isAttack = true;
}
```
<br/>
<hr/>
<br/>

- <h2 id = '7'>기타</h2>
![](/assets/images/2022/녹화_2022_10_05_00_17_33_80.gif)

<h3>유튜브 시연 영상 링크</h3>
https://youtu.be/1PEE9VyXQKo
