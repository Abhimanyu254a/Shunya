#pragma once

#include "Core/SNY-PCH.h"
#include "Core/Layer.h"

namespace Shunya
{
	class imguiLayer : public Layer
	{
	public:
		imguiLayer();
		~imguiLayer();
		virtual void OnAttach() {};
		virtual void OnDetch() {};
		void OnUpdate();
		void OnEvent(Event& event);

	};

}