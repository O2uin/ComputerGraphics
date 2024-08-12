
// 20201332P3View.cpp: CMy20201332P3View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20201332P3.h"
#endif

#include "20201332P3Doc.h"
#include "20201332P3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20201332P3View

IMPLEMENT_DYNCREATE(CMy20201332P3View, CView)

BEGIN_MESSAGE_MAP(CMy20201332P3View, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_ORTHOGONAL, &CMy20201332P3View::OnOrthogonal)
	ON_COMMAND(ID_PERSPECTIVE, &CMy20201332P3View::OnPerspective)
	ON_WM_TIMER()
	ON_COMMAND(ID_GEO_TRANSFORM, &CMy20201332P3View::OnGeoTransform)
END_MESSAGE_MAP()

// CMy20201332P3View 생성/소멸

CMy20201332P3View::CMy20201332P3View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_fRevolutionAngle = 0.0f;
	m_nProjectionMode = GL_PERSPECTIVE_MODEL;
	m_nRotateX = 0.0;
	m_nRotateY = 0.0;
	m_nRotateZ = 0.0;
	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleZ = 1.0f;
	m_fTranslateX = 0.0f;
	m_fTranslateY = 0.0f;
	m_fTranslateZ = -10.0f;
	m_bDisplayGeoDlg = FALSE;

}

CMy20201332P3View::~CMy20201332P3View()
{
}

BOOL CMy20201332P3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CMy20201332P3View 그리기

void CMy20201332P3View::OnDraw(CDC* pDC)
{
	CMy20201332P3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	GLfloat fRange = 150.0f;

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	switch (m_nProjectionMode) 
	{
	case GL_ORTHOGONAL_MODEL:
		if (m_dAspectRatio >= 1)
			glOrtho(-fRange, fRange, fRange / m_dAspectRatio, -fRange / m_dAspectRatio, -fRange * 4.0f, fRange * 4.0f);
		else
			glOrtho(-fRange * m_dAspectRatio, fRange * m_dAspectRatio, fRange,-fRange, -fRange * 4.0f, fRange * 4.0f);
		break;

	case GL_PERSPECTIVE_MODEL:
		::gluPerspective(45.0f, m_dAspectRatio, 1.0f, 500.0f);
		break;
	default:
		break;
	}
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();


	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderScene();
	::glFinish();

	::SwapBuffers(m_pDC->GetSafeHdc());
}


// CMy20201332P3View 진단

#ifdef _DEBUG
void CMy20201332P3View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20201332P3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20201332P3Doc* CMy20201332P3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20201332P3Doc)));
	return (CMy20201332P3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20201332P3View 메시지 처리기


int CMy20201332P3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	InitializeOpenGL();
	SetTimer(0, 50, NULL);

	return 0;
}


void CMy20201332P3View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	

	if (0 >= cx || 0 >= cy) {
		return;
	}
	::glViewport(0, 0, cx, cy);

	m_dAspectRatio = (GLdouble)cx / (GLdouble)cy;

}


void CMy20201332P3View::OnDestroy()
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


bool CMy20201332P3View::InitializeOpenGL()
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
		MessageBox(_T("Error making RC Current"));
		return FALSE;
	}

	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	::glClearDepth(1.0f);
	::glEnable(GL_DEPTH_TEST);
	return TRUE;
}


bool CMy20201332P3View::SetupPixelFormat()
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


void CMy20201332P3View::RenderScene()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_nMenuSelection == PROJECTION_MODEL)
	{
		glTranslatef(0.0f, 0.0f, -200.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidSphere(10.0f, 15, 15);

		glColor3f(1.0f, 1.0f, 0.0f);


		glPushMatrix();
		glRotatef(m_fRevolutionAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(90.0f, 0.0f, 0.0f);
		glutSolidSphere(6.0f, 15, 15);
		glPopMatrix();

		glPushMatrix();
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(m_fRevolutionAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(-70.0f, 0.0f, 0.0f);
		glutSolidSphere(6.0f, 15, 15);
		glPopMatrix();

		glPushMatrix();
		glRotatef(360.0f - 45.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(m_fRevolutionAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 60.0f);
		glutSolidSphere(6.0f, 15, 15);
		glPopMatrix();
	}
	if (m_nMenuSelection == GEOMETRIC_TRANSFORM) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glTranslatef(m_fTranslateX, m_fTranslateY, m_fTranslateZ);
		glRotatef(m_nRotateX, 1.0f, 0.0f, 0.0f);
		glRotatef(m_nRotateY, 0.0f, 1.0f, 0.0f);
		glRotatef(m_nRotateZ, 0.0f, 0.0f, 1.0f);
		glScalef(m_fScaleX, m_fScaleY, m_fScaleZ);
		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_LINE_LOOP);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
		glEnd();

		glBegin(GL_LINES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(3.0f, 0.0f, 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 3.0f, 0.0f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 3.0f);
		glEnd();
	}
}


void CMy20201332P3View::OnOrthogonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nMenuSelection = PROJECTION_MODEL;
	m_nProjectionMode = GL_ORTHOGONAL_MODEL;
	InvalidateRect(NULL, FALSE);
}


void CMy20201332P3View::OnPerspective()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nMenuSelection = PROJECTION_MODEL;
	m_nProjectionMode = GL_PERSPECTIVE_MODEL;
	InvalidateRect(NULL, FALSE);
}


void CMy20201332P3View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_fRevolutionAngle += 10.0f;
	if (m_fRevolutionAngle > 360.0f)
		m_fRevolutionAngle = 0.0f;
	InvalidateRect(NULL, FALSE);

	CView::OnTimer(nIDEvent);
}


void CMy20201332P3View::OnGeoTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nMenuSelection = GEOMETRIC_TRANSFORM;
	m_nProjectionMode = GL_PERSPECTIVE_MODEL;
	if (m_bDisplayGeoDlg == FALSE) {
		m_GeoDlg.Create(IDD_DIALOG_GEOMETRIC, this);
		m_bDisplayGeoDlg = TRUE;
	}
	m_GeoDlg.MoveWindow(800, 460, 720, 500);
	m_GeoDlg.ShowWindow(SW_SHOW);
}
