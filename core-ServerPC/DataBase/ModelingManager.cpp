#include "ModelingManager.h"

#ifdef ANDROID
#include <math.h>
#endif

ModelingManager::ModelingManager(void) : m_bFilpCoords(false), m_pTool(NULL)
{
	m_pModelingTool = new ModelingTool(this);
	m_pTransTool = new TransTool(this);

	m_pTool = m_pModelingTool;

	m_ptStopMove.command = AC_DOWN;
	m_ptStartMove.command = AC_UP;
	m_ptMoving.command = AC_UP;
	m_ptStoped.command = AC_CUR;
}

ModelingManager::~ModelingManager(void)
{
	delete m_pModelingTool;
	delete m_pTransTool;

	for(size_t i = 0; i < m_Buffers.size(); i++) {
		delete m_Buffers[i];
	}
}
//	
//int ModelingManager::GetID()
//{
//	return (int)m_Buffers.size();
//}

void ModelingManager::ReInitilize()
{
	m_bFilpCoords = false;

	for (size_t i = 0; i < m_Buffers.size(); i++) {
		delete m_Buffers[i];
	}

	m_Buffers.clear();
}

bool ModelingManager::CoordFlipped()
{
	return m_bFilpCoords;
}
//
//void ModelingManager::Updated()
//{
//	if (m_nUpdated == m_nModel && m_nUpdated != -1)
//		ReInitilize();
//
//	m_nUpdated = -1; 
//}

//Modeling* ModelingManager::GetUpdated()
//{
//	if (m_nUpdated == -1 || m_nUpdated >= m_Buffers.size())
//		return NULL;
//
//	return m_Buffers[m_nUpdated];
//}

void ModelingManager::GetCusor(MPoint& move, MPoint& stop, MPoint& start_move, MPoint& stop_move) const
{
	stop_move = m_ptStopMove;
	start_move = m_ptStartMove;

	move = m_ptMoving;
	stop = m_ptStoped;
}

void ModelingManager::GetCenter(float center[])
{
	center[0] = 0; center[1] = 0; center[2] = 0; 

	int count = 0;
	for(size_t i = 0; i < m_Buffers.size(); i++)
	{
		if (m_Buffers[i]->type != DT_POINT)
			continue;

		MPoint* pPoint = (MPoint*)m_Buffers[i];

		center[0] += pPoint->x; 
		center[1] += pPoint->y; 
		center[2] += pPoint->z;

		count++;
	}

	center[0] /= count;
	center[1] /= count;
	center[2] /= count;
}

template<typename Real>
void init_matrix(Real ma[16])
{
	ma[0] = 1.0;		ma[1] = 0.0;		ma[2] = 0.0;		ma[3] = 0.0;
	ma[4] = 0.0;		ma[5] = 1.0;		ma[6] = 0.0;		ma[7] = 0.0;
	ma[8] = 0.0;		ma[9] = 0.0;		ma[10] = 1.0;		ma[11] = 0.0;
	ma[12] = 0.0;		ma[13] = 0.0;		ma[14] = 0.0;		ma[15] = 1.0;
}

template<typename Real>
void matrix_times(Real ma[16], const Real mb[16])
{
	float m[16];

	m[0] = ma[0] * mb[0] + ma[1] * mb[4] + ma[2] * mb[8] + ma[3] * mb[12];
	m[1] = ma[0] * mb[1] + ma[1] * mb[5] + ma[2] * mb[9] + ma[3] * mb[13];
	m[2] = ma[0] * mb[2] + ma[1] * mb[6] + ma[2] * mb[10] + ma[3] * mb[14];
	m[3] = ma[0] * mb[3] + ma[1] * mb[7] + ma[2] * mb[11] + ma[3] * mb[15];

	m[4] = ma[4] * mb[0] + ma[5] * mb[4] + ma[6] * mb[8] + ma[7] * mb[12];
	m[5] = ma[4] * mb[1] + ma[5] * mb[5] + ma[6] * mb[9] + ma[7] * mb[13];
	m[6] = ma[4] * mb[2] + ma[5] * mb[6] + ma[6] * mb[10] + ma[7] * mb[14];
	m[7] = ma[4] * mb[3] + ma[5] * mb[7] + ma[6] * mb[11] + ma[7] * mb[15];

	m[8] = ma[8] * mb[0] + ma[9] * mb[4] + ma[10] * mb[8] + ma[11] * mb[12];
	m[9] = ma[8] * mb[1] + ma[9] * mb[5] + ma[10] * mb[9] + ma[11] * mb[13];
	m[10] = ma[8] * mb[2] + ma[9] * mb[6] + ma[10] * mb[10] + ma[11] * mb[14];
	m[11] = ma[8] * mb[3] + ma[9] * mb[7] + ma[10] * mb[11] + ma[11] * mb[15];

	m[12] = ma[12] * mb[0] + ma[13] * mb[4] + ma[14] * mb[8] + ma[15] * mb[12];
	m[13] = ma[12] * mb[1] + ma[13] * mb[5] + ma[14] * mb[9] + ma[15] * mb[13];
	m[14] = ma[12] * mb[2] + ma[13] * mb[6] + ma[14] * mb[10] + ma[15] * mb[14];
	m[15] = ma[12] * mb[3] + ma[13] * mb[7] + ma[14] * mb[11] + ma[15] * mb[15];

	for(int i = 0; i < 16; i++)
		ma[i] = m[i];
}

