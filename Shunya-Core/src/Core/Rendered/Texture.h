#pragma once
#include <string>
#include <memory>
#include "Core/Core.h"

namespace Shunya {
	class Texture
	{
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		
	};

	class Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create(uint32_t breadth,uint32_t length);
		static std::shared_ptr<Texture2D> Create(const std::string& path);
	};

}