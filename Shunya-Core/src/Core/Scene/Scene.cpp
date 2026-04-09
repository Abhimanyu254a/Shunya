#include "SNY-PCH.h"
#include "entt.hpp"
#include "Scene.h"
#include "Entity.h"
#include "glm/glm.hpp"
#include "Components.h"
#include "Core/Rendered/Renderer2D.h"

namespace Shunya
{
	class Entity;
	Scene::Scene()
	{
#if 0
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		if (m_Registry.has<TransformComponent>(entity))
		{
			auto& transform = m_Registry.get<TransformComponent>(entity);
		}
		
		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			auto& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
		}


#endif

	}
	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity(m_Registry.create(), this);

		// The absolute bare minimum for an entity to exist in space
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::OnUpdate(Timestamp ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto&& [transform , sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}



}
