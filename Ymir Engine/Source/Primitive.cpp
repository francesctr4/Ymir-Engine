#include "Primitive.h"
#include "Globals.h"
#include "Log.h"

#include <gl/GL.h>

// ------------------------------------------------------------
Primitive::Primitive() : transform(float4x4::identity), color(White), wire(false), axis(false), type(PrimitiveTypes::Primitive_Point)
{}

// ------------------------------------------------------------
PrimitiveTypes Primitive::GetType() const
{
	return type;
}

// ------------------------------------------------------------
void Primitive::Render() const
{
	glPushMatrix();
	glMultMatrixf(transform.ptr());

	if(axis == true)
	{
		// Draw Axis Grid
		glLineWidth(2.0f);

		glBegin(GL_LINES);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
		glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
		glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
		glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
		glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

		glEnd();

		glLineWidth(1.0f);
	}

	glColor3f(color.r, color.g, color.b);

	/*
	
	if(wire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
	*/

	InnerRender();

	glPopMatrix();
}

// ------------------------------------------------------------
void Primitive::InnerRender() const
{
	glPointSize(5.0f);

	glBegin(GL_POINTS);

	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glPointSize(1.0f);
}

// ------------------------------------------------------------
void Primitive::SetPos(float x, float y, float z)
{
	transform = transform * float4x4::Translate(x, y, z);
}

// ------------------------------------------------------------
void Primitive::SetRotation(float angle, const float3& u)
{
	transform = transform * float4x4::RotateAxisAngle(u, angle);
}

// ------------------------------------------------------------
void Primitive::Scale(float x, float y, float z)
{
	transform = transform * float4x4::Scale(x, y, z);
}

// CUBE ============================================
CCube::CCube() : Primitive(), size(1.0f, 1.0f, 1.0f)
{
	type = PrimitiveTypes::Primitive_Cube;
}

CCube::CCube(float sizeX, float sizeY, float sizeZ) : Primitive(), size(sizeX, sizeY, sizeZ)
{
	type = PrimitiveTypes::Primitive_Cube;
}

void CCube::InnerRender() const
{	
	float sx = size.x * 0.5f;
	float sy = size.y * 0.5f;
	float sz = size.z * 0.5f;

	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-sx, -sy, sz);
	glVertex3f( sx, -sy, sz);
	glVertex3f( sx,  sy, sz);
	glVertex3f(-sx,  sy, sz);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f( sx, -sy, -sz);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx,  sy, -sz);
	glVertex3f( sx,  sy, -sz);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(sx, -sy,  sz);
	glVertex3f(sx, -sy, -sz);
	glVertex3f(sx,  sy, -sz);
	glVertex3f(sx,  sy,  sz);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx, -sy,  sz);
	glVertex3f(-sx,  sy,  sz);
	glVertex3f(-sx,  sy, -sz);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-sx, sy,  sz);
	glVertex3f( sx, sy,  sz);
	glVertex3f( sx, sy, -sz);
	glVertex3f(-sx, sy, -sz);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f( sx, -sy, -sz);
	glVertex3f( sx, -sy,  sz);
	glVertex3f(-sx, -sy,  sz);

	glEnd();
}

// SPHERE ============================================
CSphere::CSphere() : Primitive(), radius(1.0f), numFaces(20)
{
	type = PrimitiveTypes::Primitive_Sphere;
}

CSphere::CSphere(float radius, float numFaces) : Primitive(), radius(radius), numFaces(numFaces)
{
	type = PrimitiveTypes::Primitive_Sphere;
}

