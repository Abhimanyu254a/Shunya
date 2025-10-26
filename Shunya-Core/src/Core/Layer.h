#pragma once

#include "Core/Core.h"

#include "Core/Events/Event.h"


namespace Shunya
{
	class SHUNYA_API Layer
	{
	public:
		Layer(const std::string& Debug = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetch() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_Debug; }

	protected:
		std::string m_Debug;
	};
}