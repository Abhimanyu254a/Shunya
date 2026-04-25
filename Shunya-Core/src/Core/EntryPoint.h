#pragma once

#include "Core/Application.h"

extern Shunya::Application* Shunya::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Shunya::Log::Init();
	Shunya::Log::GetClientLogger() -> info("Hello Shunya");
	printf("Hello Shunya");
	SHUNYA_PROFILE_BEGIN_SESSION("Startup", "Shunya-Startup.json");
	auto app = Shunya::CreateApplication({ argc, argv });
	SHUNYA_PROFILE_END_SESSION();

	SHUNYA_PROFILE_BEGIN_SESSION("Runtime", "Shunya-Runtime.json");
	app->Run();
	SHUNYA_PROFILE_END_SESSION();

	SHUNYA_PROFILE_BEGIN_SESSION("Delete", "Shunya-Delete.json");
	delete app;
	SHUNYA_PROFILE_END_SESSION();
	return 0;
}

