#pragma once

#include "Core/Scene/Entity.h"
#include "Core/Kernal/Timestep.h"

namespace Shunya {

	class ScriptingEntity
	{
	public:
		virtual ~ScriptingEntity() {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestamp ts) {}

	private:
		Entity m_Entity;
		friend class Scene;
	};

}