// 在变化矩阵matrix上右乘一个旋转矩阵，旋转角度为theta，旋转轴由org，normal决定
template<typename Real>
void rotate_matrix(Real theta, const Real org[], const Real normal[], Real matrix[16])
{
	Real Ta[16], Rx[16], Ry[16], Rz[16], Rxr[16], Ryr[16], Tar[16];
	init_matrix(Ta); init_matrix(Rx); init_matrix(Ry); init_matrix(Rz);
	init_matrix(Tar); init_matrix(Rxr); init_matrix(Ryr); 

	Ta[12] = -org[0];	Ta[13] = -org[1];	Ta[14] = -org[2];
	Tar[12] = org[0];	Tar[13] = org[1];	Tar[14] = org[2];

	float v = sqrt(normal[2] * normal[2] + normal[1] * normal[1]);
	if(v != 0)
	{
		float cosalf = normal[2] / v;	float sinalf = normal[1] / v;
		Rx[5] = cosalf;		Rx[6] = sinalf;		Rx[9] = -sinalf;	Rx[10] = cosalf;
	}

	float u = sqrt(normal[2] * normal[2] + normal[1] * normal[1] + normal[0] * normal[0]);
	float cosbeta = v / u;
	float sinbeta = - normal[0] / u;

	Ry[0] = cosbeta;		Ry[2] = -sinbeta;		Ry[8] = sinbeta;		Ry[10] = cosbeta;
	Rz[0] = cos(theta);		Rz[1] = sin(theta);		Rz[4] = -Rz[1];			Rz[5] = Rz[0];
	Rxr[5] = Rx[5];			Rxr[6] = -Rx[6];		Rxr[9] = -Rx[9];		Rxr[10] = Rx[10];
	Ryr[0] = Ry[0];			Ryr[2] = -Ry[2];		Ryr[8] = -Ry[8];		Ryr[10] = Ry[10];

	matrix_times(matrix, Ta);
	matrix_times(matrix, Rx);
	matrix_times(matrix, Ry);
	matrix_times(matrix, Rz);
	matrix_times(matrix, Ryr);
	matrix_times(matrix, Rxr);
	matrix_times(matrix, Tar);
}

size_t ModelingManager::GetIndices(int& poly, int& path, int& model) const
{
	return m_Buffers.size();
}

const Modeling* ModelingManager::GetBuffer(size_t index) const
{
	if (index < m_Buffers.size())
		return m_Buffers[index];

	return NULL;
}

void ModelingManager::Rotate(float theta, float center[], float axis[])
{
	rotate_matrix(theta, center, axis, m_Modelview);
}

void ModelingManager::CreatePoint(float x, float y, float z)
{
	MPoint* pPoint = new MPoint(x, y, z);
	pPoint->id = (int)m_Buffers.size();

	m_Buffers.push_back(pPoint);
	m_nCreated.push_back(pPoint->id);
}

void ModelingManager::CreatePolyline()
{
	if (m_Buffers.size() < 2)
		return;

	MPolyline* pPolyline = new MPolyline();
	pPolyline->id = (int)m_Buffers.size();

	size_t iStart = m_Buffers.size() - 1;
	while (m_Buffers[iStart]->type == DT_POINT)
	{
		if (iStart == 0)
			break;
		iStart--;
	}

	for (size_t index = iStart; index < m_Buffers.size(); index++)
		pPolyline->points.push_back(*((MPoint*)m_Buffers[index]));

	m_Buffers.push_back(pPolyline);
	m_nCreated.push_back(pPolyline->id);
}

void ModelingManager::CreatePath()
{
	if (m_Buffers.size() < 2)
		return;

	MPath* pPath = new MPath();
	pPath->id = (int)m_Buffers.size();

	size_t iStart = m_Buffers.size() - 1;
	while (m_Buffers[iStart]->type == DT_POINT)
	{
		if (iStart == 0)
			break;
		iStart--;
	}
	iStart++;

	for (size_t index = iStart; index < m_Buffers.size(); index++)
		pPath->points.push_back(*((MPoint*)m_Buffers[index]));

	m_Buffers.push_back(pPath);
	m_nCreated.push_back(pPath->id);
}

