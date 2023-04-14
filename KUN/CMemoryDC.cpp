#include "stdafx.h"
#include "CMemoryDC.h"


CMemoryDC::CMemoryDC(UINT nID, CDC * pCDC) :m_APIsize(0, 0)
{
	AddBitmap(nID, pCDC);
}

CMemoryDC::CMemoryDC(LPCTSTR szFile, CDC * pCDC) : m_APIsize(0, 0)
{
	AddFromFile(szFile, pCDC);
}

CMemoryDC::CMemoryDC(int cx, int cy, CDC * pDC) : m_APIsize(0, 0)
{
	Create(cx, cy, pDC);
}

CMemoryDC::CMemoryDC() : m_APIsize(0, 0)
{
}


CMemoryDC::~CMemoryDC()
{
	DeleteBitmap();
}

BOOL CMemoryDC::AddBitmap(UINT nBitmapID, CDC *pCDC)
{
	CBitmap bmp;
	//����λͼ
	BOOL nResu = bmp.LoadBitmapW(nBitmapID);
	if (!nResu)
		return FALSE;
	//��ȡλͼ�ĸߡ���
	BITMAP b;
	bmp.GetBitmap(&b);
	m_APIsize.SetSize(b.bmWidth, b.bmHeight);

	this->CreateCompatibleDC(pCDC);  //����һ��CDC
	this->SelectObject(&bmp);        //��λͼѡ���������CDC
	return TRUE;
}

BOOL CMemoryDC::AddFromFile(LPCTSTR szFile, CDC * pCDC)
{
	HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, szFile, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	//��ȡλͼ�ĸߡ���
	BITMAP b;
	GetObject(hBitmap, sizeof(b), &b);
	m_APIsize.SetSize(b.bmWidth, b.bmHeight);

	this->CreateCompatibleDC(pCDC);  //����һ��CDC
	this->SelectObject(hBitmap);        //��λͼѡ���������CDC
	::DeleteObject(hBitmap);
	return 0;
}

void CMemoryDC::BitTrans(int nXDest, int nYDest, int nWidthDest, int nHeightDest, CDC * pDC, int nXSrc, int nYSrc, COLORREF crTrans)
{
	CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//��ʱDC
	CBitmap bmpMask;
	bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);            // ������ɫ����λͼ
	CDC dcMask;//����DC 
	dcMask.CreateCompatibleDC(pDC);
	dcMask.SelectObject(bmpMask);
	//������λͼ���ڴ�DC�е�λͼ����������ʱDC��
	dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);

	// ������ʱDC��͸��ɫ
	dcImage.SetBkColor(crTrans);
	//����DC��͸������Ϊ��ɫ��������Ϊ��ɫ
	dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

	//��ʱDC͸������Ϊ��ɫ���������򱣳ֲ���
	dcImage.SetBkColor(RGB(0, 0, 0));
	dcImage.SetTextColor(RGB(255, 255, 255));
	dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

	// Ŀ��DC͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
	pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
}

void CMemoryDC::StretchTrans(int nXDest, int nYDest, int nWidthDest, int nHeightDest, CDC * pDC, int nXSrc, int nYSrc, int nWidthSrc, int nHeightSrc, COLORREF crTrans)
{
	CMemoryDC dcImage(nWidthDest, nHeightDest, pDC);//��ʱDC
	CBitmap bmpMask;
	// ������ɫ����λͼ
	bmpMask.CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
	CDC dcMask;
	dcMask.CreateCompatibleDC(pDC);
	dcMask.SelectObject(bmpMask);

	// ������λͼ���ڴ�DC�е�λͼ����������ʱDC��
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, this, nXSrc, nYSrc, SRCCOPY);
	else
		dcImage.StretchBlt(0, 0, nWidthDest, nHeightDest,
		this, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// ������ʱDC��͸��ɫ
	dcImage.SetBkColor(crTrans);
	//����DC��͸������Ϊ��ɫ��������Ϊ��ɫ
	dcMask.BitBlt(0, 0, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCCOPY);

	//��ʱDC͸������Ϊ��ɫ���������򱣳ֲ���
	dcImage.SetBkColor(RGB(0, 0, 0));
	dcImage.SetTextColor(RGB(255, 255, 255));
	dcImage.BitBlt(0, 0, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);

	// Ŀ��DC͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcMask, 0, 0, SRCAND);
	pDC->BitBlt(nXDest, nYDest, nWidthDest, nHeightDest, &dcImage, 0, 0, SRCPAINT);
}

void CMemoryDC::ProgressiveColor(const CRect & rect, COLORREF col1, COLORREF col2, CDC * pCD)
{
	int cx = rect.Width();
	int cy = rect.Height();
	//RGB��ɫ֮��Ĳ��
	int red = GetRValue(col2) - GetRValue(col1);
	int green = GetGValue(col2) - GetGValue(col1);
	int blue = GetBValue(col2) - GetBValue(col1);

	int i = 0;
	CPen *OldPen = pCD->GetCurrentPen();

	while (i < cx)
	{
		int r = GetRValue(col1) + i * red / cx;
		int g = GetGValue(col1) + i * green / cx;
		int b = GetBValue(col1) + i * blue / cx;

		CPen pen(PS_SOLID, 1, RGB(r, g, b));
		pCD->SelectObject(&pen);
		pCD->MoveTo(i, 0);
		pCD->LineTo(i, rect.bottom);
		i++;
	}
	if (OldPen)
		pCD->SelectObject(OldPen);
}

int CMemoryDC::GetWidth() const
{
	return m_APIsize.cx;
}

int CMemoryDC::GetHeight() const
{
	return m_APIsize.cy;
}

void CMemoryDC::DeleteBitmap()
{
	CBitmap *pBitmap = this->GetCurrentBitmap();
	if (pBitmap)
		pBitmap->DeleteObject();
}

BOOL CMemoryDC::Create(int cx, int cy, CDC * pDC)
{
	CreateCompatibleDC(pDC);
	CBitmap bitmap;
	if (pDC)
		bitmap.CreateCompatibleBitmap(pDC, cx, cy);
	else
		bitmap.CreateCompatibleBitmap(&CClientDC(NULL), cx, cy);
	m_APIsize.cx = cx;
	m_APIsize.cy = cy;
	SelectObject(bitmap);
	return TRUE;
}