void CSphere::InnerRender() const
{
	int nF;

	if (numFaces < 3) { // Ensure at least 3 faces (minimum triangle) and less than 50 faces (too much) 
		nF = 3;
	}
	else if (numFaces > 50) {
		nF = 50;
	}
	else {
		nF = numFaces;
	}

	const float TWO_PI = 2.0f * PI;

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < nF; i++) {

		for (int j = 0; j < nF; j++) {

			float theta1 = i * TWO_PI / nF;
			float theta2 = (i + 1) * TWO_PI / nF;
			float phi1 = j * PI / nF;
			float phi2 = (j + 1) * PI / nF;

			// Vertices

			float x1 = radius * sin(phi1) * cos(theta1);
			float y1 = radius * sin(phi1) * sin(theta1);
			float z1 = radius * cos(phi1);

			float x2 = radius * sin(phi1) * cos(theta2);
			float y2 = radius * sin(phi1) * sin(theta2);
			float z2 = radius * cos(phi1);

			float x3 = radius * sin(phi2) * cos(theta1);
			float y3 = radius * sin(phi2) * sin(theta1);
			float z3 = radius * cos(phi2);

			float x4 = radius * sin(phi2) * cos(theta2);
			float y4 = radius * sin(phi2) * sin(theta2);
			float z4 = radius * cos(phi2);

			// Normals (unit vectors from center)

			glNormal3f(x1 / radius, y1 / radius, z1 / radius);
			glVertex3f(x1, y1, z1);
			glNormal3f(x3 / radius, y3 / radius, z3 / radius);
			glVertex3f(x3, y3, z3);
			glNormal3f(x2 / radius, y2 / radius, z2 / radius);
			glVertex3f(x2, y2, z2);

			glNormal3f(x2 / radius, y2 / radius, z2 / radius);
			glVertex3f(x2, y2, z2);
			glNormal3f(x3 / radius, y3 / radius, z3 / radius);
			glVertex3f(x3, y3, z3);
			glNormal3f(x4 / radius, y4 / radius, z4 / radius);
			glVertex3f(x4, y4, z4);

		}

	}

	glEnd();

}

// PYRAMID ============================================
CPyramid::CPyramid() : Primitive(), size(2.0f, 2.0f, 2.0f)
{
	type = PrimitiveTypes::Primitive_Pyramid;
}

CPyramid::CPyramid(float sizeX, float sizeY, float sizeZ) : Primitive(), size(sizeX, sizeY, sizeZ)
{
	type = PrimitiveTypes::Primitive_Pyramid;
}

void CPyramid::InnerRender() const
{
	float sx = size.x * 0.5f;
	float sy = size.y * 0.5f;
	float sz = size.z * 0.5f;

	glBegin(GL_QUADS);

	// Bottom face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(sx, -sy, -sz);
	glVertex3f(sx, -sy, sz);
	glVertex3f(-sx, -sy, sz);

	glEnd();

	glBegin(GL_TRIANGLES);

	// Front face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(-sx, -sy, sz);
	glVertex3f(sx, -sy, sz);

	// Right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(sx, -sy, sz);
	glVertex3f(sx, -sy, -sz);

	// Back face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(sx, -sy, -sz);
	glVertex3f(-sx, -sy, -sz);

	// Left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sy, 0.0f);
	glVertex3f(-sx, -sy, -sz);
	glVertex3f(-sx, -sy, sz);

	glEnd();

}

// CYLINDER ============================================
CCylinder::CCylinder() : Primitive(), radius(1.0f), height(1.0f)
{
	type = PrimitiveTypes::Primitive_Cylinder;
}

CCylinder::CCylinder(float radius, float height) : Primitive(), radius(radius), height(height)
{
	type = PrimitiveTypes::Primitive_Cylinder;
}

