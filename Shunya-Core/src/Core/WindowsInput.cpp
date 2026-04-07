#include "SNY-PCH.h"
#include "input.h"

#include "Core/Application.h"
#include "GLFW/glfw3.h"


namespace Shunya
{
	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return  state == GLFW_PRESS || state == GLFW_REPEAT;


	}
	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return  state == GLFW_PRESS;
	}
	float Input::GetMouseX()
	{
		// use to work on the older versions like c++14
		/*auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);

		return (float)x_pos;*/
		auto [x, y] = GetMousePosition();
		return x;
	}
	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;

		// use to work on the older versions like c++14
		/*auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);

		return (float)y_pos;*/

	}
	std::pair<float, float>Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x_val, y_val;
		glfwGetCursorPos(window, &x_val, &y_val);

		return { (float)x_val,(float)y_val };

	}
}