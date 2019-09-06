#pragma once

// 너희들의 과제를 풀어주기위한 클래스.

// 스케일변환행렬.
// 회전변환행렬.
// 이동변환행렬.

class CMatrixMaker final 
{
public:
	explicit CMatrixMaker();
	virtual ~CMatrixMaker() = default;
public:
	// 리턴값 : 함수에서 만들어낸 결과행렬의 주소.
	static D3DXMATRIX* MatrixScaling(D3DXMATRIX* pMatrix, float fX, float fY, float fZ);
	static D3DXMATRIX* MatrixRotationZ(D3DXMATRIX* pMatrix, float fRadian);
	static D3DXMATRIX* MatrixTranslation(D3DXMATRIX* pMatrix, float fX, float fY, float fZ);

};

