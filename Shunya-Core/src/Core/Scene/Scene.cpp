////#include "SNY-PCH.h"
////#include "entt.hpp"
////#include "Scene.h"
////#include "Entity.h"
////#include "glm/glm.hpp"
////#include "Components.h"
////#include "Core/Rendered/Renderer2D.h"
////#include "Core/Rendered/Camera.h"
////
////namespace Shunya
////{
////	class Entity;
////	Scene::Scene()
////	{
////#if 0
////		entt::entity entity = m_Registry.create();
////		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
////
////		if (m_Registry.has<TransformComponent>(entity))
////		{
////			auto& transform = m_Registry.get<TransformComponent>(entity);
////		}
////		
////		auto view = m_Registry.view<TransformComponent>();
////		for (auto entity : view)
////		{
////			auto& transform = view.get<TransformComponent>(entity);
////		}
////
////		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
////		for (auto entity : group)
////		{
////			auto& transform = group.get<TransformComponent>(entity);
////		}
////
////
////#endif
////
////	}
////	Scene::~Scene()
////	{
////
////	}
////
////	// Scene.cpp
////	void Scene::OnViewportResize(uint32_t width, uint32_t height)
////	{
////		m_ViewportWidth = width;
////		m_ViewportHeight = height;
////
////		auto view = m_Registry.view<CameraComponent>();
////		for (auto entity : view)
////		{
////			auto& cameraComp = view.get<CameraComponent>(entity);
////			cameraComp.Camera.SetViewportSize(width, height);
////		}
////	
////
////
////	Entity Scene::CreateEntity(const std::string& name)
////	{
////		Entity entity(m_Registry.create(), this);
////
////		// The absolute bare minimum for an entity to exist in space
////		entity.AddComponent<TransformComponent>();
////		auto& tag = entity.AddComponent<TagComponent>();
////		tag.Tag = name.empty() ? "Entity" : name;
////
////		return entity;
////	}
////
////	//void Scene::OnUpdate(Timestamp ts)
////	//{
////	//	Camera* MainCamera = nullptr;
////	//	glm::mat4* cameraTrasform = nullptr;
////	//	{
////	//		auto group = m_Registry.view<TransformComponent, CameraComponent>();
////	//		for (auto entity : group)
////	//		{
////
////	//			auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);
////	//			if (camera.Primary)
////	//			{
////	//				MainCamera = &camera.Camera;
////	//				cameraTrasform = &transform.Transform;
////	//				break;
////
////	//			}
////	//		}
////	//	}
////
////	//		if (MainCamera)
////	//		{
////	//			Renderer2D::BeginScene(MainCamera->GetProjection(), *cameraTrasform);
////
////	//			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
////	//			for (auto entity : group)
////	//			{
////	//				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
////	//				Renderer2D::DrawQuad(transform, sprite.Color);
////	//			}
////	//		Renderer2D::EndScene();
////	//		}
////	//	
////	//}
////
////
////	void Scene::OnUpdate(Timestamp ts)
////	{
////		Camera* mainCamera = nullptr;
////		glm::mat4* cameraTransform = nullptr;
////	{
////		auto view = m_Registry.view<TransformComponent, CameraComponent>();
////		for (auto entity : view)
////		{
////			auto&& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
////			if (camera.Primary)
////			{
////				mainCamera = &camera.Camera;
////				cameraTransform = &transform.Transform;
////				break;
////			}
////		}
////	}
////
////		if (mainCamera)
////		{
////			Renderer2D::BeginScene(*mainCamera, *cameraTransform);
////
////			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
////			for (auto entity : group)
////			{
////				auto&& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
////				Renderer2D::DrawQuad(transform, sprite.Color);
////			}
////
////			Renderer2D::EndScene();
////		}
////	}
////
////}
////
////
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//#include "SNY-PCH.h"
//#include "Scene.h"
//#include "Entity.h"
//#include "Components.h"
//#include "Core/ScriptableEntity.h"
//#include "Core/Rendered/Renderer2D.h"
//#include "Core/Rendered/Camera.h"
//#include "box2d/b2_world.h"
//#include "box2d/b2_body.h"
//#include "box2d/b2_fixture.h"
//#include "box2d/b2_polygon_shape.h"
//
//namespace Shunya {
//
//	static b2BodyType Rigidbody2DTypeToBox2DBody(Rigidbody2DComponent::BodyType bodyType)
//	{
//		switch (bodyType)
//		{
//		case Rigidbody2DComponent::BodyType::Static:    return b2_staticBody;
//		case Rigidbody2DComponent::BodyType::Dynamic:   return b2_dynamicBody;
//		case Rigidbody2DComponent::BodyType::Kinematic: return b2_kinematicBody;
//		}
//
//		SHUNYA_CORE_ASSERT(false, "Unknown body type");
//		return b2_staticBody;
//	}
//
//	Scene::Scene() {}
//	Scene::~Scene() {}
//
//	template<typename Component>
//	static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
//	{
//		auto view = src.view<Component>();
//		for (auto e : view)
//		{
//			UUID uuid = src.get<IDComponent>(e).ID;
//			entt::entity dstEnttID = enttMap.at(uuid);
//
//			auto& component = src.get<Component>(e);
//			dst.emplace_or_replace<Component>(dstEnttID, component);
//		}
//	}
//
//	template<typename Component>
//	static void CopyComponentIfExists(Entity dst, Entity src)
//	{
//		if (src.HasComponent<Component>())
//			dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
//	}
//
//	Ref<Scene> Scene::Copy(Ref<Scene> other)
//	{
//		Ref<Scene> newScene = CreateRef<Scene>();
//
//		newScene->m_ViewportWidth = other->m_ViewportWidth;
//		newScene->m_ViewportHeight = other->m_ViewportHeight;
//
//		auto& srcSceneRegistry = other->m_Registry;
//		auto& dstSceneRegistry = newScene->m_Registry;
//		std::unordered_map<UUID, entt::entity> enttMap;
//
//		// Create entities in new scene
//		auto idView = srcSceneRegistry.view<IDComponent>();
//		for (auto e : idView)
//		{
//			UUID uuid = srcSceneRegistry.get<IDComponent>(e).ID;
//			const auto& name = srcSceneRegistry.get<TagComponent>(e).Tag;
//			Entity newEntity = newScene->CreateEntityWithUUID(uuid, name);
//			enttMap[uuid] = (entt::entity)newEntity;
//		}
//
//		// Copy components (except IDComponent and TagComponent)
//		CopyComponent<TransformComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
//		CopyComponent<SpriteRendererComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
//		CopyComponent<CircleRendererComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
//		CopyComponent<CameraComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
//		CopyComponent<NativeScriptComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
//		CopyComponent<Rigidbody2DComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
//		CopyComponent<BoxCollider2DComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
//
//		return newScene;
//	}
//
//	void Scene::OnViewportResize(uint32_t width, uint32_t height)
//	{
//		m_ViewportWidth = width;
//		m_ViewportHeight = height;
//
//		auto view = m_Registry.view<CameraComponent>();
//		for (auto entity : view)
//		{
//			auto& cameraComp = view.get<CameraComponent>(entity);
//			if (!cameraComp.FixedAspectRatio)
//				cameraComp.Camera.SetViewportSize(width, height);
//		}
//	} 
//
//	Entity Scene::CreateEntity(const std::string& name)
//
//	{
//		return CreateEntityWithUUID(UUID(), name);
//	}
//
//	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
//	{
//		SHUNYA_PROFILE_FUNCTION();
//		Entity entity(m_Registry.create(), this);
//		entity.AddComponent<IDComponent>().ID = uuid;
//		entity.AddComponent<TransformComponent>();
//		auto& tag = entity.AddComponent<TagComponent>();
//		tag.Tag = name.empty() ? "Entity" : name;
//		return entity;
//	}
//
//	void Scene::DestroyEntity(Entity entity)
//	{
//		m_Registry.destroy(entity);
//	}
//	void Scene::OnUpdateEditor(Timestamp ts, EditorCamera& camera)
//	{
//		Renderer2D::BeginScene(camera);
//
//		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
//		for (auto entity : group)
//		{
//			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
//			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
//		}
//		{
//			auto view = m_Registry.view<TransformComponent, CircleRendererComponent>();
//			for (auto entity : view)
//			{
//				auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
//
//				Renderer2D::DrawCircle(transform.GetTransform(), circle.Color, circle.Thickness, circle.Fade, (int)entity);
//			}
//		}
//
//		Renderer2D::EndScene();
//	}
//
//	void Scene::OnUpdateRuntime(Timestamp ts)
//	{
//		SHUNYA_PROFILE_FUNCTION("Scene::Onupdate");
//		{
//			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
//				{
//					if (!nsc.Instance)
//					{
//						nsc.Instance = nsc.InstantiateScript();
//						nsc.Instance->m_Entity = Entity{ entity, this };
//
//						nsc.Instance->OnCreate();
//					}
//
//					nsc.Instance->OnUpdate(ts);
//				});
//		}
//		// Physics
//		{
//			const int32_t velocityIterations = 6;
//			const int32_t positionIterations = 2;
//			m_PhysicsWorld->Step(ts.GetSeconds(), velocityIterations, positionIterations);
//
//			// Retrieve transform from Box2D
//			auto view = m_Registry.view<Rigidbody2DComponent>();
//			for (auto e : view)
//			{
//				Entity entity = { e, this };
//				auto& transform = entity.GetComponent<TransformComponent>();
//				auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
//
//				b2Body* body = (b2Body*)rb2d.RuntimeBody;
//				const auto& position = body->GetPosition();
//				transform.Translation.x = position.x;
//				transform.Translation.y = position.y;
//				transform.Rotation.z = body->GetAngle();
//			}
//		}
//
//
//		Camera* mainCamera = nullptr;
//		glm::mat4 cameraTransform;
//
//		auto view = m_Registry.view<TransformComponent, CameraComponent>();
//		for (auto entity : view)
//		{
//			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
//			if (camera.Primary)
//			{
//				mainCamera = &camera.Camera;
//				cameraTransform = transform.GetTransform();
//				break;
//			}
//		}
//
//		if (mainCamera)
//		{
//			Renderer2D::BeginScene(*mainCamera, cameraTransform);
//
//			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
//			for (auto entity : group)
//			{
//				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
//				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
//			}
//
//			Renderer2D::EndScene();
//		}
//	}
//
//	void Scene::OnRuntimeStart()
//	{
//		m_PhysicsWorld = new b2World({ 0.0f, -9.8f });
//
//		auto view = m_Registry.view<Rigidbody2DComponent>();
//		for (auto e : view)
//		{
//			Entity entity = { e, this };
//			auto& transform = entity.GetComponent<TransformComponent>();
//			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
//
//			b2BodyDef bodyDef;
//			bodyDef.type = Rigidbody2DTypeToBox2DBody(rb2d.Type);
//			bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
//			bodyDef.angle = transform.Rotation.z;
//
//			b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
//			body->SetFixedRotation(rb2d.FixedRotation);
//			rb2d.RuntimeBody = body;
//
//			if (entity.HasComponent<BoxCollider2DComponent>())
//			{
//				auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();
//
//				b2PolygonShape boxShape;
//				boxShape.SetAsBox(bc2d.Size.x * transform.Scale.x, bc2d.Size.y * transform.Scale.y);
//
//				b2FixtureDef fixtureDef;
//				fixtureDef.shape = &boxShape;
//				fixtureDef.density = bc2d.Density;
//				fixtureDef.friction = bc2d.Friction;
//				fixtureDef.restitution = bc2d.Restitution;
//				fixtureDef.restitutionThreshold = bc2d.RestitutionThreshold;
//				body->CreateFixture(&fixtureDef);
//			}
//		}
//	}
//
//	void Scene::OnRuntimeStop()
//	{
//		delete m_PhysicsWorld;
//		m_PhysicsWorld = nullptr;
//	}
//
//
//	void Scene::DuplicateEntity(Entity entity)
//	{
//		std::string name = entity.GetName();
//		Entity newEntity = CreateEntity(name);
//
//		CopyComponentIfExists<TransformComponent>(newEntity, entity);
//		CopyComponentIfExists<SpriteRendererComponent>(newEntity, entity);
//		CopyComponentIfExists<CameraComponent>(newEntity, entity);
//		CopyComponentIfExists<NativeScriptComponent>(newEntity, entity);
//		CopyComponentIfExists<Rigidbody2DComponent>(newEntity, entity);
//		CopyComponentIfExists<BoxCollider2DComponent>(newEntity, entity);
//	}
//
//	Entity Scene::GetPrimaryCameraEntity()
//	{
//		auto view = m_Registry.view<CameraComponent>();
//		for (auto entity : view)
//		{
//			const auto& camera = view.get<CameraComponent>(entity);
//			if (camera.Primary)
//				return Entity{ entity, this };
//		}
//		return {};
//	}
//
//	template<typename T>
//	void Scene::OnComponentAdded(Entity entity, T& component)
//	{
//		static_assert(false);
//	}
//
//	template<>
//	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
//	{
//	}
//
//	template<>
//	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
//	{
//		// component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
//	if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
//			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
//	}
//
//	template<>
//	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
//	{
//	}
//
//	template<>
//	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
//	{
//	}
//	template<>
//	void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
//	{
//	}
//
//	template<>
//	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
//	{
//	}
//
//	template<>
//	void Scene::OnComponentAdded<Rigidbody2DComponent>(Entity entity, Rigidbody2DComponent& component)
//	{
//	}
//
//	template<>
//	void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
//	{
//	}
//}









