#pragma once


// CLightDlg 대화 상자

class CLightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLightDlg)

public:
	CLightDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLightDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPositionX;
	CString m_strPositionY;
	CString m_strPositionZ;
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinPositionX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinPositionY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinPositionZ(NMHDR* pNMHDR, LRESULT* pResult);
};
