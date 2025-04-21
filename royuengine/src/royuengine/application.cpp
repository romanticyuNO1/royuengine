#include "rypch.h"

#include "application.h"
#include "log.h"

#include <glad/glad.h>


namespace Royu
{
	//�������Ͷ���󶨣�����һ���ɵ��ö���
	//std::placeholders::_1 ��ʾ�ص�����������һ������ ����std::fuction<void(Event&)>����ĸ�ʽ

	Application* Application::instance = nullptr;

	Application::Application()
	{
		instance = this;
		RY_CORE_ASSERT(!instance, "Application already exists!");

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(RY_BIND_EVENT_FN(Application::on_event));
	}


	Application::~Application()
	{

	}

	//����window.h��set callback�Ĵ���ص������ĸ�ʽstd::fuction<void(Event&)>
	void Application::on_event(Event& e)
	{
		//��on_window_close��������������жϵ���
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(RY_BIND_EVENT_FN(Application::on_window_close));

		RY_CORE_INFO("{0}", e.to_string());

		for (auto it = layer_stacks.end(); it != layer_stacks.begin();)
		{
			(*--it)->on_event(e);
			if (e.m_handled)
				break;
		}
	}

	void Application::push_layer(Layer* layer)
	{
		layer_stacks.push_layer(layer);
		layer->on_attach();
	}

	void Application::push_overlay(Layer* layer)
	{
		layer_stacks.push_overlay(layer);
		layer->on_attach();
	}

	void Application::Run()
	{
		while (m_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layer_stacks)
			{
				layer->on_update();
			}

			m_window->on_update();
		}
	}

	bool Application::on_window_close(WindowCloseEvent& e)
	{
		//�رմ����߼��ľ����߼�ʵ��
		m_running = false;
		return true;
	}
}