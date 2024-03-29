#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include "BChara.h"
#include "GameEngine_Ver3_81.h"

namespace  Stuff
{
	//タスクに割り当てるグループ名と固有名
	const  string  defGroupName("Stuff");	//グループ名
	const  string  defName("Stuff");		//タスク名
	//-------------------------------------------------------------------
	class  Resource
	{
		bool  Initialize();
		bool  Finalize();
		Resource();
	public:
		~Resource();
		typedef  shared_ptr<Resource>	SP;
		typedef  weak_ptr<Resource>		WP;
		static   WP  instance;
		static  Resource::SP  Create();
		//変更可◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇
			//共有する変数はここに追加する
		DG::Image::SP	tag1;
		DG::Image::SP	tag2;
		DG::Image::SP	tag3;
		DG::Image::SP	Explo1;
		DG::Image::SP	Explo2;
		DG::Image::SP	Explo3;
		DG::Image::SP	Explo4;
		DG::Image::SP	Explo5;
		DG::Image::SP	weap1;
		DG::Image::SP	weap2;
		DG::Image::SP	weap3;
		DG::Image::SP	weap4;
		//DG::Image::SP	weap2;

	};
	//-------------------------------------------------------------------
	class  Object : public  BChara
	{
	public:
		virtual  ~Object();
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//生成窓口 引数はtrueでタスクシステムへ自動登録
		static  Object::SP  Create(bool flagGameEnginePushBack_);
		Resource::SP	res;
	private:

		Object();
		bool  B_Initialize();
		bool  B_Finalize();
		bool  Initialize();	//「初期化」タスク生成時に１回だけ行う処理
		void  UpDate();		//「実行」１フレーム毎に行う処理
		void  Render2D_AF();	//「2D描画」１フレーム毎に行う処理
		bool  Finalize();		//「終了」タスク消滅時に１回だけ行う処理
	public:
		//変更可◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇
			//追加したい変数・メソッドはここに追加する
			//BCharaに含まれないモノのみここに追加する
		
	};
}