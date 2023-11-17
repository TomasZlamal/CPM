#pragma once
#include <wx/wx.h>
#include "meta/macros.h"

/*
* -------------------------------
* License: GNU General Public License v3.0
* Author(s): Tomas Zlamal
* Short file description: An outline for the App class, defined in the App.cpp file
* -------------------------------
*/

class App : public wxApp {
public:
  bool OnInit();
};