#pragma once

#include "SNY-PCH.h"

namespace Shunya
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}