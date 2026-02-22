#pragma once

#include "Shunya.h"

struct ProfileResult
{
	const char* Name;
	double Time;
};

class Sandbox2D : public Shunya::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D();
	virtual void OnAttach() override;
	virtual void OnDetch() override;

	void OnUpdate(Shunya::Timestamp ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Shunya::Event& e) override;

private:
	Shunya::OrthographicCameraController m_CameraController;

	Shunya::Ref<Shunya::VertexArray> m_SquareVA;
	Shunya::Ref<Shunya::Shader> m_FlatColorShader;
	Shunya::Ref<Shunya::Texture2D> m_Texture;
	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f,1.0f};
};