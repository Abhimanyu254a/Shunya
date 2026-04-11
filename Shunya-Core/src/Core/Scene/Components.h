#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Core/Rendered/Camera.h"
#include "SceneCamera.h"
#include "ScriptingEntity.h"

namespace Shunya
{

	struct TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {
		}
	};

	struct TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);	
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}
		
		operator glm::mat4&() { return Transform; }
		operator const glm::mat4&()const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
		
		operator glm::vec4&() { return Color; }
		operator const glm::vec4&()const { return Color; }
	};

	struct CameraComponent {
		SceneCamera Camera; // THIS MUST BE SceneCamera, not Camera
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptingEntity* Instance = nullptr;

		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyInstanceFunction;

		std::function<void(ScriptingEntity*)> OnCreateFunction;
		std::function<void(ScriptingEntity*)> OnDestroyFunction;
		std::function<void(ScriptingEntity*, Timestamp)> OnUpdateFunction;

		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { Instance = new T(); };
			DestroyInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };

			OnCreateFunction = [](ScriptingEntity* instance) { ((T*)instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptingEntity* instance) { ((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptingEntity* instance, Timestamp ts) { ((T*)instance)->OnUpdate(ts); };
		}
	};

}