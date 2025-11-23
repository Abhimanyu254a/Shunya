#pragma once

#include "Core/Core.h"

#include "Layer.h"


#include <vector>

namespace Shunya
{
	class SHUNYA_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* Overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* Overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*>m_Layers;
		unsigned int m_LayerInsertindex = 0;

	};
}