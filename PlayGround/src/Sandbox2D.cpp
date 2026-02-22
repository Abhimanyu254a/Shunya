#include "Sandbox2D.h"
#include <imgui.h>

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <chrono>


class Timer
{
public:
    Timer(const char* name, std::function<void(ProfileResult)> func)
        : m_Name(name), m_Func(func), m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        if (!m_Stopped)
            Stop();
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint)
            .time_since_epoch()
            .count();

        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
            .time_since_epoch()
            .count();

        m_Stopped = true;

        long long durationUs = end - start;
        double durationMs = durationUs / 1000.0;

        m_Func({ m_Name, durationMs });
    }

private:
    const char* m_Name;
    std::function<void(ProfileResult)> m_Func;
    bool m_Stopped;
    std::chrono::high_resolution_clock::time_point m_StartTimepoint;
};
#define PROFILE_SCOPE(name) \
    Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult);});

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}
Sandbox2D::~Sandbox2D()
{ }

void Sandbox2D::OnAttach() 
{
    m_Texture = Shunya::Texture2D::Create("assets/textures/cp.png");

    
}
void Sandbox2D::OnDetch()
{

}


void Sandbox2D::OnUpdate(Shunya::Timestamp ts)
{
    PROFILE_SCOPE("Sandbox2D::OnUpdate");
    m_CameraController.OnUpdate(ts);

    {
        PROFILE_SCOPE("Renderer Clear");
    
        Shunya::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        Shunya::RendererCommand::Clear();

    }
    {
		PROFILE_SCOPE("Renderer Draw");
        Shunya::Renderer2D::BeginScene(m_CameraController.GetCamera());
    }
    
    Shunya::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Shunya::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Shunya::Renderer2D::DrawQuad({ 0.0f,0.0f ,-0.1f}, { 10.f, 10.0f }, m_Texture);
    Shunya::Renderer2D::EndScene();   


    // UPLOAD COLOR: We bind the shader and send the color from ImGui

    // RENDER TRIANGLE
    // Note: Explicitly passing Identity Matrix to avoid garbage transform
    //Shunya::Renderer::Submit(textureShader, m_VertexArray, glm::mat4(1.0f));
    
}
void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    for (auto& result : m_ProfileResults)
    {
        ImGui::Text("%s  %.3f ms", result.Name, result.Time);
    }
    m_ProfileResults.clear();

	ImGui::End();

}
void Sandbox2D::OnEvent(Shunya::Event& e)
{
	m_CameraController.OnEvent(e);
}
