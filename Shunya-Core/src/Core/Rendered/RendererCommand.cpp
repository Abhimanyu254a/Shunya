#include "SNY-PCH.h"
#include "RendererCommand.h"

#include "Core/openGL/OpenglRendererAPI.h"


namespace Shunya
{

	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;

}