#pragma once
class CObj
{
public:
	CObj();
	~CObj();

public:
	const INFO& GetInfo() const											{ return m_tInfo; }
	//const POINT& GetMousePos() const									{ return m_tCursorPos; }
	const RECT& GetRect() const											{ return m_tRect; }
public:
	void SetMousePos(float x, float y)									{ m_tCursorPos.x = (LONG)x, m_tCursorPos.y = (LONG)y; }
	void SetImgPos(float _Left, float _Top, float _Right, float _Bottom) { m_tRect.left = (LONG)_Left, m_tRect.top = (LONG)_Top, m_tRect.right = (LONG)_Right, m_tRect.bottom = (LONG)_Bottom; }
	void SetImgPos(float x, float y)									{ m_tInfo.FX = x, m_tInfo.FY = y; }
public:
	void SetDead()														{ m_bIsDead = true; }
	void SetCharToGround(RECT _rc)										{ m_tInfo.FX -= 3; }
	void SetObjectType(int _Type)										{ isitBoss = _Type; }

	void SetPos(float x, float y) { m_tInfo.FX = x, m_tInfo.FY = y; }

public:
	//그라운드 타일 배치
	void SetGroundX(float _GroundX)										{ (pGroundX = _GroundX); }
	void SetGroundY(float _GroundY)										{ (pGroundY = _GroundY); }
	float GetGroundX()													{ return pGroundX; }
	float GetGroundY()													{ return pGroundY; }

public:
	//캐릭터 씬
	Char_StanceID::ID m_Character_CurStance;
	Char_StanceID::ID m_Character_PreStance;

	Char_StanceID::ID GetChar_CurStance()								{ return m_Character_CurStance; }
	Char_StanceID::ID GetChar_PreStance()								{ return m_Character_PreStance; }

	int GetChar_CurFrame()												{ return m_tFrame.iFrameStart; }
	int GetChar_CurSceneN()												{ return m_tFrame.iFrameScene; }

public:
	//텍스트박스 on/off
	void SetTextBoxTF(bool _TextBoxTF)									{ m_TextBoxTF = _TextBoxTF; }
	bool GetTextBoxTF()													{ return m_TextBoxTF; }

	void SetTextOnOff(bool _TextTF)										{ TextOnOff = _TextTF; }
	bool GetTextOnOff()													{ return TextOnOff; }
		
	void SetWhoIsTeller(int _CharNum)									{ WhoIsTeller = _CharNum; }
	void SetIsTeller(bool _IsTeller)									{ isTeller = _IsTeller; }

	void SetChapterNumber(int _ChapterNum)								{ ChapterNumber = _ChapterNum; }
	void SetTextNumber(int _TextNumber)									{ TextNumber = _TextNumber; }

	void SetTextOutCnt(int _TextOutCnt)									{ TextOutCnt = _TextOutCnt; }

public:
	//블렌딩 옵션
	void SetBlendOnOff(bool _BlendTF)									{ BlendOnOff = _BlendTF; }
	void SetFadeinout(bool _isFadeinout)								{ isFadeinout = _isFadeinout; }
	int GetFadeinout()													{ return isFadeinout; }

public:
	//스크롤 관련
	void SetPlayerSpeed(float _m_pSpeed)								{ m_pSpeed = _m_pSpeed; }

public:
	//ai 관련
	void SetTarget(CObj* Target)										{ pTarget = Target; }
	void MoveToTarget();
	bool GetLR()														{ return m_IsLR; }
	void SetLR(bool _IsLR)												{ m_IsLR = _IsLR; }
	void SetMonsterSpeed(int _pSpeed)									{ m_pSpeed = (float)_pSpeed; }

public:
	//전투관련
	void SetDamage(int _Damage)											{ m_tStatus.Cur_HP -= _Damage; }
	void SetPlayerRevive()												{ m_tStatus.Cur_HP = m_tStatus.MAX_HP; }

