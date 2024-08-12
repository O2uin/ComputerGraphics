
// 20201332P4View.cpp: CMy20201332P4View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20201332P4.h"
#endif

#include "20201332P4Doc.h"
#include "20201332P4View.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20201332P4View

IMPLEMENT_DYNCREATE(CMy20201332P4View, CView)

BEGIN_MESSAGE_MAP(CMy20201332P4View, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FILE_OPEN, &CMy20201332P4View::OnFileOpen)
	ON_COMMAND(ID_CAMERA_CONTROL, &CMy20201332P4View::OnCameraControl)
	ON_COMMAND(ID_DISPLAY_CONTROL, &CMy20201332P4View::OnDisplayControl)
	ON_COMMAND(ID_LIGHT_MAT_CONTROL, &CMy20201332P4View::OnLightMatControl)
END_MESSAGE_MAP()

// CMy20201332P4View 생성/소멸

CMy20201332P4View::CMy20201332P4View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_fRotX = 0.0f;
	m_fRotY = 0.0f;
	m_ptMouseDown = 0.0f;

	m_bRotate = FALSE;
	m_bZoom = FALSE;

	m_fTransZ = 30;

	m_From[0] = 0;	m_From[1] = 0;	m_From[2] = 10;
	m_At[0] = 0;	m_At[1] = 0;	m_At[2] = -100;
	m_Up[0] = 0;	m_Up[1] = 1;	m_Up[2] = 0;
	m_Angle = 30;

	m_strFileType = _T("COFF");
	m_strFileWinding = _T("CCW");
	m_bDisplayCameraControl = FALSE;

	m_nDisplayMode = WIRE_FRAME;
	m_nWinding = COUNTER_CLOCKWISE;

	m_bDisplayDisplayControl = FALSE;
	m_bDisplayLightMatControl = FALSE;

	m_fAmbientLight[0] = 0.1f;		m_fAmbientLight[1] = 0.1f;
	m_fAmbientLight[2] = 0.1f;		m_fAmbientLight[3] = 1.0f;

	m_fDiffuseLight[0] = 1.0f;		m_fDiffuseLight[1] = 1.0f;
	m_fDiffuseLight[2] = 1.0f;		m_fDiffuseLight[3] = 1.0f;

	m_fSpecularLight[0] = 1.0f;		m_fSpecularLight[1] = 1.0f;
	m_fSpecularLight[2] = 1.0f;		m_fSpecularLight[3] = 1.0f;

	m_fDiffuseMat[0] = 1.0f;		m_fDiffuseMat[1] = 1.0f;
	m_fDiffuseMat[2] = 1.0f;		m_fDiffuseMat[3] = 1.0f;

	m_fAmbientMat[0] = 0.1f;		m_fAmbientMat[1] = 0.1f;
	m_fAmbientMat[2] = 0.1f;		m_fAmbientMat[3] = 0.1f;

	m_fSpecularMat[0] = 0.5f;		m_fSpecularMat[1] = 0.5f;
	m_fSpecularMat[2] = 0.5f;		m_fSpecularMat[3] = 1.0f;

	m_fLightPos[0] = -50;		m_fLightPos[1] = 50;
	m_fLightPos[2] = 100;		m_fLightPos[3] = 1;
	m_nShine = 64;

	
}

CMy20201332P4View::~CMy20201332P4View()
{
}

BOOL CMy20201332P4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CMy20201332P4View 그리기

void CMy20201332P4View::OnDraw(CDC* pDC)
{
	CMy20201332P4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(m_Angle, m_dAspectRatio, 0.1f, 5000.0f);

	gluLookAt(m_From[0], m_From[1], m_From[2], m_At[0], m_At[1], m_At[2],
		m_Up[0], m_Up[1], m_Up[2]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	RenderScene();
	::glFinish();

	::SwapBuffers(m_pDC->GetSafeHdc());
}


// CMy20201332P4View 진단

#ifdef _DEBUG
void CMy20201332P4View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20201332P4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20201332P4Doc* CMy20201332P4View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20201332P4Doc)));
	return (CMy20201332P4Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20201332P4View 메시지 처리기


int CMy20201332P4View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	InitializeOpenGL();

	return 0;
}


bool CMy20201332P4View::InitializeOpenGL()
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


bool CMy20201332P4View::SetupPixelFormat()
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


void CMy20201332P4View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (0 >= cx || 0 >= cy) {
		return;
	}
	::glViewport(0, 0, cx, cy);

	m_dAspectRatio = (GLdouble)cx / (GLdouble)cy;

}


