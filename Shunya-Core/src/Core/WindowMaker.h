#pragma once

#include "Core/Window.h"

#include <GLFW/glfw3.h>

namespace Shunya {

	class WindowMaker : public Window {
	public:
		WindowMaker(const WindowProps& props);
		virtual ~WindowMaker();

		void OnUpdate() override;

		inline unsigned int GetBreadth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Length; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		void Shutdown();




	private:
	void Init(const WindowProps& props);
	 
	

	protected:
		GLFWwindow* m_Window;



		struct WindowData
		{
			std::string Title;
			unsigned int Width, Length;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}