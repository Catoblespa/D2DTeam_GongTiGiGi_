#pragma once
class CGameObject
{
protected:
	CGameObject();

public:
	virtual ~CGameObject();

public:
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	INFO GetInfo();

protected:
	virtual HRESULT Initialize() PURE;
	virtual HRESULT LateInit();
	virtual void Release() PURE;

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	CKeyMgr*		m_pKeyMgr;
	CTimeMgr*		m_pTimeMgr;

	INFO			m_pInfo;
	bool			m_bIsInit;	
};

