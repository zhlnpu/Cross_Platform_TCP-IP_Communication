#pragma once

#include <vector>
using namespace std;

#define DEFAULT_BUFLEN	4096

// DataType -----------------------------------------
typedef int DataType;
#define DT_BASE			100
#define DT_POINT		101
#define DT_POLYLINE		102
#define DT_PATH			103
#define DT_MODELRAW		104
#define DT_MODELMESH	105

// ActuratorCommand ---------------------------------
typedef int ActuratorCommand;
#define AC_EMPTY		0
#define AC_UNDO			1
#define AC_CUR			2		// Tip position
#define AC_DOWN			3		// Tip down position
#define AC_UP			4		// Tip up position

// ID
typedef int ID;

// class Modeling ---------------------------------------------------------------------
class Modeling
{
public:
	DataType			type;
	int				count;			// length of the byte array representation of the bojbect
	ID					id;
	ActuratorCommand	command;

public:
	virtual void ToCharArray(char buf[], int index);
	int base_byte_size();
	virtual int byte_size();

	Modeling();
	Modeling(char buf[], int index);
	virtual ~Modeling();
};

// class Point -----------------------------------------------------------------------
class MPoint : public Modeling
{
public:
	float x;
	float y;
	float z;

public:
	virtual void ToCharArray(char buf[], int index);
	int byte_size();

	MPoint();
	MPoint(float _x, float _y, float _z);
	MPoint(char buf[], int index);
	virtual ~MPoint();
};

// class MPolyline -------------------------------------------------------------------
class MPolyline : public Modeling
{
public:
	vector<MPoint>		points;

public:
	virtual void ToCharArray(char buf[], int index);
	int byte_size();

	MPolyline();
	MPolyline(char buf[], int index);
	virtual ~MPolyline();
};

// class MPath ----------------------------------------------------------------------
class MPath : public Modeling
{
public:
	vector<MPoint>		points;

public:
	virtual void ToCharArray(char buf[], int index);
	int byte_size();

	MPath();
	MPath(char buf[], int index);
	virtual ~MPath();
};


// class Model3D --------------------------------------------------------------------
class ModelRaw : public Modeling
{
public:
	// Modeling data
	MPolyline				polyline;
	MPath					path;

public:
	virtual void ToCharArray(char buf[], int index);
	int byte_size();

	bool isRevolution();

	ModelRaw();
	ModelRaw(char buf[], int index);
	virtual ~ModelRaw();
};

// class Model3D --------------------------------------------------------------------
class ModelMesh : public Modeling
{
public:
	// Display data
	vector<float>			points;					// each triangle have 3 points.				x, y, z, x, y, z ...
	vector<float>			normals;				// each triangle have 1 normal.				nx, ny, nz, nx, ny, nz ...
	vector<int>			triangles;				// each triangle have 3 indices.			ix, iy, iz, ix, iy, iz ...
	vector<int>			domains;				// count of triangles each domain contain.	icount, icount, ...

public:
	virtual void ToCharArray(char buf[], int index);
	int byte_size();

	void AppendTriangle(float pt[9], float normal[3]);
	void AppendDomain(int count);

	ModelMesh();
	ModelMesh(char buf[], int index);
	virtual ~ModelMesh();
};
