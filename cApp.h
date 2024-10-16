
#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp// is the "launcher"
{
    public:
        cApp();
        ~cApp();

        virtual bool OnInit();
    private:
        cMain* m_frame1 = nullptr;
};

