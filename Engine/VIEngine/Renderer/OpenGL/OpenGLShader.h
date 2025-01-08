#pragma once

#include"Resource/Shader.h"
namespace VIEngine {
	class OpenGLShader :public Shader {
	public:
		DECLARE_RTTI
	public:
		OpenGLShader();
		~OpenGLShader();
	};
}