#pragma once


// CMaterialDlg 대화 상자

class CMaterialDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMaterialDlg)

public:
	CMaterialDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMaterialDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDiffuseR;
	CString m_strDiffuseG;
	CString m_strDiffuseB;
	CString m_strShine;
	CSliderCtrl m_sliderDiffuseR;
	CSliderCtrl m_sliderDiffuseG;
	CSliderCtrl m_sliderDiffuseB;
	CSliderCtrl m_sliderShine;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
