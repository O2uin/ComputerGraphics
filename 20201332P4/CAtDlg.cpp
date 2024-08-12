// CAtDlg.cpp: 구현 파일
//

#include "pch.h"
#include "20201332P4.h"
#include "afxdialogex.h"
#include "CAtDlg.h"
#include "MainFrm.h"
#include "20201332P4Doc.h"
#include "20201332P4View.h"


// CAtDlg 대화 상자

IMPLEMENT_DYNAMIC(CAtDlg, CDialogEx)

CAtDlg::CAtDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AT, pParent)
	, m_strAtX(_T(""))
	, m_strAtY(_T(""))
	, m_strAtZ(_T(""))
{

}

CAtDlg::~CAtDlg()
{
}

void CAtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AT_X, m_strAtX);
	DDX_Text(pDX, IDC_EDIT_AT_Y, m_strAtY);
	DDX_Text(pDX, IDC_EDIT_AT_Z, m_strAtZ);
}


BEGIN_MESSAGE_MAP(CAtDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AT_X, &CAtDlg::OnDeltaposSpinAtX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AT_Y, &CAtDlg::OnDeltaposSpinAtY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AT_Z, &CAtDlg::OnDeltaposSpinAtZ)
	ON_BN_CLICKED(IDC_BUTTON_RESET_AT, &CAtDlg::OnClickedButtonResetAt)
END_MESSAGE_MAP()


// CAtDlg 메시지 처리기


BOOL CAtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	m_strAtX.Format(_T("%.1f"), pView->m_At[0]);
	m_strAtY.Format(_T("%.1f"), pView->m_At[1]);
	m_strAtZ.Format(_T("%.1f"), pView->m_At[2]);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAtDlg::OnDeltaposSpinAtX(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_At[0]++;
	else
		pView->m_At[0]--;

	m_strAtX.Format(_T("%.1f"), pView->m_At[0]);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CAtDlg::OnDeltaposSpinAtY(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_At[1]++;
	else
		pView->m_At[1]--;

	m_strAtY.Format(_T("%.1f"), pView->m_At[1]);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CAtDlg::OnDeltaposSpinAtZ(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_At[2]++;
	else
		pView->m_At[2]--;

	m_strAtZ.Format(_T("%.1f"), pView->m_At[2]);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CAtDlg::OnClickedButtonResetAt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	pView->m_At[0] = 0;
	pView->m_At[1] = 0;
	pView->m_At[2] = -100;

	m_strAtX = "0.0";
	m_strAtY = "0.0";
	m_strAtZ = "-100";

	UpdateData(FALSE);
	pView->RedrawWindow();
}
