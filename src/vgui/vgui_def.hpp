
#ifndef VGUI_DEF_HPP
#define VGUI_DEF_HPP

using GUIFlag = bool*;

namespace CGUI
{
    class Panel
    {
    public:
        void        DebugMain();
        bool        WinActive = true; // We define this bool so that we can keep track of the status of the panel with any API
        static void WinGetMenuBar();
        float       WinColors[3] = {1.0f,1.0f,1.0f}; // Array for ImGui's Color Picker
        char        WinText[1024];
    };

    class App : public Panel 
    {
      public:
      bool WinGeneric   = true;
      bool WinWrite     = false;
      bool WinDebug     = false;
      bool WinColPicker = false;
      bool WinStyleEdit = false;
      virtual void CRTStyleEdit(GUIFlag imBool);
      
    };

}

#endif