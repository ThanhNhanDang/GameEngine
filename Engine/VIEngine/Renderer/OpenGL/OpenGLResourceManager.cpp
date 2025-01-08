#include"OpenGLResourceManager.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLResourceManager)

	OpenGLResourceManager::OpenGLResourceManager():
		mVertexBufferMemoryManager("VertexBufferMemoryManager"),
		mIndexBufferMemoryManager("IndexBufferMemoryManager")

	{
	}

	OpenGLResourceManager::~OpenGLResourceManager()
	{
	}

	void OpenGLResourceManager::OnReset()
	{
		mVertexBufferMemoryManager.Reset();
		mIndexBufferMemoryManager.Reset();
	}

	VertexBuffer* OpenGLResourceManager::NewVertexBuffer()
	{
		return mVertexBufferMemoryManager.NewObject();
	}

	void OpenGLResourceManager::FreeVertexBuffer(void* memory)
	{
		mVertexBufferMemoryManager.FreeObject(memory);
	}

	IndexBuffer* OpenGLResourceManager::NewIndexBuffer()
	{
		return mIndexBufferMemoryManager.NewObject();

	}

	void OpenGLResourceManager::FreeIndexBuffer(void* memory)
	{
		mIndexBufferMemoryManager.FreeObject(memory);
	}

	Shader* OpenGLResourceManager::NewShader(const char* filepath)
	{
		return nullptr;
	}

	void OpenGLResourceManager::FreeShader(void* memory)
	{
	}

	void* OpenGLResourceManager::AllocatePerFrame(uint32_t size, uint8_t alignment)
	{
		return mGeneralMemoryManager.AllocatePerFrame(size, alignment);
	}

}