
// 20201332P1View.h: CMy20201332P1View 클래스의 인터페이스
//

#pragma once


class CMy20201332P1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy20201332P1View() noexcept;
	DECLARE_DYNCREATE(CMy20201332P1View)

// 특성입니다.
public:
	CMy20201332P1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy20201332P1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	HGLRC m_hRC;
	CDC* m_pDC;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	bool InitializeOpenGL();
	bool SetupPixelFormat();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void RenderScene();
	afx_msg void OnDestroy();
	GLfloat m_fPosX;
	GLfloat m_fPosY;
	GLfloat m_fWinHeight;
	GLfloat m_fWinWidth;
	GLfloat m_fStepX;
	GLfloat m_fStepY;
	GLsizei m_nSizeRect;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // 20201332P1View.cpp의 디버그 버전
inline CMy20201332P1Doc* CMy20201332P1View::GetDocument() const
   { return reinterpret_cast<CMy20201332P1Doc*>(m_pDocument); }
#endif

