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

		virtual void OnAttach() override;
		virtual void OnDetch() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();


	private:
		float m_time = 0.0f;


	};
}