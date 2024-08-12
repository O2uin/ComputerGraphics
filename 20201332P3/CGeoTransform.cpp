// CGeoTransform.cpp: 구현 파일
//

#include "pch.h"
#include "20201332P3.h"
#include "afxdialogex.h"
#include "CGeoTransform.h"
#include "MainFrm.h"
#include "20201332P3Doc.h"
#include "20201332P3View.h"


// CGeoTransform 대화 상자

IMPLEMENT_DYNAMIC(CGeoTransform, CDialogEx)

CGeoTransform::CGeoTransform(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GEOMETRIC, pParent)
	, m_strTranslateX(_T(""))
	, m_strTranslateY(_T(""))
	, m_strTranslateZ(_T(""))
	, m_nRotateX(0)
	, m_nRotateY(0)
	, m_nRotateZ(0)
	, m_nScaleX(_T(""))
	, m_nScaleY(_T(""))
	, m_nScaleZ(_T(""))
{

}

CGeoTransform::~CGeoTransform()
{
}

void CGeoTransform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TRANSLATE_X, m_strTranslateX);
	DDX_Text(pDX, IDC_EDIT_TRANSLATE_Y, m_strTranslateY);
	DDX_Text(pDX, IDC_EDIT_TRANSLATE_Z, m_strTranslateZ);
	DDX_Text(pDX, IDC_EDIT_ROTATE_X, m_nRotateX);
	DDX_Text(pDX, IDC_EDIT_ROTATE_Y, m_nRotateY);
	DDX_Text(pDX, IDC_EDIT_ROTATE_Z, m_nRotateZ);
	DDX_Text(pDX, IDC_EDIT_SCALE_X, m_nScaleX);
	DDX_Text(pDX, IDC_EDIT_SCALE_Y, m_nScaleY);
	DDX_Text(pDX, IDC_EDIT_SCALE_Z, m_nScaleZ);
	DDX_Control(pDX, IDC_SLIDER_ROTATE_X, m_sliderRotateX);
	DDX_Control(pDX, IDC_SLIDER_ROTATE_Y, m_sliderRotateY);
	DDX_Control(pDX, IDC_SLIDER_ROTATE_Z, m_sliderRotateZ);
}


BEGIN_MESSAGE_MAP(CGeoTransform, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRANSLATE_X, &CGeoTransform::OnDeltaposSpinTranslateX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRANSLATE_Y, &CGeoTransform::OnDeltaposSpinTranslateY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRANSLATE_Z, &CGeoTransform::OnDeltaposSpinTranslateZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN__SCALE_Y, &CGeoTransform::OnDeltaposSpinScaleY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN__SCALE_Z, &CGeoTransform::OnDeltaposSpinScaleZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE_X, &CGeoTransform::OnDeltaposSpinScaleX)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_TRANSLATE_RESET, &CGeoTransform::OnClickedButtonTranslateReset)
	ON_BN_CLICKED(IDC_BUTTON_SCALE_RESET, &CGeoTransform::OnClickedButtonScaleReset)
	ON_BN_CLICKED(IDC_BUTTON_ROTATE_RESET, &CGeoTransform::OnClickedButtonRotateReset)
END_MESSAGE_MAP()


// CGeoTransform 메시지 처리기


