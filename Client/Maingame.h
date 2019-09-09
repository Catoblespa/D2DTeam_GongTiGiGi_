#pragma once

class CGameObject;
class CMaingame
{
private:
	CMaingame();

public:
	~CMaingame();

public:	
	void Update();
	void LateUpdate();
	void Render();

private:
	HRESULT Initialize();
	void Release();

public:
	static CMaingame* Create();

private:
	CDeviceMgr*			m_pDeviceMgr;
	CTextureMgr*		m_pTextureMgr;
	CKeyMgr*			m_pKeyMgr;
	CTimeMgr*			m_pTimeMgr;
	CGameObject*		m_pTerrain;
};

