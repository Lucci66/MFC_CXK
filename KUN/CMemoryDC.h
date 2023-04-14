#pragma once
class CMemoryDC:public CDC
{
public:
	//����Դ�м���
	CMemoryDC(UINT nID, CDC *pCDC = NULL);
	//���ļ��м���
	CMemoryDC(LPCTSTR szFile, CDC *pCDC = NULL);
	//�Լ�����
	CMemoryDC(int cx, int cy, CDC* pDC = NULL);
	CMemoryDC();
	~CMemoryDC();
	//����Դ�м���
	BOOL AddBitmap(UINT nBitmapID, CDC *pCDC = NULL);
	//���ļ����м���
	BOOL AddFromFile(LPCTSTR szFile, CDC *pCDC = NULL);
	//͸��
	void BitTrans(
		int nXDest,		// Ŀ�����X
		int nYDest,		// Ŀ�����Y
		int nWidthDest,	// Ŀ����
		int nHeightDest,// Ŀ��߶�
		CDC* pDC,		// Ŀ��DC
		int nXSrc,		// ��Դ���X
		int nYSrc,		// ��Դ���Y
		COLORREF crTrans// ͸��ɫ
		);
	void StretchTrans(
		int nXDest,			// Ŀ�����X
		int nYDest,			// Ŀ�����Y
		int nWidthDest,     // Ŀ����
		int nHeightDest,    // Ŀ��߶�
		CDC* pDC,			// Ŀ��DC
		int nXSrc,			// ��Դ���X
		int nYSrc,			// ��Դ���Y
		int nWidthSrc,		// ��Դ���
		int nHeightSrc,		// ��Դ�߶�
		COLORREF crTrans	// ͸��ɫ
		);
	void DeleteBitmap();
	//����һ�ſհ��ڴ滭��
	BOOL Create(int cx, int cy, CDC* pDC = NULL);

	//����ɫ
	void ProgressiveColor(const CRect &rect, COLORREF col1, COLORREF col2,
		CDC *pCD);
public:
	int GetWidth()const;
	int GetHeight()const;
private:
	CSize m_APIsize;
};
