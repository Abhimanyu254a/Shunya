#pragma once



#ifdef SHUNYA_CORE_EXPORTS

extern Shunya::Application* Shunya::CreateApplication();

int main(int argc, char** argv)
{
	Shunya::Log::Init();

	Shunya::Log::GetCoreLogger() -> warn("Initialized Log!");
	Shunya::Log::GetClientLogger() -> info("Hello Shunya");
	
	
	printf("Hello Shunya");
	auto app = Shunya::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif
