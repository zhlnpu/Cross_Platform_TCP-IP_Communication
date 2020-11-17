#include "ToolBase.h"
#include "Input.h"

#include "ModelingManager.h"

#ifdef ANDROID
#include <math.h>
#endif

// ************************************************************************
ToolBase::ToolBase(ModelingManager* pManager) : m_pManager(pManager)
{
}

ToolBase::~ToolBase()
{
}

void ToolBase::TipStopMove(float x, float y, float z)
{
	m_pManager->TipStopMove(x, y, z);
}

void ToolBase::TipStartMove(float x, float y, float z)
{
	m_pManager->TipStartMove(x, y, z);
}

void ToolBase::TipStoped(float x, float y, float z)
{
	m_pManager->TipStoped(x, y, z);
}

void ToolBase::TipMoving(float x, float y, float z)
{
	m_pManager->TipMoving(x, y, z);
}

// ************************************************************************
TransTool::TransTool(ModelingManager* pManager) : ToolBase(pManager)
{
}

TransTool::~TransTool()
{
}

void TransTool::TipStopMove(float x, float y, float z)
{
	ToolBase::TipStopMove(x, y, z);
}

void TransTool::TipStartMove(float x, float y, float z)
{
	ToolBase::TipStartMove(x, y, z);
}

void TransTool::TipStoped(float x, float y, float z)
{
	ToolBase::TipStoped(x, y, z);
}

void TransTool::TipMoving(float x, float y, float z)
{
	ToolBase::TipMoving(x, y, z);

	float x0 = m_pManager->m_ptStopMove.x;
	float y0 = m_pManager->m_ptStopMove.y;
	float z0 = m_pManager->m_ptStopMove.z;

	m_pManager->m_ptStopMove;
	if(x != x0 || y != y0)
	{
		float center[4];
		m_pManager->GetCenter(center);

		float dir1[3] = {x - x0, y - y0, z - z0};
		float dir2[3] = {x - center[0], y - center[1], z - center[2]};

		float radius = sqrt(pow(dir2[0], 2) + pow(dir2[1], 2) + pow(dir2[2], 2));

		float divx = x - center[0];
		float divy = y - center[1];
		float divz = z - center[2];
		float theta = sqrt(divx *  divx + divy * divy + divz * divz) * 1.57f / radius;

		float axis[3] = {dir2[1] * dir1[2] - dir2[2] * dir1[1], dir2[2] * dir1[0] - dir2[0] * dir1[2], dir2[0] * dir1[1] - dir2[1] * dir1[0]};

		float len = sqrt(pow(axis[0], 2) + pow(axis[1], 2) + pow(axis[2], 2));
		axis[0] /= len; axis[1] /= len; axis[2] /= len;

		m_pManager->Rotate(theta, center, axis);
	}

	m_pManager->m_ptStopMove.x = x;
	m_pManager->m_ptStopMove.y = y;
	m_pManager->m_ptStopMove.z = z;
}

// ************************************************************************
ModelingTool::ModelingTool(ModelingManager* pManager) : ToolBase(pManager)
{
}

ModelingTool::~ModelingTool()
{
}

void ModelingTool::TipStopMove(float x, float y, float z)
{
	ToolBase::TipStoped(x, y, z);
}

void ModelingTool::TipStartMove(float x, float y, float z)
{
	ToolBase::TipStartMove(x, y, z);

	m_pManager->CreatePoint(x, y, z);
}

void ModelingTool::TipStoped(float x, float y, float z)
{
	ToolBase::TipStoped(x, y, z);
}

void ModelingTool::TipMoving(float x, float y, float z)
{
	ToolBase::TipMoving(x, y, z);
}
