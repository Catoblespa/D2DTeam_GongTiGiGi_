#include "stdafx.h"
#include "Terrain.h"
#include "Mouse.h"
#include "ScrollMgr.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release();
}

int CTerrain::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return (int)i;
	}

	return -1;
}

int CTerrain::Update()
{
	CGameObject::LateInit();

	// 1초에 100씩 움직여라.
	float fSpeed = 100.f * m_pTimeMgr->GetDeltaTime();

	if (0.f > CMouse::GetMouse().x)
		CScrollMgr::SetScrollPos(D3DXVECTOR3(-fSpeed, 0.f, 0.f));
	if (0.f > CMouse::GetMouse().y)
		CScrollMgr::SetScrollPos(D3DXVECTOR3(0.f, -fSpeed, 0.f));
	if ((float)WINCX < CMouse::GetMouse().x)
		CScrollMgr::SetScrollPos(D3DXVECTOR3(fSpeed, 0.f, 0.f));
	if ((float)WINCY < CMouse::GetMouse().y)
		CScrollMgr::SetScrollPos(D3DXVECTOR3(0.f, fSpeed, 0.f));


	if (m_pKeyMgr->KeyUp(KEY_LBUTTON))
		TileChange(CMouse::GetMouse(), 2);

	return NO_EVENT;
}

void CTerrain::LateUpdate()
{
}

void CTerrain::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	const TEX_INFO* pTexInfo = nullptr;

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		D3DXMatrixScaling(&matScale,
			m_vecTile[i]->vSize.x,
			m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x - CScrollMgr::GetScrollPos().x,
			m_vecTile[i]->vPos.y - CScrollMgr::GetScrollPos().y,
			0.f);

		matWorld = matScale * matTrans;

		pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		NULL_CHECK(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

HRESULT CTerrain::Initialize()
{
	m_vecTile.reserve(TILEX * TILEY);

	TILE_INFO* pTile = nullptr;
	float fX = 0.f, fY = 0.f;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			fX = j * TILECX + (i % 2) * (TILECX * 0.5f);
			fY = i * (TILECY * 0.5f);

			pTile = new TILE_INFO;
			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { 1.f, 1.f, 0.f };
			pTile->byDrawID = 2;
			pTile->byOption = 0;

			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}

HRESULT CTerrain::LateInit()
{
	return S_OK;
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_INFO*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTerrain::TileChange(
	const D3DXVECTOR3& vPos, BYTE byDrawID, BYTE byOption)
{
	int iIndex = GetTileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = byOption;
}

bool CTerrain::IsPicking(const D3DXVECTOR3 & vPos, size_t iIndex)
{
	// 내적 (데카르트 기준)

	// 마름모의 꼭지점 시계방향으로 12시, 3시, 6시, 9시를 구한다.
	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
	};

	// 시계방향으로 4개의 방향벡터를 구한다.
	D3DXVECTOR3 vDir[4] = 
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	// 위에서 구한 방향벡터의 법선벡터들을 구한다.
	D3DXVECTOR3 vNormal[4] = {};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Cross(&vNormal[i], &D3DXVECTOR3(0.f, 0.f, 1.f), &vDir[i]);

	// 각 꼭지점에서 마우스 위치로 향하는 벡터 4개 구한다.
	D3DXVECTOR3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	// vNormal와 vMouseDir을 내적해서 모두 음수(둔각)가 나오면 true
	for (int i = 0; i < 4; ++i)
	{
		// 하나라도 양수(예각)가 나오면 false
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;


	//////////////////////////////////////////////////////////////////////


	//// 직선의 방정식 (데카르트 기준)
	//// 마름모를 이루는 직선 4개에 대한 기울기를 구한다.
	//float fGradient[4] = 
	//{
	//	-(TILECY * 0.5f) / (TILECX * 0.5f),
	//	(TILECY * 0.5f) / (TILECX * 0.5f),
	//	-(TILECY * 0.5f) / (TILECX * 0.5f),
	//	(TILECY * 0.5f) / (TILECX * 0.5f)
	//};

	//// 마름모의 꼭지점 시계방향으로 12시, 3시, 6시, 9시를 구한다.
	//D3DXVECTOR3 vPoint[4] =
	//{
	//	D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),
	//	D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
	//	D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),
	//	D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
	//};

	//// Y절편 구한다.
	//// 0 = ax + b - y
	//// b = y - ax
	//float fB[4] = 
	//{
	//	vPoint[0].y - fGradient[0] * vPoint[0].x,
	//	vPoint[1].y - fGradient[1] * vPoint[1].x,
	//	vPoint[2].y - fGradient[2] * vPoint[2].x,
	//	vPoint[3].y - fGradient[3] * vPoint[3].x
	//};

	//// 0 = ax + b - y: 현재 점은 직선과 같은 선상에 있다. (직선이 점을 통과한다)
	//// 0 > ax + b - y: 현재 점은 직선보다 위에 있다.
	//// 0 < ax + b - y: 현재 점은 직선보다 아래에 있다.
	//return (0 < fGradient[0] * vPos.x + fB[0] - vPos.y &&
	//	0 > fGradient[1] * vPos.x + fB[1] - vPos.y &&
	//	0 > fGradient[2] * vPos.x + fB[2] - vPos.y &&
	//	0 < fGradient[3] * vPos.x + fB[3] - vPos.y);
}

CTerrain* CTerrain::Create()
{
	CTerrain* pInstance = new CTerrain;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
