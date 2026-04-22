#pragma once
#include "entt.hpp"
#include "Core/Kernal/Timestep.h"
#include "Core/Rendered/EditorCamera.h"


namespace Shunya
{
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);


		entt::registry& getReg() { return m_Registry; }
		
		void OnViewportResize(uint32_t width, uint32_t height);
		Entity GetPrimaryCameraEntity();
		void OnUpdateRuntime(Timestamp ts);
		void OnUpdateEditor(Timestamp ts, EditorCamera& camera);

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0; // ✅ add this
		uint32_t m_ViewportHeight = 0; // ✅ add this

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;

	};
}