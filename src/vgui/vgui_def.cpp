
#include <stdio.h>
#include "imgui.h"
#include "vgui_def.hpp"

using namespace CGUI;


void Panel::DebugMain()
{

}

void Panel::WinGetMenuBar()
{
    /**/
}

void App::CRTStyleEdit(GUIFlag ImBool)
{
    ImGui::Begin("Dear ImGui Style Editor", ImBool);
    ImGui::ShowStyleEditor();
    ImGui::End();
}

void App::CRTDebugLog(GUIFlag ImBool)
{
    ImGui::Begin("Debug Console",ImBool);
    ImGui::Text("Console Output: ");
    ImGui::End();
}