void CMy20201332P4View::RenderScene()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;

	glLightfv(GL_LIGHT0, GL_AMBIENT, m_fAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_fDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_fSpecularLight);
	glEnable(GL_LIGHT0);

	if (m_strFileType[0] == 'C') {
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}
	else
	{
		glDisable(GL_COLOR_MATERIAL);
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_fAmbientMat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_fDiffuseMat);
	}

	glMaterialfv(GL_FRONT, GL_SPECULAR, m_fSpecularMat);
	glMaterialf(GL_FRONT, GL_SHININESS, m_nShine);

	if (m_nWinding == CLOCKWISE)
		glFrontFace(GL_CW);

	if (m_nWinding == COUNTER_CLOCKWISE)
		glFrontFace(GL_CCW);

	switch (m_nDisplayMode) {
	case WIRE_FRAME:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	case FLAT_SHADING:
		glPolygonMode(GL_FRONT, GL_FILL);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_FLAT);
		break;
	case SMOOTH_SHADING:
		glPolygonMode(GL_FRONT, GL_FILL);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		break;
	default:
		break;
	}

	glLightfv(GL_LIGHT0, GL_POSITION, m_fLightPos);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);


	if (m_bFileOpen == TRUE) {
		for (i = 0; i < m_nCountFace; i++) {
			if (m_nDisplayMode == FLAT_SHADING || m_nDisplayMode == SMOOTH_SHADING) {
				if (m_strFileType[0] == 'C')
					glColor3f(m_FaceIndex[i].Red, m_FaceIndex[i].Green, m_FaceIndex[i].Blue);
				else
					glColor3f(1.0f, 1.0f, 1.0f);
			}

			glBegin(GL_POLYGON);
			if (m_nDisplayMode == FLAT_SHADING)
				glNormal3fv(m_fFaceNormal[i]);

			for (j = 0; j < m_FaceIndex[i].Count; j++) {
				if (m_nDisplayMode == SMOOTH_SHADING)
					glNormal3fv(m_fVertexNormal[m_FaceIndex[i].List[j]]);
				glVertex3f(m_Vertex[m_FaceIndex[i].List[j]].x, m_Vertex[m_FaceIndex[i].List[j]].y,
					m_Vertex[m_FaceIndex[i].List[j]].z);
			}
			glEnd();
		}
	}
	glPopMatrix();
}


void CMy20201332P4View::OnDestroy()
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
}


void CMy20201332P4View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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


void CMy20201332P4View::OnLButtonDown(UINT nFlags, CPoint point)
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


void CMy20201332P4View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptMouseDown = CPoint(0, 0);

	ReleaseCapture();
	::ClipCursor(NULL);

	CView::OnLButtonUp(nFlags, point);
}


void CMy20201332P4View::OnRButtonDown(UINT nFlags, CPoint point)
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


void CMy20201332P4View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptMouseDown = CPoint(0, 0);

	ReleaseCapture();
	::ClipCursor(NULL);
	CView::OnRButtonUp(nFlags, point);
}


void CMy20201332P4View::OnMouseMove(UINT nFlags, CPoint point)
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

			m_From[2] = m_fTransZ;
			m_dlgCameraControl.m_dlgFrom.m_strFromZ.Format(_T("%.1f"), m_From[2]);

			if (m_bDisplayCameraControl)
				m_dlgCameraControl.m_dlgFrom.UpdateData(FALSE);
		}
	}
	m_ptMouseDown = point;
	InvalidateRect(NULL, FALSE);
	CView::OnMouseMove(nFlags, point);
}


void CMy20201332P4View::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i, j;

	TCHAR Filter[] = _T("OFF File(*.OFF) | *.OFF |");
	CFileDialog pDlg(TRUE, _T("OFF file(*.OFF)"), _T("*.OFF"), OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST, Filter, NULL);

	if (pDlg.DoModal() == IDOK) {
		m_fRotX = 0;
		m_fRotY = 0;
		FILE* fp;
		_wfopen_s(&fp, pDlg.GetPathName(), _T("r"));

		fwscanf_s(fp, _T("%s"), m_strFileType, 5);
		fwscanf_s(fp, _T("%s"), m_strFileWinding, 4);

		if (m_strFileWinding.Compare(_T("CW")) == 0)
			m_nWinding = CLOCKWISE;
		else
			m_nWinding = COUNTER_CLOCKWISE;

		fwscanf_s(fp, _T("%d %d %d"), &m_nCountVertex, &m_nCountFace, &m_nCountEdge);

		for (i = 0; i < m_nCountVertex; i++) {
			fscanf_s(fp, "%f %f %f", &m_Vertex[i].x, &m_Vertex[i].y, &m_Vertex[i].z);
		}

		for (i = 0; i < m_nCountFace; i++) {
			fscanf_s(fp, "%d", &m_FaceIndex[i].Count);
			for (j = 0; j < m_FaceIndex[i].Count; j++) {
				fscanf_s(fp, "%d", &m_FaceIndex[i].List[j]);
			}

			if (m_strFileType.Compare(_T("COFF")) == 0) {
				fscanf_s(fp, "%f %f %f", &m_FaceIndex[i].Red, &m_FaceIndex[i].Green,
					&m_FaceIndex[i].Blue);
			}
		}
		m_bFileOpen = TRUE;
		fclose(fp);
	}
	CalcFaceNormal();
	CalcVertexNormal();
	RedrawWindow();
}


