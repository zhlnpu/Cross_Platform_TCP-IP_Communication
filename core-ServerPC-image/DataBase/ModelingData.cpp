#include "ModelingData.h"

#ifdef ANDROID
#include <string.h>

#define NULL 0
#endif

// **********************************************************************************************
// modleing
Modeling::Modeling() : id(-1), type(DT_BASE), command(AC_EMPTY)
{
};

Modeling::Modeling(char buf[], int index)
{
	// get value of type
	int pos = index, len = sizeof(DataType);
	memcpy_s(&type, len, &buf[pos], len);
	pos += len;

	// get value of count
	len = sizeof(int);
	memcpy_s(&count, len, &buf[pos], len);
	pos += len;

	// get value of type
	len = sizeof(ID);
	memcpy_s(&id, len, &buf[pos], len);
	pos += len;

	// get value of command
	len = sizeof(ActuratorCommand);
	memcpy_s(&command, len, &buf[pos], len);
}

Modeling::~Modeling()
{

}

int Modeling::base_byte_size()
{
	return sizeof(int) + sizeof(ID) + sizeof(DataType) + sizeof(ActuratorCommand);
}

int Modeling::byte_size()
{
	return base_byte_size();
}

void Modeling::ToCharArray(char buf[], int index)
{
	// copy type to buf
	size_t pos = index, len = sizeof(DataType);
	memcpy_s(&(buf[pos]), len, &type, len);
	pos += len;

	// copy byte count of the object
	int count = byte_size();
	len = sizeof(int);
	memcpy_s(&(buf[pos]), len, &count, len);
	pos += len;

	// copy id to buf
	len = sizeof(ID);
	memcpy_s(&(buf[pos]), len, &id, len);
	pos += len;

	// copy command to buf
	len = sizeof(ActuratorCommand);
	memcpy_s(&(buf[pos]), len, &command, len);
}

// **********************************************************************************************
// MPoint
MPoint::MPoint()
{
	type = DT_POINT;
	command = AC_EMPTY;
};

MPoint::MPoint(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
	type = DT_POINT;
	command = AC_EMPTY;
};

MPoint::MPoint(char buf[], int index) : Modeling(buf, index)
{
	// get value of x
	int pos = index + base_byte_size(), len = sizeof(float);
	memcpy_s(&x, len, &buf[pos], len);
	pos += len;

	// get value of y
	len = sizeof(float);
	memcpy_s(&y, len, &buf[pos], len);
	pos += len;

	// get value of z
	len = sizeof(float);
	memcpy_s(&z, len, &buf[pos], len);
	pos += len;
}

MPoint::~MPoint()
{

}

void MPoint::ToCharArray(char buf[], int index)
{
	// copy base to buf
	Modeling::ToCharArray(buf, index);

	// copy x to buf
	int pos = index + base_byte_size(), len = sizeof(float);
	memcpy_s(&buf[pos], len, &x, len);
	pos += len;

	// copy y to buf
	len = sizeof(float);
	memcpy_s(&buf[pos], len, &y, len);
	pos += len;

	// copy z to buf
	len = sizeof(float);
	memcpy_s(&buf[pos], len, &z, len);
	pos += len;
}

int MPoint::byte_size()
{
	return base_byte_size() + sizeof(float) * 3;
}

// **********************************************************************************************
// MPolyline
MPolyline::MPolyline()
{
	type = DT_POLYLINE;
	command = AC_EMPTY;

}

MPolyline::MPolyline(char buf[], int index) : Modeling(buf, index)
{
	// find count of points
	int pos = index + base_byte_size(), len = sizeof(int), count;
	memcpy_s(&count, len, &buf[pos], len);
	pos += len;

	// get value of points
	for (int i = 0; i < count; i++)
	{
		MPoint pt(buf, pos);
		points.push_back(pt);
		pos += pt.byte_size();
	}
}

MPolyline::~MPolyline()
{
};

void MPolyline::ToCharArray(char buf[], int index)
{
	// copy base to buf
	Modeling::ToCharArray(buf, index);

	// copy count of points to buf
	int count = (int)points.size();
	int pos = index + base_byte_size(), len = sizeof(int);
	memcpy_s(&buf[pos], len, &count, len);
	pos += len;

	// copy each point
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].ToCharArray(buf, pos);
		pos += points[i].byte_size();
	}
}

int MPolyline::byte_size()
{
	int len = base_byte_size() + sizeof(int);
	for (size_t i = 0; i < points.size(); i++)
		len += points[i].byte_size();

	return len;
}

// **********************************************************************************************
// Path
MPath::MPath()
{
	type = DT_PATH;
	command = AC_EMPTY;
}

MPath::MPath(char buf[], int index) : Modeling(buf, index)
{
	// find count of points
	int pos = index + base_byte_size(), len = sizeof(int);
	memcpy_s(&count, len, &buf[pos], len);
	pos += len;

	// get value of points
	for (int i = 0; i < count; i++)
	{
		MPoint pt(buf, pos);
		points.push_back(pt);
		pos += pt.byte_size();
	}
}

MPath::~MPath()
{
};

void MPath::ToCharArray(char buf[], int index)
{
	// copy base to buf
	Modeling::ToCharArray(buf, index);

	// copy count of points to buf
	int count = (int)points.size();
	int pos = index + base_byte_size(), len = sizeof(int);
	memcpy_s(&buf[pos], len, &count, len);
	pos += len;

	// copy each point
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].ToCharArray(buf, pos);
		pos += points[i].byte_size();
	}
}

