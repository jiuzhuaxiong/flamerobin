/*
  The contents of this file are subject to the Initial Developer's Public
  License Version 1.0 (the "License"); you may not use this file except in
  compliance with the License. You may obtain a copy of the License here:
  http://www.flamerobin.org/license.html.

  Software distributed under the License is distributed on an "AS IS"
  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
  License for the specific language governing rights and limitations under
  the License.

  The Original Code is FlameRobin (TM).

  The Initial Developer of the Original Code is Milan Babuskov.

  Portions created by the original developer
  are Copyright (C) 2005 Milan Babuskov.

  All Rights Reserved.

  $Id$

  Contributor(s):
*/

#ifndef FR_SIMPLEHTMLFRAME_H
#define FR_SIMPLEHTMLFRAME_H
//-----------------------------------------------------------------------------
#include <wx/wx.h>

#include "gui/BaseFrame.h"
//-----------------------------------------------------------------------------
bool showHtmlFile(wxWindow* parent, const wxFileName& fileName);

class PrintableHtmlWindow;
//-----------------------------------------------------------------------------
class SimpleHtmlFrame: public BaseFrame
{
private:
    PrintableHtmlWindow* html_window;
    static wxString getFrameId(const wxFileName& fileName);
protected:
    virtual const wxString getName() const;
    virtual const wxRect getDefaultRect() const;
public:
    SimpleHtmlFrame(wxWindow* parent, const wxFileName& fileName);

    static SimpleHtmlFrame* findFrameFor(const wxFileName& fileName);
};
//-----------------------------------------------------------------------------
#endif // FR_SIMPLEHTMLFRAME_H
