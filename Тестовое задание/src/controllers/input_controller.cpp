#include "input_controller.h"
#include <GLFW/glfw3.h>

int InputController::get_dirrection(ImGuiIO& io)
{
	if (io.KeysDown[GLFW_KEY_A])
		return -1;
	else if (io.KeysDown[GLFW_KEY_D])
		return 1;
}
