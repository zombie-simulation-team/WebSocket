#include <iostream>
#include <stdio.h>

using namespace std;


// for all others, include the necessary headers
#ifndef WX_PRECOMP
#  include "wx/wx.h"
#endif

#include "wx/socket.h"



// *************** MyApp ************************************
class MyApp : public wxApp
//class MyApp : public wxAppConsole
{
    public:
        MyApp();
        virtual bool OnInit();
        virtual int OnExit();
//        virtual int OnRun();
     // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnServerEvent(wxSocketEvent& event);
    void OnSocketEvent(wxSocketEvent& event);
    void OnServerStart();
private:
    wxSocketServer *m_server;

    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};





enum
{
    // menu items
    SERVER_QUIT = 1000,
    SERVER_START,

    // id for sockets
    SERVER_ID,
    SOCKET_ID
};

// --------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// --------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyApp, wxApp)
    EVT_SOCKET(SERVER_ID,  MyApp::OnServerEvent)
    EVT_SOCKET(SOCKET_ID,  MyApp::OnSocketEvent)
END_EVENT_TABLE()



void MyApp::OnServerStart()
{
    // Create the address - defaults to localhost
    wxIPV4address addr;
    addr.Service(3000);

    // Create the socket, we maintain a class pointer so we can shut it down
    m_server = new wxSocketServer(addr);

    // We use Ok() here to see if the server is really listening
    if (! m_server->Ok())
    {
        return;
    }

    wxPrintf(_("\nSocket server listening.\n"));

    // Setup the event handler and subscribe to connection events
    m_server->SetEventHandler(*this, SERVER_ID);
    m_server->SetNotify(wxSOCKET_CONNECTION_FLAG);
    m_server->Notify(true);
}



void MyApp::OnServerEvent(wxSocketEvent& WXUNUSED(event))
{
    // Accept the new connection and get the socket pointer
    wxSocketBase* sock = m_server->Accept(false);

    // Tell the new socket how and where to process its events
    sock->SetEventHandler(*this, SOCKET_ID);
    sock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    sock->Notify(true);

    wxPrintf(_("\nAccepted incoming connection.\n"));
}


struct {
unsigned int state:1;   // 0-stopped 1- running
unsigned int dir:1;     // 0 - left 1 - right
unsigned int spd:8;     // 0 to 255
}motor;




