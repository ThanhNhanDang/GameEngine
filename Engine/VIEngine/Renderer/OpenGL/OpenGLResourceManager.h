#pragma once

#include"Core/Type/RTTI.h"
#include"Resource/ResourceManager.h"
#include"Memory/MemoryChunkManager.h"
#include"OpenGLVertexBuffer.h"
#include"OpenGLIndexBuffer.h"

namespace VIEngine {
	class OpenGLResourceManager :public ResourceManager {
	public:
		DECLARE_RTTI
	public:
		OpenGLResourceManager();
		~OpenGLResourceManager();

		virtual void OnReset() override;
		virtual class VertexBuffer* NewVertexBuffer() override;
		virtual void FreeVertexBuffer(void* memory) override;
		virtual class IndexBuffer* NewIndexBuffer() override;
		virtual void FreeIndexBuffer(void* memory) override;
		virtual class Shader* NewShader(const char* filepath) override;
		virtual void FreeShader(void* memory) override;
		virtual void* AllocatePerFrame(uint32_t size, uint8_t alignment) override;
	private:
		MemoryManager mGeneralMemoryManager;
		MemoryChunkManager <OpenGLVertexBuffer, 100> mVertexBufferMemoryManager;
		MemoryChunkManager <OpenGLIndexBuffer, 100> mIndexBufferMemoryManager;
	};
}