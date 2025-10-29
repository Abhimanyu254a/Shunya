#pragma once

#include "SNY-PCH.h"
#include "Core/All_Event.h"
#include "Core/Layer.h"


namespace Shunya {
	class SHUNYA_API imGUILayer : public Layer	
	{
	public:
		imGUILayer();
		~imGUILayer();
		
		void OnAttach() ;
		void OnDetch() ;
		void OnUpdate() ;
		void OnEvent(Event& event) ;

	private:
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonRelasedEvent(MouseButtonRelasedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	
	private:
		float m_time = 0.0f;


	};
}