// KUNDlg.h : 头文件
//
#include "CMemoryDC.h"
#pragma once

struct CDirection
{
	int x;
	int y;
	CDirection() : x(0), y(0) {}
	CDirection(int _x, int _y) : x(_x), y(_y) {}
	// 将 CDirection 对象转换成 POINT 对象
	operator POINT() const
	{
		POINT pt = { x, y };
		return pt;
	}

	// 将 CDirection 对象转换成 POINT 对象
	POINT ToPoint() const
	{
		POINT pt = { x, y };
		return pt;
	}
};

struct SData
{
	CPoint pos;
	CDirection dir;  //(5,5) (-5,5) (5,-5) (-5,-5)
	int nIndex;
};


// CKUNDlg 对话框
class CKUNDlg : public CDialog
{
// 构造
	CMemoryDC m_dc; //创建一个内存dc
	enum{PAGE_COUNT = 18};
	CMemoryDC m_dcBack;
	CMemoryDC m_dcKUN[PAGE_COUNT];

	CArray<SData>m_arr;

public:
	CKUNDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KUN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
