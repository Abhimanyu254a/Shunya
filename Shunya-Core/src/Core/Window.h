#pragma once

#include "SNY-PCH.h"

#include "Core.h"
#include "Events/Event.h"


namespace Shunya {
	struct WindowProps
	{
		std::string Title;
		uint32_t Breadth;
		uint32_t Height;

		WindowProps(
			const std::string& title = "Shunya",
			uint32_t breadth = 1280,
			uint32_t height = 720
		) : Title(title), Breadth(breadth), Height(height)
		{
		}
	};


	class SHUNYA_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetBreadth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enableed) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;



		static Window* Create(const WindowProps& props = WindowProps());
	};
}