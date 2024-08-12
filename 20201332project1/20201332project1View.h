
// 20201332project1View.h: CMy20201332project1View 클래스의 인터페이스
//

#pragma once


class CMy20201332project1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy20201332project1View() noexcept;
	DECLARE_DYNCREATE(CMy20201332project1View)

// 특성입니다.
public:
	CMy20201332project1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy20201332project1View();
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
	GLfloat m_fRotX;
	GLfloat m_fRotY;
	CPoint m_ptMouseDown;
	bool m_bRotate;
	bool m_bZoom;
	GLfloat m_fTransZ;

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	GLfloat m_fRevolutionAngle;
	GLfloat m_fRevolutionEarth;
	GLfloat m_fRevolutionMoon;
	GLfloat m_fRotationEarth;

	GLfloat m_fFramePerYear;
	GLdouble m_dAspectRatio;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	GLuint TextureLoad(LPCWSTR filename);

	GLuint m_nTexture[3];
	afx_msg void OnRevolution();
	afx_msg void OnStop();
	bool m_bRevolution;
	void renderSphere(float cx, float cy, float cz, float radius, int paint);
};

#ifndef _DEBUG  // 20201332project1View.cpp의 디버그 버전
inline CMy20201332project1Doc* CMy20201332project1View::GetDocument() const
   { return reinterpret_cast<CMy20201332project1Doc*>(m_pDocument); }
#endif

