#pragma once
class CTexture
{
protected:
	CTexture();

public:
	virtual ~CTexture();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"", /* 상태 키*/
		int iIndex = 0	/* 이미지 번호 */) PURE;

public:
	virtual HRESULT LoadTexture(
		const wstring& wstrFilePath, /* 불러올 이미지 경로 */
		const wstring& wstrStateKey = L"", /* 상태 키*/
		int iImgCount = 0 /* 이미지 개수 */) PURE;

protected:
	virtual void Release() PURE;

protected:
	CDeviceMgr*	m_pDeviceMgr;
};

