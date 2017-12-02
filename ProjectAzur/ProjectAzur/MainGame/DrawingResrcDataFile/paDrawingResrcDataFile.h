//==================================================================================================================================//
//!< @file		paDrawingResrcDataFile.h
//!< @brief		pa::DrawingResrcDataFileクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/28	更新履歴：2017/11/29
//==================================================================================================================================//

#ifndef PA_DRAWING_DATA_FILE_H
#define PA_DRAWING_DATA_FILE_H

#include <string>
#include <map>
#include "sl/Library/Utility/slRect.h"
#include "sl/Library/Utility/slDefine.h"
#include <sl/Library/Singleton/slBasicSingleton.h>

namespace pa
{

//===================================================================================//
//!< 描画に関するリソースデータ構造体
//===================================================================================//
struct DrawingResrcData
{
	float		m_Width;		//!< 横の長さ
	float		m_Height;		//!< 高さ
	sl::fRect	m_UVRect;		//!< UV値(左上UV値と右下のUV値)
};	// struct DrawingResrcData

//===================================================================================//
//!< ツールが作成する描画に関するリソースデータファイルを管理するクラス 
//===================================================================================//
class DrawingResrcDataFile final : public sl::BasicSingleton<DrawingResrcDataFile>
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
	* DrawingResrcDataを取得する関数
	* @param[in] rFileName		ファイル名
	* @param[in] id				データのID
	* @return 指定したDrawingResrcDataの参照
	*/
	inline DrawingResrcData& GetDrawingData(const std::string& rFileName, int id)
	{
		return m_DrawingResrcDatas[rFileName][id];
	}

	/**
	* ロードしているデータを指定して解放する関数
	* @param[in] rFileName 解放したいデータのファイル名
	*/
	void ReleaseData(const std::string& rFileName);

	/** 現在ロードしているデータを全て解放する関数 */
	void ReleaseDataALL();

private:
	friend class sl::StaticCreation<DrawingResrcDataFile>;

	std::string														m_FileDirectoryPath;			//!< データファイルを格納しているディレクトリのパス
	std::map< std::string, std::map<int, DrawingResrcData> >		m_DrawingResrcDatas;			//!< DrawingDataを格納しているmap.intはID

	/** Contructor */
	DrawingResrcDataFile() = default;

	/** Destructor */
	~DrawingResrcDataFile() = default;

	SL_DISALLOW_COPY_AND_ASSIGN(DrawingResrcDataFile);

};	// class DrawingResrcDataFile

}	// namespace pa

#endif // PA_DRAWING_DATA_FILE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
