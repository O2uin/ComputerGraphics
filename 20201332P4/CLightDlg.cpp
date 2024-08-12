// CLightDlg.cpp: 구현 파일
//

#include "pch.h"
#include "20201332P4.h"
#include "CLightDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "20201332P4Doc.h"
#include "20201332P4View.h"


// CLightDlg 대화 상자

IMPLEMENT_DYNAMIC(CLightDlg, CDialogEx)

CLightDlg::CLightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LIGHT, pParent)
	, m_strPositionX(_T(""))
	, m_strPositionY(_T(""))
	, m_strPositionZ(_T(""))
{

}

CLightDlg::~CLightDlg()
{
}

void CLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POSITION_X, m_strPositionX);
	DDX_Text(pDX, IDC_EDIT_POSITION_Y, m_strPositionY);
	DDX_Text(pDX, IDC_EDIT_POSITION_Z, m_strPositionZ);
}


BEGIN_MESSAGE_MAP(CLightDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_POSITION_X, &CLightDlg::OnDeltaposSpinPositionX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_POSITION_Y, &CLightDlg::OnDeltaposSpinPositionY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_POSITION_Z, &CLightDlg::OnDeltaposSpinPositionZ)
END_MESSAGE_MAP()


// CLightDlg 메시지 처리기


BOOL CLightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	m_strPositionX.Format(_T("%.1f"), pView->m_fLightPos[0]);
	m_strPositionY.Format(_T("%.1f"), pView->m_fLightPos[1]);
	m_strPositionZ.Format(_T("%.1f"), pView->m_fLightPos[2]);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CLightDlg::OnDeltaposSpinPositionX(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fLightPos[0] += 5;
	else
		pView->m_fLightPos[0] -= 5;

	m_strPositionX.Format(_T("%.1f"), pView->m_fLightPos[0]);
	UpdateData(FALSE);
	pView->RedrawWindow();

	*pResult = 0;
}


void CLightDlg::OnDeltaposSpinPositionY(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fLightPos[1] += 5;
	else
		pView->m_fLightPos[1] -= 5;

	m_strPositionX.Format(_T("%.1f"), pView->m_fLightPos[1]);
	UpdateData(FALSE);
	pView->RedrawWindow();

	*pResult = 0;
}


void CLightDlg::OnDeltaposSpinPositionZ(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fLightPos[2] += 5;
	else
		pView->m_fLightPos[2] -= 5;

	m_strPositionX.Format(_T("%.1f"), pView->m_fLightPos[2]);
	UpdateData(FALSE);
	pView->RedrawWindow();

	*pResult = 0;
}
