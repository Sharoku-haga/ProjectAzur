//==================================================================================================================================//
//!< @file		slDXModel2DStorage.h
//!< @brief		sl::DXModel2DStorageクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/02	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_MODEL_2D_STORAGE_H
#define SL_DX_MODEL_2D_STORAGE_H

#include <map>
#include "../../../Graphics/slGraphicsID.h"

namespace sl
{

class DXModel2D;

//===================================================================================//
//!< DirectXにおける2Dモデルを保管するクラス
//===================================================================================//
class DXModel2DStorage
{

public:
	/** Constructor */
	DXModel2DStorage();

	/** Destructor */
	~DXModel2DStorage();

	/**
	* 2Dモデルを加える関数
	* @param[in] pModel	2Dモデル	
	* @return モデルのID
	*/
	ModelID AddDXModel2D(DXModel2D* pModel);

	/**
	* 指定した2Dモデルを解放する関数
	* @param[in] rID	解放したい2DモデルのID
	*/
	void ReleaseDXModel2D(const ModelID& rID);

	/** 2Dモデルデータを全て解放する関数 */
	void ReleaseALL();

	/**
	* Getter
	* @param[in] rID 取得したい2DモデルのID
	* @return 引数で指定した2Dモデルのポインタ
	*/
	inline DXModel2D*const GetModel2DData(const ModelID& rID) 
	{ 
		return m_pModel2Ds[rID.m_Num];  
	}

private:
	std::map<int, DXModel2D*>		m_pModel2Ds;		//!< 2Dモデルデータを格納するmap
	int								m_IDNumCount;		//!< ID番号のカウント数

	/** 
	* 現在使用できるIDを検索する関数 
	* @return 使用できるID番号
	*/
	int SearchAvailableIDNum();

};	// class DXModel2DStorage

}	// namespace sl

#endif	// SL_DX_MODEL_2D_STORAGE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
