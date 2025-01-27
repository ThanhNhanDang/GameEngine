#include"ResourceManager.h"
#include"Core/GlobalMemory.h"
#include"Renderer/OpenGL/OpenGLResourceManager.h"
namespace VIEngine {
	ResourceManager* ResourceManager::sInstance = nullptr;


	ResourceManager& ResourceManager::Get() {
		return *sInstance;
	}

	void ResourceManager::OnInit(ERendererSpec rendererSpec) {
		switch (rendererSpec)		
		{
		case VIEngine::ERendererSpec::OpenGL:
			sInstance = GlobalMemoryUsage::Get().NewOnStack<OpenGLResourceManager>(OpenGLResourceManager::RunTimeType.GetTypeName());
			break;
		case VIEngine::ERendererSpec::DirectX:
			VI_ASSERT(false && "Currently not supported for DirectX");
			break;
		default:
			VI_ASSERT(false && "Unknow Renderer API");
			break;
		}
	}

	void ResourceManager::OnShutdown() {
		sInstance->OnReset();
	}
}