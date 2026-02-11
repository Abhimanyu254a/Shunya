#include "SNY-PCH.h"

#include "OrthographicCameraController.h"

#include "Core/Rendered/OrthographicCamera.h"

#include "input.h"
#include "Core/KeyCode.h"


namespace Shunya {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio ,bool rotation )
		: m_AspectRatio(aspectRatio),m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,m_ZoomLevel), m_Rotation(rotation)
	{

	}


	void OrthographicCameraController::OnUpdate(Timestamp ts)
	{
		if (Input::IsKeyPressed( SHUNYA_KEY_D))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts.GetSeconds();
		else if (Input::IsKeyPressed(SHUNYA_KEY_A))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts.GetSeconds();

		if (Input::IsKeyPressed(SHUNYA_KEY_W))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts.GetSeconds();
		else if (Input::IsKeyPressed(SHUNYA_KEY_S))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts.GetSeconds();

		if(m_Rotation)
		{

			if (Input::IsKeyPressed(SHUNYA_KEY_E)) 
			{
				SHUNYA_CORE_INFO("Rotating! Current: {0}", m_CameraRotation);
				m_CameraRotation += m_CameraRotationSpeed * ts.GetSeconds();
			}
		if (Input::IsKeyPressed(SHUNYA_KEY_Q))
			m_CameraRotation -= m_CameraRotationSpeed * ts.GetSeconds();
			
		m_Camera.SetRotation(m_CameraRotation);

		}
		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;


	}
	void OrthographicCameraController::OnEvent(Event& e) 
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SHUNYA_BIND(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SHUNYA_BIND(OrthographicCameraController::OnWindowResized));

	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.Get_Y() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;

	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) 
	{
		m_AspectRatio = (float)e.GetLength() /(float)e.GetBreadth();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;

	}
}