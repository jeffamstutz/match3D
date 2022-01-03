// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

static const char *g_defaultLayout =
R"layout(
[Window][MainDockSpace]
Pos=0,25
Size=1280,774
Collapsed=0

[Window][Dear ImGui Demo]
Pos=873,25
Size=407,774
Collapsed=0
DockId=0x00000004,0

[Window][NodeEditor]
Pos=0,25
Size=871,774
Collapsed=0
DockId=0x00000003,0

[Window][Debug##Default]
Pos=60,60
Size=400,400
Collapsed=0

[Docking][Data]
DockSpace   ID=0x782A6D6B Window=0xDEDC5B90 Pos=0,25 Size=1280,774 Split=X
  DockNode  ID=0x00000003 Parent=0x782A6D6B SizeRef=871,774 CentralNode=1 Selected=0x1793893C
  DockNode  ID=0x00000004 Parent=0x782A6D6B SizeRef=407,774 Selected=0xE927CF2F
)layout";

const char *getDefaultUILayout()
{
  return g_defaultLayout;
}
