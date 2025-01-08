#include"Application.h"
#include<iostream>

#include"Core/Logger/Logger.h"
#include"Memory/MemoryMonitor.h"
#include"GlobalMemory.h"
#include"ECS/SystemManager.h"
#include"ECS/Coordinator.h"
#include"Core/System/System.h"
#include"Resource/ResourceManager.h"

#define DISPATCH_LAYER_EVENT(eventType, eventContext) for (auto iter =\
	mLayerStack->rbegin(); iter != mLayerStack->rend(); ++iter) {\
	if ((*iter)->On##eventType(eventContext)) {\
		break;\
	}\
}

namespace VIEngine { 
	Application* Application::sInstance = nullptr;

	Application& Application::Get() {
		return *sInstance;
	}

	Application::Application(const ApplicationConfiguration& config) : mConfig(config), mEventDispatcher(), 
			mIsRunning(true), mInputState(nullptr), mTime(), mPerFrameData()
	{
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));
		mLayerStack = GlobalMemoryUsage::Get().NewOnStack<LayerStack>(LayerStack::RunTimeType.GetTypeName());
		mSystemManager = GlobalMemoryUsage::Get().NewOnStack<ECS::SystemManager>(ECS::SystemManager::RunTimeType.GetTypeName());
		mCoordinator = GlobalMemoryUsage::Get().NewOnStack<ECS::Coordinator>(ECS::Coordinator::RunTimeType.GetTypeName());
		mRenderer = GlobalMemoryUsage::Get().NewOnStack<Renderer>(Renderer::RunTimeType.GetTypeName());
		
		sInstance = this; 
	}

	bool Application::Init() {
		Logger::Init();

		if (!mNativeWindow->Init(mConfig, &mEventDispatcher)) {
			return false;
		}

		mInputState = mNativeWindow->GetInputState();

		mEventDispatcher.AddEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(OnWindowResizedEvent));
		mEventDispatcher.AddEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(OnKeyPressedEvent));
		mEventDispatcher.AddEventListener<KeyHeldEvent>(BIND_EVENT_FUNCTION(OnKeyHeldEvent));
		mEventDispatcher.AddEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(OnKeyReleasedEvent));
		mEventDispatcher.AddEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(OnMouseMovedEvent));
		mEventDispatcher.AddEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OnMouseScrolledEvent));
		mEventDispatcher.AddEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonPressedEvent));
		mEventDispatcher.AddEventListener<MouseButtonHeldEvent>(BIND_EVENT_FUNCTION(OnMouseButtonHeldEvent));
		mEventDispatcher.AddEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(OnMouseButtonReleasedEvent));

		/*auto& collisionSystem = mSystemManager->AddSystem<CollisionResolver>();
		auto& animationSystem = mSystemManager->AddSystem<AnimationSystem>();
		auto& renderer2D = mSystemManager->AddSystem<Renderer2D>();

		mSystemManager->AddSystemDependency(&animationSystem, &collisionSystem);
		mSystemManager->AddSystemDependency(&renderer2D, &collisionSystem, &animationSystem);

		collisionSystem.SetUpdateInterval(1.5f);
		animationSystem.SetUpdateInterval(1.5f);
		renderer2D.SetUpdateInterval(1.5f);*/

		mSystemManager->OnInit();
		mRenderer->OnInit(mConfig);
		ResourceManager::OnInit(mConfig.RendererSpec);
		return true;
	}

	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);

		const float MAX_DELTA_TIME = 0.05f;
		float minDeltaTime = 1.0f / mConfig.MaxFPS;

		OnInitClient();

		while (mIsRunning && !mNativeWindow->ShouldClose()) {
			static float lastFrameTime = 0.0f;

			while (mNativeWindow->GetTimeSeconds() - lastFrameTime < minDeltaTime);

			mPerFrameData.FrameIndex++;

			float currentFrameTime = mNativeWindow->GetTimeSeconds();

			mTime = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;

			mNativeWindow->PollsEvent();

			for (auto layer : *mLayerStack) {
				layer->OnProcessInput(*mInputState);
			}
			
			mNativeWindow->Swapbuffers();
			while (mTime.GetDeltaTime() > MAX_DELTA_TIME) {
				mPerFrameData.IsCatchUpPhase = true;
				for (auto layer : *mLayerStack) {
					layer->OnUpdate(MAX_DELTA_TIME);
				}

				mSystemManager->OnUpdate(MAX_DELTA_TIME);

				mTime -= MAX_DELTA_TIME;
			}
			mPerFrameData.IsCatchUpPhase = false;

			for (auto layer : *mLayerStack) {
				layer->OnUpdate(mTime);
			} 

			mSystemManager->OnUpdate(MAX_DELTA_TIME);

			for (auto layer : *mLayerStack) {
				layer->OnGUIRender();
			}

			if (mRenderer->BeginScene()) {
				mRenderer->Render();
				mRenderer->EndScene();
			}
			MemoryMonitor::Get().Update();
		}

		OnShutdownClient();
	}

	void Application::Shutdown() {
		//GlobalMemoryUsage::Get().FreeOnStack(mLayerStack);
		mRenderer->OnShutdown();
		mSystemManager->OnShutdown();
		mNativeWindow->Shutdown();
		ResourceManager::OnShutdown();
		MemoryMonitor::Get().Clear();
		MemoryMonitor::Get().DectecMemoryLeaks();
	}

	bool Application::OnWindowResizedEvent(const WindowResizedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(WindowResizedEvent, eventContext);
		return false;
	}

	bool Application::OnKeyPressedEvent(const KeyPressedEvent& eventContext) {
		if (eventContext.IsKey(EKeyCode::ESCAPE)) {
			mIsRunning = false;
			return true;
		}

		DISPATCH_LAYER_EVENT(KeyPressedEvent, eventContext);
		return false;
	}
	
	bool Application::OnKeyHeldEvent(const KeyHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyHeldEvent, eventContext);
		return false;
	}
	
	bool Application::OnKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(KeyReleasedEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseMovedEvent(const MouseMovedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseMovedEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseScrolledEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonPressedEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonHeldEvent, eventContext);
		return false;
	}
	
	bool Application::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		DISPATCH_LAYER_EVENT(MouseButtonReleasedEvent, eventContext);
		return false;
	}

	void Application::PushLayer(Layer* layer) {
		mLayerStack->Push(layer);
		layer->OnAttach();
	}

	void Application::PushOverlayLayer(Layer* layer) {
		mLayerStack->PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer) {
		mLayerStack->Pop(layer);
		layer->OnDetach();
	}
	
	void Application::PopOverlayLayer(Layer* layer) {
		mLayerStack->PopOverlay(layer);
		layer->OnDetach();
	}
}