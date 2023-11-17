#pragma once
#include <wx/wx.h>
#include "meta/macros.h"

/*
* -------------------------------
* License: GNU General Public License v3.0
* Author(s): Tomas Zlamal
* Short file description: An outline for the MyFrame class
* -------------------------------
*/

class MyFrame : public wxFrame
{
public:
  enum class appStatus {
    login,
    home,
    info,
    addEntry,
    showEntries
  };
  MyFrame(const wxString& title);
private:
  appStatus state;
  wxPanel* currentPanel;
  wxString password;
  wxString currentText;
  wxStaticText* remainingText;
  wxTextCtrl* inputText;
  bool keyIsShown;

  void onCriticalError();

  void LoginOnSubmit(wxCommandEvent& evt);
  void LoginOnTextChanged(wxCommandEvent& evt);
  void LoginOnMore(wxCommandEvent& evt);
  void LoginOnShow(wxCommandEvent& evt);

  void HomeOnLoginButtonClicked(wxCommandEvent& evt);
  void HomeOnAddEntryButtonClicked(wxCommandEvent& evt);
  void HomeOnShowEntriesButtonClicked(wxCommandEvent& evt);

  void InfoOnBack(wxCommandEvent& evt);

  void Refresh();

  void showLoginScreen();
  void showHomeScreen();
  void showInfoScreen();
  void showAddEntryScreen();
  void showEntriesScreen();
};