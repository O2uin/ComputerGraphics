#pragma once


// CDisplayControl 대화 상자

class CDisplayControl : public CDialogEx
{
	DECLARE_DYNAMIC(CDisplayControl)

public:
	CDisplayControl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDisplayControl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DISPLAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioWire();
	afx_msg void OnRadioSmooth();
	afx_msg void OnRadioFlat();
	afx_msg void OnClickedButtonReset();
};
