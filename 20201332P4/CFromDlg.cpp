// CFromDlg.cpp: 구현 파일
//

#include "pch.h"
#include "20201332P4.h"
#include "afxdialogex.h"
#include "CFromDlg.h"
#include "MainFrm.h"
#include "20201332P4Doc.h"
#include "20201332P4View.h"


// CFromDlg 대화 상자

IMPLEMENT_DYNAMIC(CFromDlg, CDialogEx)

CFromDlg::CFromDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FROM, pParent)
	, m_strFromX(_T(""))
	, m_strFromY(_T(""))
	, m_strFromZ(_T(""))
{

}

CFromDlg::~CFromDlg()
{
}

void CFromDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FROM_X, m_strFromX);
	DDX_Text(pDX, IDC_EDIT_FROM_Y, m_strFromY);
	DDX_Text(pDX, IDC_EDIT_FROM_Z, m_strFromZ);
}


BEGIN_MESSAGE_MAP(CFromDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FROM_X, &CFromDlg::OnDeltaposSpinFromX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FROM_Y, &CFromDlg::OnDeltaposSpinFromY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FROM_Z, &CFromDlg::OnDeltaposSpinFromZ)
	ON_BN_CLICKED(IDC_BUTTON_RESET_FROM, &CFromDlg::OnClickedButtonResetFrom)
END_MESSAGE_MAP()


// CFromDlg 메시지 처리기


BOOL CFromDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	m_strFromX.Format(_T("%.1f"), pView->m_From[0]);
	m_strFromY.Format(_T("%.1f"), pView->m_From[1]);
	m_strFromZ.Format(_T("%.1f"), pView->m_From[2]);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFromDlg::OnDeltaposSpinFromX(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_From[0]++;
	else
		pView->m_From[0]--;

	m_strFromX.Format(_T("%.1f"), pView->m_From[0]);
	UpdateData(FALSE);

	pView->RedrawWindow();

	*pResult = 0;
}


void CFromDlg::OnDeltaposSpinFromY(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_From[1]++;
	else
		pView->m_From[1]--;

	m_strFromY.Format(_T("%.1f"), pView->m_From[1]);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CFromDlg::OnDeltaposSpinFromZ(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_From[2]++;
	else
		pView->m_From[2]--;

	m_strFromZ.Format(_T("%.1f"), pView->m_From[2]);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CFromDlg::OnClickedButtonResetFrom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	pView->m_From[0] = 0;
	pView->m_From[1] = 0;
	pView->m_From[2] = 10;

	m_strFromX = "0.0";
	m_strFromY = "0.0";
	m_strFromZ = "10.0";

	UpdateData(FALSE);
	pView->RedrawWindow();
}