void CCylinder::InnerRender() const
{
	int n = 30;

	// Cylinder Bottom
	glBegin(GL_POLYGON);
	
	for(int i = 360; i >= 0; i -= (360 / n))
	{
		float a = i * PI / 180; // degrees to radians
		glVertex3f(-height*0.5f, radius * cos(a), radius * sin(a));
	}
	glEnd();

	// Cylinder Top
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	for(int i = 0; i <= 360; i += (360 / n))
	{
		float a = i * PI / 180; // degrees to radians
		glVertex3f(height * 0.5f, radius * cos(a), radius * sin(a));
	}
	glEnd();

	// Cylinder "Cover"
	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i < 480; i += (360 / n))
	{
		float a = i * PI / 180; // degrees to radians

		glVertex3f(height*0.5f,  radius * cos(a), radius * sin(a) );
		glVertex3f(-height*0.5f, radius * cos(a), radius * sin(a) );
	}
	glEnd();
}

// POINT ==================================================
CPoint::CPoint() : Primitive(), position(0.0f,0.0f,0.0f)
{
	type = PrimitiveTypes::Primitive_Point;
}

CPoint::CPoint(float x, float y, float z) : Primitive(), position(x, y, z)
{
	type = PrimitiveTypes::Primitive_Point;
}

void CPoint::InnerRender() const
{
	glBegin(GL_POINTS);

	glVertex3f(position.x, position.y, position.z);

	glEnd();
}

// LINE ==================================================
CLine::CLine() : Primitive(), origin(0, 0, 0), destination(1, 1, 1)
{
	type = PrimitiveTypes::Primitive_Line;
}

CLine::CLine(float x, float y, float z) : Primitive(), origin(0, 0, 0), destination(x, y, z)
{
	type = PrimitiveTypes::Primitive_Line;
}

void CLine::InnerRender() const
{
	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glVertex3f(origin.x, origin.y, origin.z);
	glVertex3f(destination.x, destination.y, destination.z);

	glEnd();

	glLineWidth(1.0f);
}

// PLANE ==================================================
CPlane::CPlane() : Primitive(), normal(0, 1, 0), constant(1)
{
	type = PrimitiveTypes::Primitive_Plane;
}

CPlane::CPlane(float x, float y, float z, float d) : Primitive(), normal(x, y, z), constant(d)
{
	type = PrimitiveTypes::Primitive_Plane;
}

