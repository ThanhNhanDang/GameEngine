#include"Renderer.h"
#include"RenderCommand.h"
#include "Core/Logger/Logger.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(Renderer)

		Renderer::Renderer() {

	}
	Renderer::~Renderer() {

	}
	RenderCommandQueue Renderer::sRenderCommandQueue;

	void Renderer::Submit(const RenderCallback& renderCallback) {
		if (Application::Get().GetPerFrameData().IsCatchUpPhase)return;
		sRenderCommandQueue.Enqueue(renderCallback);
	}

	void Renderer::ClearColor(float r, float g, float b, float w) {
		Submit([r, g, b, w]() {
			RenderCommand::ClearColor(r, g, b, w);
			});
	}

	void Renderer::OnInit(const ApplicationConfiguration& appConfig) {
		CORE_LOG_TRACE("Renderer init succeess");
		Submit([rendererSpec= appConfig.RendererSpec]() {
			RenderCommand::OnInit(rendererSpec);
		});

	}
	bool Renderer::BeginScene() {
		return true;
	}
	void Renderer::Render() {
		sRenderCommandQueue.ProcessAndRender();
	}
	void Renderer::EndScene() {

	}
	void Renderer::OnShutdown() {

		CORE_LOG_TRACE("Renderer is shutdown");
		Submit([]() {
			RenderCommand::OnShutdown();
		});
	}
}