#pragma once
#include "GameObject.h"


#define NORMAL_TILE	0
#define BOMB_TILE	1
#define JUMP_TILE	2
#define LEFT_TILE	3
#define RIGHT_TILE	4
#define BROKEN_TILE	5
#define BLACK_TILE	6

class CTerrain :
	public CGameObject
{
private:
	bool m_bIsData;

private:
	CTerrain();

public:
	virtual ~CTerrain();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual HRESULT LateInit() override;
	virtual void Release() override;

private:
	bool IsPicking();

	bool CheckInOut(const POINT& pt, const int iIndex);

private:
	void SaveTile(const wstring& wstrFilePath);
	void LoadTile(const wstring& wstrFilePath);

public:
	static CTerrain* Create();

private:
	vector<TILE_INFO*>	m_vecTile;
};

