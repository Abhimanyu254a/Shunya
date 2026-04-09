#pragma once
#include "Scene.h"
#include "entt.hpp"

namespace Shunya
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->getReg().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->getReg().get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->getReg().any_of<T>(m_EntityHandle);
		}
		
		template<typename T>
		void RemoveComponent()
		{
			m_Scene->getReg().remove<T>(m_EntityHandle);
		}
	private:
		entt::entity m_EntityHandle{ 0 };
		Scene* m_Scene = nullptr;
	};
}