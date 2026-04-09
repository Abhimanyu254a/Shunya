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
		
		
		void OnUpdate(Timestamp ts);
	private:
		entt::registry m_Registry;


	};
}