#pragma once
#include "afxdialogex.h"


// CAtDlg 대화 상자

class CAtDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAtDlg)

public:
	CAtDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAtDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strAtX;
	CString m_strAtY;
	CString m_strAtZ;
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinAtX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAtY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAtZ(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonResetAt();
};
