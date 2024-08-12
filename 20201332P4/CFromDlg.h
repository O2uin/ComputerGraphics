#pragma once
#include "afxdialogex.h"


// CFromDlg 대화 상자

class CFromDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFromDlg)

public:
	CFromDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFromDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FROM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFromX;
	CString m_strFromY;
	CString m_strFromZ;
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinFromX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFromY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFromZ(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonResetFrom();
};