void MyApp::OnSocketEvent(wxSocketEvent& event)
{
    wxSocketBase *sock = event.GetSocket();
    wxPrintf(wxString(_(" Socket Function ")) + _("\n"));
    // Process the event
    switch(event.GetSocketEvent())
    {
        case wxSOCKET_INPUT:
        {
            char buf[10];
            char PktSize;
            char cmd;
            char Speed1;
            char Speed2;
            char Speed3;


            char speed[10];
            sock->Read(&PktSize, 1);
            sock->Read(&cmd, 1);
            wxPrintf(wxString::Format(wxT(" Packet Size %d \n"), PktSize));

            switch (cmd) {
            case 0:   // No command
               buf[0]=6;
               buf[1]=0;
               strcpy(&buf[2], "Err");
               sock->Write(buf, 6);
               wxPrintf(wxString(_(" No Command ")) + _("\n"));
            break;
            case 1:   // Start Motor
               if (motor.state == 0) {
                // Start motor
                   motor.state =1;
                   buf[0]=5;
                   buf[1]=0;
                   strcpy(&buf[2], "Ok");
                   sock->Write(buf, 5);
                   wxPrintf(wxString(_(" Start motor ")) + _("\n"));
               }
               else {
                // Motor already running error
                   buf[0]=6;
                   buf[1]=0;
                   strcpy(&buf[2], "Err");
                   sock->Write(buf, 6);
                   wxPrintf(wxString(_(" ERROR: Motor is already running ")) + _("\n"));
               }
             break;

            case 2:   // stop Motor
              if (motor.state == 1) {
                   motor.state =0;
                   buf[0]=5;
                   buf[1]=0;
                   strcpy(&buf[2], "Ok");
                   sock->Write(buf, 5);
                   wxPrintf(wxString(_(" Motor Stopped ")) + _("\n"));
               }
               else {
                // Motor already stopped error
                   buf[0]=6;
                   buf[1]=0;
                   strcpy(&buf[2], "Err");
                   sock->Write(buf, 6);
                   wxPrintf(wxString(_(" ERROR: Motor Already Stopped")) + _("\n"));
               }

            break;

            case 3:   // Rotate Left
             if (motor.state == 1) {
                   motor.dir = 0;
                   buf[0]=5;
                   buf[1]=0;
                   strcpy(&buf[2], "Ok");
                   sock->Write(buf, 5);
                   wxPrintf(wxString(_(" Rotate Left ")) + _("\n"));
               }
               else {
                // Motor already running error
                   buf[0]=6;
                   buf[1]=0;
                   strcpy(&buf[2], "Err");
                   sock->Write(buf, 6);
                   wxPrintf(wxString(_(" ERROR: Motor OFF for Rotate Left")) + _("\n"));
               }
            break;

            case 4:   // Rotate Right
                if (motor.state == 1) {
                   motor.dir = 1;
                   buf[0]=5;
                   buf[1]=0;
                   strcpy(&buf[2], "Ok");
                   sock->Write(buf, 5);
                   wxPrintf(wxString(_(" Rotate Right ")) + _("\n"));
               }
               else {
                // Motor already running error
                   buf[0]=6;
                   buf[1]=0;
                   strcpy(&buf[2], "Err");
                   sock->Write(buf, 6);
                   wxPrintf(wxString(_("ERROR: Motor OFF for Rotate Right ")) + _("\n"));
               }
            break;

            case 5:   // Speed
            if ((motor.state == 1)) {
                    switch(PktSize){
                    case 5:
                        sock->Read(&Speed1, 1);
                        sock->Read(&Speed2, 1);
                        sock->Read(&Speed3, 1);
                        wxPrintf(wxString::Format(wxT("Setting motor speed to: %i"),Speed1,Speed2,Speed3));
                        break;
                    case 4:
                        sock->Read(&Speed1, 1);
                        sock->Read(&Speed2, 1);
                        wxPrintf(wxString::Format(wxT("Setting motor speed to: %i"),Speed1, Speed2));
                        break;
                    case 3:
                        sock->Read(&Speed1, 1);
                        wxPrintf(wxString::Format(wxT("Setting motor speed to: %i"),Speed1));
                        break;
                    }
                   strcpy(&buf[2], "Ok");
                   sock->Write(buf, 5);
//                   wxPrintf(wxString(_(" Set Speed: "))+ wxString(speed) + _("\n"));
               }
               else {
                // Motor already running error
                   buf[0]=6;
                   buf[1]=0;
                   strcpy(&buf[2], "Err");
                   sock->Write(buf, 6);
                   wxPrintf(wxString(_(" Motor is not on ")) + _("\n"));
               }
            break;

            default:
                   buf[0]=6;
                   buf[1]=0;
                   strcpy(&buf[2], "Err");
                   sock->Write(buf, 6);
                   wxPrintf(wxString(_(" Default ERROR ")) + _("\n"));
            break;

            }
            wxPrintf(_("\nWrote string back to client.\n"));

            // We are done with the socket, destroy it
            sock->Destroy();

            break;
        }
        case wxSOCKET_LOST:
        {
            sock->Destroy();
            break;
        }
    }
}


MyApp::MyApp():wxApp()
//MyApp::MyApp():wxAppConsole()
{
}

bool MyApp::OnInit()
{

   wxPrintf(_("Started Server.\n"));

   OnServerStart();

   return true; // on continue le traitement
}



int MyApp::OnExit()
{
    cout<<"OnExit"<<endl;
return 0;
}

IMPLEMENT_APP(MyApp);






