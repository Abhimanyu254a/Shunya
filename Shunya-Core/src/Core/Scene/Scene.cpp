#include "SNY-PCH.h"
#include "entt.hpp"
#include "Scene.h"
#include "glm/glm.hpp"

namespace Shunya
{
	Scene::Scene()
	{
		struct Meshcomponents {};
		struct TransformComponents
		{
			glm::mat4 Transform;

			TransformComponents() = default;
			TransformComponents(const TransformComponents&) = default;
			TransformComponents(const glm::mat4& transform)
				: Transform(transform) {}
			
			operator glm::mat4&() { return Transform; }
			operator const glm::mat4&()const { return Transform; }

		};
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponents>(entity, glm::mat4(1.0f));

		if (m_Registry.has<TransformComponents>(entity))
		{
			auto& transform = m_Registry.get<TransformComponents>(entity);
		}
		
		auto view = m_Registry.view<TransformComponents>();
		for (auto entity : view)
		{
			auto& transform = view.get<TransformComponents>(entity);
		}

		auto group = m_Registry.group<TransformComponents>(entt::get<Meshcomponents>);
		for (auto entity : group)
		{
			auto& transform = group.get<TransformComponents>(entity);
		}



	}
	Scene::~Scene()
	{

	}

}
