/***************************************************************
 * Name:      SocketsTestMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alex (apons@fiu.edu)
 * Created:   2014-03-22
 * Copyright: Alex ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "SocketsTestMain.h"
#include <wx/msgdlg.h>



//(*InternalHeaders(SocketsTestFrame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SocketsTestFrame)
const long SocketsTestFrame::ID_BUTTON2 = wxNewId();
const long SocketsTestFrame::ID_STATICTEXT1 = wxNewId();
const long SocketsTestFrame::ID_TEXTCTRL1 = wxNewId();
const long SocketsTestFrame::ID_BUTTON1 = wxNewId();
const long SocketsTestFrame::ID_CHOICE1 = wxNewId();
const long SocketsTestFrame::ID_SPINCTRL1 = wxNewId();
const long SocketsTestFrame::ID_STATICTEXT2 = wxNewId();
const long SocketsTestFrame::ID_STATICTEXT3 = wxNewId();
const long SocketsTestFrame::idMenuQuit = wxNewId();
const long SocketsTestFrame::idMenuAbout = wxNewId();
const long SocketsTestFrame::ID_STATUSBAR1 = wxNewId();
//*)

//BEGIN_EVENT_TABLE(SocketsTestFrame,wxFrame)
    //(*EventTable(SocketsTestFrame)
    //*)
//END_EVENT_TABLE()


BEGIN_EVENT_TABLE(SocketsTestFrame, wxFrame)
    EVT_MENU(CLIENT_QUIT,       SocketsTestFrame::OnQuit)
    EVT_MENU(CLIENT_OPEN,       SocketsTestFrame::OnConnectToServer)
    EVT_SOCKET(SOCKET_ID,       SocketsTestFrame::OnSocketEvent)
END_EVENT_TABLE()


SocketsTestFrame::SocketsTestFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SocketsTestFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, _("Test Server"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(500,500));
    SetMaxSize(wxSize(-1,-1));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("./connect.ico"))));
    	SetIcon(FrameIcon);
    }
    Button2 = new wxButton(this, ID_BUTTON2, _("Quit"), wxPoint(304,296), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter Info for Echo from Server"), wxPoint(16,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(16,56), wxSize(376,216), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Button1 = new wxButton(this, ID_BUTTON1, _("Send"), wxPoint(24,288), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Choice1 = new wxChoice(this, ID_CHOICE1, wxPoint(168,384), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("Turn On")) );
    Choice1->Append(_("Turn Off"));
    Choice1->Append(_("Turn Left"));
    Choice1->Append(_("Turn Right"));
    Choice1->Append(_("Set Speed"));
    SpinCtrl1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("1"), wxPoint(24,384), wxDefaultSize, 0, 1, 255, 1, _T("ID_SPINCTRL1"));
    SpinCtrl1->SetValue(_T("1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Speed: "), wxPoint(24,360), wxSize(144,17), 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Motor Options:"), wxPoint(168,360), wxSize(168,17), 0, _T("ID_STATICTEXT3"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SocketsTestFrame::OnButton1Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SocketsTestFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SocketsTestFrame::OnAbout);
    //*)


    wxMenu *m_menuFile, *m_menuSocket;


    m_menuFile = new wxMenu();
    m_menuFile->Append(CLIENT_QUIT, _("E&xit\tAlt-X"), _("Quit client"));

    m_menuSocket = new wxMenu();
    m_menuSocket->Append(CLIENT_OPEN, _("&Connect"), _("Connect to server"));

    MenuBar1->Append(m_menuFile, _("&XFile"));
    MenuBar1->Append(m_menuSocket, _("&Client"));

    // Make a textctrl for logging

    TextCtrl1->AppendText(_("Welcome to the Socket Event Demo: Client ready\n"));

}

SocketsTestFrame::~SocketsTestFrame()
{
    //(*Destroy(SocketsTestFrame)
    //*)
}

void SocketsTestFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void SocketsTestFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}






// event handlers



void SocketsTestFrame::OnConnectToServer(wxCommandEvent& WXUNUSED(event))
{

    // Ask user for server address
    wxString hostname = wxGetTextFromUser(
    _("Enter the address of the Socket Event Demo server:"),
    _("Connect ..."),
    _("localhost"));

    wxIPV4address addr;
    addr.Hostname(hostname);
    addr.Service(3000);

    // Create the socket
    wxSocketClient* Socket = new wxSocketClient();

    // Set up the event handler and subscribe to most events
    Socket->SetEventHandler(*this, SOCKET_ID);
    Socket->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    Socket->Notify(true);

    // Wait for the connection event
    Socket->Connect(addr, false);
}


void SocketsTestFrame::OnSocketEvent(wxSocketEvent& event)
{
     static int cnt = 1;
    // The socket that had the event
    wxSocketBase* sock = event.GetSocket();

    // Common buffer shared by the events
    char buf[10]={};

    switch(event.GetSocketEvent())
    {
        case wxSOCKET_CONNECTION:
        {
            wxString tt = wxString::Format(wxT("\nConnection Num:%i\n"),cnt++);
            TextCtrl1->AppendText(tt);
            TextCtrl1->AppendText(_("Connected to server.\n"));

            // Fill the arry with the numbers 0 through 9 as characters
            char mychar = '0';
//            buf[0] = 2;
//            buf[1] = 1;
            unsigned int choice = Choice1->GetSelection();
            switch(choice){
                case 0:
                    buf[0] = 2;
                    buf[1] = 1;
                    TextCtrl1->AppendText(_("Sending Do nothing \n"));
                    break;
                case 1:
                    buf[0] = 2;
                    buf[1] = 2;
                    TextCtrl1->AppendText(_("Sending Turn On Motor \n"));
                    break;
                case 2:
                    buf[0] = 2;
                    buf[1] = 3;
                    TextCtrl1->AppendText(_("Sending Turn Motor Left \n"));
                    break;
                case 3:
                    buf[0] = 2;
                    buf[1] = 4;
                    TextCtrl1->AppendText(_("Sending Turn Motor Right \n"));
                    break;
                case 4:
                    int speed = SpinCtrl1->GetValue();
                    if(speed < 10){
                        buf[0] = 3;
                    }else if(speed < 100){
                        buf[0] = 4;
                    }else if(speed >= 100){
                        buf[0] = 5;
                    }
                    else{
                        buf[0] = 3;
                    }
                    buf[1] = 5;
                    TextCtrl1->AppendText(wxString::Format(wxT("The speed being sent is: %d \n"), speed));
                    buf[2] = speed;
                    break;

            }

            // Send the characters to the server
            sock->Write(buf, 10);
            break;
        }
        case wxSOCKET_INPUT:
        {
            sock->Read(buf, 6);

            TextCtrl1->AppendText(wxString(wxT("Received from server: ")) + buf + ("\n"));

            break;
        }

        // The server hangs up after sending the data
        case wxSOCKET_LOST:
        {
            sock->Destroy();

            TextCtrl1->AppendText(_("\nConnection lost.\n"));

            break;
        }
    }
}




void SocketsTestFrame::OnButton1Click(wxCommandEvent& event)
{
 wxIPV4address addr;
    addr.Hostname(wxT("localhost"));
    addr.Service(3000);

    // Create the socket
    wxSocketClient* Socket = new wxSocketClient();

    // Set up the event handler and subscribe to most events
    Socket->SetEventHandler(*this, SOCKET_ID);
    Socket->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    Socket->Notify(true);

    // Wait for the connection event
    Socket->Connect(addr, false);

}

void SocketsTestFrame::OnButton2Click(wxCommandEvent& event)
{
      Close();
}
