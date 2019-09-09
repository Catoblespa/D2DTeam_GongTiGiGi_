#pragma once
#include "GameObject.h"
class CTerrain :
	public CGameObject
{
private:
	CTerrain();

public:
	virtual ~CTerrain();

public:
	int GetTileIndex(const D3DXVECTOR3& vPos);

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual HRESULT LateInit() override;
	virtual void Release() override;

public:
	void TileChange(const D3DXVECTOR3& vPos, BYTE byDrawID, BYTE byOption = 0);

private:
	bool IsPicking(const D3DXVECTOR3& vPos, size_t iIndex);

public:
	static CTerrain* Create();

private:
	vector<TILE_INFO*>	m_vecTile;
};
