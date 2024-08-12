// CLightMatControl.cpp: 구현 파일
//

#include "pch.h"
#include "20201332P4.h"
#include "CLightMatControl.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "20201332P4Doc.h"
#include "20201332P4View.h"


// CLightMatControl 대화 상자

IMPLEMENT_DYNAMIC(CLightMatControl, CDialogEx)

CLightMatControl::CLightMatControl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LIGHT_MAT, pParent)
{
	m_nTabSelection = 0;
}

CLightMatControl::~CLightMatControl()
{
}

void CLightMatControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_LIGHT_MAT, m_tabLightMat);
}


BEGIN_MESSAGE_MAP(CLightMatControl, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_LIGHT_MAT, &CLightMatControl::OnSelchangeTabLightMat)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CLightMatControl::OnClickedButtonReset)
END_MESSAGE_MAP()


// CLightMatControl 메시지 처리기


BOOL CLightMatControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_tabLightMat.DeleteAllItems();
	m_tabLightMat.InsertItem(0, _T("Material"));
	m_tabLightMat.InsertItem(1, _T("Light Pos"));

	CRect rect;
	m_dlgMat.Create(IDD_DIALOG_MAT, &m_tabLightMat);
	m_dlgMat.GetWindowRect(&rect);
	m_dlgMat.MoveWindow(5, 25, rect.Width(), rect.Height());
	m_dlgMat.ShowWindow(SW_SHOW);

	m_dlgLight.Create(IDD_DIALOG_LIGHT, &m_tabLightMat);
	m_dlgLight.GetWindowRect(&rect);
	m_dlgLight.MoveWindow(5, 25, rect.Width(), rect.Height());
	m_dlgLight.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CLightMatControl::OnSelchangeTabLightMat(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nTabSelection = m_tabLightMat.GetCurSel();

	switch (m_nTabSelection) {
	case 0:
		m_dlgMat.ShowWindow(SW_SHOW);
		m_dlgLight.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_dlgMat.ShowWindow(SW_HIDE);
		m_dlgLight.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}


void CLightMatControl::OnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy20201332P4View* pView = (CMy20201332P4View*)(pFrame->GetActiveView());

	if (m_nTabSelection == 0) {
		pView->m_fDiffuseMat[0] = 1.0f;
		pView->m_fDiffuseMat[1] = 1.0f;
		pView->m_fDiffuseMat[2] = 1.0f;
		pView->m_nShine = 64;
		
		m_dlgMat.m_sliderDiffuseR.SetPos(pView->m_fDiffuseMat[0] * 255);
		m_dlgMat.m_sliderDiffuseG.SetPos(pView->m_fDiffuseMat[1] * 255);
		m_dlgMat.m_sliderDiffuseB.SetPos(pView->m_fDiffuseMat[2] * 255);
		m_dlgMat.m_sliderShine.SetPos(pView->m_nShine);
		
		m_dlgMat.m_strDiffuseR.Format(_T("%.0f"), pView->m_fDiffuseMat[0] * 255);
		m_dlgMat.m_strDiffuseG.Format(_T("%.0f"), pView->m_fDiffuseMat[1] * 255);
		m_dlgMat.m_strDiffuseB.Format(_T("%.0f"), pView->m_fDiffuseMat[2] * 255);
		m_dlgMat.m_strShine.Format(_T("%.0f"), pView->m_nShine);
		m_dlgMat.UpdateData(FALSE);
	}

	if (m_nTabSelection == 1) {
		pView->m_fLightPos[0] = -50;
		pView->m_fLightPos[1] = 50;
		pView->m_fLightPos[2] = 100;

		m_dlgLight.m_strPositionX.Format(_T("%.1f"), pView->m_fLightPos[0]);
		m_dlgLight.m_strPositionY.Format(_T("%.1f"), pView->m_fLightPos[1]);
		m_dlgLight.m_strPositionZ.Format(_T("%.1f"), pView->m_fLightPos[2]);
		m_dlgLight.UpdateData(FALSE);
	}
	pView->RedrawWindow();
}
