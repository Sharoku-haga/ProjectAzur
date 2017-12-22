//==================================================================================================================================//
//!< @file		paEventListener.h
//!< @brief		pa::EventListenerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/21	更新履歴：2017/12/21
//==================================================================================================================================//

#ifndef PA_EVENT_LISTENER_H
#define PA_EVENT_LISTENER_H

#include <map>
#include <deque>
#include <string>
#include <functional>

namespace pa
{

//===================================================================================//
//!< イベントマネージャーからイベントを受け取り、
//!< そのイベントを別クラスに通知するクラス
//!< また同期イベントが通知された際は
//!< 登録されたイベント関数で処理を行う
//===================================================================================//
class EventListener final
{

public:
	/** Constructor */
	EventListener() = default;

	/** Destructor */
	~EventListener() = default;

	/**
	* 同期イベントの処理に使用する関数を登録する関数
	* @param[in] rEventName					イベント名
	* @param[in] rCallBackFunc				イベントの際によびだすコールバック関数
	*/
	void RegisterSynEventFunc(const std::string& rEventName, const std::function<void(void)>& rCallBackFunc);
	
	/** 
	* 登録している同期イベントの処理関数を呼び出す関数
	* @param[in] rEventName		処理を行うイベント名
	*/
	void CallSynEventFunc(const std::string& rEventName);  

	/** 現在受けとっているイベントを全て削除する関数 */
	void DeleteCurrentEvent(); 

	/**
	* 受け取っているイベントが現在空なのか、もしくはあるのか確認する関数
	* @return 結果 true→空である false→空でない
	*/
	inline bool EmptyCurrentEvent() { return m_CurrentEvent.empty(); }

	/**
	* Getter
	* @return 現在イベントマネージャーから受け取っているイベントを格納したdeque
	*/
	inline const std::deque<std::string>& GetCurrentEvent() { return m_CurrentEvent; };

private:
	friend class EventManager;

	std::deque<std::string>									m_CurrentEvent;					//!< 現在ゲーム中で発生したイベントを格納しておくdeque
	std::map<std::string, std::function<void(void)>>		m_SynEventFunc;					//!< 同期イベント処理を格納しておくmap

	/** 
	* 現在発生しているイベントを受け取る関数。イベントマネージャーが呼び出す関数
	* @param[in] rEventName		現在発生しているイベント名
	*/
	void ReceiveEvent(const std::string& rEventName); 

};	// class EventListener

}	// namespace pa

#endif	// PA_EVENT_LISTENER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
