#pragma once

#include "Core/Rendered/Buffer.h"

namespace Shunya
{
	class OpenglVertexBuffer : public VertexBuffer
	{
	public:
		OpenglVertexBuffer(uint32_t size);
		OpenglVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenglVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		uint32_t m_RendererID = 0;
		BufferLayout m_Layout;
	};

	class OpenglIndexBuffer : public IndexBuffer
	{
	public:
		OpenglIndexBuffer(uint32_t* vertices, uint32_t count);
		virtual ~OpenglIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
		virtual uint32_t GetCount() const { return m_Count; };

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Count = 0;

	};
}