BOOL CGeoTransform::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());
	m_nRotateX = pView->m_nRotateX;
	m_nRotateY = pView->m_nRotateY;
	m_nRotateZ = pView->m_nRotateZ;
	m_nScaleX.Format(_T("%3.1f"), pView->m_fScaleX);
	m_nScaleY.Format(_T("%3.1f"), pView->m_fScaleY);
	m_nScaleZ.Format(_T("%3.1f"), pView->m_fScaleZ);
	m_strTranslateX.Format(_T("%3.1f"), pView->m_fTranslateX);
	m_strTranslateY.Format(_T("%3.1f"), pView->m_fTranslateY);
	m_strTranslateZ.Format(_T("%3.1f"), pView->m_fTranslateZ);
	UpdateData(FALSE);
	m_sliderRotateX.SetRange(0, 360);
	m_sliderRotateX.SetPos(pView->m_nRotateX);
	m_sliderRotateY.SetRange(0, 360);
	m_sliderRotateY.SetPos(pView->m_nRotateY);
	m_sliderRotateZ.SetRange(0, 360);
	m_sliderRotateZ.SetPos(pView->m_nRotateZ);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGeoTransform::OnDeltaposSpinTranslateX(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fTranslateX = pView->m_fTranslateX + 0.1;
	else
		pView->m_fTranslateX = pView->m_fTranslateX - 0.1;

	m_strTranslateX.Format(_T("%3.1f"), pView->m_fTranslateX);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CGeoTransform::OnDeltaposSpinTranslateY(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fTranslateY = pView->m_fTranslateY + 0.1;
	else
		pView->m_fTranslateY = pView->m_fTranslateY - 0.1;

	m_strTranslateX.Format(_T("%3.1f"), pView->m_fTranslateY);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CGeoTransform::OnDeltaposSpinTranslateZ(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fTranslateZ = pView->m_fTranslateZ + 0.1;
	else
		pView->m_fTranslateZ = pView->m_fTranslateZ - 0.1;

	m_strTranslateX.Format(_T("%3.1f"), pView->m_fTranslateZ);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CGeoTransform::OnDeltaposSpinScaleY(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fScaleY = pView->m_fScaleY + 0.1;
	else
		if (pView->m_fScaleY > 0)
			pView->m_fScaleY = pView->m_fScaleY - 0.1;

	m_strTranslateX.Format(_T("%3.1f"), pView->m_fScaleY);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CGeoTransform::OnDeltaposSpinScaleZ(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fScaleZ = pView->m_fScaleZ + 0.1;
	else
		if (pView->m_fScaleZ > 0)
			pView->m_fScaleZ = pView->m_fScaleZ - 0.1;

	m_strTranslateX.Format(_T("%3.1f"), pView->m_fScaleZ);
	UpdateData(FALSE);

	pView->RedrawWindow();
	*pResult = 0;
}


void CGeoTransform::OnDeltaposSpinScaleX(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	if (pNMUpDown->iDelta < 0)
		pView->m_fScaleX = pView->m_fScaleX + 0.1;
	else
		if(pView->m_fScaleX>0)
			pView->m_fScaleX = pView->m_fScaleX - 0.1;

	m_strTranslateX.Format(_T("%3.1f"), pView->m_fScaleX);
	UpdateData(FALSE);

	pView->RedrawWindow();

	*pResult = 0;
}


void CGeoTransform::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	int nRotateX = m_sliderRotateX.GetPos();
	int nRotateY = m_sliderRotateY.GetPos();
	int nRotateZ = m_sliderRotateZ.GetPos();

	if (pScrollBar->GetSafeHwnd() == m_sliderRotateX.m_hWnd)
		m_nRotateX = nRotateX;
	else if (pScrollBar->GetSafeHwnd() == m_sliderRotateY.m_hWnd)
		m_nRotateY = nRotateY;
	else if (pScrollBar->GetSafeHwnd() == m_sliderRotateZ.m_hWnd)
		m_nRotateZ = nRotateZ;
	else
		return;

	UpdateData(FALSE);
	pView->m_nRotateX = m_nRotateX;
	pView->m_nRotateY = m_nRotateY;
	pView->m_nRotateZ = m_nRotateZ;
	pView->RedrawWindow();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CGeoTransform::OnClickedButtonTranslateReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	pView->m_fTranslateX = 0.0f;
	pView->m_fTranslateY = 0.0f;
	pView->m_fTranslateZ = -10.0f;

	m_strTranslateX = "0.0";
	m_strTranslateY = "0.0";
	m_strTranslateZ = "-10.0";

	UpdateData(FALSE);
	pView->RedrawWindow();
}


void CGeoTransform::OnClickedButtonScaleReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	pView->m_fScaleX = 1.0f;
	pView->m_fScaleY = 1.0f;
	pView->m_fScaleZ = 1.0f;

	m_nScaleX = "1.0";
	m_nScaleY = "1.0";
	m_nScaleZ = "1.0";

	UpdateData(FALSE);
	pView->RedrawWindow();
}


void CGeoTransform::OnClickedButtonRotateReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P3View* pView = (CMy20201332P3View*)(pFrame->GetActiveView());

	pView->m_nRotateX = 0;
	pView->m_nRotateY = 0;
	pView->m_nRotateZ = 0;

	m_nRotateX = 0;
	m_nRotateY = 0;
	m_nRotateZ = 0;

	m_sliderRotateX.SetPos(pView->m_nRotateX);
	m_sliderRotateY.SetPos(pView->m_nRotateY);
	m_sliderRotateZ.SetPos(pView->m_nRotateZ);

	UpdateData(FALSE);
	pView->RedrawWindow();
}
