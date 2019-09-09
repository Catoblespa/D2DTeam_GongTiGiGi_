#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::TileCollision(const vector<TILE_INFO*> tile, CGameObject * player, int collisionID)
{
	for (size_t iIndex = 0; iIndex < tile.size(); iIndex++)
		if (collisionID == tile[iIndex]->byDrawID)
		{
			//������ 1��, 5��, 7��, 11��
			D3DXVECTOR3 vPoint[4] = {
				D3DXVECTOR3(tile[iIndex]->vPos.x + TILECX * 0.5f, tile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),//1�� ��
				D3DXVECTOR3(tile[iIndex]->vPos.x + TILECX * 0.5f, tile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),//5�� ��
				D3DXVECTOR3(tile[iIndex]->vPos.x - TILECX * 0.5f, tile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),//7�� ��
				D3DXVECTOR3(tile[iIndex]->vPos.x - TILECX * 0.5f, tile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),//11�� ��
			};

			//���⺤�� 3�� 6�� 9�� 12��
			D3DXVECTOR3 vDir[4] = { vPoint[1] - vPoint[0],	vPoint[2] - vPoint[1],	vPoint[3] - vPoint[2],	vPoint[0] - vPoint[3] };

			//��������
			D3DXVECTOR3 vNormal[4] = {};
			for (int i = 0; i < 4; ++i)
				D3DXVec3Cross(&vNormal[i], &D3DXVECTOR3(0.f, 0.f, 1.f), &vDir[i]);

			//������->�÷��̾�pos
			D3DXVECTOR3 vPlayerDir[4] =	{player->GetInfo().vPos - vPoint[0],player->GetInfo().vPos - vPoint[1],	player->GetInfo().vPos - vPoint[2],player->GetInfo().vPos - vPoint[3]};

			//vNormal . vPlayerDir (����)
			for (int i = 0; i < 4; ++i)
			{
				//����
				if (0.f < D3DXVec3Dot(&vNormal[i], &vPlayerDir[i]))
					return false;
			}
			return true;
		}

}
