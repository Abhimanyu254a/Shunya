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
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override {  return m_ColorAttachments[index]; }
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

	private:
		uint32_t m_RendererID = 0; // <--- MUST INITIALIZE TO 0
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;

	};

}