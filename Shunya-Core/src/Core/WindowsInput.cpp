#include "SNY-PCH.h"
#include "WindowsInput.h"

#include "Core/Application.h"
#include "GLFW/glfw3.h"


namespace Shunya
{
	Input* Input::s_Instance = new WindowsInput;
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return  state == GLFW_PRESS || state == GLFW_REPEAT;


	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return  state == GLFW_PRESS;
	}
	float WindowsInput::GetMouseXImpl()
	{
		// use to work on the older versions like c++14
		/*auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);

		return (float)x_pos;*/
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;

		// use to work on the older versions like c++14
		/*auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);

		return (float)y_pos;*/

	}
	std::pair<float, float>WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x_val, y_val;
		glfwGetCursorPos(window, &x_val, &y_val);

		return { (float)x_val,(float)y_val };

	}
}