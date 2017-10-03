#include "MyMesh.h"
#include <list>

void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue,-fValue, fValue); //0
	vector3 point1( fValue,-fValue, fValue); //1
	vector3 point2( fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue,-fValue,-fValue); //4
	vector3 point5( fValue,-fValue,-fValue); //5
	vector3 point6( fValue, fValue,-fValue); //6
	vector3 point7(-fValue, fValue,-fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);

	float halfHeight = a_fHeight / 2;
	float degreeDivs = 360 / a_nSubdivisions;
	std::vector<vector3> basePoints;

	vector3 tip(0, halfHeight, 0);
	vector3 baseCenter(0, -halfHeight, 0);

	for (int c = 0; c < a_nSubdivisions; c++) {
		basePoints.push_back(vector3(cos(((c+1)*degreeDivs) * PI/180) * a_fRadius, -halfHeight,
			sin(((c + 1)*degreeDivs) * PI / 180) * a_fRadius));
	}

	//Add triangles
	//BASE
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == basePoints.size() - 1) {
			AddTri(basePoints[k], basePoints[0], baseCenter);
		}
		else {
			AddTri(basePoints[k], basePoints[k+1], baseCenter);
		}
	}

	//SIDES
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == basePoints.size() - 1) {
			AddTri(tip, basePoints[0], basePoints[k]);
		}
		else {
			AddTri(tip, basePoints[k+1], basePoints[k]);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);

	float halfHeight = a_fHeight / 2;
	float degreeDivs = 360 / a_nSubdivisions;
	std::vector<vector3> botBasePoints;
	std::vector<vector3> topBasePoints;

	vector3 topCenter(0, halfHeight, 0);
	vector3 baseCenter(0, -halfHeight, 0);

	for (int c = 0; c < a_nSubdivisions; c++) {
		botBasePoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * a_fRadius, -halfHeight,
			sin(((c + 1)*degreeDivs) * PI / 180) * a_fRadius));
	}

	for (int c = 0; c < a_nSubdivisions; c++) {
		topBasePoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * a_fRadius, halfHeight,
			sin(((c + 1)*degreeDivs) * PI / 180) * a_fRadius));
	}

	//Add Quads and Tris
	//TOP BASE
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == topBasePoints.size() - 1) {
			AddTri(topCenter, topBasePoints[0], topBasePoints[k]);
		}
		else {
			AddTri(topCenter, topBasePoints[k + 1], topBasePoints[k]);
		}
	}

	//BOTTOM BASE
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == botBasePoints.size() - 1) {
			AddTri(botBasePoints[k], botBasePoints[0], baseCenter);
		}
		else {
			AddTri(botBasePoints[k], botBasePoints[k + 1], baseCenter);
		}
	}

	//SIDES
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == botBasePoints.size() - 1) {
			AddQuad(topBasePoints[k], topBasePoints[0], botBasePoints[k], botBasePoints[0]);
		}
		else {
			AddQuad(topBasePoints[k], topBasePoints[k+1], botBasePoints[k], botBasePoints[k+1]);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);

	float halfHeight = a_fHeight / 2;
	float degreeDivs = 360 / a_nSubdivisions;
	std::vector<vector3> botOutBasePoints;
	std::vector<vector3> topOutBasePoints;
	std::vector<vector3> botInBasePoints;
	std::vector<vector3> topInBasePoints;

	vector3 topCenter(0, halfHeight, 0);
	vector3 baseCenter(0, -halfHeight, 0);

	for (int c = 0; c < a_nSubdivisions; c++) {
		botOutBasePoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * a_fOuterRadius, -halfHeight,
			sin(((c + 1)*degreeDivs) * PI / 180) * a_fOuterRadius));
	}

	for (int c = 0; c < a_nSubdivisions; c++) {
		topOutBasePoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * a_fOuterRadius, halfHeight,
			sin(((c + 1)*degreeDivs) * PI / 180) * a_fOuterRadius));
	}

	for (int c = 0; c < a_nSubdivisions; c++) {
		botInBasePoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * a_fInnerRadius, -halfHeight,
			sin(((c + 1)*degreeDivs) * PI / 180) * a_fInnerRadius));
	}

	for (int c = 0; c < a_nSubdivisions; c++) {
		topInBasePoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * a_fInnerRadius, halfHeight,
			sin(((c + 1)*degreeDivs) * PI / 180) * a_fInnerRadius));
	}

	//Add Quads
	//OUTER SIDES
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == botOutBasePoints.size() - 1) {
			AddQuad(topOutBasePoints[k], topOutBasePoints[0], botOutBasePoints[k], botOutBasePoints[0]);
		}
		else {
			AddQuad(topOutBasePoints[k], topOutBasePoints[k + 1], botOutBasePoints[k], botOutBasePoints[k + 1]);
		}
	}

	//INNER SIDES
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == botInBasePoints.size() - 1) {
			AddQuad(botInBasePoints[k], botInBasePoints[0], topInBasePoints[k], topInBasePoints[0]);
		}
		else {
			AddQuad(botInBasePoints[k], botInBasePoints[k + 1], topInBasePoints[k], topInBasePoints[k + 1]);
		}
	}

	//TOP FACES
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == botInBasePoints.size() - 1) {
			AddQuad(topInBasePoints[k], topInBasePoints[0], topOutBasePoints[k], topOutBasePoints[0]);
		}
		else {
			AddQuad(topInBasePoints[k], topInBasePoints[k+1], topOutBasePoints[k], topOutBasePoints[k+1]);
		}
	}

	//BOTTOM FACES
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == botInBasePoints.size() - 1) {
			AddQuad(botOutBasePoints[k], botOutBasePoints[0], botInBasePoints[k], botInBasePoints[0]);
		}
		else {
			AddQuad(botOutBasePoints[k], botOutBasePoints[k + 1], botInBasePoints[k], botInBasePoints[k + 1]);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// Replace this with your code
	GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);

	vector3 top = vector3(0,a_fRadius,0);
	vector3 center = vector3();
	vector3 bot = vector3(0,-a_fRadius,0);
	float degreeDivs = 360 / a_nSubdivisions;
	float divsDist = a_fRadius / a_nSubdivisions;
	std::vector<vector3> midPoints;
	std::vector<vector3> topPoints;
	std::vector<vector3> botPoints;

	//for (int c = 0; c < a_nSubdivisions; c++) {
	//	for (int k = 0; k < a_nSubdivisions; k++) {
	//		vector3 pt = vector3((cos(((k + 1)*degreeDivs) * PI / 180) * a_fRadius),
	//			sin(((k + 1)*degreeDivs) * PI / 180) * a_fRadius,
	//			((2 * PI*a_fRadius) + cos(((k + 1)*degreeDivs) * PI / 180) * a_fRadius));
	//
	//		points.push_back(pt);
	//	}
	//}

	//Calculate midpoints
	for (int c = 0; c < a_nSubdivisions; c++) {
		midPoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * a_fRadius, 0,
			sin(((c + 1)*degreeDivs) * PI / 180) * a_fRadius));
	}

	//Calculate rows above midpoints
	for (int c = 0; c < a_nSubdivisions; c++) {
		topPoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * (a_fRadius-divsDist), divsDist*2.5f,
		sin(((c + 1)*degreeDivs) * PI / 180) * (a_fRadius - divsDist)));
	}

	//Calculate rows below midpoints
	for (int c = 0; c < a_nSubdivisions; c++) {
		botPoints.push_back(vector3(cos(((c + 1)*degreeDivs) * PI / 180) * (a_fRadius - divsDist), -divsDist*2.5f,
			sin(((c + 1)*degreeDivs) * PI / 180) * (a_fRadius - divsDist)));
	}

	//ADD TOP MIDDLE QUADS
	for (int c = 0; c < a_nSubdivisions; c++) {
		if (c == topPoints.size() - 1) {
			AddQuad(topPoints[c], topPoints[0], midPoints[c], midPoints[0]);
		}
		else {
			AddQuad(topPoints[c], topPoints[c+1], midPoints[c], midPoints[c+1]);
		}
	}

	//ADD TOP MIDDLE QUADS
	for (int c = 0; c < a_nSubdivisions; c++) {
		if (c == botPoints.size() - 1) {
			AddQuad(midPoints[c], midPoints[0], botPoints[c], botPoints[0]);
		}
		else {
			AddQuad(midPoints[c], midPoints[c + 1], botPoints[c], botPoints[c + 1]);
		}
	}

	//TEST CENTER PLATFORM
	//for (int k = 0; k < a_nSubdivisions; k++) {
	//	if (k == midPoints.size() - 1) {
	//		AddTri(center, midPoints[0], midPoints[k]);
	//	}
	//	else {
	//		AddTri(center, midPoints[k + 1], midPoints[k]);
	//	}
	//}

	//ADD TOP CAP TRI's
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == topPoints.size() - 1) {
			AddTri(top, topPoints[0], topPoints[k]);
		}
		else {
			AddTri(top, topPoints[k + 1], topPoints[k]);
		}
	}

	//ADD BOTTOM CAP TRI's
	for (int k = 0; k < a_nSubdivisions; k++) {
		if (k == botPoints.size() - 1) {
			AddTri(botPoints[k], botPoints[0], bot);
		}
		else {
			AddTri(botPoints[k], botPoints[k + 1], bot);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}