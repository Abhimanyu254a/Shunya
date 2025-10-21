#include <Shunya.h>

class ExampleLayer : public Shunya::Layer
{
public:
	ExampleLayer():Layer("Example")
	{
	}
	void OnUpdate() override
	{
		SHUNYA_INFO("Example  :: Update");
	}
	void OnEvent(Shunya::Event& event) override
	{
		SHUNYA_TRACE("{0}", event.GetName());

	}
};



class PlayGround : public Shunya::Application
{
public:
   PlayGround()
   {
	   PushLayer(new ExampleLayer());
   }
   ~PlayGround()
   {
   }
};

Shunya::Application* Shunya::CreateApplication()
{
   return new PlayGround();
}
