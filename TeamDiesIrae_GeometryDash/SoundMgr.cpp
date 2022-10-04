#include "stdafx.h"
#include "SoundMgr.h"

CSoundMgr* CSoundMgr::m_pInstance = nullptr;

CSoundMgr::CSoundMgr()
{
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Init()
{
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
	
	FMOD_Channel_SetVolume(m_pChannelArr[BGM], 0.5f);

	LoadSoundFile();
}

void CSoundMgr::UpdateSound()
{
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::SoundLoudControl(CHANNEL_ID eID, float _Loud)
{
	CurSoundLoud = _Loud;
	FMOD_Channel_SetVolume(m_pChannelArr[eID], CurSoundLoud);
}

void CSoundMgr::PlaySound(const TCHAR * pSoundKey, CHANNEL_ID eID)
{
	auto& iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
		[&pSoundKey](auto& MyPair)
	{
		return !lstrcmp(pSoundKey, MyPair.first);
	});

	if (m_MapSound.end() == iter_find)
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter_find->second,
		FALSE, &m_pChannelArr[eID]);

	UpdateSound();
}

void CSoundMgr::PlayBGM(const TCHAR * pSoundKey)
{
	auto& iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
		[&pSoundKey](auto& MyPair)
	{
		return !lstrcmp(pSoundKey, MyPair.first);
	});

	if (m_MapSound.end() == iter_find)
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter_find->second,
		FALSE, &m_pChannelArr[BGM]);

	FMOD_Channel_SetMode(m_pChannelArr[BGM], FMOD_LOOP_NORMAL);

	UpdateSound();
}

void CSoundMgr::StopSound(CHANNEL_ID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);
	UpdateSound();
}

void CSoundMgr::StopAll()
{
	for (int i = 0; i < MAX_CHANNEL; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);

	UpdateSound();
}

void CSoundMgr::Release()
{
	for_each(m_MapSound.begin(), m_MapSound.end(),
		[](auto& MyPair)
	{
		delete[] MyPair.first;
		FMOD_Sound_Release(MyPair.second);
	});

	m_MapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void CSoundMgr::SoundFadeOut(CHANNEL_ID eID)
{
	if (FadeOut <= CurSoundLoud)
	{
		CurSoundLoud -= 0.008;
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], CurSoundLoud);
}

void CSoundMgr::SoundFadeIn(CHANNEL_ID eID)
{
	if (FadeIn >= CurSoundLoud)
	{
		CurSoundLoud += 0.008;
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], CurSoundLoud);
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd;

	int handle = _findfirst("../Sound/*.*", &fd);

	if (0 == handle)
	{
		MessageBox(g_hWnd, L"_findfirst failed!", L"Failed!!", MB_OK);
		return;
	}

	char szFullPath[128] = "";
	char szRelativePath[128] = "../Sound/";

	int iResult = 0;

	while (-1 != iResult)
	{
		strcpy_s(szFullPath, szRelativePath);
		strcat_s(szFullPath, fd.name);

		TCHAR* pSoundKey = new TCHAR[strlen(fd.name) + 1];

		// 멀티 -> 와이드로 변환.
		MultiByteToWideChar(CP_ACP, 0, fd.name, strlen(fd.name) + 1,
			pSoundKey, strlen(fd.name) + 1);

		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eResult = FMOD_System_CreateSound(m_pSystem, szFullPath,
			FMOD_HARDWARE, nullptr, &pSound);

		if (FMOD_OK == eResult)
		{
			auto& iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
				[&pSoundKey](auto& MyPair)
			{
				return !lstrcmp(pSoundKey, MyPair.first);
			});

			if (m_MapSound.end() == iter_find)
				m_MapSound.insert({ pSoundKey, pSound });
			else
			{
				delete[] pSoundKey;
				FMOD_Sound_Release(pSound);
			}
		}
		else
			delete[] pSoundKey;

		iResult = _findnext(handle, &fd);
	}
	FMOD_System_Update(m_pSystem);
}
