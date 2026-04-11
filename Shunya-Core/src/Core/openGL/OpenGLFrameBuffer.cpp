#include "SNY-PCH.h"
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Shunya {

	OpenGLFrambuffer::OpenGLFrambuffer(const FramebufferSpecification& spec)
		:m_Specification(spec)
	{
		Invalidate();
	}
	OpenGLFrambuffer::~OpenGLFrambuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}
    void OpenGLFrambuffer::Invalidate()
    {
        glCreateFramebuffers(1, &m_RendererID);

        // ✅ Color attachment — pure DSA
        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachement);
        glTextureStorage2D(m_ColorAttachement, 1, GL_RGBA8,
            m_Specification.Width, m_Specification.Height);
        glTextureParameteri(m_ColorAttachement, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_ColorAttachement, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0,
            m_ColorAttachement, 0);

        // ✅ Depth attachment — pure DSA
        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
        glTextureStorage2D(m_DepthAttachment, 1, GL_DEPTH24_STENCIL8,
            m_Specification.Width, m_Specification.Height);
        glNamedFramebufferTexture(m_RendererID, GL_DEPTH_STENCIL_ATTACHMENT,
            m_DepthAttachment, 0);

        // ✅ Verify completeness
        SHUNYA_CORE_ASSERT(
            glCheckNamedFramebufferStatus(m_RendererID, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
            "Framebuffer is incomplete!"
        );
    }
	void OpenGLFrambuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}
	void OpenGLFrambuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); 

	}
    void OpenGLFrambuffer::Resize(uint32_t width, uint32_t height)
    {
        m_Specification.Width = width;
        m_Specification.Height = height;

        // Delete old textures
        glDeleteTextures(1, &m_ColorAttachement);
        glDeleteTextures(1, &m_DepthAttachment);
        glDeleteFramebuffers(1, &m_RendererID);

        Invalidate(); // recreate with new size
    }


}