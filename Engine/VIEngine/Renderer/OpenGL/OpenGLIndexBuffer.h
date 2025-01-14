#pragma once

#include"Resource/IndexBuffer.h"

namespace VIEngine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		DECLARE_RTTI
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();

		virtual void Release() override;
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void SetData(void* data, uint32_t size, uint32_t nums, ERendererMode mode = ERendererMode::Static) override;
		VI_FORCE_INLINE virtual uint32_t GetID() const override { return mID; }
		VI_FORCE_INLINE virtual uint32_t GetSize() const override { return mSize; }
		VI_FORCE_INLINE virtual uint32_t GetNums() const override { return mNums; }
		
	private:
		uint32_t mID, mSize, mNums;
	};
}