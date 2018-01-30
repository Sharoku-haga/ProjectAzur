//==================================================================================================================================//
//!< @file		paBehaviorBase.h		
//!< @brief		pa::BehaviorBaseクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

#ifndef PA_BEHAVIOR_BASE_H
#define PA_BEHAVIOR_BASE_H

#include <string>

namespace pa
{

struct FishParam;

//===================================================================================//
//!< 振る舞いのベースクラス
//===================================================================================//
class BehaviorBase
{

public:
	/** Constructor */
	BehaviorBase() = default;

	/** Destructor */
	virtual ~BehaviorBase() =default;

	/**
	* 更新関数
	* @param[out] rParam 魚のパラメータ
	* @return 振る舞いが完了したかどうか ture→完了した false→完了していない
	*/
	virtual bool Update(FishParam& rParam) = 0;

	/**
	* Getter
	* @retrun 振る舞いの名前
	*/
	const std::string& GetName()
	{
		return m_Name;
	}

protected:
	std::string	m_Name;		//!< 振る舞いの名前

};	// class BehaviorBase

}	// namespace pa

#endif // PA_BEHAVIOR_BASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
