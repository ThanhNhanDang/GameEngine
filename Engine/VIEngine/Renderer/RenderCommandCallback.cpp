#include"RenderCommandCallback.h"

namespace VIEngine {
	RenderCommandCallback::RenderCommandCallback() : mFrameIndex(0) {

	}

	RenderCommandCallback::RenderCommandCallback(const RenderCallback renderCallback) : mCallback(renderCallback), mFrameIndex(0) {

	}

	RenderCommandCallback::~RenderCommandCallback() {

	}
	void RenderCommandCallback::Execute() {
		mCallback();
	}
}