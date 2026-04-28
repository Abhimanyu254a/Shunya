////#include "SNY-PCH.h"
////#include "Renderer2D.h"
////
////#include "Core/Core.h"
////#include "VertexArray.h"
////#include "Shader.h"
////#include "RendererCommand.h"
////#include <glm/gtc/matrix_transform.hpp>
////#include "Core/Rendered/UniformBuffer.h"
////#include <glm/gtc/type_ptr.hpp>
////#include "Core/openGL/OpenGLShader.h" 
////#include <gl/GL.h>
////
////namespace Shunya {
////
////	struct QuadVertex
////	{
////		glm::vec3 Position;
////		glm::vec2 TexCoord;
////		glm::vec4 Color;
////		float TexIndex;
////		float TilingFactor;
////		int EntityID;
////	};
////	struct CircleVertex
////	{
////		glm::vec3 WorldPosition;
////		glm::vec3 LocalPosition;
////		glm::vec4 Color;
////		float Thickness;
////		float Fade;
////
////		// Editor-only
////		int EntityID;
////	};
////
////	struct Renderer2DData
////	{
////		static constexpr uint32_t MaxQuads = 10000;
////		static constexpr uint32_t MaxVertices = MaxQuads * 4;
////		static constexpr uint32_t MaxIndices = MaxQuads * 6;
////		static constexpr const uint32_t MaxTextureSlots = 32;
////
////		Ref<VertexArray> QuadVertexArray;
////		Ref<VertexBuffer> QuadVertexBuffer;
////		Ref<Shader>QuadShader;
////		Ref<Texture2D> WhiteTexture;
////
////		uint32_t QuadIndexCount = 0;
////		QuadVertex* QuadVertexBufferBase = nullptr;
////		QuadVertex* QuadVertexBufferPtr = nullptr;
////
////		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
////		uint32_t textureSlotindex = 1;
////
////		glm::vec4 QuadVertexPosition[4];
////
////		Renderer2D::Statistics Stats;
////
////		// MOVED INSIDE THE STRUCT
////		struct CameraData
////		{
////			glm::mat4 ViewProjection;
////		};
////		CameraData CameraBuffer;
////		Ref<UniformBuffer> CameraUniformBuffer;
////	};
////
////	static Renderer2DData s_Data;
////
////	void Renderer2D::Init()
////	{
////		SHUNYA_PROFILE_FUNCTION();
////
////		s_Data.QuadVertexArray = VertexArray::Create();
////		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
////
////		s_Data.QuadVertexBuffer->SetLayout({
////				{ ShaderDataType::Float3, "a_Position" },
////				{ ShaderDataType::Float2, "a_TexCoord" },
////				{ ShaderDataType::Float4, "a_Color" },
////				{ ShaderDataType::Float, "a_TexIndex" },
////				{ ShaderDataType::Float, "a_TilingFactor" },
////				{ ShaderDataType::Int,    "a_EntityID" }
////			});
////
////		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
////		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
////
////		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
////		uint32_t offset = 0;
////		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
////			quadIndices[i + 0] = offset + 0;
////			quadIndices[i + 1] = offset + 1;
////			quadIndices[i + 2] = offset + 2;
////			quadIndices[i + 3] = offset + 2;
////			quadIndices[i + 4] = offset + 3;
////			quadIndices[i + 5] = offset + 0;
////			offset += 4;
////		}
////		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
////		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
////		delete[] quadIndices;
////
////		s_Data.WhiteTexture = Texture2D::Create(1, 1);
////		uint32_t whiteTextureData = 0xffffffff;
////		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
////
////		int samplers[32];
////		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
////		{
////			samplers[i] = i;
////		}
////
////		s_Data.TextureShader = Shader::Create("assets/Shaders/Texture.glsl");
////
////		// UNCOMMENTED TO FIX THE BLACK SCREEN
////		s_Data.TextureShader->Bind();
////		s_Data.TextureShader->SetIntArray("u_Texture", samplers, s_Data.MaxTextureSlots);
////
////		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
////
////		s_Data.QuadVertexPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
////		s_Data.QuadVertexPosition[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
////		s_Data.QuadVertexPosition[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
////		s_Data.QuadVertexPosition[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
////		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);
////	}
////
////	void Renderer2D::FlushAndReset()
////	{
////		EndScene();
////		s_Data.QuadIndexCount = 0;
////		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
////		s_Data.textureSlotindex = 1;
////	}
////
////	void Renderer2D::Shutdown()
////	{
////		SHUNYA_PROFILE_FUNCTION();
////		delete[] s_Data.QuadVertexBufferBase;
////		s_Data.QuadVertexBufferBase = nullptr;
////	}
////
////	void Renderer2D::DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID)
////	{
////		DrawQuad(transform, src.Color, entityID);
////	}
////
////	void Renderer2D::BeginScene(const OrthographicCamera& camera)
////	{
////		SHUNYA_PROFILE_FUNCTION("Renderer2D::begineScene");
////		// FIXED: Uses GetViewProjectionMatrix() instead of GetViewProjection()
////		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjectionMatrix();
////		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
////		s_Data.QuadIndexCount = 0;
////		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
////		s_Data.textureSlotindex = 1;
////	}
////
////	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
////	{
////		SHUNYA_PROFILE_FUNCTION("Renderer2D::begineScene");
////		s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
////		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
////
////		s_Data.QuadIndexCount = 0;
////		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
////		s_Data.textureSlotindex = 1;
////	}
////
////	void Renderer2D::BeginScene(const EditorCamera& camera)
////	{
////		SHUNYA_PROFILE_FUNCTION("Renderer2D::BeginScene");
////		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
////		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
////
////		s_Data.QuadIndexCount = 0;
////		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
////		s_Data.textureSlotindex = 1;
////	}
////
////	void Renderer2D::EndScene()
////	{
////		SHUNYA_PROFILE_FUNCTION("Renderer2d::EndScene");
////		size_t datasize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
////		SHUNYA_CORE_ASSERT(datasize <= (size_t)UINT32_MAX, "Quad vertex buffer data size exceeds 32-bit limit");
////		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, static_cast<uint32_t>(datasize));
////		Flush();
////	}
////
////	void Renderer2D::Flush()
////	{
////		for (uint32_t i = 0; i < s_Data.textureSlotindex; i++)
////		{
////			s_Data.TextureSlots[i]->Bind(i);
////		}
////
////		s_Data.TextureShader->Bind();
////		RendererCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
////		s_Data.Stats.DrawCalls++;
////	}
////
////	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
////	{
////		DrawQuad({ position.x, position.y, 0.0f }, size, color);
////	}
////
////	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
////	{
////		SHUNYA_PROFILE_FUNCTION();
////		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
////		DrawQuad(transform, color, -1);
////	}
////
////	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
////	{
////		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
////	}
////
////	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
////	{
////		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
////		DrawQuad(transform, texture, tilingFactor, tintColor, -1);
////	}
////
////	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID)
////	{
////		SHUNYA_PROFILE_FUNCTION();
////		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
////			FlushAndReset();
////
////		const float texIndex = 0.0f;
////		const float tilingFactor = 1.0f;
////
////		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[0];
////		s_Data.QuadVertexBufferPtr->Color = color;
////		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
////		s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
////		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
////		s_Data.QuadVertexBufferPtr->EntityID = entityID;
////		s_Data.QuadVertexBufferPtr++;
////
////		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[1];
////		s_Data.QuadVertexBufferPtr->Color = color;
////		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
////		s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
////		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
////		s_Data.QuadVertexBufferPtr->EntityID = entityID;
////		s_Data.QuadVertexBufferPtr++;
////
////		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[2];
////		s_Data.QuadVertexBufferPtr->Color = color;
////		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
////		s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
////		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
////		s_Data.QuadVertexBufferPtr->EntityID = entityID;
////		s_Data.QuadVertexBufferPtr++;
////
////		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[3];
////		s_Data.QuadVertexBufferPtr->Color = color;
////		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
////		s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
////		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
////		s_Data.QuadVertexBufferPtr->EntityID = entityID;
////		s_Data.QuadVertexBufferPtr++;
////
////		s_Data.QuadIndexCount += 6;
////		s_Data.Stats.QuadCount++;
////	}
////
////	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
////	{
////		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
////			FlushAndReset();
////
////		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
////		float textureIndex = 0.0f;
////
////		for (uint32_t i = 1; i < s_Data.textureSlotindex; i++) {
////			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
////				textureIndex = (float)i;
////				break;
////			}
////		}
////
////		if (textureIndex == 0.0f)
////		{
////			textureIndex = (float)s_Data.textureSlotindex;
////			s_Data.TextureSlots[s_Data.textureSlotindex] = texture;
////			s_Data.textureSlotindex++;
////		}
////
////		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[0];
////		s_Data.QuadVertexBufferPtr->Color = color;
////		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
////		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
////		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
////		s_Data.QuadVertexBufferPtr->EntityID = entityID;
////		s_Data.QuadVertexBufferPtr++;
////
////		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[1];
////		s_Data.QuadVertexBufferPtr->Color = color;
////		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
////		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
////		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
////		s_Data.QuadVertexBufferPtr->EntityID = entityID;
////		s_Data.QuadVertexBufferPtr++;
////
////		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[2];
////		s_Data.QuadVertexBufferPtr->Color = color;
////		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
////		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
////		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
////		s_Data.QuadVertexBufferPtr->EntityID = entityID;
////		s_Data.QuadVertexBufferPtr++;
////
////		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[3];
////		s_Data.QuadVertexBufferPtr->Color = color;
////		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
////		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
////		s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
////		s_Data.QuadVertexBufferPtr->EntityID = entityID;
////		s_Data.QuadVertexBufferPtr++;
////
////		s_Data.QuadIndexCount += 6;
////		s_Data.Stats.QuadCount++;
////	}
////
////	void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
////	{
////		DrawRotateQuad({ position.x, position.y, 0.0f }, rotation, size, color);
////	}
////
////	void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
////	{
////		SHUNYA_PROFILE_FUNCTION();
////		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
////			FlushAndReset();
////
////		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
////			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
////			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
////
////		DrawQuad(transform, color, -1);
////	}
////
////	void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
////	{
////		DrawRotateQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tilingFactor, tintColor);
////	}
////
////	void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
////	{
////		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
////			FlushAndReset();
////
////		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
////			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
////			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
////
////		DrawQuad(transform, texture, tilingFactor, tintColor, -1);
////	}
////
////	void Renderer2D::ResetStats()
////	{
////		memset(&s_Data.Stats, 0, sizeof(Statistics));
////	}
////
////	Renderer2D::Statistics Renderer2D::GetStats()
////	{
////		return s_Data.Stats;
////	}
////}
//
//
//
//
//
//
//
//
//#include "SNY-PCH.h"
//#include "Renderer2D.h"
//
//#include "Core/Core.h"
//#include "VertexArray.h"
//#include "Shader.h"
//#include "RendererCommand.h"
//#include <glm/gtc/matrix_transform.hpp>
//#include "Core/Rendered/UniformBuffer.h"
//#include <glm/gtc/type_ptr.hpp>
//#include "Core/openGL/OpenGLShader.h" 
//#include <gl/GL.h>
//
//namespace Shunya {
//
//	struct QuadVertex
//	{
//		glm::vec3 Position;
//		glm::vec2 TexCoord;
//		glm::vec4 Color;
//		float TexIndex;
//		float TilingFactor;
//		int EntityID;
//	};
//
//	struct CircleVertex
//	{
//		glm::vec3 WorldPosition;
//		glm::vec3 LocalPosition;
//		glm::vec4 Color;
//		float Thickness;
//		float Fade;
//		int EntityID;
//	};
//
//	struct LineVertex
//	{
//		glm::vec3 Position;
//		glm::vec4 Color;
//
//		// Editor-only
//		int EntityID;
//	};
//
//	struct Renderer2DData
//	{
//		static constexpr uint32_t MaxQuads = 10000;
//		static constexpr uint32_t MaxVertices = MaxQuads * 4;
//		static constexpr uint32_t MaxIndices = MaxQuads * 6;
//		static constexpr const uint32_t MaxTextureSlots = 32;
//
//		Ref<VertexArray> QuadVertexArray;
//		Ref<VertexBuffer> QuadVertexBuffer;
//		Ref<Shader> TextureShader; // Quad Shader
//		Ref<Texture2D> WhiteTexture;
//
//		Ref<VertexArray> CircleVertexArray;
//		Ref<VertexBuffer> CircleVertexBuffer;
//		Ref<Shader> CircleShader;
//
//		uint32_t QuadIndexCount = 0;
//		QuadVertex* QuadVertexBufferBase = nullptr;
//		QuadVertex* QuadVertexBufferPtr = nullptr;
//
//		uint32_t CircleIndexCount = 0;
//		CircleVertex* CircleVertexBufferBase = nullptr;
//		CircleVertex* CircleVertexBufferPtr = nullptr;
//
//		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
//		uint32_t textureSlotindex = 1;
//
//		glm::vec4 QuadVertexPosition[4];
//
//		Renderer2D::Statistics Stats;
//
//		struct CameraData
//		{
//			glm::mat4 ViewProjection;
//		};
//		CameraData CameraBuffer;
//		Ref<UniformBuffer> CameraUniformBuffer;
//	};
//
//	static Renderer2DData s_Data;
//
//	void Renderer2D::Init()
//	{
//		SHUNYA_PROFILE_FUNCTION();
//
//		// ── Quads ───────────────────────────────────────────────────────────
//		s_Data.QuadVertexArray = VertexArray::Create();
//		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
//
//		s_Data.QuadVertexBuffer->SetLayout({
//				{ ShaderDataType::Float3, "a_Position" },
//				{ ShaderDataType::Float2, "a_TexCoord" },
//				{ ShaderDataType::Float4, "a_Color" },
//				{ ShaderDataType::Float, "a_TexIndex" },
//				{ ShaderDataType::Float, "a_TilingFactor" },
//				{ ShaderDataType::Int,    "a_EntityID" }
//			});
//
//		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
//		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
//
//		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
//		uint32_t offset = 0;
//		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
//			quadIndices[i + 0] = offset + 0;
//			quadIndices[i + 1] = offset + 1;
//			quadIndices[i + 2] = offset + 2;
//			quadIndices[i + 3] = offset + 2;
//			quadIndices[i + 4] = offset + 3;
//			quadIndices[i + 5] = offset + 0;
//			offset += 4;
//		}
//		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
//		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
//		delete[] quadIndices;
//
//		// ── Circles ─────────────────────────────────────────────────────────
//		s_Data.CircleVertexArray = VertexArray::Create();
//		s_Data.CircleVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(CircleVertex));
//
//		s_Data.CircleVertexBuffer->SetLayout({
//			{ ShaderDataType::Float3, "a_WorldPosition" },
//			{ ShaderDataType::Float3, "a_LocalPosition" },
//			{ ShaderDataType::Float4, "a_Color"         },
//			{ ShaderDataType::Float,  "a_Thickness"     },
//			{ ShaderDataType::Float,  "a_Fade"          },
//			{ ShaderDataType::Int,    "a_EntityID"      }
//			});
//
//		s_Data.CircleVertexArray->AddVertexBuffer(s_Data.CircleVertexBuffer);
//		s_Data.CircleVertexArray->SetIndexBuffer(quadIB); // Share the quad index buffer
//		s_Data.CircleVertexBufferBase = new CircleVertex[s_Data.MaxVertices];
//
//		// ── Textures & Shaders ──────────────────────────────────────────────
//		s_Data.WhiteTexture = Texture2D::Create(1, 1);
//		uint32_t whiteTextureData = 0xffffffff;
//		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
//
//		int samplers[32];
//		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
//		{
//			samplers[i] = i;
//		}
//
//		s_Data.TextureShader = Shader::Create("assets/Shaders/Texture.glsl");
//		s_Data.CircleShader = Shader::Create("assets/Shaders/Renderer2D_Circle.glsl");
//
//		s_Data.TextureShader->Bind();
//		s_Data.TextureShader->SetIntArray("u_Texture", samplers, s_Data.MaxTextureSlots);
//
//		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
//
//		s_Data.QuadVertexPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
//		s_Data.QuadVertexPosition[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
//		s_Data.QuadVertexPosition[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
//		s_Data.QuadVertexPosition[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
//
//		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);
//	}
//
//	void Renderer2D::Shutdown()
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		delete[] s_Data.QuadVertexBufferBase;
//		delete[] s_Data.CircleVertexBufferBase;
//		s_Data.QuadVertexBufferBase = nullptr;
//		s_Data.CircleVertexBufferBase = nullptr;
//	}
//
//	void Renderer2D::BeginScene(const OrthographicCamera& camera)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjectionMatrix();
//		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
//		StartBatch();
//	}
//
//	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
//		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
//		StartBatch();
//	}
//
//	void Renderer2D::BeginScene(const EditorCamera& camera)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
//		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
//		StartBatch();
//	}
//
//	void Renderer2D::EndScene()
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		Flush();
//	}
//
//	void Renderer2D::StartBatch()
//	{
//		s_Data.QuadIndexCount = 0;
//		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
//
//		s_Data.CircleIndexCount = 0;
//		s_Data.CircleVertexBufferPtr = s_Data.CircleVertexBufferBase;
//
//		s_Data.textureSlotindex = 1;
//	}
//
//	void Renderer2D::Flush()
//	{
//		if (s_Data.QuadIndexCount)
//		{
//			size_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
//			s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, static_cast<uint32_t>(dataSize));
//
//			for (uint32_t i = 0; i < s_Data.textureSlotindex; i++)
//			{
//				s_Data.TextureSlots[i]->Bind(i);
//			}
//
//			s_Data.TextureShader->Bind();
//			RendererCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
//			s_Data.Stats.DrawCalls++;
//		}
//
//		if (s_Data.CircleIndexCount)
//		{
//			size_t dataSize = (uint8_t*)s_Data.CircleVertexBufferPtr - (uint8_t*)s_Data.CircleVertexBufferBase;
//			s_Data.CircleVertexBuffer->SetData(s_Data.CircleVertexBufferBase, static_cast<uint32_t>(dataSize));
//
//			s_Data.CircleShader->Bind();
//			RendererCommand::DrawIndexed(s_Data.CircleVertexArray, s_Data.CircleIndexCount);
//			s_Data.Stats.DrawCalls++;
//		}
//	}
//
//	void Renderer2D::NextBatch()
//	{
//		Flush();
//		StartBatch();
//	}
//
//	void Renderer2D::DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID)
//	{
//		if (src.Texture)
//			DrawQuad(transform, src.Texture, src.TilingFactor, src.Color, entityID);
//		else
//			DrawQuad(transform, src.Color, entityID);
//	}
//
//	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
//	{
//		DrawQuad({ position.x, position.y, 0.0f }, size, color);
//	}
//
//	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
//		DrawQuad(transform, color, -1);
//	}
//
//	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
//	{
//		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
//	}
//
//	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
//	{
//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
//		DrawQuad(transform, texture, tilingFactor, tintColor, -1);
//	}
//
//	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//
//		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
//			NextBatch();
//
//		const float texIndex = 0.0f;
//		const float tilingFactor = 1.0f;
//		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
//
//		for (size_t i = 0; i < 4; i++)
//		{
//			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[i];
//			s_Data.QuadVertexBufferPtr->Color = color;
//			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
//			s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
//			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
//			s_Data.QuadVertexBufferPtr->EntityID = entityID;
//			s_Data.QuadVertexBufferPtr++;
//		}
//
//		s_Data.QuadIndexCount += 6;
//		s_Data.Stats.QuadCount++;
//	}
//
//	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//
//		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
//			NextBatch();
//
//		float textureIndex = 0.0f;
//		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
//
//		for (uint32_t i = 1; i < s_Data.textureSlotindex; i++) {
//			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
//				textureIndex = (float)i;
//				break;
//			}
//		}
//
//		if (textureIndex == 0.0f)
//		{
//			if (s_Data.textureSlotindex >= Renderer2DData::MaxTextureSlots)
//				NextBatch();
//
//			textureIndex = (float)s_Data.textureSlotindex;
//			s_Data.TextureSlots[s_Data.textureSlotindex] = texture;
//			s_Data.textureSlotindex++;
//		}
//
//		for (size_t i = 0; i < 4; i++)
//		{
//			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[i];
//			s_Data.QuadVertexBufferPtr->Color = tintColor;
//			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
//			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
//			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
//			s_Data.QuadVertexBufferPtr->EntityID = entityID;
//			s_Data.QuadVertexBufferPtr++;
//		}
//
//		s_Data.QuadIndexCount += 6;
//		s_Data.Stats.QuadCount++;
//	}
//
//	void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
//	{
//		DrawRotateQuad({ position.x, position.y, 0.0f }, rotation, size, color);
//	}
//
//	void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
//			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
//			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
//
//		DrawQuad(transform, color, -1);
//	}
//
//	void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
//	{
//		DrawRotateQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tilingFactor, tintColor);
//	}
//
//	void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
//			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
//			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
//
//		DrawQuad(transform, texture, tilingFactor, tintColor, -1);
//	}
//
//	void Renderer2D::DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness /*= 1.0f*/, float fade /*= 0.005f*/, int entityID /*= -1*/)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//
//		if (s_Data.CircleIndexCount >= Renderer2DData::MaxIndices)
//			NextBatch();
//
//		for (size_t i = 0; i < 4; i++)
//		{
//			s_Data.CircleVertexBufferPtr->WorldPosition = transform * s_Data.QuadVertexPosition[i];
//			s_Data.CircleVertexBufferPtr->LocalPosition = s_Data.QuadVertexPosition[i] * 2.0f;
//			s_Data.CircleVertexBufferPtr->Color = color;
//			s_Data.CircleVertexBufferPtr->Thickness = thickness;
//			s_Data.CircleVertexBufferPtr->Fade = fade;
//			s_Data.CircleVertexBufferPtr->EntityID = entityID;
//			s_Data.CircleVertexBufferPtr++;
//		}
//
//		s_Data.CircleIndexCount += 6;
//		s_Data.Stats.QuadCount++; // Can separate into CircleCount later if desired
//	}
//
//	void Renderer2D::ResetStats()
//	{
//		memset(&s_Data.Stats, 0, sizeof(Statistics));
//	}
//
//	Renderer2D::Statistics Renderer2D::GetStats()
//	{
//		return s_Data.Stats;
//	}
//}








