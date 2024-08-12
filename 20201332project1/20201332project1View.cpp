
// 20201332project1View.cpp: CMy20201332project1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20201332project1.h"
#endif

#include "20201332project1Doc.h"
#include "20201332project1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20201332project1View

IMPLEMENT_DYNCREATE(CMy20201332project1View, CView)

BEGIN_MESSAGE_MAP(CMy20201332project1View, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_REVOLUTION, &CMy20201332project1View::OnRevolution)
	ON_COMMAND(ID_STOP, &CMy20201332project1View::OnStop)
END_MESSAGE_MAP()

// CMy20201332project1View 생성/소멸

CMy20201332project1View::CMy20201332project1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_fRotX = 0.0f;
	m_fRotY = 0.0f;
	m_ptMouseDown = 0.0f;

	m_bRotate = FALSE;
	m_bZoom = FALSE;

	m_fTransZ = -250;

	m_fRevolutionAngle = 0.0f;
	m_fRevolutionEarth = 0.0f;
	m_fRevolutionMoon = 0.0f;
	m_fRotationEarth = 0.0f;

	m_fFramePerYear = 360.0f;

	m_bRevolution = FALSE;
}

CMy20201332project1View::~CMy20201332project1View()
{
}

BOOL CMy20201332project1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CMy20201332project1View 그리기

void CMy20201332project1View::OnDraw(CDC* pDC)
{
	CMy20201332project1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	GLfloat fRange = 150.0f;

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	::gluPerspective(45.0f, m_dAspectRatio, 1.0f, 500.0f);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();


	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderScene();
	::glFinish();

	::SwapBuffers(m_pDC->GetSafeHdc());
}


// CMy20201332project1View 진단

#ifdef _DEBUG
void CMy20201332project1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20201332project1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20201332project1Doc* CMy20201332project1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20201332project1Doc)));
	return (CMy20201332project1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20201332project1View 메시지 처리기


int CMy20201332project1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	InitializeOpenGL();
	SetTimer(0, 50, NULL);

	return 0;
}


bool CMy20201332project1View::InitializeOpenGL()
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

	glGenTextures(3, m_nTexture);
	m_nTexture[0] = TextureLoad(_T("sun.bmp"));
	m_nTexture[1] = TextureLoad(_T("earth.bmp"));
	m_nTexture[2] = TextureLoad(_T("moon.bmp"));

	return TRUE;
}


bool CMy20201332project1View::SetupPixelFormat()
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


void CMy20201332project1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//GLdouble aspect_ratio;
	if (0 >= cx || 0 >= cy) {
		return;
	}
	::glViewport(0, 0, cx, cy);
	
	//aspect_ratio = (GLdouble)cx / (GLdouble)cy;
	m_dAspectRatio = (GLdouble)cx / (GLdouble)cy;

	/*::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	::gluPerspective(45.0f, aspect_ratio, 0.01f, 200.0f);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();*/
}


void CMy20201332project1View::RenderScene()
{
	// TODO: 여기에 구현 코드 추가.
	GLfloat ambientLight[] = { 0.25f,0.25f,0.25f,1.0f };//주변반사=>광원에 노출없이 생김
	GLfloat diffuseLight[] = { 1.0f,1.0f,1.0f,0.9f };//난반사=>빛 방향에 따라 물체 밝기 변화
	GLfloat lightPos[] = { 10.0f,0.0f,0.0f,0.0f };//광원 위치
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };//정반사=>반질한 면 표현, 광원 색 보이는 점?
	GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 10);
	glDepthFunc(GL_LEQUAL);

	glTranslatef(0.0f, 0.0f, m_fTransZ);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);

	//태양
	glBindTexture(GL_TEXTURE_2D, m_nTexture[0]);//텍스처
	glRotatef(m_fRevolutionAngle, 0.0f, 1.0f, 0.0f);//자전(태양)
	renderSphere(0, 0, 0, 30, 40);
	//glutSolidSphere(30.0f, 50, 50);//크기

	//지구
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, m_nTexture[1]);//텍스처
		glRotatef(m_fRevolutionEarth, 0.0f, 1.0f, 0.0f);//태양 기준 revolutionEarth만큼 공전(지구)
		glTranslatef(120.0f, 0.0f, 0.0f);//원점에서 떨어진 거리
		glRotatef(m_fRotationEarth, 0.0f, 1.0f, 0.0f);//지구 기준, rotationEarth만큼 자전(지구)
		renderSphere(0, 0, 0, 10, 40);
		//glutSolidSphere(10.0f, 15, 15);//크기, 둥근정도?

		//달
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, m_nTexture[2]);//텍스처
			glRotatef(m_fRevolutionMoon, 0.0f, 1.0f, 0.0f);//지구 기준, revolutionMoon만큼 공전(달)
			glTranslatef(30.0f, 0.0f, 0.0f);
			renderSphere(0, 0, 0, 5, 40);
			//glutSolidSphere(5.0f, 15, 15);
		glPopMatrix();
	glPopMatrix();

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	
	
}


