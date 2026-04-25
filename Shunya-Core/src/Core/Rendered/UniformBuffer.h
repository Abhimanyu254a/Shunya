#pragma once



namespace Shunya {

	class UniformBuffer
	{
	public:
		UniformBuffer() {}
		virtual ~UniformBuffer() {}
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;
		
		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
	};

}