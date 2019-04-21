/***************************************************************
 * Name:      SocketsTestMain.h
 * Purpose:   Defines Application Frame
 * Author:    Alex (apons@fiu.edu)
 * Created:   2014-03-22
 * Copyright: Alex ()
 * License:
 **************************************************************/

#ifndef SOCKETSTESTMAIN_H
#define SOCKETSTESTMAIN_H

//(*Headers(SocketsTestFrame)
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
//*)

#include "wx/socket.h"

class SocketsTestFrame: public wxFrame
{
    public:

        SocketsTestFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SocketsTestFrame();

    private:

        //(*Handlers(SocketsTestFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        //*)

   // event handlers for Socket menu
    void OnConnectToServer(wxCommandEvent& event);

    // socket event handler
    void OnSocketEvent(wxSocketEvent& event);

        //(*Identifiers(SocketsTestFrame)
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_CHOICE1;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SocketsTestFrame)
        wxStatusBar* StatusBar1;
        wxButton* Button1;
        wxButton* Button2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxChoice* Choice1;
        wxTextCtrl* TextCtrl1;
        wxStaticText* StaticText2;
        wxSpinCtrl* SpinCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};


enum
{
    // menu items
    CLIENT_QUIT = 1000,
    CLIENT_OPEN,

    // id for socket
    SOCKET_ID
};








#endif // SOCKETSTESTMAIN_H
