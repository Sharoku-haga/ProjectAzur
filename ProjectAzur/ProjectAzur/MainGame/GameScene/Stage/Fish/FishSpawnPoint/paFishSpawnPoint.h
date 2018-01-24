//==================================================================================================================================//
//!< @file		paFishSpawnPoint.h
//!< @brief		pa::FishSpawnPointクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/24	更新履歴：
//==================================================================================================================================//

#ifndef PA_FISH_SPAWN_POINT_H
#define PA_FISH_SPAWN_POINT_H

#include <vector>
#include <D3DX11.h>
#include <D3DX10.h>

namespace pa
{

//===================================================================================//
//!< 魚の出現ポイントクラス
//===================================================================================//
class FishSpawnPoint
{

public:
	/** Constructor */
	FishSpawnPoint();

	/** Destructor */
	~FishSpawnPoint() = default;

	/** 初期化関数 */
	void Initialize();

	/**
	* 更新関数 
	* 出現ポイントの座標を更新する
	*/
	void UpdatePoint();

	/**
	* Getter
	* @return 出現ポイントの座標
	*/
	D3DXVECTOR2& GetPointPos()
	{
		return m_PointPos[m_CurrentPointID];
	}

	/**
	* Getter
	* @return 現在のポイントID
	*/
	int GetCurrentPointID() { return m_CurrentPointID; }

private:
	std::vector<D3DXVECTOR2>		m_PointPos;				//!< ポイント座標群
	unsigned int					m_CurrentPointID;		//!< 現在のポイントID

};	// class FishSpawnPoint

}	// namespace pa

#endif	// PA_FISH_SPAWN_POINT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
