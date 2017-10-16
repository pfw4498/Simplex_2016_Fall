#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));
	
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 20.0f, ZERO_V3, AXIS_Y);

	//if the light position is zero move it
	if (m_pLightMngr->GetPosition(1) == ZERO_V3)
		m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 3.0f));

	//if the background is cornflowerblue change it to black (its easier to see)
	if (vector3(m_v4ClearColor) == C_BLUE_CORNFLOWER)
	{
		m_v4ClearColor = vector4(ZERO_V3, 1.0f);
	}
	
	//if there are no segments create 7
	if(m_uOrbits < 1)
		m_uOrbits = 7;

	float fSize = 1.0f; //initial size of orbits

	//creating a color using the spectrum 
	uint uColor = 650; //650 is Red
	//prevent division by 0
	float decrements = 250.0f / (m_uOrbits > 1? static_cast<float>(m_uOrbits - 1) : 1.0f); //decrement until you get to 400 (which is violet)
	/*
		This part will create the orbits, it start at 3 because that is the minimum subdivisions a torus can have
	*/
	uint uSides = 3; //start with the minimal 3 sides
	for (uint i = uSides; i < m_uOrbits + uSides; i++)
	{
		vector3 v3Color = WaveLengthToRGB(uColor); //calculate color based on wavelength
		m_shapeList.push_back(m_pMeshMngr->GenerateTorus(fSize, fSize - 0.1f, 3, i, v3Color)); //generate a custom torus and add it to the meshmanager

		//A03 CODE HERE
		std::vector<vector3>stops; //add a list of stops to the list of lists of stops
		std::vector<uint>path; //add a list of paths to the list of lists of path positions

		//This for loop calculates each vertex position of each torus, then adds those into the list of lists of stops
		//This loop also add a list of 0-vertices for the current path spot
		for (uint k = 0; k < i; k++) {
			float degreeDivs = 360 / i;
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;

			X = cos(((k + 1)*degreeDivs) * PI / 180) * fSize;
			Y = sin(((k + 1)*degreeDivs) * PI / 180) * fSize;

			stops.push_back(vector3(X,Y,Z));
			static uint num = k;
			path.push_back(k);
		}
		//Add the info to their respective lists
		stopsList.push_back(stops);
		pathsList.push_back(path);

		fSize += 0.5f; //increment the size for the next orbit
		uColor -= static_cast<uint>(decrements); //decrease the wavelength
	}
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	matrix4 m4Offset = IDENTITY_M4; //offset of the orbits, starts as the global coordinate system
	/*
		The following offset will orient the orbits as in the demo, start without it to make your life easier.
	*/
	m4Offset = glm::rotate(IDENTITY_M4, 90.0f, AXIS_Z);

	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	// draw a shapes
	for (uint i = 0; i < m_uOrbits; ++i)
	{
		m_pMeshMngr->AddMeshToRenderList(m_shapeList[i], glm::rotate(m4Offset, 90.0f, AXIS_X));

		//calculate the current position
		vector3 v3CurrentPos = ZERO_V3;
		matrix4 m4Model = glm::translate(m4Offset, v3CurrentPos);

		//This loop keeps track of each sphere around each torus
		//For an added visual effect, I wanted to render spheres at each vertex
		//	and they all travel around their own torus
		for (int k = 0; k < pathsList[i].size(); ++k) {
			vector3 Start;
			vector3 End;
			//Check to see if the next path spot would cause an error with the vector list
			if (pathsList[i][k] < stopsList[i].size() - 1) {
				Start = stopsList[i][pathsList[i][k]];
				End = stopsList[i][pathsList[i][k+1]];
			}
			else {
				Start = stopsList[i][pathsList[i][k]];
				End = stopsList[i][0];
			}

			float fMax = 0.5f;
			float fPercent = static_cast<float>(MapValue(fTimer, 0.0f, fMax, 0.0f, 1.0f));

			v3CurrentPos = glm::lerp(Start, End, fPercent);
			if (fPercent >= 1.0f) {
				//path++;
				fTimer = m_pSystem->GetDeltaTime(uClock);
				//path %= stopsList.size();
			}
			m4Model = glm::translate(m4Offset, v3CurrentPos);
			//draw spheres
			m_pMeshMngr->AddSphereToRenderList(m4Model * glm::scale(vector3(0.1)), C_WHITE);
		}
	}

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
	//release GUI
	ShutdownGUI();
}