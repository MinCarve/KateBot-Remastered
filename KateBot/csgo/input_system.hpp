#ifndef __INPUT_SYSTEM__
#define __INPUT_SYSTEM__

#define c_vk_bc(x, a) case x: return a

namespace input_system {
	uintptr_t GetPointer(void);
	bool IsButtonDown(ButtonCode_t button);
	void Init(void);

	ButtonCode_t vktobc(int vk);
}

#endif