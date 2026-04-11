#pragma once

#include "Core/Rendered/FrameBuffer.h"

namespace Shunya {

	class OpenGLFrambuffer : public FrameBuffer
	{
	public:
		OpenGLFrambuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFrambuffer();

		void Invalidate();
		
		virtual void Bind() override;
		virtual void UnBind() override;
		void Resize(uint32_t width, uint32_t height);
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachement; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachement, m_DepthAttachment;
		FramebufferSpecification m_Specification;

	};

}