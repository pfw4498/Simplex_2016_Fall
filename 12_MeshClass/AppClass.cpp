#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Parker Wilson - pfw4498@g.rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Original Cubes
	//Make MyMesh object
	//m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(2.0f, C_BROWN);
	//
	////Make MyMesh object
	//m_pMesh1 = new MyMesh();
	//m_pMesh1->GenerateCube(1.0f, C_WHITE);

#pragma region Wilson_E04Code

	//This very long sequence of code creates a bunch of cubes, and adds them
	// to a vector of MyMesh pointers, which is declared in AppClass.h
	//There are 46 cubes that I need
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh);

	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh1);

	m_pMesh2 = new MyMesh();
	m_pMesh2->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh2);

	m_pMesh3 = new MyMesh();
	m_pMesh3->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh3);

	m_pMesh4 = new MyMesh();
	m_pMesh4->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh4);

	m_pMesh5 = new MyMesh();
	m_pMesh5->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh5);

	m_pMesh6 = new MyMesh();
	m_pMesh6->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh6);

	m_pMesh7 = new MyMesh();
	m_pMesh7->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh7);

	m_pMesh8 = new MyMesh();
	m_pMesh8->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh8);

	m_pMesh9 = new MyMesh();
	m_pMesh9->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh9);

	m_pMesh10 = new MyMesh();
	m_pMesh10->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh10);

	m_pMesh11 = new MyMesh();
	m_pMesh11->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh11);

	m_pMesh12 = new MyMesh();
	m_pMesh12->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh12);

	m_pMesh13 = new MyMesh();
	m_pMesh13->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh13);

	m_pMesh14 = new MyMesh();
	m_pMesh14->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh14);

	m_pMesh15 = new MyMesh();
	m_pMesh15->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh15);

	m_pMesh16 = new MyMesh();
	m_pMesh16->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh16);

	m_pMesh17 = new MyMesh();
	m_pMesh17->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh17);

	m_pMesh18 = new MyMesh();
	m_pMesh18->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh18);

	m_pMesh19 = new MyMesh();
	m_pMesh19->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh19);

	m_pMesh20 = new MyMesh();
	m_pMesh20->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh20);

	m_pMesh21 = new MyMesh();
	m_pMesh21->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh21);

	m_pMesh22 = new MyMesh();
	m_pMesh22->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh22);

	m_pMesh23 = new MyMesh();
	m_pMesh23->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh23);

	m_pMesh24 = new MyMesh();
	m_pMesh24->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh24);

	m_pMesh25 = new MyMesh();
	m_pMesh25->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh25);

	m_pMesh26 = new MyMesh();
	m_pMesh26->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh26);

	m_pMesh27 = new MyMesh();
	m_pMesh27->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh27);

	m_pMesh28 = new MyMesh();
	m_pMesh28->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh28);

	m_pMesh29 = new MyMesh();
	m_pMesh29->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh29);

	m_pMesh30 = new MyMesh();
	m_pMesh30->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh30);

	m_pMesh31 = new MyMesh();
	m_pMesh31->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh31);

	m_pMesh32 = new MyMesh();
	m_pMesh32->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh32);

	m_pMesh33 = new MyMesh();
	m_pMesh33->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh33);

	m_pMesh34 = new MyMesh();
	m_pMesh34->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh34);

	m_pMesh35 = new MyMesh();
	m_pMesh35->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh35);

	m_pMesh36 = new MyMesh();
	m_pMesh36->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh36);

	m_pMesh37 = new MyMesh();
	m_pMesh37->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh37);

	m_pMesh38 = new MyMesh();
	m_pMesh38->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh38);

	m_pMesh39 = new MyMesh();
	m_pMesh39->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh39);

	m_pMesh40 = new MyMesh();
	m_pMesh40->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh40);

	m_pMesh41 = new MyMesh();
	m_pMesh41->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh41);

	m_pMesh42 = new MyMesh();
	m_pMesh42->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh42);

	m_pMesh43 = new MyMesh();
	m_pMesh43->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh43);

	m_pMesh44 = new MyMesh();
	m_pMesh44->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh44);

	m_pMesh45 = new MyMesh();
	m_pMesh45->GenerateCube(2.0f, C_BLUE);
	cubes.push_back(m_pMesh45);

