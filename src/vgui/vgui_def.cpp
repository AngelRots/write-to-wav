
#include <stdio.h>
#include "imgui.h"
#include "vgui_def.hpp"

using namespace CGUI;

bool Panel::isActive()
{
    return true;
}

void Panel::DebugMain()
{
   ImGui::Begin("Oh no!");
   ImGui::End();
}