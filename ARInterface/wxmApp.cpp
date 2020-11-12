//
//  wxmApp.cpp
//  DateTime
//
//  Created by Joseph Costello on 10/18/20.
//

#include "wxmApp.hpp"
#include "wxmView.hpp"


bool wxmApp::OnInit() {
    auto frame = new wxmView;
    frame->Show(true);
    return true;
}