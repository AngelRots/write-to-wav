
#include <stdio.h>
#include "imgui.h"
#include "vgui_def.hpp"


bool CGUI::Panel::isActive()
{
    return true;
}

void CGUI::Panel::DebugMain()
{
   ImGui::Begin("Oh no!");
   ImGui::End();
}