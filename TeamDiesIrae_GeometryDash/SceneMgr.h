#pragma once
class CScene;
class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

public:
	enum SCENEID
	{
		SCENE_LOADING = 0,
		SCENE_SELECTCHARACTER,
		SCENE_SELECTMODE,
		SCENE_TUTORIAL,
		SCENE_SELECTSTAGE,
		SCENE_MAP_ROCOTOWN,
		SCENE_MAP_VOLCANO,
		SCENE_MAP_BEROIA,
		SCENE_MAP_SANCTUARY,
		SCENE_MAP_RAVEN,
		SCENE_MINIGAME,

		SCENE_BEGIN,
		SCENE_END
	};

public:
	void Init();
	int Update();
	void LateUpdate();
	void Render(HDC hdc);
	void Release();

public:
	void SceneChange(SCENEID eID);
	void GameStart(HDC hdc);

public:
	static CSceneMgr* GetInstance()
	{
		if (m_pInstacne == nullptr)
		{
			m_pInstacne = new CSceneMgr;
		}
		return m_pInstacne;
	}

	void DestroyInstance()
	{
		if (m_pInstacne != nullptr)
		{
			delete m_pInstacne;
			m_pInstacne = nullptr;
		}
	}
	
private:
	static CSceneMgr* m_pInstacne;
	
	DWORD			dwBackScroll;

	CScene*			m_pScene;
	SCENEID			m_eCurScene;
	SCENEID			m_ePreScene;
	int				iframe;
};

