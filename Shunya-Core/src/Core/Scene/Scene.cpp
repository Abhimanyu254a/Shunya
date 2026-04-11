//#include "SNY-PCH.h"
//#include "entt.hpp"
//#include "Scene.h"
//#include "Entity.h"
//#include "glm/glm.hpp"
//#include "Components.h"
//#include "Core/Rendered/Renderer2D.h"
//#include "Core/Rendered/Camera.h"
//
//namespace Shunya
//{
//	class Entity;
//	Scene::Scene()
//	{
//#if 0
//		entt::entity entity = m_Registry.create();
//		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
//
//		if (m_Registry.has<TransformComponent>(entity))
//		{
//			auto& transform = m_Registry.get<TransformComponent>(entity);
//		}
//		
//		auto view = m_Registry.view<TransformComponent>();
//		for (auto entity : view)
//		{
//			auto& transform = view.get<TransformComponent>(entity);
//		}
//
//		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
//		for (auto entity : group)
//		{
//			auto& transform = group.get<TransformComponent>(entity);
//		}
//
//
//#endif
//
//	}
//	Scene::~Scene()
//	{
//
//	}
//
//	// Scene.cpp
//	void Scene::OnViewportResize(uint32_t width, uint32_t height)
//	{
//		m_ViewportWidth = width;
//		m_ViewportHeight = height;
//
//		auto view = m_Registry.view<CameraComponent>();
//		for (auto entity : view)
//		{
//			auto& cameraComp = view.get<CameraComponent>(entity);
//			cameraComp.Camera.SetViewportSize(width, height);
//		}
//	
//
//
//	Entity Scene::CreateEntity(const std::string& name)
//	{
//		Entity entity(m_Registry.create(), this);
//
//		// The absolute bare minimum for an entity to exist in space
//		entity.AddComponent<TransformComponent>();
//		auto& tag = entity.AddComponent<TagComponent>();
//		tag.Tag = name.empty() ? "Entity" : name;
//
//		return entity;
//	}
//
//	//void Scene::OnUpdate(Timestamp ts)
//	//{
//	//	Camera* MainCamera = nullptr;
//	//	glm::mat4* cameraTrasform = nullptr;
//	//	{
//	//		auto group = m_Registry.view<TransformComponent, CameraComponent>();
//	//		for (auto entity : group)
//	//		{
//
//	//			auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);
//	//			if (camera.Primary)
//	//			{
//	//				MainCamera = &camera.Camera;
//	//				cameraTrasform = &transform.Transform;
//	//				break;
//
//	//			}
//	//		}
//	//	}
//
//	//		if (MainCamera)
//	//		{
//	//			Renderer2D::BeginScene(MainCamera->GetProjection(), *cameraTrasform);
//
//	//			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
//	//			for (auto entity : group)
//	//			{
//	//				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
//	//				Renderer2D::DrawQuad(transform, sprite.Color);
//	//			}
//	//		Renderer2D::EndScene();
//	//		}
//	//	
//	//}
//
//
//	void Scene::OnUpdate(Timestamp ts)
//	{
//		Camera* mainCamera = nullptr;
//		glm::mat4* cameraTransform = nullptr;
//	{
//		auto view = m_Registry.view<TransformComponent, CameraComponent>();
//		for (auto entity : view)
//		{
//			auto&& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
//			if (camera.Primary)
//			{
//				mainCamera = &camera.Camera;
//				cameraTransform = &transform.Transform;
//				break;
//			}
//		}
//	}
//
//		if (mainCamera)
//		{
//			Renderer2D::BeginScene(*mainCamera, *cameraTransform);
//
//			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
//			for (auto entity : group)
//			{
//				auto&& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
//				Renderer2D::DrawQuad(transform, sprite.Color);
//			}
//
//			Renderer2D::EndScene();
//		}
//	}
//
//}
//
//














#include "SNY-PCH.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Core/Rendered/Renderer2D.h"
#include "Core/Rendered/Camera.h"

namespace Shunya {

	Scene::Scene() {}
	Scene::~Scene() {}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComp = view.get<CameraComponent>(entity);
			cameraComp.Camera.SetViewportSize(width, height);
		}
	} // <-- THE MISSING BRACKET IS RESTORED HERE

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity(m_Registry.create(), this);
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestamp ts)
	{
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;

		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (camera.Primary)
			{
				mainCamera = &camera.Camera;
				cameraTransform = &transform.Transform;
				break;
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}
}