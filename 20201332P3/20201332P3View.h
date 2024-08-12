
// 20201332P3View.h: CMy20201332P3View 클래스의 인터페이스
//
#include "CGeoTransform.h"

#pragma once

#define GL_ORTHOGONAL_MODEL		1
#define GL_PERSPECTIVE_MODEL	2
#define PROJECTION_MODEL		3
#define GEOMETRIC_TRANSFORM		4


class CMy20201332P3View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy20201332P3View() noexcept;
	DECLARE_DYNCREATE(CMy20201332P3View)

// 특성입니다.
public:
	CMy20201332P3Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy20201332P3View();
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	bool InitializeOpenGL();
	bool SetupPixelFormat();
	void RenderScene();
	GLint m_nProjectionMode;
	GLdouble m_dAspectRatio;
	int m_nMenuSelection;
	afx_msg void OnOrthogonal();
	afx_msg void OnPerspective();
	GLfloat m_fRevolutionAngle;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	GLfloat m_fTranslateX;
	GLfloat m_fTranslateY;
	GLfloat m_fTranslateZ;
	GLint m_nRotateX;
	GLint m_nRotateY;
	GLint m_nRotateZ;
	GLfloat m_fScaleX;
	GLfloat m_fScaleY;
	GLfloat m_fScaleZ;

	CGeoTransform m_GeoDlg;
	afx_msg void OnGeoTransform();
	bool m_bDisplayGeoDlg;
};

#ifndef _DEBUG  // 20201332P3View.cpp의 디버그 버전
inline CMy20201332P3Doc* CMy20201332P3View::GetDocument() const
   { return reinterpret_cast<CMy20201332P3Doc*>(m_pDocument); }
#endif