void CPlane::InnerRender() const
{
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	float d = 200.0f;

	for(float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
}

// CONE ==================================================
CCone::CCone() : Primitive(), radius(1.0f), numFaces(30), height(2.0f)
{
	type = PrimitiveTypes::Primitive_Cone;
}

CCone::CCone(float radius, int numFaces, float height) : Primitive(), radius(radius), numFaces(numFaces), height(height)
{
	type = PrimitiveTypes::Primitive_Cone;
}

void CCone::InnerRender() const
{
	int nF;

	if (numFaces < 3) { // Ensure at least 3 faces (minimum triangle) and less than 50 faces (too much) 
		nF = 3;
	}
	else if (numFaces > 50) {
		nF = 50;
	}
	else {
		nF = numFaces;
	}

	const float TWO_PI = 2.0f * PI;

	glBegin(GL_TRIANGLES);

	// Base
	for (int i = 0; i < nF; i++) {

		float theta1 = i * TWO_PI / nF;
		float theta2 = (i + 1) * TWO_PI / nF;

		// Vertices for the base
		float x1 = radius * cos(theta1);
		float z1 = radius * sin(theta1);
		float x2 = radius * cos(theta2);
		float z2 = radius * sin(theta2);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(x1, 0.0f, z1);
		glVertex3f(x2, 0.0f, z2);

	}

	// Side
	for (int i = 0; i < nF; i++) {

		float theta1 = i * TWO_PI / nF;
		float theta2 = (i + 1) * TWO_PI / nF;

		// Vertices for the side
		float x1 = radius * cos(theta1);
		float z1 = radius * sin(theta1);
		float x2 = radius * cos(theta2);
		float z2 = radius * sin(theta2);

		glNormal3f(x1, radius / sqrt(radius * radius + height * height), z1);
		glVertex3f(x1, 0.0f, z1);
		glVertex3f(0.0f, height, 0.0f);
		glVertex3f(x2, 0.0f, z2);

	}

	glEnd();

}

// TORUS ==================================================
CTorus::CTorus() : Primitive(), outerRadius(3.0f), innerRadius(1.0f), numFacesOuter(20), numFacesInner(20)
{
	type = PrimitiveTypes::Primitive_Torus;
}

CTorus::CTorus(float outerRadius, float innerRadius, int numFacesOuter, int numFacesInner) : Primitive(), outerRadius(outerRadius), innerRadius(innerRadius), numFacesOuter(numFacesOuter), numFacesInner(numFacesInner)
{
	type = PrimitiveTypes::Primitive_Torus;
}

void CTorus::InnerRender() const
{
	int nFO;
	int nFI;

	if (numFacesOuter < 3) { // Ensure at least 3 faces for the outer circle (minimum triangle)
		nFO = 3;
	}
	else if (numFacesOuter > 50) {
		nFO = 50;
	}
	else {
		nFO = numFacesOuter;
	}

	if (numFacesInner < 3) {
		nFI = 3;  // Ensure at least 3 faces for the inner circle (minimum triangle)
	}
	else if (numFacesInner > 50) {
		nFI = 50;
	}
	else {
		nFI = numFacesInner;
	}

	const float TWO_PI = 2.0f * 3.14159265359f;

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < nFO; i++) {

		for (int j = 0; j < nFI; j++) {

			float theta1 = i * TWO_PI / nFO;
			float theta2 = (i + 1) * TWO_PI / nFO;
			float phi1 = j * TWO_PI / nFI;
			float phi2 = (j + 1) * TWO_PI / nFI;

			// Vertices
			float x1 = (outerRadius + innerRadius * cos(phi1)) * cos(theta1);
			float y1 = innerRadius * sin(phi1);
			float z1 = (outerRadius + innerRadius * cos(phi1)) * sin(theta1);

			float x2 = (outerRadius + innerRadius * cos(phi1)) * cos(theta2);
			float y2 = innerRadius * sin(phi1);
			float z2 = (outerRadius + innerRadius * cos(phi1)) * sin(theta2);

			float x3 = (outerRadius + innerRadius * cos(phi2)) * cos(theta1);
			float y3 = innerRadius * sin(phi2);
			float z3 = (outerRadius + innerRadius * cos(phi2)) * sin(theta1);

			float x4 = (outerRadius + innerRadius * cos(phi2)) * cos(theta2);
			float y4 = innerRadius * sin(phi2);
			float z4 = (outerRadius + innerRadius * cos(phi2)) * sin(theta2);

			// Normals (unit vectors from the center)
			float nx1 = cos(phi1) * cos(theta1);
			float ny1 = sin(phi1);
			float nz1 = cos(phi1) * sin(theta1);

			float nx2 = cos(phi1) * cos(theta2);
			float ny2 = sin(phi1);
			float nz2 = cos(phi1) * sin(theta2);

			float nx3 = cos(phi2) * cos(theta1);
			float ny3 = sin(phi2);
			float nz3 = cos(phi2) * sin(theta1);

			float nx4 = cos(phi2) * cos(theta2);
			float ny4 = sin(phi2);
			float nz4 = cos(phi2) * sin(theta2);

			// Triangle 1
			glNormal3f(nx1, ny1, nz1);
			glVertex3f(x1, y1, z1);
			glNormal3f(nx3, ny3, nz3);
			glVertex3f(x3, y3, z3);
			glNormal3f(nx2, ny2, nz2);
			glVertex3f(x2, y2, z2);

			// Triangle 2
			glNormal3f(nx2, ny2, nz2);
			glVertex3f(x2, y2, z2);
			glNormal3f(nx3, ny3, nz3);
			glVertex3f(x3, y3, z3);
			glNormal3f(nx4, ny4, nz4);
			glVertex3f(x4, y4, z4);

		}

	}

	glEnd();

}