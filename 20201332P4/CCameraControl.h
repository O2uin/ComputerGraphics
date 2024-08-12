#pragma once
#include "afxdialogex.h"

#include "CFromDlg.h"
#include "CAtDlg.h"
#include "CUpDlg.h"

// CCameraControl 대화 상자

class CCameraControl : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraControl)

public:
	CCameraControl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCameraControl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabSelection;
	CString m_strAngle;
	CFromDlg m_dlgFrom;
	CAtDlg m_dlgAt;
	CUpDlg m_dlgUp;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabSelection(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAngle(NMHDR* pNMHDR, LRESULT* pResult);
};
