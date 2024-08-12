// CCameraControl.cpp: 구현 파일
//

#include "pch.h"
#include "20201332P4.h"
#include "afxdialogex.h"
#include "CCameraControl.h"
#include "MainFrm.h"
#include "20201332P4Doc.h"
#include "20201332P4View.h"


// CCameraControl 대화 상자

IMPLEMENT_DYNAMIC(CCameraControl, CDialogEx)

CCameraControl::CCameraControl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CAMERA, pParent)
	, m_strAngle(_T(""))
{

}

CCameraControl::~CCameraControl()
{
}

void CCameraControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SELECTION, m_tabSelection);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_strAngle);
}


BEGIN_MESSAGE_MAP(CCameraControl, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SELECTION, &CCameraControl::OnSelchangeTabSelection)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ANGLE, &CCameraControl::OnDeltaposSpinAngle)
END_MESSAGE_MAP()


// CCameraControl 메시지 처리기


BOOL CCameraControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_tabSelection.DeleteAllItems();
	m_tabSelection.InsertItem(0, _T("From"));
	m_tabSelection.InsertItem(1, _T("At"));
	m_tabSelection.InsertItem(2, _T("Up"));

	CRect rect;
	m_dlgFrom.Create(IDD_DIALOG_FROM, &m_tabSelection);
	m_dlgFrom.GetWindowRect(&rect);
	m_dlgFrom.MoveWindow(5, 25, rect.Width(), rect.Height());
	m_dlgFrom.ShowWindow(SW_SHOW);

	m_dlgAt.Create(IDD_DIALOG_AT, &m_tabSelection);
	m_dlgAt.GetWindowRect(&rect);
	m_dlgAt.MoveWindow(5, 25, rect.Width(), rect.Height());
	m_dlgAt.ShowWindow(SW_HIDE);

	m_dlgUp.Create(IDD_DIALOG_UP, &m_tabSelection);
	m_dlgUp.GetWindowRect(&rect);
	m_dlgUp.MoveWindow(5, 25, rect.Width(), rect.Height());
	m_dlgUp.ShowWindow(SW_HIDE);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());
	m_strAngle.Format(_T("%.1f"), pView->m_Angle);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCameraControl::OnSelchangeTabSelection(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelection = m_tabSelection.GetCurSel();

	switch (nSelection) 
	{
		case 0:
			m_dlgFrom.ShowWindow(SW_SHOW);
			m_dlgAt.ShowWindow(SW_HIDE);
			m_dlgUp.ShowWindow(SW_HIDE);
			break;
		case 1:
			m_dlgFrom.ShowWindow(SW_HIDE);
			m_dlgAt.ShowWindow(SW_SHOW);
			m_dlgUp.ShowWindow(SW_HIDE);
			break;
		case 2:
			m_dlgFrom.ShowWindow(SW_HIDE);
			m_dlgAt.ShowWindow(SW_HIDE);
			m_dlgUp.ShowWindow(SW_SHOW);
			break;

	}

	*pResult = 0;
}


void CCameraControl::OnDeltaposSpinAngle(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_Angle++;
	else
		pView->m_Angle--;

	m_strAngle.Format(_T("%.1f"), pView->m_Angle);
	UpdateData(FALSE);

	pView->RedrawWindow();

	*pResult = 0;
}
