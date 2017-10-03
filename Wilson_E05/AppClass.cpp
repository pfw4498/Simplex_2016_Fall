#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Parker Wilson - pfw4498@g.rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(vector3(5.0f,3.0f,15.0f), ZERO_V3, AXIS_Y);

	m_pModel = new Simplex::Model();
	m_pModel->Load("Sorted\\WallEye.bto");
	
	m_stopsList.push_back(vector3(-4.0f, -2.0f, 5.0f));
	m_stopsList.push_back(vector3(1.0f, -2.0f, 5.0f));

	m_stopsList.push_back(vector3(-3.0f, -1.0f, 3.0f));
	m_stopsList.push_back(vector3(2.0f, -1.0f, 3.0f));

	m_stopsList.push_back(vector3(-2.0f, 0.0f, 0.0f));
	m_stopsList.push_back(vector3(3.0f, 0.0f, 0.0f));

	m_stopsList.push_back(vector3(-1.0f, 1.0f, -3.0f));
	m_stopsList.push_back(vector3(4.0f, 1.0f, -3.0f));

	m_stopsList.push_back(vector3(0.0f, 2.0f, -5.0f));
	m_stopsList.push_back(vector3(5.0f, 2.0f, -5.0f));

	m_stopsList.push_back(vector3(1.0f, 3.0f, -5.0f));
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// Draw the model
	m_pModel->PlaySequence();

	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	//calculate the current position
	vector3 v3CurrentPos;


	

	//your code goes here
	v3CurrentPos = vector3(-4.0f, -2.0f, 5.0f);

	vector3 Start;
	vector3 End;
	static uint path = 0;
	if (path < m_stopsList.size() - 1) {
		Start = m_stopsList[path];
		End = m_stopsList[path + 1];
	}
	else {
		Start = m_stopsList[m_stopsList.size() - 1];
		End = m_stopsList[0];
	}

	float fMax = 1.0f;
	float fPercent = static_cast<float>(MapValue(fTimer, 0.0f, fMax, 0.0f, 1.0f));

	v3CurrentPos = glm::lerp(Start, End, fPercent);
	if (fPercent >= 1.0f) {
		path++;
		fTimer = m_pSystem->GetDeltaTime(uClock);
		path %= m_stopsList.size();
	}

	//NOTES FROM CLASS HERE

	//matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	//matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	//matrix4 m4Model = IDENTITY_M4;
	//float fMax = 2.0f;
	//
	//vector3 v3Stop0 = vector3(0.0f, 0.0f, 0.0f);
	//vector3 v3Stop1 = vector3(5.0f, 0.0f, 0.0f);
	//vector3 v3Stop2 = vector3(0.0f, 3.0f, 0.0f);
	//
	//static DWORD startTime = GetTickCount();
	//DWORD currentTime = GetTickCount();
	//float fCurrentTime = (currentTime - startTime) / 1000.0f;
	//
	//float fPercent = MapValue(fCurrentTime, 0.0f, fMax, 0.0f, 1.0f);
	//
	//vector3 v3Current = glm::lerp(v3Stop0, v3Stop1, fPercent);
	//m4Model = glm::translate(IDENTITY_M4, v3Current);
	//
	//if (fCurrentTime > fMax) {
	//	startTime = GetTickCount();
	//}

	//-------------------
	


	
	matrix4 m4Model = glm::translate(v3CurrentPos);
	m_pModel->SetModelMatrix(m4Model);

	m_pMeshMngr->Print("\nTimer: ");//Add a line on top
	m_pMeshMngr->PrintLine(std::to_string(fTimer), C_YELLOW);

	// Draw stops
	for (uint i = 0; i < m_stopsList.size(); ++i)
	{
		m_pMeshMngr->AddSphereToRenderList(glm::translate(m_stopsList[i]) * glm::scale(vector3(0.05f)), C_GREEN, RENDER_WIRE);
	}
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pModel);
	//release GUI
	ShutdownGUI();
}