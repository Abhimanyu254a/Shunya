#pragma once

#include "SNY-PCH.h"

#include "Layer.h"

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
		float m_time = 0.0f;

	};
}