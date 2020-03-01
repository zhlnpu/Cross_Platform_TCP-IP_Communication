#pragma once

#include "Input.h"
#include "ToolBase.h"

class ModelingManager
{
private:
//	bool					m_bTipDown;				// Figertip state

	float					m_Modelview[16];		// model view matrix

	// operator elements -----------------------------------------------------------
	MPoint					m_ptStopMove;
	MPoint					m_ptStartMove;
	MPoint					m_ptMoving;
	MPoint					m_ptStoped;

	// tools
	ToolBase*				m_pTool;

	TransTool*				m_pTransTool;
	ModelingTool*			m_pModelingTool;

	bool					m_bFilpCoords;

public:
	// created object buffer -------------------------------------------------------
	vector<Modeling*>		m_Buffers;				// m_Buffers: MPoint, MPoint, ..., MPolyline, MPoint, MPoint, ..., MPoint, MPath, Model3D
	vector<int>				m_nCreated;				// m_nCreated: the ids are created
	vector<int>				m_nRemoves;				// m_nRemoves: the ids should be removed


	void CreatePoint(float x, float y, float z);
	void CreatePolyline();
	void CreatePath();
	void CreateModelRaw();
private:
	void FlipCoordinate();
	void UndoModeling();
	void GoModeling();

	void ReInitilize();

	void ProcessCommand(Command* pCommand);
	void ProcessGesture(Gesture* pInput);
	void ProcessFingertip(FingerTip* pInput);

public:
	bool CoordFlipped();

	void TipStopMove(float x, float y, float z);
	void TipStartMove(float x, float y, float z);
	void TipMoving(float x, float y, float z);
	void TipStoped(float x, float y, float z);

	// Process gesture and fingertip --------------------------------------------------
	void ProcessInput(InputBase* pInput);

	void GetCusor(MPoint& move, MPoint& stop, MPoint& start_move, MPoint& stop_move) const;

	void GetCenter(float center[]);
	void Rotate(float theta, float center[], float axis[]);

	size_t GetIndices(int& poly, int& path, int& model) const;
	const Modeling* GetBuffer(size_t index) const;

	void test(char input[]);

	ModelingManager(void);
	~ModelingManager(void);

	friend class ToolBase;
	friend class TransTool;
	friend class ModelingTool;
};
