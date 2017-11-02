//==================================================================================================================================//
//!< @file		slDXModel2DStorage.cpp
//!< @brief		sl::DXModel2DStorageクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/02	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXModel2DStorage.h"
#include "slDXModel2D.h"
#include "../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXModel2DStorage::DXModel2DStorage()
	: m_IDNumCount(0)
{}

DXModel2DStorage::~DXModel2DStorage()
{
	ReleaseALL();
}

ModelID DXModel2DStorage::AddDXModel2D(DXModel2D* pModel)
{
	ModelID id;		// 戻り値のID

	if(m_IDNumCount == INT_MAX)
	{	// IDの値がMAX値なら空いているIDを検索してそこにデータ格納
		id.m_Num = SearchAvailableIDNum();
		m_pModel2Ds[id.m_Num] = pModel;
		return id;
	}

	m_pModel2Ds[m_IDNumCount] = pModel;
	id.m_Num = m_IDNumCount;
	++m_IDNumCount;

	return id;
}

void DXModel2DStorage::ReleaseDXModel2D(const ModelID& rID)
{
	SafeDelete(m_pModel2Ds[rID.m_Num]);
	m_pModel2Ds.erase(rID.m_Num);
}

void DXModel2DStorage::ReleaseALL()
{
	for(auto& pModel : m_pModel2Ds)
	{
		SafeDelete(pModel.second);
	}
	m_pModel2Ds.clear();
	m_IDNumCount = 0;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

int DXModel2DStorage::SearchAvailableIDNum()
{
	int id;

	/** @todo ここは少し見直しした方がいいかもしれない */
	for(id = 0; id < INT_MAX; ++id)
	{
		if(m_pModel2Ds.find(id) == m_pModel2Ds.end())
		{
			break;
		}
	}
	
	return id;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
