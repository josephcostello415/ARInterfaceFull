//
//  wxmApp.hpp
//  DateTime
//
//  Created by Joseph Costello on 10/18/20.
//

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class wxmApp : public wxApp
{
public:
    virtual bool OnInit() override;
};