#include "SNY-PCH.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Core/ScriptableEntity.h" // Ensure this matches your fixed script header name
#include "Core/Rendered/Renderer2D.h"
#include "Core/Rendered/Camera.h"
#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

namespace Shunya {

	static b2BodyType Rigidbody2DTypeToBox2DBody(Rigidbody2DComponent::BodyType bodyType)
	{
		switch (bodyType)
		{
		case Rigidbody2DComponent::BodyType::Static:    return b2_staticBody;
		case Rigidbody2DComponent::BodyType::Dynamic:   return b2_dynamicBody;
		case Rigidbody2DComponent::BodyType::Kinematic: return b2_kinematicBody;
		}

		SHUNYA_CORE_ASSERT(false, "Unknown body type");
		return b2_staticBody;
	}

	Scene::Scene() {}
	Scene::~Scene() {}

	template<typename Component>
	static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		auto view = src.view<Component>();
		for (auto e : view)
		{
			UUID uuid = src.get<IDComponent>(e).ID;
			entt::entity dstEnttID = enttMap.at(uuid);

			auto& component = src.get<Component>(e);
			dst.emplace_or_replace<Component>(dstEnttID, component);
		}
	}

	template<typename Component>
	static void CopyComponentIfExists(Entity dst, Entity src)
	{
		if (src.HasComponent<Component>())
			dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
	}

	Ref<Scene> Scene::Copy(Ref<Scene> other)
	{
		Ref<Scene> newScene = CreateRef<Scene>();

		newScene->m_ViewportWidth = other->m_ViewportWidth;
		newScene->m_ViewportHeight = other->m_ViewportHeight;

		auto& srcSceneRegistry = other->m_Registry;
		auto& dstSceneRegistry = newScene->m_Registry;
		std::unordered_map<UUID, entt::entity> enttMap;

		// Create entities in new scene
		auto idView = srcSceneRegistry.view<IDComponent>();
		for (auto e : idView)
		{
			UUID uuid = srcSceneRegistry.get<IDComponent>(e).ID;
			const auto& name = srcSceneRegistry.get<TagComponent>(e).Tag;
			Entity newEntity = newScene->CreateEntityWithUUID(uuid, name);
			enttMap[uuid] = (entt::entity)newEntity;
		}

		// Copy components (except IDComponent and TagComponent)
		CopyComponent<TransformComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
		CopyComponent<SpriteRendererComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
		CopyComponent<CircleRendererComponent>(dstSceneRegistry, srcSceneRegistry, enttMap); // ✅ Added Circle
		CopyComponent<CameraComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
		CopyComponent<NativeScriptComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
		CopyComponent<Rigidbody2DComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);
		CopyComponent<BoxCollider2DComponent>(dstSceneRegistry, srcSceneRegistry, enttMap);

		return newScene;
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComp = view.get<CameraComponent>(entity);
			if (!cameraComp.FixedAspectRatio)
				cameraComp.Camera.SetViewportSize(width, height);
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
	{
		SHUNYA_PROFILE_FUNCTION();
		Entity entity(m_Registry.create(), this);
		entity.AddComponent<IDComponent>().ID = uuid;
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdateEditor(Timestamp ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		// Draw Sprites
		{
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}
		}

		// Draw Circles ✅ Added missing editor circle rendering
		{
			auto view = m_Registry.view<TransformComponent, CircleRendererComponent>();
			for (auto entity : view)
			{
				auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
				Renderer2D::DrawCircle(transform.GetTransform(), circle.Color, circle.Thickness, circle.Fade, (int)entity);
			}
		}

		Renderer2D::EndScene();
	}

	void Scene::OnUpdateRuntime(Timestamp ts)
	{
		SHUNYA_PROFILE_FUNCTION("Scene::OnUpdateRuntime");

		// Scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();
					}
					nsc.Instance->OnUpdate(ts);
				});
		}

		// Physics
		{
			const int32_t velocityIterations = 6;
			const int32_t positionIterations = 2;
			m_PhysicsWorld->Step(ts.GetSeconds(), velocityIterations, positionIterations);

			auto view = m_Registry.view<Rigidbody2DComponent>();
			for (auto e : view)
			{
				Entity entity = { e, this };
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

				b2Body* body = (b2Body*)rb2d.RuntimeBody;
				const auto& position = body->GetPosition();
				transform.Translation.x = position.x;
				transform.Translation.y = position.y;
				transform.Rotation.z = body->GetAngle();
			}
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;

		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (camera.Primary)
			{
				mainCamera = &camera.Camera;
				cameraTransform = transform.GetTransform();
				break;
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			// Draw Sprites
			{
				auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
				for (auto entity : group)
				{
					auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
					Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
				}
			}

			// Draw Circles ✅ Added missing runtime circle rendering
			{
				auto circleView = m_Registry.view<TransformComponent, CircleRendererComponent>();
				for (auto entity : circleView)
				{
					auto [transform, circle] = circleView.get<TransformComponent, CircleRendererComponent>(entity);
					Renderer2D::DrawCircle(transform.GetTransform(), circle.Color, circle.Thickness, circle.Fade, (int)entity);
				}
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnRuntimeStart()
	{
		m_PhysicsWorld = new b2World({ 0.0f, -9.8f });

		auto view = m_Registry.view<Rigidbody2DComponent>();
		for (auto e : view)
		{
			Entity entity = { e, this };
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

			b2BodyDef bodyDef;
			bodyDef.type = Rigidbody2DTypeToBox2DBody(rb2d.Type);
			bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
			bodyDef.angle = transform.Rotation.z;

			b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
			body->SetFixedRotation(rb2d.FixedRotation);
			rb2d.RuntimeBody = body;

			if (entity.HasComponent<BoxCollider2DComponent>())
			{
				auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();

				b2PolygonShape boxShape;
				boxShape.SetAsBox(bc2d.Size.x * transform.Scale.x, bc2d.Size.y * transform.Scale.y);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &boxShape;
				fixtureDef.density = bc2d.Density;
				fixtureDef.friction = bc2d.Friction;
				fixtureDef.restitution = bc2d.Restitution;
				fixtureDef.restitutionThreshold = bc2d.RestitutionThreshold;
				body->CreateFixture(&fixtureDef);
			}
		}
	}

	void Scene::OnRuntimeStop()
	{
		delete m_PhysicsWorld;
		m_PhysicsWorld = nullptr;
	}

	void Scene::DuplicateEntity(Entity entity)
	{
		std::string name = entity.GetName();
		Entity newEntity = CreateEntity(name);

		CopyComponentIfExists<TransformComponent>(newEntity, entity);
		CopyComponentIfExists<SpriteRendererComponent>(newEntity, entity);
		CopyComponentIfExists<CircleRendererComponent>(newEntity, entity); // ✅ Added Circle
		CopyComponentIfExists<CameraComponent>(newEntity, entity);
		CopyComponentIfExists<NativeScriptComponent>(newEntity, entity);
		CopyComponentIfExists<Rigidbody2DComponent>(newEntity, entity);
		CopyComponentIfExists<BoxCollider2DComponent>(newEntity, entity);
	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{ entity, this };
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		// static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) {}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component) {}

	template<>
	void Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component) {} // ✅ Added Circle

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component) {}

	template<>
	void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component) {}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component) {}

	template<>
	void Scene::OnComponentAdded<Rigidbody2DComponent>(Entity entity, Rigidbody2DComponent& component) {}

	template<>
	void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component) {}
	

}