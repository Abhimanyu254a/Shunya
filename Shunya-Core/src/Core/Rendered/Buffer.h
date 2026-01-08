#pragma once

namespace Shunya
{
	enum class ShaderDataType {
		None = 0,Float,Float2,Float3,Float4,Mat3,Mat4, Int,Int2,Int3,Int4,Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case  Shunya::ShaderDataType::Bool:  return 4;
		case  Shunya::ShaderDataType::Float:  return 4;
		case  Shunya::ShaderDataType::Float2:  return 4*2;
		case  Shunya::ShaderDataType::Float3:  return 4*3;
		case  Shunya::ShaderDataType::Float4:  return 4*4;
		case  Shunya::ShaderDataType::Mat3:  return 4*3*3;
		case  Shunya::ShaderDataType::Mat4:  return 4*4*4;
		case  Shunya::ShaderDataType::Int:  return 4;
		case  Shunya::ShaderDataType::Int2:  return 4*2;
		case  Shunya::ShaderDataType::Int3:  return 4*3;
		case  Shunya::ShaderDataType::Int4:  return 4*4;
		case  Shunya::ShaderDataType::None:  return 1;

		}

		SHUNYA_CORE_ASSERT(false, "Unknow ShaderDataType");
		return 0;
	}


	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement() {};

		BufferElement( ShaderDataType Type, const std::string& name,bool normalized = false)
			:Name(name), Type(Type), Size(0), Offset(0),Normalized(normalized)
		{

		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Bool:  return 1;
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4 ;
			case ShaderDataType::Mat3:  return 3 * 3;
			case ShaderDataType::Mat4:  return 4 * 4 ;
			case ShaderDataType::Int:  return 1;
			case ShaderDataType::Int2:  return 2;
			case ShaderDataType::Int3:  return  3;
			case ShaderDataType::Int4:  return 4 ;
			case ShaderDataType::None:  return 1;
			}
		}


	};
	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}
		inline const std::vector<BufferElement>& GetElement() const { return m_Elements; }
		
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const{ return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const{ return m_Elements.end(); }

		inline uint32_t GetStride() const { return m_Stride; }
	private:
		

		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Size = ShaderDataTypeSize(element.Type);
				element.Offset = offset;
				offset += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

	};


	class VertexBuffer {
	public:
		VertexBuffer() {}

		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

	};

	class IndexBuffer {
	public:
		IndexBuffer() {}
		virtual ~IndexBuffer() = default;

		virtual void Bind() const= 0;
		virtual void Unbind() const= 0;

		virtual uint32_t GetCount() const = 0;
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}