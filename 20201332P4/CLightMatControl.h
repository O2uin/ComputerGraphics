#pragma once

#include "CMaterialDlg.h"
#include "CLightDlg.h"

// CLightMatControl 대화 상자

class CLightMatControl : public CDialogEx
{
	DECLARE_DYNAMIC(CLightMatControl)

public:
	CLightMatControl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLightMatControl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIGHT_MAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabLightMat;
	CMaterialDlg m_dlgMat;
	CLightDlg m_dlgLight;
	virtual BOOL OnInitDialog();
	int m_nTabSelection;
	afx_msg void OnSelchangeTabLightMat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonReset();
};