void ModelingManager::CreateModelRaw()
{
	if(m_Buffers.size() < 2)
		return;

	int nPoly = -1, nPath = -1;

	int index = (int)m_Buffers.size() - 1;
	while (m_Buffers[index]->type != DT_PATH)
		index--;
	nPath = index;

	while (m_Buffers[index]->type != DT_POLYLINE)
		index--;
	nPoly = index;

	ModelRaw* pModel = new ModelRaw();
	pModel->id = (int)m_Buffers.size();

	pModel->polyline = *(MPolyline*)m_Buffers[nPoly];
	pModel->path = *(MPath*)m_Buffers[nPath];

	m_Buffers.push_back(pModel);
	m_nCreated.push_back(pModel->id);

	m_pTool = m_pTransTool;
}

void ModelingManager::FlipCoordinate()
{
	m_bFilpCoords = !m_bFilpCoords;
}

void ModelingManager::GoModeling()
{
	int index = (int)m_Buffers.size() - 1;
	while (m_Buffers[index]->type != DT_POINT)
		index--;

	if (index == 0 && m_Buffers.size() > 0)
		CreatePolyline();

	if (m_Buffers[index]->type == DT_POLYLINE && index < m_Buffers.size())
		CreatePath();

	if (m_Buffers[index]->type == DT_PATH)
		CreateModelRaw();
}

void ModelingManager::UndoModeling()
{
	if(m_Buffers.size() > 0) {
		Modeling* pModeling = m_Buffers[m_Buffers.size() - 1];

		if(pModeling->type == DT_MODELMESH)
			m_pTool = m_pModelingTool;

		m_nRemoves.push_back(pModeling->id);

		delete pModeling;

		m_Buffers.pop_back();
	}
}

void ModelingManager::TipStopMove(float x, float y, float z)
{
	m_ptStopMove.x = x;
	m_ptStopMove.y = y;
	m_ptStopMove.z = z;

//	m_bTipDown = true;
}

void ModelingManager::TipStartMove(float x, float y, float z)
{
	m_ptStartMove.x = x;
	m_ptStartMove.y = y;
	m_ptStartMove.z = z;

//	m_bTipDown = false;
}

void ModelingManager::TipMoving(float x, float y, float z)
{
	m_ptMoving.x = x;
	m_ptMoving.y = y;
	m_ptMoving.z = z;

//	m_bTipDown = false;
}

void ModelingManager::TipStoped(float x, float y, float z)
{
	m_ptStoped.x = x;
	m_ptStoped.y = y;
	m_ptStoped.z = z;
}

void ModelingManager::ProcessCommand(Command* pCommand)
{

}

void ModelingManager::ProcessGesture(Gesture* pInput)
{
	if (pInput->gestureType == GT_FLIP)
		FlipCoordinate();

	if (pInput->gestureType == GT_BACK)
		UndoModeling();

	if (pInput->gestureType == GT_GO)
		GoModeling();
}

void ModelingManager::ProcessFingertip(FingerTip* pInput)
{
	// 1. 指令 -------------------------------------------------------------------
	if(m_pTool != NULL) {
		if(pInput->tipType == TIP_STOPMOVE) {						// 接触基准面
			m_pTool->TipStopMove(pInput->x, pInput->y, pInput->z);
		} else if(pInput->tipType == TIP_STARTMOVE) {				// 离开基准面
			m_pTool->TipStartMove(pInput->x, pInput->y, pInput->z);
		} else if(pInput->tipType == TIP_STOPED) {					// 指尖移动
			CreatePoint(pInput->x, pInput->y, pInput->z);
			m_pTool->TipStoped(pInput->x, pInput->y, pInput->z);
		} else if(pInput->tipType == TIP_MOVING) {
			m_pTool->TipMoving(pInput->x, pInput->y, pInput->z);
		}
	}
}

void ModelingManager::ProcessInput(InputBase* pInput)
{
	if (pInput->inputType == IT_COMMAND)
		ProcessCommand((Command*)pInput);
	else if (pInput->inputType == IT_GESTURE)
		ProcessGesture((Gesture*)pInput);
	else if (pInput->inputType == IT_FINGERTIP)
		ProcessFingertip((FingerTip*)pInput);
}

void ModelingManager::test(char input[])
{
	if (strcmp(input, "1") == 0)
		CreatePoint(-10, -10, 0);
	if (strcmp(input, "2") == 0)
		CreatePoint(-10, 10, 0);
	if (strcmp(input, "3") == 0)
		CreatePoint(10, 10, 0);
	if (strcmp(input, "4") == 0)
		CreatePoint(10, -10, 0);

	if (strcmp(input, "5") == 0)
		CreatePolyline();

	if (strcmp(input, "6") == 0)
		CreatePoint(0, 0, 0);
	if (strcmp(input, "7") == 0)
		CreatePoint(0, 5, 20);
	if (strcmp(input, "8") == 0)
		CreatePath();

	if (strcmp(input, "9") == 0)
		CreateModelRaw();

}
