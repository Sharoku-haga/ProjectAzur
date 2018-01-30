//==================================================================================================================================//
//!< @file		paBehaviorFactory.h
//!< @brief		pa::BehaviorFactoryクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

#ifndef PA_BEHAVIOR_FACTORY_H
#define PA_BEHAVIOR_FACTORY_H

#include <string>
#include <map>
#include "paBehaviorBase.h"

namespace pa
{

//===================================================================================//
//!< Behaviorを管理するFactoryクラス 
//===================================================================================//
class BehaviorFactory
{

public:
	/** Constructor */
	BehaviorFactory();

	/** Destructor */
	~BehaviorFactory();

	/** 初期化関数 */
	void Initialize();

	/**
	* 指定したBehaviorBaseのインスタンスのポインタを取得する関数
	* @param[in] rName 取得したいBehaviorBaseの名前
	* @return  指定したBehaviorBaseのインスタンスのポインタ
	*/
	BehaviorBase* GetBehavior(const std::string& rName);

	/** 破棄関数 */
	void Finalize();

private:
	std::map<std::string, BehaviorBase*>	m_pBehavior;		//!< BehaviorBaseのインスタンスのポインタを格納したmap

};	// class BehaviorFactory

}	// namespace pa

#endif // PA_BEHAVIOR_FACTORY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
