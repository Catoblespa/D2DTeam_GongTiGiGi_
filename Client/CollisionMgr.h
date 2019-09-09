#pragma once
class CGameObject;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	//벡터 타일, 플레이어, 충돌아이디 
	static bool TileCollision(const vector<TILE_INFO*> tile,CGameObject* player, int collisionID);
};

