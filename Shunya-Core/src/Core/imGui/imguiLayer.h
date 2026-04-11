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
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;
		void SetDarkThemeColors();

		void Begin();
		void End();

		void SetBlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_time = 0.0f;


	};
}