#include "SNY-PCH.h"

#include "LayerStack.h"

namespace Shunya
{
	LayerStack::LayerStack()
	{

	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			layer->OnDetch();
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertindex, layer);
		m_LayerInsertindex++;
	}

	void LayerStack::PushOverlay(Layer* Overlay)
	{
		m_Layers.emplace_back(Overlay);


	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{

			m_Layers.erase(it);
			m_LayerInsertindex--;
		}
	}

	void LayerStack::PopOverlay(Layer* Overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), Overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

}

