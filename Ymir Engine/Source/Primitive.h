#pragma once
#include "Color.h"
#include "External/MathGeoLib/include/Math/float4x4.h"
#include "External/MathGeoLib/include/Math/float2.h"
#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/TransformOps.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Pyramid,
	Primitive_Cylinder,
	Primitive_Cone,
	Primitive_Torus,
};

class Primitive
{
public:

	Primitive();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const float3& u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;

public:
	
	Color color;
	float4x4 transform;
	bool axis,wire;

protected:
	PrimitiveTypes type;
};

// ============================================
class CCube : public Primitive
{
public :
	CCube();
	CCube(float sizeX, float sizeY, float sizeZ);
	void InnerRender() const override;
public:
	float3 size;
};

// ============================================
class CSphere : public Primitive
{
public:
	CSphere();
	CSphere(float radius, float numFaces);
	void InnerRender() const;
public:
	float radius;
	int numFaces;
};

// ============================================
class CPyramid : public Primitive
{
public:
	CPyramid();
	CPyramid(float sizeX, float sizeY, float sizeZ);
	void InnerRender() const;
public:
	float3 size;
};

// ============================================
class CCylinder : public Primitive
{
public:
	CCylinder();
	CCylinder(float radius, float height);
	void InnerRender() const override;
public:
	float radius;
	float height;
};

// ============================================
class CPoint : public Primitive
{
public:
	CPoint();
	CPoint(float x, float y, float z);
	void InnerRender() const override;
public:
	float3 position;
};

// ============================================
class CLine : public Primitive
{
public:
	CLine();
	CLine(float x, float y, float z);
	void InnerRender() const override;
public:
	float3 origin;
	float3 destination;
};

// ============================================
class CPlane : public Primitive
{
public:
	CPlane();
	CPlane(float x, float y, float z, float d);
	void InnerRender() const override;
public:
	float3 normal;
	float constant;
};

// ============================================
class CCone : public Primitive
{
public:
	CCone();
	CCone(float radius, int numFaces, float height);
	void InnerRender() const override;
public:
	float radius;
	int numFaces;
	float height;
};

// ============================================
class CTorus : public Primitive
{
public:
	CTorus();
	CTorus(float outerRadius, float innerRadius, int numFacesOuter, int numFacesInner);
	void InnerRender() const override;
public:
	float outerRadius;
	float innerRadius;
	int numFacesOuter;
	int numFacesInner;
};