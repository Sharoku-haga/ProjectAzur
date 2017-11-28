//==================================================================================================================================//
//!< @file		paDrawingDataFile.h
//!< @brief		pa::DrawingDataFileクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/28	更新履歴：2017/11/29
//==================================================================================================================================//

#ifndef PA_DRAWING_DATA_FILE_H
#define PA_DRAWING_DATA_FILE_H

#include <string>
#include <map>
#include "sl/Library/Utility/slRect.h"
#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Singleton/slBasicSingleton.h"

namespace pa
{

//===================================================================================//
//!< 描画に関するデータ構造体
//===================================================================================//
struct DrawingData
{
	float		m_Width;		//!< 横の長さ
	float		m_Height;		//!< 高さ
	sl::fRect	m_UVRect;		//!< UV値(左上UV値と右下のUV値)
};	// struct DrawingData

//===================================================================================//
//!< ツールが作成する描画に関するデータファイルを管理するクラス 
//===================================================================================//
class DrawingDataFile final : public sl::BasicSingleton<DrawingDataFile>
{

public:
	/**
	* 初期化関数
	* @param[in] rFileDirectoryPath データファイルを格納しているディレクトリのパス
	*/
	void Initialize(const std::string& rFileDirectoryPath);

	/**
	* データファイルをロードする関数
	* @param[in] rFileName データファイル名
	* @return 結果 true→成功 false→失敗
	*/
	bool LoadDataFile(const std::string& rFileName);

	/**
	* DrawingDataを取得する関数
	* @param[in] rFileName		ファイル名
	* @param[in] id				データのID
	* @return 指定したDrawingDataの参照
	*/
	inline DrawingData& GetDrawingData(const std::string& rFileName, int id)
	{
		return m_DrawingDatas[rFileName][id];
	}

	/**
	* ロードしているデータを指定して解放する関数
	* @param[in] rFileName 解放したいデータのファイル名
	*/
	void ReleaseData(const std::string& rFileName);

	/** 現在ロードしているデータを全て解放する関数 */
	void ReleaseDataALL();

private:
	friend class sl::StaticCreation<DrawingDataFile>;

	std::string											m_FileDirectoryPath;		//!< データファイルを格納しているディレクトリのパス
	std::map< std::string, std::map<int, DrawingData> > m_DrawingDatas;			//!< DrawingDataを格納しているmap.intはID

	/** Contructor */
	DrawingDataFile() = default;

	/** Destructor */
	~DrawingDataFile() = default;

	SL_DISALLOW_COPY_AND_ASSIGN(DrawingDataFile);

};	// class DrawingDataFile

}	// namespace pa

#endif // PA_DRAWING_DATA_FILE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
