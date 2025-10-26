#include "Core/SNY-PCH.h"

#include "imguiLayer.h"
#include "iamgui.h"
#include "Core"

namespace Shunya
{
	imguiLayer::imguiLayer()
		:Layer("iamGUI_Layer")
	{

	}
	imguiLayer::~imguiLayer()
	{

	}
	void imguiLayer::OnAttach()
	{
		imGUI::CreateContext();
		imGUI::My
	}
	void imguiLayer::OnUpdate()
	{

	}
	void imguiLayer::OnEvent(Event& event)
	{

	}


}