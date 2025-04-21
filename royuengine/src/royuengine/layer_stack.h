#pragma once

#include "royuengine/core.h"
#include "layer.h"

#include <vector>

namespace Royu
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void push_layer(Layer* layer);
		void push_overlay(Layer* layer);
		void pop_layer(Layer* layer);
		void pop_overlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layers_insert;
		//unsigned int layers_insert_index = 0;
	};
}