#include "lfpch.h"
#include "LoFox/Core/Application.h"

#include "LoFox/Core/Log.h"

#include <vulkan/vulkan.h>

#include "LoFox/Utils/VulkanUtils.h"
#include "LoFox/Utils/Utils.h"
#include "LoFox/Utils/Time.h"

#include "LoFox/Core/Input.h"

#include "LoFox/Renderer/Renderer.h"

namespace LoFox {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpec& spec)
		: m_Spec(spec) {

		LF_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		LF_OVERSPECIFY("Creating application named \"{0}\":\n", m_Spec.Name);

		Input::SetKeyboard(Keyboard::BelgianPeriod);

		m_Window = Window::Create({ m_Spec.Name, 1720, 960 });
		m_Window->SetWindowEventCallback(LF_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init(m_Window);
		m_RenderContext = Renderer::GetContext();

		LF_OVERSPECIFY("Creation of application \"{0}\" complete.\n", m_Spec.Name);
	}

	void Application::Run() {

		m_IsRunning = true;
		while (m_IsRunning) {

			float time = Time::GetTime();
			float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_Window->OnUpdate();

			for (auto& layer : m_LayerStack)
				layer->OnUpdate(timestep);

			if (!m_Window->IsMinimized())
				m_RenderContext->OnRender();
		}

		Renderer::WaitIdle();
	}

	Application::~Application() {

		LF_OVERSPECIFY("Destroying application named \"{0}\"", m_Spec.Name);

		for (auto& layer : m_LayerStack)
			layer->OnDetach();

		Renderer::Shutdown();

		LF_OVERSPECIFY("Finished destruction of application named \"{0}\"", m_Spec.Name);
	}

	void Application::OnEvent(Event& event) {

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(LF_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(LF_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto layer : m_LayerStack) {

			if (event.Handled)
				break;
			layer->OnEvent(event);
		}
	}

	bool Application::OnWindowResize(WindowResizeEvent& event) {

		m_RenderContext->OnResize(event.GetWidth(), event.GetHeight());
		return true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {

		LF_OVERSPECIFY("Closing application named \"{0}\"", m_Spec.Name);
		m_IsRunning = false;
		return true;
	}
}