#pragma once

#include "SNY-PCH.h"

#include "Core.h"
#include "Events/Event.h"


namespace Shunya{
	struct WindowProps
	{
		std::string Title;
		unsigned int Breadth;
		unsigned int Height;

		WindowProps(
			const std::string& title = "Shunya",
			unsigned int breadth = 1280,
			unsigned int height = 720
		) : Title(title), Breadth(breadth), Height(height)
		{
		}
	};


	class SHUNYA_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetBreadth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enableed) = 0;
		virtual bool IsVSync() const = 0;


		static Window* Create(const WindowProps& props = WindowProps());
	};
}