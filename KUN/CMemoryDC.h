#pragma once
class CMemoryDC:public CDC
{
public:
	//从资源中加载
	CMemoryDC(UINT nID, CDC *pCDC = NULL);
	//从文件中加载
	CMemoryDC(LPCTSTR szFile, CDC *pCDC = NULL);
	//自己加载
	CMemoryDC(int cx, int cy, CDC* pDC = NULL);
	CMemoryDC();
	~CMemoryDC();
	//从资源中加载
	BOOL AddBitmap(UINT nBitmapID, CDC *pCDC = NULL);
	//从文件夹中加载
	BOOL AddFromFile(LPCTSTR szFile, CDC *pCDC = NULL);
	//透明
	void BitTrans(
		int nXDest,		// 目标起点X
		int nYDest,		// 目标起点Y
		int nWidthDest,	// 目标宽度
		int nHeightDest,// 目标高度
		CDC* pDC,		// 目标DC
		int nXSrc,		// 来源起点X
		int nYSrc,		// 来源起点Y
		COLORREF crTrans// 透明色
		);
	void StretchTrans(
		int nXDest,			// 目标起点X
		int nYDest,			// 目标起点Y
		int nWidthDest,     // 目标宽度
		int nHeightDest,    // 目标高度
		CDC* pDC,			// 目标DC
		int nXSrc,			// 来源起点X
		int nYSrc,			// 来源起点Y
		int nWidthSrc,		// 来源宽度
		int nHeightSrc,		// 来源高度
		COLORREF crTrans	// 透明色
		);
	void DeleteBitmap();
	//创建一张空白内存画布
	BOOL Create(int cx, int cy, CDC* pDC = NULL);

	//渐进色
	void ProgressiveColor(const CRect &rect, COLORREF col1, COLORREF col2,
		CDC *pCD);
public:
	int GetWidth()const;
	int GetHeight()const;
private:
	CSize m_APIsize;
};
