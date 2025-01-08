#include"GameplayLayer.h"
#include<VIEngine/Base.h>
#include<Core/System/System.h>
#include<Renderer/Renderer.h>

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::OnAttach() {
	LOG_TRACE("GameplayLayer is attached");

}

void GameplayLayer::OnDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::OnUpdate(VIEngine::Time time) {
	VIEngine::Renderer::ClearColor(0.3f, 0.3f, 0.6f);
}

bool GameplayLayer::OnKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) {
	return false;
}

