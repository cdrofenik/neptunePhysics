// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include "wx/wx.h"
#include "wx/glcanvas.h"

class MainGLCanvas; //forward declaration

// OpenGL view data
struct GLData
{
	bool initialized;           // have OpenGL been initialized?
	float beginx, beginy;       // position of mouse
	float quat[4];              // orientation of object
	float zoom;                 // field of view in degrees
};

// Define a new application type, each program should derive a class from wxApp
class NeptunePhysicsApp : public wxApp
{
public:
	NeptunePhysicsApp() {}

	// virtual wxApp methods
	virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MainFrame : public wxFrame
{
public:
	// ctor(s)
	MainFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
			  const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);

	// event handlers (these functions should _not_ be virtual)
	void OnMenuFileExit(wxCommandEvent& event);
	void OnMenuAddObject(wxCommandEvent& event);
	void OnMenuHelpAbout(wxCommandEvent& event);

private:
	MainGLCanvas *m_canvas;

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

class MainGLCanvas : public wxGLCanvas
{
public:
	MainGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = 0,
		const wxString& name = wxT("MainGLCanvas"));

	virtual ~MainGLCanvas();

protected:
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
	void OnMouse(wxMouseEvent& event);

private:
	void InitGL();
	void ResetProjectionMode();

	wxGLContext* m_glRC;
	GLData       m_gldata;

	wxDECLARE_NO_COPY_CLASS(MainGLCanvas);
	wxDECLARE_EVENT_TABLE();
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// menu items
	App_MenuFileExit = wxID_EXIT,
	App_MenuFileAddObject = wxID_HIGHEST + 1,

	// it is important for the id corresponding to the "About" command to have
	// this standard value as otherwise it won't be handled properly under Mac
	// (where it is special and put into the "Apple" menu)
	App_MenuHelpAbout = wxID_ABOUT
};
