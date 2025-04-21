#include "rypch.h"

#include "layer_stack.h"

namespace Royu
{
	LayerStack::LayerStack()
	{
		layers_insert = layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers)
		{
			delete layer;
		}
	}

	/*确保覆盖层在lyers后半部分*/
	void LayerStack::push_layer(Layer* layer)
	{
		layers_insert = layers.emplace(layers_insert, layer);
	}

	void LayerStack::push_overlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
	}

	void LayerStack::pop_layer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) //find it
		{
			layers.erase(it);
			layers_insert--;
		}
	}

	void LayerStack::pop_overlay(Layer* overlay)
	{
		auto it = std::find(layers.begin(), layers.end(), overlay);
		if (it != layers.end()) //find it
		{
			layers.erase(it);
		}
	}
}