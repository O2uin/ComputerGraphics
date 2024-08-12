// CMaterialDlg.cpp: 구현 파일
//

#include "pch.h"
#include "20201332P4.h"
#include "CMaterialDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "20201332P4Doc.h"
#include "20201332P4View.h"


// CMaterialDlg 대화 상자

IMPLEMENT_DYNAMIC(CMaterialDlg, CDialogEx)

CMaterialDlg::CMaterialDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAT, pParent)
	, m_strDiffuseR(_T(""))
	, m_strDiffuseG(_T(""))
	, m_strDiffuseB(_T(""))
	, m_strShine(_T(""))
{

}

CMaterialDlg::~CMaterialDlg()
{
}

void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DIFFUSE_R, m_strDiffuseR);
	DDX_Text(pDX, IDC_EDIT_DIFFUSE_G, m_strDiffuseG);
	DDX_Text(pDX, IDC_EDIT_DIFFUSE_B, m_strDiffuseB);
	DDX_Text(pDX, IDC_EDIT_SHINE, m_strShine);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_R, m_sliderDiffuseR);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_G, m_sliderDiffuseG);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_B, m_sliderDiffuseB);
	DDX_Control(pDX, IDC_SLIDER_SHINE, m_sliderShine);
}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMaterialDlg 메시지 처리기


BOOL CMaterialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	m_strDiffuseR.Format(_T("%.0f"), pView->m_fDiffuseMat[0] * 255);
	m_strDiffuseG.Format(_T("%.0f"), pView->m_fDiffuseMat[1] * 255);
	m_strDiffuseB.Format(_T("%.0f"), pView->m_fDiffuseMat[2] * 255);
	m_strShine.Format(_T("%.d"), pView->m_nShine);
	UpdateData(FALSE);

	m_sliderDiffuseR.SetRange(0, 255);
	m_sliderDiffuseR.SetPos(pView->m_fDiffuseMat[0] * 255);

	m_sliderDiffuseG.SetRange(0, 255);
	m_sliderDiffuseG.SetPos(pView->m_fDiffuseMat[1] * 255);

	m_sliderDiffuseB.SetRange(0, 255);
	m_sliderDiffuseB.SetPos(pView->m_fDiffuseMat[2] * 255);

	m_sliderShine.SetRange(0, 128);
	m_sliderShine.SetPos(pView->m_nShine);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMaterialDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	int nDiffuseR = m_sliderDiffuseR.GetPos();
	int nDiffuseG = m_sliderDiffuseG.GetPos();
	int nDiffuseB = m_sliderDiffuseB.GetPos();
	int nShine = m_sliderShine.GetPos();

	if (pScrollBar->GetSafeHwnd() == m_sliderDiffuseR.m_hWnd)
		m_strDiffuseR.Format(_T("%d"), nDiffuseR);
	else if (pScrollBar->GetSafeHwnd() == m_sliderDiffuseG.m_hWnd)
		m_strDiffuseG.Format(_T("%d"), nDiffuseG);
	else if (pScrollBar->GetSafeHwnd() == m_sliderDiffuseB.m_hWnd)
		m_strDiffuseB.Format(_T("%d"), nDiffuseB);
	else if (pScrollBar->GetSafeHwnd() == m_sliderShine.m_hWnd)
		m_strShine.Format(_T("%d"), nShine);
	else
		return;

	UpdateData(FALSE);
	pView->m_fDiffuseMat[0] = (GLfloat)(nDiffuseR) / 255;
	pView->m_fDiffuseMat[1] = (GLfloat)(nDiffuseG) / 255;
	pView->m_fDiffuseMat[2] = (GLfloat)(nDiffuseB) / 255;

	pView->m_nShine = nShine;
	pView->RedrawWindow();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
