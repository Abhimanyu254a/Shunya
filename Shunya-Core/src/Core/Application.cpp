#include "SNY-PCH.h"
#include "Log.h"

#include <vector>
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/openGL/OpenGLVertexArray.h"
#include "input.h"

namespace Shunya
{
#define BIND_FUN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;


	//Application::Application()
	//{
	//	SHUNYA_CORE_ASSERT(!s_Instance, "Applicational ready exists!");
	//	s_Instance = this;

	//	m_Window = std::unique_ptr<Window>(Window::Create());
	//	m_Window->SetEventCallback(BIND_FUN(OnEvent));

	//	m_ImGuiLayer = new imGUILayer();
	//	PushOverlay(m_ImGuiLayer);

	//	m_VertexArray.reset(VertexArray::Create());

	//	float vertices[3 * 7] = {
	//		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
	//		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	//		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	//	};

	//	std::shared_ptr<VertexBuffer> vertexBuffer;
	//	vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	//	BufferLayout layout = {
	//		{ ShaderDataType::Float3, "a_Position" },
	//		{ ShaderDataType::Float4, "a_Color" }
	//	};
	//	vertexBuffer->SetLayout(layout);
	//	m_VertexArray->AddVertexBuffer(vertexBuffer);

	//	uint32_t indices[3] = { 0, 1, 2 };
	//	std::shared_ptr<IndexBuffer> indexBuffer;
	//	indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	//	m_VertexArray->AddIndexBuffer(indexBuffer);

	//	vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	//	float squareVertices[3 * 4] = {
	//		-0.75f, -0.75f, 0.0f,
	//		 0.75f, -0.75f, 0.0f,
	//		 0.75f,  0.75f, 0.0f,
	//		-0.75f,  0.75f, 0.0f
	//	};

	//	//std::shared_ptr<VertexBuffer> squareVB;
	//	//squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));


	//	//squareVB->SetLayout({
	//	//	{ ShaderDataType::Float3, "a_Position" }
	//	//	});
	//	//m_SquareVA->AddVertexBuffer(vertexBuffer);

	//	//uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	//	//std::shared_ptr<IndexBuffer> squareIB;
	//	//squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	//	//m_SquareVA->AddIndexBuffer(squareIB);

	//	std::string vertexSrc = R"(
	//		#version 330 core
	//		
	//		layout(location = 0) in vec3 a_Position;
	//		layout(location = 1) in vec4 a_Color;

	//		out vec3 v_Position;
	//		out vec4 v_Color;

	//		void main()
	//		{
	//			v_Position = a_Position;
	//			v_Color = a_Color;
	//			gl_Position = vec4(a_Position, 1.0);	
	//		}
	//	)";

	//	std::string fragmentSrc = R"(
	//		#version 330 core
	//		
	//		layout(location = 0) out vec4 color;

	//		in vec3 v_Position;
	//		in vec4 v_Color;

	//		void main()
	//		{
	//			color = v_Color * vec4(v_Position * 0.5 + 0.5, 1.0);
	//			
	//		}
	//	)";

	//	m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

	//	std::string blueShaderVertexSrc = R"(
	//		#version 330 core
	//		
	//		layout(location = 0) in vec3 a_Position;

	//		out vec3 v_Position;

	//		void main()
	//		{
	//			v_Position = a_Position;
	//			gl_Position = vec4(a_Position, 1.0);	
	//		}
	//	)";

	//	std::string blueShaderFragmentSrc = R"(
	//		#version 330 core
	//		
	//		layout(location = 0) out vec4 color;

	//		in vec3 v_Position;

	//		void main()
	//		{
	//			color = vec4(0.2, 0.3, 0.8, 1.0);
	//		}
	//	)";

	//	m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	//}
//------------------------------------------------------------------------------------------------------------------------------
Application::Application()
{
	SHUNYA_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_FUN(OnEvent));

	m_ImGuiLayer = new imGUILayer();
	PushOverlay(m_ImGuiLayer);

