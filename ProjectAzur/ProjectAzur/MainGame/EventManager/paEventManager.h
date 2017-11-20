//==================================================================================================================================//
//!< @file		paEventManager.h
//!< @brief		pa::EventManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/21	更新履歴：2017/11/22
//==================================================================================================================================//

#ifndef PA_EVENT_MANAGER_H
#define PA_EVENT_MANAGER_H

#include <string>
#include <map>
#include <list>
#include <deque>
#include "sl/Library/Singleton/slBasicSingleton.h"
#include "sl/Library/Utility/slDefine.h"

namespace pa
{

class EventListener;

//===================================================================================//
//!< イベントを管理するクラス
//===================================================================================//
class EventManager final : public sl::BasicSingleton<EventManager>
{

public:
	/**
	* 初期化関数
	* 登録しているイベント、及びそれに対応するリスナーのポインタを全て削除する
	*/
	void Initialize();

	/**
	* イベント処理更新関数
	* 毎フレームをよんで、イベントをチェック、処理する関数
	*/
	void Update();

	/*
	* イベントとそれに対応するリスナーを登録する関数
	* なおイベントが登録されていない場合は自動的に追加する
	* @param[in] rEventName		登録したいイベントor リスナーが登録したいイベントタイプ
	* @param[in] pListener		上記のイベントタイプに登録したいEventListenerクラスのインスタンスへのポインタ
	*/
	void RegisterEventListener(const std::string& rEventName, EventListener* pListener); 

	/*
	* 現在登録しているイベントを削除する関数
	* @param[in] rEventName 削除したいイベント名
	*/
	void DeleteEvent(const std::string& rEventName);

	/**
	* 現在登録しているイベント群から指定したリスナーを削除する関数
	* @param[in] rEventName		登録したいイベントor リスナーが登録したいイベントタイプ
	* @param[in] pListener		削除したいリスナー
	*/
	void DeleteEventListener(const std::string& rEventName, EventListener* pListener);
	
	/**
	* 同期的なイベントをLisnerに発信する関数
	* @param[in] rEventType 発信したいイベント名
	*/
	void TriggerSynEvent(const std::string& rEventName);  

	/**
	* ゲーム中で発生したイベントを受け取る関数
	* @param[in] rEventType 発生したイベント名
	*/
	void ReceiveEvent(const std::string& rEventName);  
   
private:
	friend class sl::StaticCreation<EventManager>;

	std::map<std::string, std::list<EventListener*>>	m_pEventListener;		//!< 登録している通常イベントとそれに対応するリスナーのポインタmap
	std::deque<std::string>								m_CurrentEvent;			//!< 現在ゲーム中で発生したイベントを格納しておくdeque

	/** Constructor */
	EventManager() = default;

	/** Destructor */
	~EventManager() = default;

	SL_DISALLOW_COPY_AND_ASSIGN(EventManager);

};	// class EventManager

}	// namespace pa

#endif	//PA_EVENT_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
