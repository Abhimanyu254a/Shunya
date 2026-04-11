#pragma once
#include "entt.hpp"
#include "Core/Kernal/Timestep.h"


namespace Shunya
{
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());


		entt::registry& getReg() { return m_Registry; }
		
		void OnViewportResize(uint32_t width, uint32_t height);
		void OnUpdate(Timestamp ts);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0; // ✅ add this
		uint32_t m_ViewportHeight = 0; // ✅ add this

		friend class Entity;
		friend class SceneHierarchyPanel;

	};
}