	// -------------------------------------------------------------
	// 1. TRIANGLE RENDERING SETUP
	// -------------------------------------------------------------
	m_VertexArray.reset(VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	// FIX: Use 'auto' and '='. No .reset() nonsense.
	std::shared_ptr<VertexBuffer>vertexBuffer;
	vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" }
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	std::shared_ptr<IndexBuffer>indexBuffer;
	indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(indexBuffer); 

	// -------------------------------------------------------------
	// 2. SQUARE RENDERING SETUP
	// -------------------------------------------------------------
	m_SquareVA.reset(VertexArray::Create());

	float squareVertices[3 * 7] = {
		-0.75f, -0.75f, 0.0f,
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		-0.75f,  0.75f, 0.0f
	};
	std::shared_ptr<VertexBuffer>squareVB;
	squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

	// Square only has Position, no Color in this array
	squareVB->SetLayout({
		{ ShaderDataType::Float3, "a_Position" }
		});

	// FIX: Add the SQUARE buffer, not the triangle 'vertexBuffer'

	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<IndexBuffer>squareIB;
	squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	// -------------------------------------------------------------
	// 3. SHADERS
	// -------------------------------------------------------------
	// ... (Your Triangle Shader strings here are fine) ...
	




 std::string vertexSrc = R"(
 #version 410 core
 
 layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec4 a_Color;


 // Define an output variable to send data to the Fragment Shader
 out vec3 v_Position;
	out vec4 v_Color;

 void main()
 {
 // Pass the raw position data to the next stage
 v_Position = a_Position;
 v_Color = a_Color;
 gl_Position = vec4(a_Position, 1.0);

 }
 )";

 //////
 std::string fragmentSrc = R"(
 #version 410 core
 
 layout(location = 0) out vec4 color;

 // This 'in' variable must match the 'out' variable from the Vertex Shader exactly
 in vec3 v_Position;
in vec4 v_Color;

