#pragma once

#ifdef SHUNYA_CORE_EXPORTS

extern Shunya::Application* Shunya::CreateApplication();

int main(int argc, char** argv)

{
	printf("Hello Shunya");
	auto app = Shunya::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif
