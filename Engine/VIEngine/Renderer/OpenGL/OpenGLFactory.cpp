#include"OpenGLFactory.h"
#include<glad/gl.h>
namespace VIEngine {
	uint32_t OpenGLFactory::ToOpenGLMode(ERendererMode mode) {
		if (mode == ERendererMode::Dynamic) return GL_DYNAMIC_DRAW;
		if (mode == ERendererMode::Stream) return GL_STREAM_DRAW;
		return GL_STATIC_DRAW;
	}
}