void CMy20201332project1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) {
	case VK_UP:
		m_fRotX -= 5.0f;
		
		break;
	case VK_DOWN:
		m_fRotX += 5.0f;
		
		break;
	case VK_LEFT:
		m_fRotY -= 5.0f;
		
		break;
	case VK_RIGHT:
		m_fRotY += 5.0f;
		
		break;
	}
	RedrawWindow();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy20201332project1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bRotate = TRUE;
	m_bZoom = FALSE;
	m_ptMouseDown = point;
	SetCapture();

	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ROTATE);
	SetCursor(hCursor);

	CRect rectClient;
	GetClientRect(&rectClient);
	ClientToScreen(&rectClient);
	::ClipCursor(&rectClient);
	CView::OnLButtonDown(nFlags, point);
}


void CMy20201332project1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptMouseDown = CPoint(0, 0);

	ReleaseCapture();
	::ClipCursor(NULL);
	CView::OnLButtonUp(nFlags, point);
}


void CMy20201332project1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bRotate = FALSE;
	m_bZoom = TRUE;
	m_ptMouseDown = point;
	SetCapture();

	HCURSOR hCursor = AfxGetApp()->LoadCursorW(IDC_CURSOR_ZOOM);
	SetCursor(hCursor);

	CRect rectClient;
	GetClientRect(&rectClient);
	ClientToScreen(&rectClient);
	::ClipCursor(&rectClient);
	CView::OnRButtonDown(nFlags, point);
}


void CMy20201332project1View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptMouseDown = CPoint(0, 0);

	ReleaseCapture();
	::ClipCursor(NULL);
	CView::OnRButtonUp(nFlags, point);
}


void CMy20201332project1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bRotate) {
		if (GetCapture() == this) {
			m_fRotX += (point.y - m_ptMouseDown.y) / 3.6;
			m_fRotY += (point.x - m_ptMouseDown.x) / 3.6;
		}
	}
	if (m_bZoom) {
		if (GetCapture() == this) {
			m_fTransZ += (point.y - m_ptMouseDown.y);
		}
	}
	m_ptMouseDown = point;
	InvalidateRect(NULL, FALSE);
	CView::OnMouseMove(nFlags, point);
}


void CMy20201332project1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bRevolution) {
		m_fRevolutionAngle += 10.0f;//태양
		if (m_fRevolutionAngle > 360.0f)
			m_fRevolutionAngle = 0.0f;

		m_fRotationEarth += (360.0f * 360.0f) / m_fFramePerYear;//지구자전
		if (m_fRotationEarth >= 360.0f)
			m_fRotationEarth = 0.0f;

		m_fRevolutionMoon += (360.0f * 12.0f) / m_fFramePerYear;//달자전
		if (m_fRevolutionMoon >= 360.0f)
			m_fRevolutionMoon = 0.0f;

		m_fRevolutionEarth += 360.0f / m_fFramePerYear;//지구공전 
		if (m_fRevolutionEarth >= 360.0f)
			m_fRevolutionEarth = 0.0f;

		InvalidateRect(NULL, FALSE);
	}
	CView::OnTimer(nIDEvent);
}


