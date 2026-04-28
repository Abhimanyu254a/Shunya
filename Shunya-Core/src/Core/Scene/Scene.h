#pragma once
#include "entt.hpp"
#include "Core/UUID.h"
#include "Core/Kernal/Timestep.h"
#include "Core/Rendered/EditorCamera.h"

class b2World;
namespace Shunya
{
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();
		static Ref<Scene> Copy(Ref<Scene> other);
		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}

		void OnRuntimeStart();
		void OnRuntimeStop();
		entt::registry& getReg() { return m_Registry; }
		
		void OnViewportResize(uint32_t width, uint32_t height);
		Entity GetPrimaryCameraEntity();
		void OnUpdateRuntime(Timestamp ts);
		void OnUpdateEditor(Timestamp ts, EditorCamera& camera);
		void DuplicateEntity(Entity entity);


	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0; // ✅ add this
		uint32_t m_ViewportHeight = 0; // ✅ add this
		b2World* m_PhysicsWorld = nullptr;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;

	};

	struct CircleRendererComponent;
	template<>
	void Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component);
}