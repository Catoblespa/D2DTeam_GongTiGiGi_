#include "stdafx.h"
#include "Maingame.h"
#include "Terrain.h"

CMaingame::CMaingame()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pKeyMgr(CKeyMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pTerrain(nullptr)
{
}


CMaingame::~CMaingame()
{
	Release();
}

void CMaingame::Update()
{
	m_pTimeMgr->UpdateTime();
	m_pKeyMgr->Update();
	m_pTerrain->Update();
}

void CMaingame::LateUpdate()
{
	m_pTerrain->LateUpdate();
}

void CMaingame::Render()
{
	m_pDeviceMgr->Render_Begin();

	// 앞으로 모든 오브젝트는 이 사이에서 렌더링 수행.
	m_pTerrain->Render();

	m_pDeviceMgr->Render_End();
}

HRESULT CMaingame::Initialize()
{
	HRESULT hr = 0;

	hr = m_pTimeMgr->InitTime();
	FAILED_CHECK_MSG_RETURN(hr, L"InitTime 실패", E_FAIL);

	hr = m_pDeviceMgr->InitDevice(CDeviceMgr::MODE_WIN);
	FAILED_CHECK_MSG_RETURN(hr, L"장치초기화 실패", E_FAIL);

	// Terrain
	m_pTerrain = CTerrain::Create();
	NULL_CHECK_MSG_RETURN(m_pTerrain, L"Terrain Create Failed", E_FAIL);

	return S_OK;
}

void CMaingame::Release()
{
	SafeDelete(m_pTerrain);

	m_pTimeMgr->DestroyInstance();
	m_pKeyMgr->DestroyInstance();
	m_pTextureMgr->DestroyInstance();
	m_pDeviceMgr->DestroyInstance();
}

CMaingame* CMaingame::Create()
{
	CMaingame* pInstance = new CMaingame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