	//int GetPlayerHP()													{ return m_tStatus.Cur_HP; }
	STATUS GetStatus()													{ return m_tStatus; }
	void SetPlayerPotion()												{ m_tStatus.Potion++; }
	void SetPlayerWeapon(int _WeaponNumber);
	void SetPlayerMoney(bool _bs, int _Money);

	void SetIsBattle(bool _IsBattle)									{ m_IsBattle = _IsBattle; }

public:
	//스킬관련
	void Skeill_X(int _Dst, bool _LR);

public:
	//미니게임 관련
	void SetIsPuzzle(bool _IsPuzzle)									{ isPuzzle = _IsPuzzle; }
	void SetPuzzlePos(int x, int y);
	void SetXCnt(int _CntX)												{ m_CntX = _CntX; }
	void SetYCnt(int _CntY)												{ m_CntY = _CntY; }

	int GetPuzzleNum()													{ return PuszzleNum; }
	void SetPuzzleNum(int _Num)											{ PuszzleNum = _Num; }
	int GetCntX()														{ return m_CntX; }
	int GetCntY()														{ return m_CntY; }

	void ChangePuzzle(CObj** _Src, CObj** _Dest);

public:
	const RECT& GetTriangleObstacleInfo()const							{ return m_TriangleObstacle; }

	//CObj* pSellect_Player = AbstractFactory<COLeo>::CreateObj();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


public:
	virtual void Init() = 0;
	virtual void LateInit();
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

	void CanMoveInit(bool _TF);
public:
	void UpdateRect();
	void UpdateInfo();
	void MoveFrame();
	void MoveSkillFrame();
	void MoveTo(bool LR);

public:
	void MoveSelectCharacter(int _pSpeed, float _Dest);
	void MoveTutorial(int _pSpeed);
	void MoveHorseRace(int _Dst);

public:
	void BeNpc_Standing();
	void BeNpc_Attacking();
	void BeNpc_Walking();
	void BENPC_HIT();

public:
	void HitBySkillCOnOff();
protected:
	bool SW_HitBySkillC = false;
	float SkillCDest = 0;

protected:
	CObj*		pTarget;

	map<int, CObj*>				Monster_Map;
	map<int, CObj*>::iterator	Monster_Iter;

	INFO		m_tInfo;
	RECT		m_tRect;
	STATUS		m_tStatus;

	POINT		m_tCursorPos;

	FRAME		m_tFrame;
	FRAME		m_tSkillFrame;

	RECT		m_TriangleObstacle;
	
	float		pGroundX;
	float		pGroundY;

	int			pGroundCnt;
	int			CharacterNum = 0;

public:
	bool		m_bIsDead = 0;
	bool		m_ObjectMove = true;

	bool		m_Start;

public:
	//대화창
	bool		m_TextBoxTF;
	bool		TextBoxOnOff;
	bool		TextOnOff;
	int			TextOutCnt;

	int			WhoIsTeller;
	bool		isTeller;

	int			ChapterNumber;
	int			TextNumber;

public:
	//캐릭터 npc일때
	bool		m_IsLR;
	bool		m_IsIdle;
	bool		m_GotoL;
	bool		m_GotoR;

public:
	//전투하는 맵인지 아닌지 판별 필요
	bool		m_IsBattle; //임시

public:
	//미니게임 관련
	bool		isPuzzle;
	INFO		m_tPuzzleInfo;
	int			PuszzleNum;
	int			m_CntX;
	int			m_CntY;

	int			CntX = 0;
	int			MaxCntX = 3;

	int			CntY = 0;
	int			MaxCntY = 3;

public:
	bool		BlendOnOff = 0;
	bool		isFadeinout = 0;

public:
	float		m_pSpeed;
	float		m_pSpeedY;

public:
	int			ScrollMax;

public:
	int			isitBoss;

public:
	//shake
	bool		ScreenShake;
	int			ShakeCnt;
	int			Count = 0;

	int			m_SwiftX;
	int			m_SwiftY;
};

