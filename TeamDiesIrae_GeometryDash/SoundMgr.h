#pragma once
class CSoundMgr
{
public:
	CSoundMgr();
	~CSoundMgr();
public:
	enum CHANNEL_ID 
	{ 
		BGM,
		BGM_SelectMap,
		SOUNDEFFECT,
		SOUNDEFFECT1,
		MAX_CHANNEL = 100
	};

public:
	void Init();
	void UpdateSound();
	void SoundLoudControl(CHANNEL_ID eID, float _Loud);
	void PlaySound(const TCHAR* pSoundKey, CHANNEL_ID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	void Release();

public:
	void SoundFadeOut(CHANNEL_ID eID);
	void SoundFadeIn(CHANNEL_ID eID);

public:
	static CSoundMgr* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CSoundMgr;
		}
		return m_pInstance;
	}
	void DestroyInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	void LoadSoundFile();

private:
	static CSoundMgr* m_pInstance;
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound; // FMOD_SOUND: ���� ���Ͽ� ���� ������ ���� ����ü.

	// FMOD_CHANNEL: ���带 ����ϰ� �����ϴ� ����. ex) ���� ���� ��.
	FMOD_CHANNEL*	m_pChannelArr[MAX_CHANNEL];

	// FMOD_SYSTEM: FMOD_SOUND�� FMOD_CHANNEL�� �Ѱ� �����ϴ� ��ü.
	FMOD_SYSTEM*	m_pSystem;

private:
	float CurSoundLoud;

	float FadeIn = 0.3;
	float FadeOut = 0;
};