#include "SNY-PCH.h"
#include "Renderer2D.h"

#include "Core/Core.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RendererCommand.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Rendered/UniformBuffer.h"
#include <glm/gtc/type_ptr.hpp>
#include "Core/openGL/OpenGLShader.h" 
#include <gl/GL.h>

namespace Shunya {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec4 Color;
		float TexIndex;
		float TilingFactor;
		int EntityID;
	};

	struct CircleVertex
	{
		glm::vec3 WorldPosition;
		glm::vec3 LocalPosition;
		glm::vec4 Color;
		float Thickness;
		float Fade;
		int EntityID;
	};

	struct LineVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		int EntityID;
	};

	struct Renderer2DData
	{
		static constexpr uint32_t MaxQuads = 10000;
		static constexpr uint32_t MaxVertices = MaxQuads * 4;
		static constexpr uint32_t MaxIndices = MaxQuads * 6;
		static constexpr const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader; // Quad Shader
		Ref<Texture2D> WhiteTexture;

		Ref<VertexArray> CircleVertexArray;
		Ref<VertexBuffer> CircleVertexBuffer;
		Ref<Shader> CircleShader;

		Ref<VertexArray> LineVertexArray;
		Ref<VertexBuffer> LineVertexBuffer;
		Ref<Shader> LineShader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		uint32_t CircleIndexCount = 0;
		CircleVertex* CircleVertexBufferBase = nullptr;
		CircleVertex* CircleVertexBufferPtr = nullptr;

		uint32_t LineVertexCount = 0;
		LineVertex* LineVertexBufferBase = nullptr;
		LineVertex* LineVertexBufferPtr = nullptr;

		float LineWidth = 2.0f;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t textureSlotindex = 1;

		glm::vec4 QuadVertexPosition[4];

		Renderer2D::Statistics Stats;

		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		SHUNYA_PROFILE_FUNCTION();

		// ── Quads ───────────────────────────────────────────────────────────
		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

		s_Data.QuadVertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TexCoord" },
				{ ShaderDataType::Float4, "a_Color" },
				{ ShaderDataType::Float, "a_TexIndex" },
				{ ShaderDataType::Float, "a_TilingFactor" },
				{ ShaderDataType::Int,    "a_EntityID" }
			});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		// ── Circles ─────────────────────────────────────────────────────────
		s_Data.CircleVertexArray = VertexArray::Create();
		s_Data.CircleVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(CircleVertex));

		s_Data.CircleVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_WorldPosition" },
			{ ShaderDataType::Float3, "a_LocalPosition" },
			{ ShaderDataType::Float4, "a_Color"         },
			{ ShaderDataType::Float,  "a_Thickness"     },
			{ ShaderDataType::Float,  "a_Fade"          },
			{ ShaderDataType::Int,    "a_EntityID"      }
			});

		s_Data.CircleVertexArray->AddVertexBuffer(s_Data.CircleVertexBuffer);
		s_Data.CircleVertexArray->SetIndexBuffer(quadIB); // Share the quad index buffer
		s_Data.CircleVertexBufferBase = new CircleVertex[s_Data.MaxVertices];

		// ── Lines ───────────────────────────────────────────────────────────
		s_Data.LineVertexArray = VertexArray::Create();
		s_Data.LineVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(LineVertex));

		s_Data.LineVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"    },
			{ ShaderDataType::Int,    "a_EntityID" }
			});

		s_Data.LineVertexArray->AddVertexBuffer(s_Data.LineVertexBuffer);
		s_Data.LineVertexBufferBase = new LineVertex[s_Data.MaxVertices];

		// ── Textures & Shaders ──────────────────────────────────────────────
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int samplers[32];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		s_Data.TextureShader = Shader::Create("assets/Shaders/Texture.glsl");
		s_Data.CircleShader = Shader::Create("assets/Shaders/Renderer2D_Circle.glsl");
		s_Data.LineShader = Shader::Create("assets/Shaders/Renderer2D_Line.glsl"); // You need to create this shader

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Texture", samplers, s_Data.MaxTextureSlots);

		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadVertexPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);
	}

	void Renderer2D::Shutdown()
	{
		SHUNYA_PROFILE_FUNCTION();
		delete[] s_Data.QuadVertexBufferBase;
		delete[] s_Data.CircleVertexBufferBase;
		delete[] s_Data.LineVertexBufferBase;
		s_Data.QuadVertexBufferBase = nullptr;
		s_Data.CircleVertexBufferBase = nullptr;
		s_Data.LineVertexBufferBase = nullptr;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		SHUNYA_PROFILE_FUNCTION();
		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjectionMatrix();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
		StartBatch();
	}

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		SHUNYA_PROFILE_FUNCTION();
		s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
		StartBatch();
	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		SHUNYA_PROFILE_FUNCTION();
		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraData));
		StartBatch();
	}

	void Renderer2D::EndScene()
	{
		SHUNYA_PROFILE_FUNCTION();
		Flush();
	}

	void Renderer2D::StartBatch()
	{
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.CircleIndexCount = 0;
		s_Data.CircleVertexBufferPtr = s_Data.CircleVertexBufferBase;

		s_Data.LineVertexCount = 0;
		s_Data.LineVertexBufferPtr = s_Data.LineVertexBufferBase;

		s_Data.textureSlotindex = 1;
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount)
		{
			size_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
			s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, static_cast<uint32_t>(dataSize));

			for (uint32_t i = 0; i < s_Data.textureSlotindex; i++)
			{
				s_Data.TextureSlots[i]->Bind(i);
			}

			s_Data.TextureShader->Bind();
			RendererCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
			s_Data.Stats.DrawCalls++;
		}

		if (s_Data.CircleIndexCount)
		{
			size_t dataSize = (uint8_t*)s_Data.CircleVertexBufferPtr - (uint8_t*)s_Data.CircleVertexBufferBase;
			s_Data.CircleVertexBuffer->SetData(s_Data.CircleVertexBufferBase, static_cast<uint32_t>(dataSize));

			s_Data.CircleShader->Bind();
			RendererCommand::DrawIndexed(s_Data.CircleVertexArray, s_Data.CircleIndexCount);
			s_Data.Stats.DrawCalls++;
		}

		if (s_Data.LineVertexCount)
		{
			size_t dataSize = (uint8_t*)s_Data.LineVertexBufferPtr - (uint8_t*)s_Data.LineVertexBufferBase;
			s_Data.LineVertexBuffer->SetData(s_Data.LineVertexBufferBase, static_cast<uint32_t>(dataSize));

			s_Data.LineShader->Bind();
			RendererCommand::SetLineWidth(s_Data.LineWidth);
			RendererCommand::DrawLines(s_Data.LineVertexArray, s_Data.LineVertexCount);
			s_Data.Stats.DrawCalls++;
		}
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer2D::DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID)
	{
		if (src.Texture)
			DrawQuad(transform, src.Texture, src.TilingFactor, src.Color, entityID);
		else
			DrawQuad(transform, src.Color, entityID);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		SHUNYA_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, color, -1);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, texture, tilingFactor, tintColor, -1);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID)
	{
		SHUNYA_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		const float texIndex = 0.0f;
		const float tilingFactor = 1.0f;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		for (size_t i = 0; i < 4; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr->EntityID = entityID;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
	{
		SHUNYA_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		for (uint32_t i = 1; i < s_Data.textureSlotindex; i++) {
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.textureSlotindex >= Renderer2DData::MaxTextureSlots)
				NextBatch();

			textureIndex = (float)s_Data.textureSlotindex;
			s_Data.TextureSlots[s_Data.textureSlotindex] = texture;
			s_Data.textureSlotindex++;
		}

		for (size_t i = 0; i < 4; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr->EntityID = entityID;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		DrawRotateQuad({ position.x, position.y, 0.0f }, rotation, size, color);
	}

	void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		SHUNYA_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color, -1);
	}

	void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotateQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		SHUNYA_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor, -1);
	}

	void Renderer2D::DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness /*= 1.0f*/, float fade /*= 0.005f*/, int entityID /*= -1*/)
	{
		SHUNYA_PROFILE_FUNCTION();

		if (s_Data.CircleIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		for (size_t i = 0; i < 4; i++)
		{
			s_Data.CircleVertexBufferPtr->WorldPosition = transform * s_Data.QuadVertexPosition[i];
			s_Data.CircleVertexBufferPtr->LocalPosition = s_Data.QuadVertexPosition[i] * 2.0f;
			s_Data.CircleVertexBufferPtr->Color = color;
			s_Data.CircleVertexBufferPtr->Thickness = thickness;
			s_Data.CircleVertexBufferPtr->Fade = fade;
			s_Data.CircleVertexBufferPtr->EntityID = entityID;
			s_Data.CircleVertexBufferPtr++;
		}

		s_Data.CircleIndexCount += 6;
		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color, int entityID)
	{
		SHUNYA_PROFILE_FUNCTION();

		s_Data.LineVertexBufferPtr->Position = p0;
		s_Data.LineVertexBufferPtr->Color = color;
		s_Data.LineVertexBufferPtr->EntityID = entityID;
		s_Data.LineVertexBufferPtr++;

		s_Data.LineVertexBufferPtr->Position = p1;
		s_Data.LineVertexBufferPtr->Color = color;
		s_Data.LineVertexBufferPtr->EntityID = entityID;
		s_Data.LineVertexBufferPtr++;

		s_Data.LineVertexCount += 2;
	}

	void Renderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID)
	{
		SHUNYA_PROFILE_FUNCTION();

		glm::vec3 p0 = glm::vec3(position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z);
		glm::vec3 p1 = glm::vec3(position.x + size.x * 0.5f, position.y - size.y * 0.5f, position.z);
		glm::vec3 p2 = glm::vec3(position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z);
		glm::vec3 p3 = glm::vec3(position.x - size.x * 0.5f, position.y + size.y * 0.5f, position.z);

		DrawLine(p0, p1, color, entityID);
		DrawLine(p1, p2, color, entityID);
		DrawLine(p2, p3, color, entityID);
		DrawLine(p3, p0, color, entityID);
	}

	void Renderer2D::DrawRect(const glm::mat4& transform, const glm::vec4& color, int entityID)
	{
		SHUNYA_PROFILE_FUNCTION();

		glm::vec3 lineVertices[4];
		for (size_t i = 0; i < 4; i++)
			lineVertices[i] = transform * s_Data.QuadVertexPosition[i];

		DrawLine(lineVertices[0], lineVertices[1], color, entityID);
		DrawLine(lineVertices[1], lineVertices[2], color, entityID);
		DrawLine(lineVertices[2], lineVertices[3], color, entityID);
		DrawLine(lineVertices[3], lineVertices[0], color, entityID);
	}

	float Renderer2D::GetLineWidth()
	{
		return s_Data.LineWidth;
	}

	void Renderer2D::SetLineWidth(float width)
	{
		s_Data.LineWidth = width;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
}