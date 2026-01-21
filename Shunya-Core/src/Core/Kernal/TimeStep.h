#pragma once

namespace Shunya{
	class Timestamp {
	public:
		Timestamp(float time = 0.0f)
			:m_Time(time)
		{

		}

		float GetSeconds() { return m_Time; }
		float GetMilliSec() { return m_Time * 1000.0f; }




	private:
		float m_Time;

	};
}