/*
Copyright (c) 2004, 2005, 2006 The FlameRobin Development Team

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


  $Id$

*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "config/Config.h"
#include "images.h"
#include "gui/controls/PrintableHtmlWindow.h"
#include "gui/SimpleHtmlFrame.h"
//-----------------------------------------------------------------------------
bool showHtmlFile(wxWindow* parent, const wxFileName& fileName)
{
    if (!fileName.FileExists())
    {
        wxString msg;
        msg.Printf(_("The HTML document \"%s\" does not exist!"),
            fileName.GetFullPath().c_str());
        wxMessageBox(msg, _("FlameRobin"), wxOK | wxICON_ERROR);
        return false;
    }

    SimpleHtmlFrame* shf = SimpleHtmlFrame::findFrameFor(fileName);
    if (shf)
    {
        shf->Raise();
        return true;
    }
    shf = new SimpleHtmlFrame(parent, fileName.GetFullPath());
    shf->Show();
    return true;
}
//-----------------------------------------------------------------------------
SimpleHtmlFrame::SimpleHtmlFrame(wxWindow* parent, const wxFileName& fileName)
    : BaseFrame(parent, -1, wxEmptyString)
{
    html_window = new PrintableHtmlWindow(this);
    CreateStatusBar();
    html_window->SetRelatedFrame(this, wxT("%s"));
    html_window->SetRelatedStatusBar(0);

    html_window->LoadPage(fileName.GetFullPath());
    fileNameM = fileName.GetFullName();
    setIdString(this, getFrameId(fileName));

    #include "flamerobin.xpm"
    wxBitmap bmp(flamerobin_xpm);
    wxIcon icon;
    icon.CopyFromBitmap(bmp);
    SetIcon(icon);
}
//-----------------------------------------------------------------------------
const wxRect SimpleHtmlFrame::getDefaultRect() const
{
    return wxRect(-1, -1, 600, 420);
}
//-----------------------------------------------------------------------------
const wxString SimpleHtmlFrame::getName() const
{
    return wxT("SimpleHtmlFrameFrame");
}
//-----------------------------------------------------------------------------
const wxString SimpleHtmlFrame::getStorageName() const
{
    wxString name(getName());
    if (!fileNameM.IsEmpty())
        name += Config::pathSeparator + fileNameM;
    return name;
}
//-----------------------------------------------------------------------------
wxString SimpleHtmlFrame::getFrameId(const wxFileName& fileName)
{
    if (fileName.HasName())
        return wxString(wxT("SimpleHtmlFrame/") + fileName.GetFullPath());
    else
        return wxEmptyString;
}
//-----------------------------------------------------------------------------
SimpleHtmlFrame* SimpleHtmlFrame::findFrameFor(const wxFileName& fileName)
{
    BaseFrame* bf = frameFromIdString(getFrameId(fileName));
    if (!bf)
        return 0;
    return dynamic_cast<SimpleHtmlFrame*>(bf);
}
//-----------------------------------------------------------------------------