void CMy20201332project1View::OnDestroy()
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


GLuint CMy20201332project1View::TextureLoad(LPCWSTR filename)
{
	// TODO: 여기에 구현 코드 추가.
	AUX_RGBImageRec*	texture;
	GLuint				texObject;

	texture = auxDIBImageLoad(filename);//filename에서 정보 가져옴
	if (!texture) {
		MessageBox(_T("Picture could not be loaded"));
		exit(1);
	}

	glGenTextures(1, &texObject);//텍스처 오브젝트 생성
	glBindTexture(GL_TEXTURE_2D, texObject);//바인딩

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
	return (texObject);

	//return GLuint();
}


void CMy20201332project1View::OnRevolution()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bRevolution = TRUE;
}


void CMy20201332project1View::OnStop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bRevolution = FALSE;
}


void CMy20201332project1View::renderSphere(float cx, float cy, float cz, float radius, int paint)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	const float PI = 3.14159265358979f; //삼각함수에 필요한 원주율 선언 180각도
	const float TWOPI = 6.28318530717958f; //원주율의 2배 360도
	const float PIDIV2 = 1.57079632679489f; // 90도

	float theta1 = 0.0;
	float theta2 = 0.0;
	float theta3 = 0.0;

	float ex = 0.0f;
	float ey = 0.0f;
	float ez = 0.0f;

	float px = 0.0f;
	float py = 0.0f;
	float pz = 0.0f;

	// 반지름이 - 인경우 부호변경
	if (radius < 0)
		radius = -radius;

	// 정밀도가 -인 경우 부호변경
	if (paint < 0)
		paint = -paint;

	// 구가 너무 작으면, 바로 대신 OpenGL에 포인터를 찍는다.
	if (paint < 4 || radius <= 0) {
		glBegin(GL_POINTS);
		glVertex3f(cx, cy, cz);
		glEnd();
		return;
	}

	//vertex 좌표 설정으은 x와 z의 값을 왼쪽끝에서 오른쪽 끝까지를 (0도 ~ 360도)로 잡고 회전시키면서 좌표를 찍는다.
	//반경 r과 정밀도 n으로 c에 중앙에 두게 되는 구를 만듭니다 0 반경 구를 위해 포인트를 끕니다
	for (i = 0; i < paint / 2; ++i) {   //중심각을 갖는 원의 둘레점의 좌표를 계산
		theta1 = i * TWOPI / paint - PIDIV2;
		theta2 = (i + 1) * TWOPI / paint - PIDIV2;

		glBegin(GL_TRIANGLE_STRIP);
		{
			for (j = 0; j <= paint; ++j)
			{
				theta3 = j * TWOPI / paint;

				ex = cos(theta2) * cos(theta3);
				ey = sin(theta2); //사인값이 x,z,에 곱해줄 배율이 된다.
				ez = cos(theta2) * sin(theta3); //z축 방향으로 바라보았을때 원의 모양이 되도록 하기 위해서 ex,ez값에 곱해줄 배율과 ey값을 설정한다.
				px = cx + radius * ex;
				py = cy + radius * ey;
				pz = cz + radius * ez;
				//반경과 정밀도 n으로  중앙에 두게 되는 구를 만든다 반경 구를 위해 vertex를 찍는다
				glNormal3f(ex, ey, ez);
				glTexCoord2f(-(j / (float)paint), 2 * (i + 1) / (float)paint);
				glVertex3f(px, py, pz);

				ex = cos(theta1) * cos(theta3);
				ey = sin(theta1);
				ez = cos(theta1) * sin(theta3);
				px = cx + radius * ex;
				py = cy + radius * ey;
				pz = cz + radius * ez;

				glNormal3f(ex, ey, ez);
				glTexCoord2f(-(j / (float)paint), 2 * i / (float)paint);
				glVertex3f(px, py, pz);
			}
		}
		glEnd();
	}
}
