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

#include "core/Observer.h"
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <map>
#include "BaseFrame.h"
//-----------------------------------------------------------------------------
class CriteriaItem
{
public:
    enum Type { ctType, ctName, ctDescription, ctDDL, ctField, ctDB };
    wxString value;
    Database *database; // only used for ctDB type
    long listIndex;
    CriteriaItem(const wxString& v, Database *db)
        :value(v), database(db), listIndex(-1)
    {
    }
    bool operator==(const CriteriaItem& other) const
    {
        return (value == other.value && database == other.database);
    };
    static wxString getTypeString(Type type)
    {
        switch (type)
        {
            case ctType:        return _("Type is");
            case ctName:        return _("Name is");
            case ctDescription: return _("Description contains");
            case ctDDL:         return _("DDL contains");
            case ctField:       return _("Has field");
            case ctDB:          return _("In database");
        };
        return wxEmptyString;
    }
};
class MetadataItem;
class AdjustableListCtrl;   // declaration in cpp file
class MainFrame;
//-----------------------------------------------------------------------------
class AdvancedSearchFrame : public BaseFrame, public Observer
{
private:
    typedef std::multimap<CriteriaItem::Type, CriteriaItem> CriteriaCollection;
    CriteriaCollection searchCriteriaM;
    void addCriteria(CriteriaItem::Type type, wxString value,
        Database *db = 0);
    void rebuildList();
    std::vector<MetadataItem *> results;
    void addResult(Database* db, MetadataItem* item);
    bool match(CriteriaItem::Type type, const wxString& text);

    // observer stuff
    void update();
    void removeSubject(Subject* subject);

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
    AdvancedSearchFrame(MainFrame *parent);
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
        ID_listctrl_criteria,
        ID_listctrl_results
    };

    // events
    void OnCheckboxDdlToggle(wxCommandEvent& event);
    void OnButtonRemoveClick(wxCommandEvent& event);
    void OnButtonStartClick(wxCommandEvent& event);
    void OnButtonAddTypeClick(wxCommandEvent& event);
    void OnButtonAddNameClick(wxCommandEvent& event);
    void OnButtonAddDescriptionClick(wxCommandEvent& event);
    void OnButtonAddDDLClick(wxCommandEvent& event);
    void OnButtonAddFieldClick(wxCommandEvent& event);
    void OnButtonAddDatabaseClick(wxCommandEvent& event);
    void OnListCtrlResultsRightClick(wxListEvent& event);
    void OnListCtrlResultsItemSelected(wxListEvent& event);
    void OnListCtrlCriteriaActivate(wxListEvent& event);
    DECLARE_EVENT_TABLE()
};
//-----------------------------------------------------------------------------
#endif
