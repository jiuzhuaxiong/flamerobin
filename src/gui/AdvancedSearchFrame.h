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
  are Copyright (C) 2006 Milan Babuskov.

  All Rights Reserved.

  $Id$

  Contributor(s):
*/
#ifndef FR_ADVANCEDSEARCHFRAME_H
#define FR_ADVANCEDSEARCHFRAME_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>

#include "BaseFrame.h"
//-----------------------------------------------------------------------------
class CriteriaItem
{
public:
    enum Type { ctType, ctName, ctDescription, ctDDL, ctField, ctDB };
    Type type;
    wxString value;
    Database *database; // only used for ctDB type
    CriteriaItem(Type t, const wxString& v, Database *db = 0)
        :type(t), value(v), database(db)
    {
    }
    wxString getTypeString() const
    {
        switch (type)
        {
            case ctType:        return _("Type");
            case ctName:        return _("Name");
            case ctDescription: return _("Description");
            case ctDDL:         return _("DDL contains");
            case ctField:       return _("Has field");
            case ctDB:          return _("In database");
        };
        return wxEmptyString;
    }
};
class AdjustableListCtrl;   // declaration in cpp file
//-----------------------------------------------------------------------------
class AdvancedSearchFrame : public BaseFrame
{
private:
    std::vector<CriteriaItem> searchCriteriaM;
    void addCriteria(const CriteriaItem& item);

protected:
    wxPanel *mainPanel;
    wxStaticText *m_staticText1;
    wxChoice *choice_type;
    wxButton *button_add_type;
    wxStaticText *m_staticText2;
    wxTextCtrl *textctrl_name;
    wxButton *button_add_name;
    wxStaticText *m_staticText3;
    wxTextCtrl *textctrl_description;
    wxButton *button_add_description;
    wxStaticText *m_staticText4;
    wxTextCtrl *textctrl_ddl;
    wxButton *button_add_ddl;
    wxStaticText *m_staticText5;
    wxTextCtrl *textctrl_field;
    wxButton *button_add_field;
    wxStaticText *m_staticText6;
    wxChoice *choice_database;
    wxButton *button_add_database;
    AdjustableListCtrl *listctrl_criteria;
    wxButton *button_remove;
    wxButton *button_search;
    wxStaticText *label_search_results;
    wxCheckBox *checkbox_ddl;
    wxSplitterWindow *splitter1;
    wxPanel *top_splitter_panel;
    AdjustableListCtrl *listctrl_results;
    wxPanel *bottom_splitter_panel;
    wxTextCtrl *stc_ddl;

public:
    AdvancedSearchFrame(wxWindow *parent);
    enum
    {
        ID_button_remove=100,
        ID_button_start,
        ID_button_add_type,
        ID_button_add_name,
        ID_button_add_description,
        ID_button_add_ddl,
        ID_button_add_field,
        ID_button_add_database,
        ID_checkbox_ddl,
        ID_listctrl_results
    };

    void OnButtonRemoveClick(wxCommandEvent& event);
    void OnButtonStartClick(wxCommandEvent& event);
    void OnButtonAddTypeClick(wxCommandEvent& event);
    void OnButtonAddNameClick(wxCommandEvent& event);
    void OnButtonAddDescriptionClick(wxCommandEvent& event);
    void OnButtonAddDDLClick(wxCommandEvent& event);
    void OnButtonAddFieldClick(wxCommandEvent& event);
    void OnButtonAddDatabaseClick(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};
//-----------------------------------------------------------------------------
#endif
