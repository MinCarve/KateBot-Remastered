#include "../main.h"
#include "input_system.hpp"

cs_virtual_table	cs_vt_inputsystem;
uint32_t			cs_nv_m_dwButton;

bool input_system::IsButtonDown(ButtonCode_t button) {
	uint32_t v;

	v = mem->Read<uint32_t>(cs_vt_inputsystem.address() + (((button >> 0x5) * 0x4) + cs_nv_m_dwButton));
	return (v >> (button & 0x1F)) & 1;
}

void input_system::Init() {
	cs_interface_reg inputsystem;

	inputsystem = interfaces::find("inputsystem.dll");
	cs_vt_inputsystem = inputsystem.find("InputSystemVersion");

	cs_nv_m_dwButton = mem->Read<uint32_t>(cs_vt_inputsystem.function(0xF) + 0x21D);
}

ButtonCode_t input_system::vktobc(int vk) {
	std::unordered_map<std::string, ButtonCode_t> const table = {
			{"0", KEY_0}, {"1", KEY_1}, {"2", KEY_2}, {"3", KEY_3},
			{"4", KEY_4}, {"5", KEY_5}, {"6", KEY_6}, {"7", KEY_7},
			{"8", KEY_8}, {"9", KEY_9}, { "A", KEY_A },{ "B", KEY_B },
			{ "C", KEY_C }, { "D", KEY_D }, { "E", KEY_E }, { "F", KEY_F },
			{ "G", KEY_G }, { "H", KEY_H }, { "I", KEY_I }, { "J", KEY_J },
			{ "K", KEY_K }, { "L", KEY_L }, { "M", KEY_M }, { "N", KEY_N },
			{ "O", KEY_O }, { "P", KEY_P }, { "Q", KEY_Q }, { "R", KEY_R },
			{ "S", KEY_S }, { "T", KEY_T }, { "U", KEY_U }, { "V", KEY_V },
			{ "W", KEY_W }, { "X", KEY_X }, { "Y", KEY_Y }, { "Z", KEY_Z },
	};

	if ((vk >= '0' && vk <= '9') || (vk >= 'A' && vk <= 'Z'))
		if (auto it = table.find(std::to_string(vk)); it != table.end())
			return it->second;

	switch (vk)
	{
		c_vk_bc(VK_LBUTTON, MOUSE_LEFT);
		c_vk_bc(VK_RBUTTON, MOUSE_RIGHT);
		c_vk_bc(VK_MBUTTON, MOUSE_MIDDLE);
		c_vk_bc(VK_XBUTTON1, MOUSE_4);
		c_vk_bc(VK_XBUTTON2, MOUSE_5);
		c_vk_bc(VK_BACK, KEY_BACKSPACE);
		c_vk_bc(VK_TAB, KEY_TAB);
		c_vk_bc(VK_RETURN, KEY_ENTER);
		c_vk_bc(VK_SHIFT, KEY_LSHIFT);
		c_vk_bc(VK_LSHIFT, KEY_LSHIFT);
		c_vk_bc(VK_RSHIFT, KEY_RSHIFT);
		c_vk_bc(VK_CONTROL, KEY_LCONTROL);
		c_vk_bc(VK_LCONTROL, KEY_LCONTROL);
		c_vk_bc(VK_RCONTROL, KEY_RCONTROL);
		c_vk_bc(VK_MENU, KEY_LALT);
		c_vk_bc(VK_LMENU, KEY_LALT);
		c_vk_bc(VK_RMENU, KEY_RALT);
		c_vk_bc(VK_INSERT, KEY_INSERT);
		c_vk_bc(VK_DELETE, KEY_DELETE);
		c_vk_bc(VK_HOME, KEY_HOME);
		c_vk_bc(VK_NUMPAD0, KEY_PAD_0);
		c_vk_bc(VK_NUMPAD1, KEY_PAD_1);
		c_vk_bc(VK_NUMPAD2, KEY_PAD_2);
		c_vk_bc(VK_NUMPAD3, KEY_PAD_3);
		c_vk_bc(VK_NUMPAD4, KEY_PAD_4);
		c_vk_bc(VK_NUMPAD5, KEY_PAD_5);
		c_vk_bc(VK_NUMPAD6, KEY_PAD_6);
		c_vk_bc(VK_NUMPAD7, KEY_PAD_7);
		c_vk_bc(VK_NUMPAD8, KEY_PAD_8);
		c_vk_bc(VK_NUMPAD9, KEY_PAD_9);
		c_vk_bc(VK_F1, KEY_F1);
		c_vk_bc(VK_F2, KEY_F2);
		c_vk_bc(VK_F3, KEY_F3);
		c_vk_bc(VK_F4, KEY_F4);
		c_vk_bc(VK_F5, KEY_F5);
		c_vk_bc(VK_F6, KEY_F6);
		c_vk_bc(VK_F7, KEY_F7);
		c_vk_bc(VK_F8, KEY_F8);
		c_vk_bc(VK_F9, KEY_F9);
		c_vk_bc(VK_F10, KEY_F10);
		c_vk_bc(VK_F11, KEY_F11);
		c_vk_bc(VK_F12, KEY_F12);
	}

	return BUTTON_CODE_NONE;
}