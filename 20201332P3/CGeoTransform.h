#pragma once
#include "afxdialogex.h"


// CGeoTransform 대화 상자

class CGeoTransform : public CDialogEx
{
	DECLARE_DYNAMIC(CGeoTransform)

public:
	CGeoTransform(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGeoTransform();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GEOMETRIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTranslateX;
	CString m_strTranslateY;
	CString m_strTranslateZ;
	int m_nRotateX;
	int m_nRotateY;
	int m_nRotateZ;
	CString m_nScaleX;
	CString m_nScaleY;
	CString m_nScaleZ;
	CSliderCtrl m_sliderRotateX;
	CSliderCtrl m_sliderRotateY;
	CSliderCtrl m_sliderRotateZ;
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinTranslateX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTranslateY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTranslateZ(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinScaleY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinScaleZ(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinScaleX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickedButtonTranslateReset();
	afx_msg void OnClickedButtonScaleReset();
	afx_msg void OnClickedButtonRotateReset();
};
