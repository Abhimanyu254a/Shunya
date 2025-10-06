#pragma once

#include "Event.h"

#include <sstream>
#include <string>


namespace Shunya
{
	class SHUNYA_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int breadth, unsigned int length)
			: m_breadth(breadth), m_length(length) {}
		inline unsigned int GetBreadth() const { return m_breadth; }
		inline unsigned int GetLength() const { return m_length; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowsResize " << m_breadth << " " << m_length;
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	protected:
		unsigned int m_breadth;
		unsigned int  m_length;


	};

	class SHUNYA_API WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};


	class SHUNYA_API AppTickEvent : public Event
	{
	public: 
		AppTickEvent() {};

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	class SHUNYA_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {};

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	class SHUNYA_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {};

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};



}