// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/filedlg.h"
#endif

#if !wxUSE_GLCANVAS
#error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include "main.h"
#include "../TriangleMesh.h"

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif

#include <GL/glu.h>

#define wxMAIN_WINDOW_WIDTH 1024
#define wxMAIN_WINDOW_HEIGHT 576

// ----------------------------------------------------------------------------
// NeptunePhysicsApp: Main app
// ----------------------------------------------------------------------------

bool NeptunePhysicsApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	wxSize frameSize(wxMAIN_WINDOW_WIDTH, wxMAIN_WINDOW_HEIGHT);

	MainFrame *frame = new MainFrame(NULL, wxT("Neptune Physics Simulator"),
		wxDefaultPosition, frameSize);
	frame->Show(true);

	return true;
}

IMPLEMENT_APP(NeptunePhysicsApp)


// ----------------------------------------------------------------------------
// MainFrame: the main frame/window
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(App_MenuFileExit, MainFrame::OnMenuFileExit)
EVT_MENU(App_MenuFileAddObject, MainFrame::OnMenuAddObject)
EVT_MENU(App_MenuHelpAbout, MainFrame::OnMenuHelpAbout)
wxEND_EVENT_TABLE()

std::vector<TriangleMesh> objectList;

MainFrame::MainFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
	const wxSize& size, long style)
	: wxFrame(frame, wxID_ANY, title, pos, size, style)
{
	SetIcon(wxICON(sample));

	// File menu
	wxMenu *fileMenu = new wxMenu;
	//fileMenu->AppendSeparator();
	fileMenu->Append(App_MenuFileExit);

	// Object menu
	wxMenu *objectMenu = new wxMenu;
	objectMenu->Append(App_MenuFileAddObject, "&Add object...\tF1", "Add object to the scene");

	// Help menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(App_MenuHelpAbout, "&About\tF9", "Show about dialog");

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, wxT("&File"));
	menuBar->Append(objectMenu, wxT("&Object"));
	menuBar->Append(helpMenu, wxT("&Help"));

	SetMenuBar(menuBar);
	CreateStatusBar();

	Show(true);


	wxSize glCanvasSize(200, 200);
	m_canvas = new MainGLCanvas(this, wxID_ANY, wxDefaultPosition,
		GetClientSize(), wxSUNKEN_BORDER);
}

void MainFrame::OnMenuAddObject(wxCommandEvent& event) {

	wxString caption = wxT("Choose a Wavefront file (*.OBJ)");
	wxString wildcard = wxT("Obj files(*.obj) | *.obj");
	wxString defaultDir = wxT("c:\\temp");
	wxString defaultFilename = wxEmptyString;

	wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxString path = dialog.GetPath();
		int filterIndex = dialog.GetFilterIndex();

		//Load .obj file
		TriangleMesh tmpObject;
		tmpObject.createWavefrontMesh(path.c_str());
		objectList.push_back(tmpObject);
	}
}

void MainFrame::OnMenuHelpAbout(wxCommandEvent& event) {
	wxMessageBox(wxString::Format
		(
		"Welcome to %s!\n"
		"\n"
		"This application is  running under %s",
		"Neptune Physics Simulator",
		wxGetOsDescription()
		),
		"About Neptune Physics Simulator",
		wxOK | wxICON_INFORMATION,
		this);
}

void MainFrame::OnMenuFileExit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

// ----------------------------------------------------------------------------
// MainGLCanvas: the OpenGL canvas
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MainGLCanvas, wxGLCanvas)
EVT_SIZE(MainGLCanvas::OnSize)
EVT_PAINT(MainGLCanvas::OnPaint)
EVT_ERASE_BACKGROUND(MainGLCanvas::OnEraseBackground)
EVT_MOUSE_EVENTS(MainGLCanvas::OnMouse)
wxEND_EVENT_TABLE()

MainGLCanvas::MainGLCanvas(wxWindow *parent,
						   wxWindowID id,
						   const wxPoint& pos,
						   const wxSize& size,
						   long style,
						   const wxString& name)
	: wxGLCanvas(parent, id, NULL, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name)
{
	m_glRC = new wxGLContext(this);

	m_gldata.initialized = false;

	// initialize view matrix
	m_gldata.beginx = 0.0f;
	m_gldata.beginy = 0.0f;
	m_gldata.zoom = 45.0f;
}

MainGLCanvas::~MainGLCanvas()
{
	delete m_glRC;
}

void MainGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	// must always be here
	wxPaintDC dc(this);

	SetCurrent(*m_glRC);

	// Initialize OpenGL
	if (!m_gldata.initialized)
	{
		InitGL();
		ResetProjectionMode();
		m_gldata.initialized = true;
	}

	// Clear
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Transformations
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	GLfloat m[4][4];
	
	//build_rotmatrix(m, m_gldata.quat);
	
	glMultMatrixf(&m[0][0]);

	for (int x = 0; x < 10; x++){
		glBegin(GL_LINE_LOOP);
		glVertex3f(x, 0, 0);
		glVertex3f(x, 0.5, 0);
		glEnd();
	};

	for (int y = 0; y < 10; y++){
		glBegin(GL_LINE_LOOP);
		glVertex3f(y, 0, 0);
		glVertex3f(y, 0.5, 0);
		glEnd();
	};
	
	glFlush();

	SwapBuffers();
}

void MainGLCanvas::OnSize(wxSizeEvent& WXUNUSED(event))
{
	// Reset the OpenGL view aspect.
	// This is OK only because there is only one canvas that uses the context.
	// See the cube sample for that case that multiple canvases are made current with one context.
	ResetProjectionMode();
}

void MainGLCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
	// Do nothing, to avoid flashing on MSW
}

void MainGLCanvas::OnMouse(wxMouseEvent& event)
{
	if (event.Dragging())
	{
		wxSize sz(GetClientSize());

		/* drag in progress, simulate trackball */
		/*float spin_quat[4];
		trackball(spin_quat,
			(2.0*m_gldata.beginx - sz.x) / sz.x,
			(sz.y - 2.0*m_gldata.beginy) / sz.y,
			(2.0*event.GetX() - sz.x) / sz.x,
			(sz.y - 2.0*event.GetY()) / sz.y);

		add_quats(spin_quat, m_gldata.quat, m_gldata.quat);
*/
		/* orientation has changed, redraw mesh */
		Refresh(false);
	}

	m_gldata.beginx = event.GetX();
	m_gldata.beginy = event.GetY();
}

void MainGLCanvas::InitGL()
{
	static const GLfloat light0_pos[4] = { -50.0f, 50.0f, 0.0f, 0.0f };

	// white light
	static const GLfloat light0_color[4] = { 0.6f, 0.6f, 0.6f, 1.0f };

	static const GLfloat light1_pos[4] = { 50.0f, 50.0f, 0.0f, 0.0f };

	// cold blue light
	static const GLfloat light1_color[4] = { 0.4f, 0.4f, 1.0f, 1.0f };

	/* remove back faces */
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	/* speedups */
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

	/* light */
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_color);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void MainGLCanvas::ResetProjectionMode()
{
	if (!IsShownOnScreen())
		return;

	// This is normally only necessary if there is more than one wxGLCanvas
	// or more than one wxGLContext in the application.
	SetCurrent(*m_glRC);

	int w, h;
	GetClientSize(&w, &h);

	// It's up to the application code to update the OpenGL viewport settings.
	// In order to avoid extensive context switching, consider doing this in
	// OnPaint() rather than here, though.
	glViewport(0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
