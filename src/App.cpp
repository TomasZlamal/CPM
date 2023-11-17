#include "../include/App.hpp"
#include "../include/frame.hpp"

/*
* -------------------------------
* License: GNU General Public License v3.0
*	Author(s): Tomas Zlamal
*	Short file description: A definition for the app class
* -------------------------------
*/

wxIMPLEMENT_APP(App);
bool App::OnInit()
{

	MyFrame* frame = new MyFrame(wxT("Password manager"));
	frame->SetBackgroundColour(wxColour(*wxWHITE));
	frame->Center();
	frame->SetClientSize(700, 400);

	frame->Show(true);
		
	return true;
}