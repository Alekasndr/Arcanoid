#include "input_controller.h"
#include <GLFW/glfw3.h>

int InputController::get_direction(ImGuiIO& io)
{
	// process user input
	if (io.KeysDown[GLFW_KEY_A])
		return -1.0f;
	else if (io.KeysDown[GLFW_KEY_D])
		return 1.0f;
}
