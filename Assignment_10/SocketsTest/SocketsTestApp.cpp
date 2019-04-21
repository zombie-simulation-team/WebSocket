/***************************************************************
 * Name:      SocketsTestApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Alex (apons@fiu.edu)
 * Created:   2014-03-22
 * Copyright: Alex ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "SocketsTestApp.h"

//(*AppHeaders
#include "SocketsTestMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SocketsTestApp);

bool SocketsTestApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SocketsTestFrame* Frame = new SocketsTestFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
