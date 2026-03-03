#include "SNY-PCH.h"

#include "OpenGLTexture.h"
#include<string>
#include "stb_image.h"

#include <glad/glad.h>	

namespace Shunya {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		SHUNYA_PROFILE_FUNCTION();

		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(),&width,&height,&channels,0);
		SHUNYA_CORE_ASSERT(data, "Failed to load image");
		m_Width = width;
		m_Height = height;

		GLenum internalFormate = 0, dataFormate = 0;
		if (channels == 4)
		{
			internalFormate = GL_RGBA8;
			dataFormate = GL_RGBA;
		}
		if (channels == 3)
		{
			internalFormate = GL_RGB8;
			dataFormate = GL_RGB;
		}
		m_InternalFormat = internalFormate;
		m_DataFormat = dataFormate;



		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormate, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
		
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormate, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}
	OpenGLTexture2D::OpenGLTexture2D(uint32_t breadth, uint32_t length)
		:m_Width(breadth), m_Height(length)
	{
		SHUNYA_PROFILE_FUNCTION();

		m_InternalFormat= GL_RGB8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);


	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		SHUNYA_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);

	}
	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		SHUNYA_PROFILE_FUNCTION();

		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		SHUNYA_CORE_ASSERT(size == m_Width * m_Height * bpp, "location: OpenglTexture Data must be entire Texture! ");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

	}
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		SHUNYA_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);

	}



}