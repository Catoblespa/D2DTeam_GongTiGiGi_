#pragma once
class CGameObject;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	//���� Ÿ��, �÷��̾�, �浹���̵� 
	static bool TileCollision(const vector<TILE_INFO*> tile,CGameObject* player, int collisionID);
};

