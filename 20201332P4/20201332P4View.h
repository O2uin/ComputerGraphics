
// 20201332P4View.h: CMy20201332P4View 클래스의 인터페이스
//

#pragma once
#include "CCameraControl.h"
#include "CDisplayControl.h"
#include "CLightMatControl.h"

#define WIRE_FRAME			1
#define FLAT_SHADING		2
#define SMOOTH_SHADING		3
#define CLOCKWISE			4
#define COUNTER_CLOCKWISE	5

struct Vertex {
	float x;
	float y;
	float z;
};

struct Index {
	int Count;
	int List[30];
	float Red;
	float Green;
	float Blue;
};


class CMy20201332P4View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy20201332P4View() noexcept;
	DECLARE_DYNCREATE(CMy20201332P4View)

// 특성입니다.
public:
	CMy20201332P4Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy20201332P4View();
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
	GLfloat m_fRotX;
	GLfloat m_fRotY;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CPoint m_ptMouseDown;
	bool m_bRotate;
	bool m_bZoom;
	GLfloat m_fTransZ;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	GLdouble m_dAspectRatio;
	GLfloat m_From[3];
	GLfloat m_At[3];
	GLfloat m_Up[3];
	GLfloat m_Angle;

	bool m_bFileOpen;
	CString m_strFileType;
	CString m_strFileWinding;

	int m_nCountVertex;
	int m_nCountFace;
	int m_nCountEdge;
	Vertex m_Vertex[6000];
	Index m_FaceIndex[5000];
	afx_msg void OnFileOpen();
	CCameraControl m_dlgCameraControl;
	afx_msg void OnCameraControl();
	bool m_bDisplayCameraControl;
	GLfloat m_fAmbientLight[4];
	GLfloat m_fDiffuseLight[4];
	GLfloat m_fSpecularLight[4];
	GLfloat m_fAmbientMat[4];
	GLfloat m_fDiffuseMat[4];
	GLfloat m_fSpecularMat[4];
	GLfloat m_fLightPos[4];
	GLfloat m_fFaceNormal[5000][3];
	GLfloat m_fVertexNormal[6000][3];
	int m_nShine;
	int m_nWinding;
	int m_nDisplayMode;
	void CalcNormal(float vertex[][3], float normal[]);
	void ReduceToUnit(float vector[]);
	void CalcFaceNormal();
	void CalcVertexNormal();
	CDisplayControl m_dlgDisplayControl;
	afx_msg void OnDisplayControl();
	bool m_bDisplayDisplayControl;
	CLightMatControl m_dlgLightMatControl;
	afx_msg void OnLightMatControl();
	bool m_bDisplayLightMatControl;
};

#ifndef _DEBUG  // 20201332P4View.cpp의 디버그 버전
inline CMy20201332P4Doc* CMy20201332P4View::GetDocument() const
   { return reinterpret_cast<CMy20201332P4Doc*>(m_pDocument); }
#endif

