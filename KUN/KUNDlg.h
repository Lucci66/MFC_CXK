// KUNDlg.h : ͷ�ļ�
//
#include "CMemoryDC.h"
#pragma once

struct CDirection
{
	int x;
	int y;
	CDirection() : x(0), y(0) {}
	CDirection(int _x, int _y) : x(_x), y(_y) {}
	// �� CDirection ����ת���� POINT ����
	operator POINT() const
	{
		POINT pt = { x, y };
		return pt;
	}

	// �� CDirection ����ת���� POINT ����
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


// CKUNDlg �Ի���
class CKUNDlg : public CDialog
{
// ����
	CMemoryDC m_dc; //����һ���ڴ�dc
	enum{PAGE_COUNT = 18};
	CMemoryDC m_dcBack;
	CMemoryDC m_dcKUN[PAGE_COUNT];

	CArray<SData>m_arr;

public:
	CKUNDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KUN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