#pragma endregion

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

	//Original Cubes
	//m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall));
	//m_pMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3( 3.0f, 0.0f, 0.0f)));

#pragma region Wilson_E04Code

	static float value = 0.0f;

	//Row at y=0
	cubes[0]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(0.0f + value, 0.0f + sin(value), 0.0f)));
	cubes[1]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + value, 0.0f + sin(value), 0.0f)));
	cubes[2]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(4.0f + value, 0.0f + sin(value), 0.0f)));
	cubes[3]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(6.0f + value, 0.0f + sin(value), 0.0f)));
	cubes[4]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + value, 0.0f + sin(value), 0.0f)));
	cubes[5]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-4.0f + value, 0.0f + sin(value), 0.0f)));
	cubes[6]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-6.0f + value, 0.0f + sin(value), 0.0f)));
	cubes[32]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(10.0f + value, 0.0f + sin(value), 0.0f)));
	cubes[33]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-10.0f + value, 0.0f + sin(value), 0.0f)));

	//Row at y=2
	cubes[7]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(0.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[8]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[9]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(4.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[10]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(6.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[11]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(8.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[12]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(10.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[13]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[14]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-4.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[15]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-6.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[16]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-8.0f + value, 2.0f + sin(value), 0.0f)));
	cubes[17]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-10.0f + value, 2.0f + sin(value), 0.0f)));

	//Row at y=4
	cubes[18]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(0.0f + value, 4.0f + sin(value), 0.0f)));
	cubes[19]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + value, 4.0f + sin(value), 0.0f)));
	cubes[20]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(6.0f + value, 4.0f + sin(value), 0.0f)));
	cubes[21]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(8.0f + value, 4.0f + sin(value), 0.0f)));
	cubes[22]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + value, 4.0f + sin(value), 0.0f)));
	cubes[23]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-6.0f + value, 4.0f + sin(value), 0.0f)));
	cubes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-8.0f + value, 4.0f + sin(value), 0.0f)));

	//Row at y=6
	cubes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(0.0f + value, 6.0f + sin(value), 0.0f)));
	cubes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + value, 6.0f + sin(value), 0.0f)));
	cubes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(4.0f + value, 6.0f + sin(value), 0.0f)));
	cubes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(6.0f + value, 6.0f + sin(value), 0.0f)));
	cubes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + value, 6.0f + sin(value), 0.0f)));
	cubes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-4.0f + value, 6.0f + sin(value), 0.0f)));
	cubes[24]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-6.0f + value, 6.0f + sin(value), 0.0f)));

	//Row at y=-2
	cubes[34]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(6.0f + value, -2.0f + sin(value), 0.0f)));
	cubes[35]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(10.0f + value, -2.0f + sin(value), 0.0f)));
	cubes[36]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-6.0f + value, -2.0f + sin(value), 0.0f)));
	cubes[37]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-10.0f + value, -2.0f + sin(value), 0.0f)));

	//Row at y=-4
	cubes[38]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2.0f + value, -4.0f + sin(value), 0.0f)));
	cubes[39]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(4.0f + value, -4.0f + sin(value), 0.0f)));
	cubes[40]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-2.0f + value, -4.0f + sin(value), 0.0f)));
	cubes[41]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-4.0f + value, -4.0f + sin(value), 0.0f)));

	//Antennae
	cubes[42]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-4.0f + value, 8.0f + sin(value), 0.0f)));
	cubes[43]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(4.0f + value, 8.0f + sin(value), 0.0f)));
	cubes[44]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(6.0f + value, 10.0f + sin(value), 0.0f)));
	cubes[45]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(-6.0f + value, 10.0f + sin(value), 0.0f)));

	//Increase this value to move, y value moves by the sin of value
	value += 0.015f;

#pragma endregion

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
	//if (m_pMesh != nullptr)
	//{
	//	delete m_pMesh;
	//	m_pMesh = nullptr;
	//}
	//SafeDelete(m_pMesh1);
	for (uint i = 0; i < cubes.size(); i++) {
		SafeDelete(cubes[i]);
	}
	//release GUI
	ShutdownGUI();
}