int MPath::byte_size()
{
	int len = base_byte_size() + sizeof(int);
	for (size_t i = 0; i < points.size(); i++)
		len += points[i].byte_size();

	return len;
}

// **********************************************************************************************
// Model3D
ModelRaw::ModelRaw()
{
	type = DT_MODELRAW;
	command = AC_EMPTY;
};

ModelRaw::ModelRaw(char buf[], int index) : Modeling(buf, index)
{
	// get value of polyline
	int pos = index + base_byte_size();
	polyline = MPolyline(buf, pos);
	pos += polyline.byte_size();

	// get value of path
	path = MPath(buf, pos);
	pos += path.byte_size();
}

ModelRaw::~ModelRaw()
{

}

void ModelRaw::ToCharArray(char buf[], int index)
{
	// copy base to buf
	Modeling::ToCharArray(buf, index);

	// copy polyline to buf
	int pos = index + base_byte_size();
	polyline.ToCharArray(buf, pos);
	pos += polyline.byte_size();

	// copy path to buf
	path.ToCharArray(buf, pos);
	pos += path.byte_size();
}

int ModelRaw::byte_size()
{
	int len = base_byte_size();

	len += polyline.byte_size();

	len += path.byte_size();

	return len;
}

bool ModelRaw::isRevolution()
{
	if (path.points.size() == 0)
		return false;

	float n = 0;
	for (size_t i = 0; i < path.points.size(); i++)
	{
		n += path.points[i].z;
	}

	if (n == 0)
		return true;
	else
		return false;
}

// **********************************************************************************************
// ModelMesh
ModelMesh::ModelMesh()
{
	type = DT_MODELMESH;
	command = AC_EMPTY;
};

ModelMesh::ModelMesh(char buf[], int index) : Modeling(buf, index)
{
	// get value of points
	int pos = index + base_byte_size(), len = sizeof(int), count;
	memcpy_s(&count, len, &buf[pos], len);
	pos += len;

	if (count > 0)
	{
		points.resize(count);

		len = count * sizeof(float);
		memcpy_s(&points[0], len, &buf[pos], len);
		pos += len;
	}

	// get value of normals
	len = sizeof(int);
	memcpy_s(&count, len, &buf[pos], len);
	pos += len;

	if (count > 0)
	{
		normals.resize(count);

		len = count * sizeof(float);
		memcpy_s(&normals[0], len, &buf[pos], len);
		pos += len;
	}

	// get value of triangles
	len = sizeof(int);
	memcpy_s(&count, len, &buf[pos], len);
	pos += len;

	if (count > 0)
	{
		triangles.resize(count);

		len = count * sizeof(int);
		memcpy_s(&triangles[0], len, &buf[pos], len);
		pos += len;
	}

	// get value of domains
	len = sizeof(int);
	memcpy_s(&count, len, &buf[pos], len);
	pos += len;

	if (count > 0)
	{
		domains.resize(count);

		len = count * sizeof(int);
		memcpy_s(&domains[0], len, &buf[pos], len);
		pos += len;
	}
}

ModelMesh::~ModelMesh()
{

}

void ModelMesh::ToCharArray(char buf[], int index)
{
	// copy base to buf
	Modeling::ToCharArray(buf, index);

	// copy points to buf
	int count = (int)points.size();
	int pos = index + base_byte_size(), len = sizeof(int);
	memcpy_s(&buf[pos], len, &count, len);
	pos += len;

	if (count > 0)
	{
		len = count * sizeof(float);
		memcpy_s(&buf[pos], len, &points[0], len);
		pos += len;
	}

	// copy normals to buf
	count = (int)normals.size();
	len = sizeof(int);
	memcpy_s(&buf[pos], len, &count, len);
	pos += len;

	if (count > 0)
	{
		len = count * sizeof(float);
		memcpy_s(&buf[pos], len, &normals[0], len);
		pos += len;
	}

	// copy triangles to buf
	count = (int)triangles.size();
	len = sizeof(int);
	memcpy_s(&buf[pos], len, &count, len);
	pos += len;

	if (count > 0)
	{
		len = count * sizeof(int);
		memcpy_s(&buf[pos], len, &triangles[0], len);
		pos += len;
	}

	// copy domains to buf
	count = (int)domains.size();
	len = sizeof(int);
	memcpy_s(&buf[pos], len, &count, len);
	pos += len;

	if (count > 0)
	{
		len = count * sizeof(int);
		memcpy_s(&buf[pos], len, &domains[0], len);
		pos += len;
	}
}

int ModelMesh::byte_size()
{
	int len = base_byte_size();

	len += sizeof(int);
	len += sizeof(float) * (int)points.size();

	len += sizeof(int);
	len += sizeof(float) * (int)normals.size();

	len += sizeof(int);
	len += sizeof(int) * (int)triangles.size();

	len += sizeof(int);
	len += sizeof(int) * (int)domains.size();

	return len;
}

void ModelMesh::AppendTriangle(float pt[9], float normal[3])
{
	size_t index = points.size() / 9;

	for (int i = 0; i < 9; i++) {
		points.push_back(pt[i]);
	}

	for (int i = 0; i < 3; i++) {
		normals.push_back(normal[i]);
	}

	triangles.push_back((int)index);
}

void ModelMesh::AppendDomain(int count)
{
	domains.push_back(count);
}
