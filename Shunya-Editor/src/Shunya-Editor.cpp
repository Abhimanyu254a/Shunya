    #include <Shunya.h>
#include <Core/EntryPoint.h>
#include "Core/openGL/OpenGLShader.h"
#include <imgui.h>
#include "Core/Core.h"

#include "Core/imGui/imguiLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"


namespace Shunya
{

    class ShunyaEditor : public Application
    {
    public:
        ShunyaEditor(ApplicationCommandLineArgs args)
			:Application("Shunya Editor",args)
        {
            PushLayer(new EditorLayer());
        }
        ~ShunyaEditor()
        {
        }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        return new ShunyaEditor(args);
    }
}