#pragma once
#include "afxdialogex.h"


// CUpDlg 대화 상자

class CUpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpDlg)

public:
	CUpDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strUpX;
	CString m_strUpY;
	CString m_strUpZ;
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinUpX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinUpY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinUpZ(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonResetUp();
};