 void main()
 {
 // MATHEMATICAL MAGIC:
 // v_Position values range from approx -0.5 to 0.5.
 // Colors need to be 0.0 to 1.0.
 // (v_Position * 0.5) + 0.5 shifts the range perfectly.
 
 // X controls Red, Y controls Green, Z controls Blue
 color = vec4(v_Position * 0.5 + 0.5, 1.0);
	color = v_Color;	
 }
 )";




	m_Shader.reset(new Shader(vertexSrc, fragmentSrc));









	std::string blueShaderVertexSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 a_Position;
        out vec3 v_Position;
        void main()
        {
            v_Position = a_Position;
            // FIX: Typo 'A_Position' -> 'a_Position'
            gl_Position = vec4(a_Position, 1.0);    
        }
    )";

	std::string blueShaderFragmentSrc = R"(
        #version 330 core
        layout(location = 0) out vec4 color;
        in vec3 v_Position;
        void main()
        {
            color = vec4(0.2, 0.3, 0.8, 1.0);
        }
    )";

	m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
}
//------------------------------------------------------------------------------------------------------------------------------
	//Application::Application()
	//{
	//	SHUNYA_CORE_ASSERT(!s_Instance, "Applicational ready exists!");
	//	s_Instance = this;
	//	m_Window = std::unique_ptr<Window>(Window::Create());
	//	m_Window->SetEventCallback(BIND_FUN(OnEvent));


	//	m_ImGuiLayer = new imGUILayer();
	//	PushOverlay(m_ImGuiLayer);

	//	m_VertexArray.reset(VertexArray::Create());

	//	float vertices[3 * 7] = {
	//			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
	//			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	//			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	//	};
	//	
	//	std::shared_ptr<VertexBuffer> vertexBuffer;
	//	vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	//	BufferLayout layout = {
	//		{ ShaderDataType::Float3, "a_Position" },
	//		{ ShaderDataType::Float4, "a_Color" }
	//	};
	//	vertexBuffer->SetLayout(layout);
	//	m_VertexArray->AddVertexBuffer(vertexBuffer);


	//	

	//	m_VertexBuffer->SetLayout(layout);
	//	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//	

	//	uint32_t indices[3] = { 0,1,2 };
	//	m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
	//	m_VertexArray->AddIndexBuffer(m_IndexBuffer);

	//	m_SquareVR.reset(VertexArray::Create());

	//	float vertices[3 * 7] = {
	//		// X      Y      Z
	//		-0.5f, -0.5f, 0.0f,0.8f,0.2f,0.8f,1.0f, // Bottom Left
	//		 0.5f, -0.5f, 0.0f, 0.2f,0.3f,0.8f,1.0f,// Bottom Right
	//		 0.0f,  0.5f, 0.0f ,0.8f,0.8f,0.2f,1.0f // Top Center
	//	};

	//	std::shared_ptr<VertexBuffer> squareVB = std::make_shared<VertexBuffer>();




 //       std::string vertexSrc = R"(
 //           #version 410 core
 //           
 //           layout(location = 0) in vec3 a_Position;
	//		layout(location = 1) in vec4 a_Color;


 //           // Define an output variable to send data to the Fragment Shader
 //           out vec3 v_Position;
	//		out vec4 v_Color;

 //           void main()
 //           {
 //               // Pass the raw position data to the next stage
 //               v_Position = a_Position;
 //               v_Color = a_Color;
 //               gl_Position = vec4(a_Position, 1.0);
 //           }
 //       )";

 //
 //       std::string fragmentSrc = R"(
 //           #version 410 core
 //           
 //           layout(location = 0) out vec4 color;

 //           // This 'in' variable must match the 'out' variable from the Vertex Shader exactly
 //           in vec3 v_Position;
	//		in vec4 v_Color;

 //           void main()
 //           {
 //               // MATHEMATICAL MAGIC:
 //               // v_Position values range from approx -0.5 to 0.5.
 //               // Colors need to be 0.0 to 1.0.
 //               // (v_Position * 0.5) + 0.5 shifts the range perfectly.
 //               
 //               // X controls Red, Y controls Green, Z controls Blue
 //               color = vec4(v_Position * 0.5 + 0.5, 1.0);
	//			color = v_Color;	
 //           }
 //       )";




	//	m_Shader.reset(new Shader(vertexSrc, fragmentSrc));




	//	std::string blueShaderVertexSrc = R"(
	//		#version 330 core
	//		
	//		layout(location = 0) in vec3 a_Position;

	//		out vec3 v_Position;

	//		void main()
	//		{
	//			v_Position = a_Position;
	//			gl_Position = vec4(A_Position, 1.0);	
	//		}
	//	)";

	//	std::string blueShaderFragmentSrc = R"(
	//		#version 330 core
	//		
	//		layout(location = 0) out vec4 color;

	//		in vec3 v_Position;

	//		void main()
	//		{
	//			color = vec4(0.2, 0.3, 0.8, 1.0);
	//		}
	//	)";

	//	m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	//}
	Application::~Application()
	{
	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
		Overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_FUN(OnWindowClose));

		SHUNYA_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// --- RENDER SQUARE ---
			m_BlueShader->Bind();
			m_SquareVA->Bind();
			// Robustness fix: Get count from the bound VAO, not a null member variable
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			// --- RENDER TRIANGLE ---
			m_Shader->Bind();
			m_VertexArray->Bind();
			// Robustness fix: Get count from the bound VAO
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	//void Application::Run()
	//{
	//	while (m_Running)
	//	{
	//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//		glClear(GL_COLOR_BUFFER_BIT);

	//		//m_BlueShader->Bind();
	//		//m_SquareVA->Bind();
	//		//glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	//		m_Shader->Bind();
	//		m_VertexArray->Bind();
	//		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

	//		for (Layer* layer : m_LayerStack)
	//		{
	//			layer->OnUpdate();

	//		}

	//		m_ImGuiLayer->Begin();
	//		for (Layer* layer : m_LayerStack)
	//		{
	//			layer->OnImGuiRender();
	//		}
	//		m_ImGuiLayer->End();




	//		m_Window->OnUpdate();
	//	}
	//}
	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;


		return true;
	}

}