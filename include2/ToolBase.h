#pragma once

#include "ModelingData.h"

class ModelingManager;

enum ToolType
{
	TT_NULL			= 0,
	TT_BUTTON		= 1,
	TT_TRANS		= 2,
	TT_POLYLINE		= 3,
	TT_PPATH		= 4,
};

class ToolBase
{
protected:
	ModelingManager*		m_pManager;

public:
	virtual void TipStopMove(float x, float y, float z);
	virtual void TipStartMove(float x, float y, float z);
	virtual void TipStoped(float x, float y, float z);
	virtual void TipMoving(float x, float y, float z);

	ToolBase(ModelingManager* pManager);
	virtual ~ToolBase();
};

class TransTool : public ToolBase
{
public:
	virtual void TipStopMove(float x, float y, float z);
	virtual void TipStartMove(float x, float y, float z);
	virtual void TipStoped(float x, float y, float z);
	virtual void TipMoving(float x, float y, float z);

	TransTool(ModelingManager* pManager);
	virtual ~TransTool();
};

class ModelingTool : public ToolBase
{
public:
	virtual void TipStopMove(float x, float y, float z);
	virtual void TipStartMove(float x, float y, float z);
	virtual void TipStoped(float x, float y, float z);
	virtual void TipMoving(float x, float y, float z);

	ModelingTool(ModelingManager* pManager);
	virtual ~ModelingTool();
};
