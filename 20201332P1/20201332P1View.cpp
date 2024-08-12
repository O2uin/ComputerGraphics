
// 20201332P1View.cpp: CMy20201332P1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20201332P1.h"
#endif

#include "20201332P1Doc.h"
#include "20201332P1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20201332P1View

IMPLEMENT_DYNCREATE(CMy20201332P1View, CView)

BEGIN_MESSAGE_MAP(CMy20201332P1View, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMy20201332P1View 생성/소멸

CMy20201332P1View::CMy20201332P1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_fPosX = 100.0f;
	m_fPosY = 150.0f;
	m_nSizeRect = 50;
	m_fStepX = 2.0f;
	m_fStepY = 2.0f;

}

CMy20201332P1View::~CMy20201332P1View()
{
}

BOOL CMy20201332P1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CMy20201332P1View 그리기

void CMy20201332P1View::OnDraw(CDC* pDC)
{
	CMy20201332P1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderScene();
	::glFinish();

	::SwapBuffers(m_pDC->GetSafeHdc());
}


// CMy20201332P1View 진단

#ifdef _DEBUG
void CMy20201332P1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20201332P1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20201332P1Doc* CMy20201332P1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20201332P1Doc)));
	return (CMy20201332P1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20201332P1View 메시지 처리기


int CMy20201332P1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	InitializeOpenGL();

	return 0;
}


bool CMy20201332P1View::InitializeOpenGL()
{
	// TODO: 여기에 구현 코드 추가.
	m_pDC = new CClientDC(this);

	if (m_pDC == NULL) {
		MessageBox(_T("Error Obtaining DC"));
		return FALSE;
	}

	if (!SetupPixelFormat()) {
		return FALSE;
	}

	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	if (m_hRC == 0) {
		MessageBox(_T("Error Creating RC"));
		return FALSE;
	}

	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE) {
		MessageBox(_T("Error Making RC Current"));
		return FALSE;
	}

	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	::glClearDepth(1.0f);

	::glEnable(GL_DEPTH_TEST);
	return TRUE;
}


bool CMy20201332P1View::SetupPixelFormat()
{
	// TODO: 여기에 구현 코드 추가.
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0) {
		return FALSE;
	}

	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE) {
		return FALSE;
	}
	return TRUE;
}


void CMy20201332P1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	GLdouble aspect_ratio;

	if (0 >= cx || 0 >= cy) {
		return;
	}
	::glViewport(0, 0, cx, cy);

	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	//::gluPerspective(45.0f, aspect_ratio, 0.01f, 200.0f);

	if (cx <= cy) {
		m_fWinHeight = 250.0f / aspect_ratio;
		m_fWinWidth = 250.0f;
	}
	else {
		m_fWinHeight = 250.0f;
		m_fWinWidth = 250.0f * aspect_ratio;
	}
	gluOrtho2D(0.0f, m_fWinWidth, 0.0f, m_fWinHeight);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}


void CMy20201332P1View::RenderScene()
{
	// TODO: 여기에 구현 코드 추가.
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(m_fPosX, m_fPosY, m_fPosX + m_nSizeRect, m_fPosY + m_nSizeRect);
	SetTimer(0, 33, NULL);
}


void CMy20201332P1View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (::wglMakeCurrent(0, 0) == FALSE) {
		MessageBox(_T("Could not make RC non-current"));
	}

	if (::wglDeleteContext(m_hRC) == FALSE) {
		MessageBox(_T("Could not delete RC"));
	}

	if (m_pDC) {
		delete m_pDC;
	}
	m_pDC = NULL;

	KillTimer(0);
}


void CMy20201332P1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_fPosX > m_fWinWidth - m_nSizeRect || m_fPosX < 0)
		m_fStepX = -m_fStepX;
	
	if (m_fPosY > m_fWinHeight - m_nSizeRect || m_fPosY < 0)
		m_fStepY = -m_fStepY;

	if (m_fPosX > m_fWinWidth - m_nSizeRect)
		m_fPosX = m_fWinWidth - m_nSizeRect - 1;

	if (m_fPosY > m_fWinHeight - m_nSizeRect)
		m_fPosY = m_fWinHeight - m_nSizeRect - 1;

	m_fPosX += m_fStepX;
	m_fPosY += m_fStepY;

	InvalidateRect(NULL, FALSE);

	CView::OnTimer(nIDEvent);
}
