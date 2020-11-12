//
//  wxmView.cpp
//  DateTime
//
//  Created by Joseph Costello on 10/18/20.
//

#include "wxmView.hpp"

#include <wx/grid.h>
#include <wx/clipbrd.h>
#include <wx/url.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/combo.h>
#include <wx/odcombo.h>
#include <wx/valgen.h>
#include <curl/curl.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"



#define frameWidth 800
#define frameHeight 800

CONST std::string ICONPATH = "G:/Downloads/WeatherIcons-20201111T215307Z-001/";

wxGridSizer* layout = new wxGridSizer(3, 3, 10, 10);

enum {
    ID_VALUE_WINDOW = 80091,
    ID_VALUE_TIMER = 10001,

};

//Constructor
wxmView::wxmView()
    : wxFrame(NULL, wxID_ANY, "DateTime")
{
    //Set background color and size
    this->wxWindow::SetBackgroundColour(*wxGREEN);
    this->SetSize(frameWidth, frameHeight);
    //Set min and max size (window cannot be resized)
    SetMinSize(GetSize());
    SetMaxSize(GetSize());

    //Initialize and start timer with event intervals of 100 milliseconds
    m_timer = new wxTimer(this, ID_VALUE_TIMER);
    m_timer->Start(100);

    wxPanel* panel = new wxPanel();


    //Create font for text
    wxFont myFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    //Get current time
    wxDateTime now = wxDateTime::Now();
    //Initialize text for string
    time = new wxStaticText(this, wxID_ANY, now.Format("%c", wxDateTime::EST).c_str(), wxPoint(100,700), wxSize(300, 50));
    //Set font of text
    time->SetFont(myFont);

    GetWeather();

    layout->Add(time,0,wxEXPAND);

    SetSizer(layout);


    //Show application
    this->Refresh();
    //Center frame on window
    this->Center();
}

//Helper function for updating time when timer event is intialized
void wxmView::OnTimer(wxTimerEvent& event) {
    //Get current time
    wxDateTime current = wxDateTime::Now();
    //Update text
    time->SetLabel(current.Format("%c", wxDateTime::EST).c_str());
    //End function
    event.Skip();
}

void wxmView::OnPaint(wxPaintEvent& event) {

    wxPaintDC dc(this);
    wxInitAllImageHandlers();

    std::string iconname = "rain.png";

    wxImage image(ICONPATH+iconname);

    wxBitmap bmp(image);

    dc.DrawBitmap(bmp, 100, 100, false);
}

void wxmView::GetWeather() {
    CURL* hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://community-open-weather-map.p.rapidapi.com/weather?q=Newport%20News&lat=0&lon=0&callback=test&id=2172797&lang=null&units=%22metric%22&mode=html");

    FILE* file = fopen("weather.html","w");

    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, file);

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "x-rapidapi-key: b062fb1234msh977ff028b6e1ae5p1fe16bjsn7dfc281d6e2f");
    headers = curl_slist_append(headers, "x-rapidapi-host: community-open-weather-map.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(hnd);

    curl_easy_cleanup(hnd);
    fclose(file);

    //temp = new wxStaticText(this, wxID_ANY, std::to_string(), wxPoint(100, 700), wxSize(300, 50));
    
}

//Destructor
wxmView::~wxmView() {}


BEGIN_EVENT_TABLE(wxmView, wxFrame)
//Listen for timer event and run OnTimer function
EVT_TIMER(ID_VALUE_TIMER, wxmView::OnTimer)
EVT_PAINT(wxmView::OnPaint)
wxEND_EVENT_TABLE()