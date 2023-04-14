// KUNDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KUN.h"
#include "KUNDlg.h"
#include "CMemoryDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKUNDlg �Ի���




CKUNDlg::CKUNDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKUNDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	/*m_arr.SetSize(1);
	SData& data = m_arr[0];
	data.pos = CPoint(100, 100);
	data.dir = CDirection(5, 5);
	data.nIndex = 0;*/
}

void CKUNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKUNDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CKUNDlg ��Ϣ�������

BOOL CKUNDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_dcBack.AddFromFile(_T("./images/ˢ����.bmp"));
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, 0, 0, cx, cy, 0);
	m_dc.Create(cx, cy);
	int i = -1;
	CString str;
	while(++i < _countof(m_dcKUN)){
		str.Format(_T("./images/CXK_%d.bmp"), i+1);
		m_dcKUN[i].AddFromFile(str);
	}

	SetTimer(1, 60, NULL);

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKUNDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(rect);
	m_dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &m_dcBack, 0, 0, m_dcBack.GetWidth(), m_dcBack.GetHeight(), SRCCOPY);
	int i = 0, nSize = m_arr.GetSize();
	while(i < nSize){
		SData& d = m_arr[i];
		m_dcKUN[d.nIndex].BitTrans(d.pos.x, d.pos.y, 
			m_dcKUN->GetWidth(), m_dcKUN->GetHeight(), &m_dc, 0, 0, RGB(255,255,255));
		if (++d.nIndex > 17)
		{
			d.nIndex = 0;
		}
		d.pos.Offset(d.dir.ToPoint());
		GetClientRect(rect);
		if (d.pos.x >= rect.right - m_dcKUN->GetWidth() || d.pos.x <= 0)
		{
			d.dir.x *= -1;
		}
		if (d.pos.y >= rect.bottom - m_dcKUN->GetHeight() || d.pos.y <= 0)
		{
			d.dir.y *= -1;
		}
		++i;
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dc, 0, 0, SRCCOPY);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CKUNDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKUNDlg::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialog::OnNcPaint() for painting messages
}

BOOL CKUNDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CKUNDlg::OnLButtonDown(UINT nFlags, CPoint point)
{//�������������ĸ���
	// TODO: Add your message handler code here and/or call default
	SData data = { point,CDirection(5,5), 0};
	if (rand()%2)
	{
		data.dir.x *= -1;
	}
	if (rand()%2)
	{
		data.dir.y *= -1;
	}
	m_arr.Add(data);
	CDialog::OnLButtonDown(nFlags, point);
}

void CKUNDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	//static int nIndex = 0;

	//CMemoryDC mdc(m_dcKUN->GetWidth(), m_dcKUN->GetHeight(), &dc);  //�ڲ�����DC��80��70
	//CRect rect(0, 0, m_dcKUN->GetWidth(), m_dcKUN->GetHeight());
	//mdc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
	//m_dcKUN[nIndex].BitTrans(0, 0, m_dcKUN->GetWidth(), m_dcKUN->GetHeight(), &mdc, 0, 0, RGB(255, 255, 255));
	////dc.BitBlt(10, 10, m_dcKUN->GetWidth(), m_dcKUN->GetHeight(), &mdc, 0, 0, SRCCOPY);
	//if (++nIndex > 17)
	//{
	//	nIndex = 0;
	//}
	Invalidate(FALSE);
	CDialog::OnTimer(nIDEvent);
}