void CMy20201332P4View::OnCameraControl()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_bDisplayCameraControl == FALSE)
	{
		m_dlgCameraControl.Create(IDD_DIALOG_CAMERA, this);
		m_bDisplayCameraControl = TRUE;
	}
	m_dlgCameraControl.MoveWindow(655, 55, 235, 320);
	m_dlgCameraControl.ShowWindow(SW_SHOW);
}


void CMy20201332P4View::CalcNormal(float vertex[][3], float normal[])
{
	// TODO: 여기에 구현 코드 추가.
	float vertex1[3], vertex2[3];

	vertex1[0] = vertex[0][0] - vertex[1][0];
	vertex1[1] = vertex[0][1] - vertex[1][1];
	vertex1[2] = vertex[0][2] - vertex[1][2];

	vertex2[0] = vertex[1][0] - vertex[2][0];
	vertex2[1] = vertex[1][1] - vertex[2][1];
	vertex2[2] = vertex[1][2] - vertex[2][2];

	normal[0] = vertex1[1] * vertex2[2] - vertex1[2] * vertex2[1];
	normal[1] = vertex1[2] * vertex2[0] - vertex1[0] * vertex2[2];
	normal[2] = vertex1[0] * vertex2[1] - vertex1[1] * vertex2[0];

	ReduceToUnit(normal);
}


void CMy20201332P4View::ReduceToUnit(float vector[])
{
	// TODO: 여기에 구현 코드 추가.
	float length;
	length = (float)sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));

	if (length == 0.01f)
		length = 1.0f;
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}


void CMy20201332P4View::CalcFaceNormal()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	float normal[3], vertices[3][3];

	for (i = 0; i < 5000; i++)
		for (j = 0; j < 3; j++)
			m_fFaceNormal[i][j] = 0.0f;

	for (i = 0; i < m_nCountFace; i++) {
		for (j = 0; j < 3; j++) {
			vertices[j][0] = m_Vertex[m_FaceIndex[i].List[j]].x;
			vertices[j][1] = m_Vertex[m_FaceIndex[i].List[j]].y;
			vertices[j][2] = m_Vertex[m_FaceIndex[i].List[j]].z;
		}
		CalcNormal(vertices, normal);

		if (m_nWinding == CLOCKWISE) {
			m_fFaceNormal[i][0] = -normal[0];
			m_fFaceNormal[i][1] = -normal[1];
			m_fFaceNormal[i][2] = -normal[2];
		}

		if (m_nWinding == COUNTER_CLOCKWISE) {
			m_fFaceNormal[i][0] = normal[0];
			m_fFaceNormal[i][1] = normal[1];
			m_fFaceNormal[i][2] = normal[2];
		}
	}
}


void CMy20201332P4View::CalcVertexNormal()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;

	for (i = 0; i < 6000; i++)
		for (j = 0; j < 3; j++)
			m_fVertexNormal[i][j] = 0.0f;

	for (i = 0; i < m_nCountFace; i++) {
		for (j = 0; j < m_FaceIndex[i].Count; j++) {
			m_fVertexNormal[m_FaceIndex[i].List[j]][0] += m_fFaceNormal[i][0];
			m_fVertexNormal[m_FaceIndex[i].List[j]][1] += m_fFaceNormal[i][1];
			m_fVertexNormal[m_FaceIndex[i].List[j]][2] += m_fFaceNormal[i][2];
		}
	}
	for (i = 0; i < m_nCountVertex; i++) {
		ReduceToUnit(m_fVertexNormal[i]);
	}
}


void CMy20201332P4View::OnDisplayControl()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_bDisplayDisplayControl == FALSE) {
		m_dlgDisplayControl.Create(IDD_DIALOG_DISPLAY, this);
		m_bDisplayDisplayControl = TRUE;
	}
	m_dlgDisplayControl.MoveWindow(655, 340, 290, 330);
	m_dlgDisplayControl.ShowWindow(SW_SHOW);
}


void CMy20201332P4View::OnLightMatControl()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_bDisplayLightMatControl == FALSE) {
		m_dlgLightMatControl.Create(IDD_DIALOG_LIGHT_MAT, this);
		m_bDisplayLightMatControl = TRUE;
	}
	m_dlgLightMatControl.MoveWindow(655, 55, 320, 400);
	m_dlgLightMatControl.ShowWindow(SW_SHOW);
}
