#pragma once

#include <sstream>
#include <string>

#include "Event.h"


namespace Shunya
{

	class SHUNYA_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

			inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }


		std::string ToString() const override
		{
			std::stringstream ss;

			ss << "Mouse Moved Event\n" << "Mouse X Value " << m_MouseX << "\n Mouse Y Value " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		float m_MouseX, m_MouseY;

	};

	class SHUNYA_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			: m_X(x), m_Y(y) {
		}

		inline float Get_X() const { return m_X; }
		inline float Get_Y() const { return m_Y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled Event\n" << "Mouse Scroll up " << m_X << "\n Mouse Scroll down " << m_Y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		float m_X, m_Y;
	};

	class SHUNYA_API MouseButtonEvent : public Event
	{
	public:
		inline int m_MouseButtonEvent() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: m_button(button){}

		int m_button;
	};

	class SHUNYA_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Clicked Event " << m_button;

			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)


	};

	class SHUNYA_API MouseButtonRelasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonRelasedEvent(int button)
			: MouseButtonEvent(button) {}

		
		std::string ToString() const override
		{
			std::stringstream ss;

			ss << "Mouse Key Released Event" << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};




}
