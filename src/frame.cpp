#include "../include/frame.hpp"
#include <string>

/*
* -------------------------------
* License: GNU General Public License v3.0
* Author(s): Tomas Zlamal
* Short file description: A definition for the MyFrame class
* -------------------------------
*/

MyFrame::MyFrame(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, { 700, 400 }, wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN), keyIsShown(false)
{
  wxImage::AddHandler(new wxPNGHandler);
  state = appStatus::login;
  currentText = "";
  CreateStatusBar();
  Refresh();
}
void MyFrame::Refresh() {
  if (this->currentPanel) {
    if (!this->currentPanel->Destroy()) {
      onCriticalError();
    }
  }
  switch (state) {
    case appStatus::login: {
      showLoginScreen();
    } break;
    case appStatus::home: {
      showHomeScreen();
    } break;
    case appStatus::info: {
      showInfoScreen();
    } break;
    case appStatus::addEntry: {
      showAddEntryScreen();
    } break;
    case appStatus::showEntries: {
      showEntriesScreen();
    } break;
    default: {
      onCriticalError();
    } break;
  }
}

void MyFrame::showLoginScreen()
{
  wxPanel* inputPanel = new wxPanel(this);
  this->currentPanel = inputPanel;

  wxButton* button = new wxButton(inputPanel, wxID_ANY, "Submit", wxPoint(300, 200), wxSize(70, 40));
  wxStaticText* text = new wxStaticText(inputPanel, wxID_ANY, "Input your encryption key", wxPoint(265, 140));
  wxStaticText* remaining = new wxStaticText(inputPanel, wxID_ANY, "16 characters remaining", wxPoint(270, 340));
  wxTextCtrl* input = new wxTextCtrl(inputPanel, wxID_ANY, "", wxPoint(270, 170), wxSize(130, 20), wxTE_PASSWORD);
  wxButton* more = new wxButton(inputPanel, wxID_ANY, "More info", wxPoint(0, 0), wxSize(70, 40));
  wxBitmap* icon = new wxBitmap("resources/visibility_FILL0_wght400_GRAD0_opsz24.png", wxBITMAP_TYPE_PNG);
  wxBitmapBundle bundle{ *icon };
  wxBitmapButton* show = new wxBitmapButton(inputPanel, wxID_ANY, bundle, wxPoint(410, 170), wxSize(30, 20));
  inputText = input;
  remainingText = remaining;

  button->Bind(wxEVT_BUTTON, &MyFrame::LoginOnSubmit, this);
  input->Bind(wxEVT_TEXT, &MyFrame::LoginOnTextChanged, this);
  more->Bind(wxEVT_BUTTON, &MyFrame::LoginOnMore, this);
  show->Bind(wxEVT_BUTTON, &MyFrame::LoginOnShow, this);
  // !!! important
  this->Layout();
}

void MyFrame::showHomeScreen()
{
  wxPanel* homePanel = new wxPanel(this);
  this->currentPanel = homePanel;

  wxButton* button = new wxButton(homePanel, wxID_ANY, "Input a different key", wxPoint(0, 0), wxSize(180, 25));
  wxButton* addEntryButton = new wxButton(homePanel, wxID_ANY, "Add an entry", wxPoint(230, 200), wxSize(180, 25));
  wxButton* showEntriesButton = new wxButton(homePanel, wxID_ANY, "Show decrypted passwords", wxPoint(230, 225), wxSize(180, 25));

  button->Bind(wxEVT_BUTTON, &MyFrame::HomeOnLoginButtonClicked, this);
  addEntryButton->Bind(wxEVT_BUTTON, &MyFrame::HomeOnAddEntryButtonClicked, this);
  showEntriesButton->Bind(wxEVT_BUTTON, &MyFrame::HomeOnShowEntriesButtonClicked, this);
  // !!! important
  this->Layout();
}

void MyFrame::showInfoScreen()
{
  wxPanel* infoPanel = new wxPanel(this);
  this->currentPanel = infoPanel;

  // dynamic binding
  wxButton* back = new wxButton(infoPanel, wxID_ANY, "Back", wxPoint(0, 0), wxSize(70, 40));
  wxStaticText* Text1 = new wxStaticText(infoPanel, wxID_ANY, "Input your key that you used/will use for your password", wxPoint(100, 110));
  wxStaticText* Text2 = new wxStaticText(infoPanel, wxID_ANY, "If you input an incorrect key, the keys will get decrypted incorrectly", wxPoint(100, 130));
  wxStaticText* Text3 = new wxStaticText(infoPanel, wxID_ANY, "The standard I use requires you to enter a 16 character key, to ensure security.", wxPoint(100, 150));

  back->Bind(wxEVT_BUTTON, &MyFrame::InfoOnBack, this);
  // !!! important
  this->Layout();
}

void MyFrame::showAddEntryScreen()
{
  wxPanel* addEntryPanel = new wxPanel(this);
  this->currentPanel = addEntryPanel;

  // !!! important
  this->Layout();
}

void MyFrame::showEntriesScreen()
{
  wxPanel* showEntriesPanel = new wxPanel(this);
  this->currentPanel = showEntriesPanel;

  // !!! important
  this->Layout();
}

void MyFrame::onCriticalError()
{
  CreateStatusBar();
  wxLogStatus("A critical error has occured, shutting down; Code DFF001");
  Sleep(2000);
  Close();
}

void MyFrame::LoginOnSubmit(wxCommandEvent& evt) {
  if (currentText.length() != 16) {
    wxLogStatus("Your key isn't the correct size, try again.");
    return;
  }
  password = currentText;
  state = appStatus::home;
  Refresh();
}
void MyFrame::LoginOnTextChanged(wxCommandEvent& evt) {
  currentText = evt.GetString();
  if (currentText.length() <= 16) {
    remainingText->SetLabel(wxString::Format(wxT("%d"), 16-(int)currentText.length()) + wxString(" characters remaining"));
  }
  else {
    remainingText->SetLabel("Too many characters");
  }
}

void MyFrame::HomeOnLoginButtonClicked(wxCommandEvent& evt)
{
  state = appStatus::login;
  Refresh();
}

void MyFrame::HomeOnAddEntryButtonClicked(wxCommandEvent& evt)
{
  state = appStatus::addEntry;
  Refresh();
}

void MyFrame::HomeOnShowEntriesButtonClicked(wxCommandEvent& evt)
{
  state = appStatus::showEntries;
  Refresh();
}

void MyFrame::LoginOnMore(wxCommandEvent& evt)
{
  state = appStatus::info;
  Refresh();
}

void MyFrame::InfoOnBack(wxCommandEvent& evt)
{
  state = appStatus::login;
  Refresh();
}

void MyFrame::LoginOnShow(wxCommandEvent& evt)
{
  keyIsShown = !keyIsShown;
  inputText->Destroy();
  if (keyIsShown) {
    inputText = new wxTextCtrl(currentPanel, wxID_ANY, currentText, wxPoint(270, 170), wxSize(130, 20));
  }
  else {
    inputText = new wxTextCtrl(currentPanel, wxID_ANY, currentText, wxPoint(270, 170), wxSize(130, 20), wxTE_PASSWORD);
  }
  inputText->Bind(wxEVT_TEXT, &MyFrame::LoginOnTextChanged, this);
}
