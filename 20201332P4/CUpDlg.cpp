// CUpDlg.cpp: 구현 파일
//

#include "pch.h"
#include "20201332P4.h"
#include "afxdialogex.h"
#include "CUpDlg.h"
#include "MainFrm.h"
#include "20201332P4Doc.h"
#include "20201332P4View.h"


// CUpDlg 대화 상자

IMPLEMENT_DYNAMIC(CUpDlg, CDialogEx)

CUpDlg::CUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UP, pParent)
	, m_strUpX(_T(""))
	, m_strUpY(_T(""))
	, m_strUpZ(_T(""))
{

}

CUpDlg::~CUpDlg()
{
}

void CUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UP_X, m_strUpX);
	DDX_Text(pDX, IDC_EDIT_UP_Y, m_strUpY);
	DDX_Text(pDX, IDC_EDIT_UP_Z, m_strUpZ);
}


BEGIN_MESSAGE_MAP(CUpDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_UP_X, &CUpDlg::OnDeltaposSpinUpX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_UP_Y, &CUpDlg::OnDeltaposSpinUpY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_UP_Z, &CUpDlg::OnDeltaposSpinUpZ)
	ON_BN_CLICKED(IDC_BUTTON_RESET_UP, &CUpDlg::OnClickedButtonResetUp)
END_MESSAGE_MAP()


// CUpDlg 메시지 처리기


BOOL CUpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	m_strUpX.Format(_T("%.1f"), pView->m_Up[0]);
	m_strUpY.Format(_T("%.1f"), pView->m_Up[1]);
	m_strUpZ.Format(_T("%.1f"), pView->m_Up[2]);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUpDlg::OnDeltaposSpinUpX(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_Up[0]++;
	else
		pView->m_Up[0]--;

	m_strUpX.Format(_T("%.1f"), pView->m_Up[0]);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CUpDlg::OnDeltaposSpinUpY(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_Up[1]++;
	else
		pView->m_Up[1]--;

	m_strUpY.Format(_T("%.1f"), pView->m_Up[1]);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CUpDlg::OnDeltaposSpinUpZ(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_Up[2]++;
	else
		pView->m_Up[2]--;

	m_strUpZ.Format(_T("%.1f"), pView->m_Up[2]);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CUpDlg::OnClickedButtonResetUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	pView->m_Up[0] = 0;
	pView->m_Up[1] = 1;
	pView->m_Up[2] = 0;

	m_strUpX = "0.0";
	m_strUpY = "1.0";
	m_strUpZ = "0.0";

	UpdateData(FALSE);
	pView->RedrawWindow();
}
