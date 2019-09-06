#include "stdafx.h"
#include "MatrixMaker.h"


CMatrixMaker::CMatrixMaker()
{

}

D3DXMATRIX* CMatrixMaker::MatrixScaling(D3DXMATRIX* pMatrix, float fX, float fY, float fZ)
{
	D3DXMatrixIdentity(pMatrix);

	pMatrix->_11 = fX;
	pMatrix->_22 = fY;
	pMatrix->_33 = fZ;

	return pMatrix;
}

D3DXMATRIX * CMatrixMaker::MatrixRotationZ(D3DXMATRIX* pMatrix, float fRadian)
{
	D3DXMatrixIdentity(pMatrix);

	/*P(x, y, z, w) * {	_11, _12, _13, _14
						_21, _22, _23, _24
						_31, _32, _33, _34
						_41, _42, _43, _44	}

	= Q(x * cos - y * sin, x * sin + y * cos, 0, 0)*/	

	pMatrix->_11 = cosf(fRadian);
	pMatrix->_12 = sinf(fRadian);
	pMatrix->_21 = -sinf(fRadian);
	pMatrix->_22 = cosf(fRadian);

	return pMatrix;
}

D3DXMATRIX* CMatrixMaker::MatrixTranslation(D3DXMATRIX * pMatrix, float fX, float fY, float fZ)
{
	D3DXMatrixIdentity(pMatrix);

	pMatrix->_41 = fX;
	pMatrix->_42 = fY;
	pMatrix->_43 = fZ;

	return pMatrix;
}

