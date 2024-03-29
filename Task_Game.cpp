//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
#include  "Task_Ending.h"
#include  "Task_Player.h"
#include  "Task_Sprite.h"
#include  "Task_BaggageAppear.h"
#include  "Task_XRay.h"
#include  "Task_IDList.h"
#include  "Task_Baggage.h"
#include  "Task_Belt.h"
#include  "Task_Pause.h"
#include  "Task_TimeOver.h"
#include  "time.h"

namespace  Game
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		this->tile = DG::Image::Create("./data/image/tile.png");
		this->ray = DG::Image::Create("./data/image/ray.jpg");
		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
		this->tile.reset();
		this->ray.reset();
		return true;
	}
	//-------------------------------------------------------------------
	//「初期化」タスク生成時に１回だけ行う処理
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName, defName, true);
		//リソースクラス生成orリソース共有
		this->res = Resource::Create();

		//★データ初期化
		this->timer = 5;
		this->timer *= 1000;
		this->render2D_Priority[1] = 0.9f;
		this->pause = false;
		this->sTime = clock();

	   //★タスクの生成
		auto b = BAppear::Object::Create(true);
		auto belt = Belt::Object::Create(true);
	   //マップの生成
		
		//プレイヤの生成
		auto  pl = Player::Object::Create(true);
		auto x = XRay::Object::Create(true);
		//妖精の生成
		//auto  spr = Sprite::Object::Create(true);
		//spr->pos = pl->pos;
		

		return  true;
	}
	//-------------------------------------------------------------------
	//「終了」タスク消滅時に１回だけ行う処理
	bool  Object::Finalize()
	{
		//★データ＆タスク解放
		ge->KillAll_G("フィールド");
		ge->KillAll_G("プレイヤ");
		ge->KillAll_G("Baggage");
		ge->KillAll_G("XRay");
		ge->KillAll_G("Belt");
		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//★引き継ぎタスクの生成
		}
		return  true;
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		this->eTime = clock();
		auto inp = ge->in1->GetState();
		if (this->eTime - this->sTime >= this->timer) {
			ge->StopAll_G("Baggage");
			ge->StopAll_G("Belt");
			ge->StopAll_G("Dog");
			auto t = TimeOver::Object::Create(true);
		}
		if (inp.ST.down) {
			//自身に消滅要請
			this->Kill();
		}

		if (inp.B2.down) {
			auto id = IDList::Object::Create(true);
		}

		if (inp.SE.down) {
			if (!this->pause) {
				ge->StopAll_G("Baggage");
				ge->StopAll_G("Belt");
				ge->StopAll_G("Dog");
				auto p = Pause::Object::Create(true);
				this->pause = true;
			}
			else {
				ge->StopAll_G("Baggage",false);
				ge->StopAll_G("Belt",false);
				ge->StopAll_G("Dog",false);
				this->pause = false;
			}
		}
		
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
		ML::Box2D draw(0, 0, 64, 64);
		ML::Box2D src(0, 0, 32, 32);
		ML::Box2D bdraw(0, 170, 80, 50);
		ML::Box2D bsrc(0, 0, 1200, 750);
		//stringstream s;
		//s << "./data/image/belt/beltframe" << this->time % 5 << ".png";
		//this->res->belt->ReLoad(s.str());
		int i = 0;
		for (i; i < ge->screenHeight / 2; i += 32) {
			draw.y = i;
			for (int j = 0; j <= ge->screenWidth; j += 32) {
				draw.x = j;
				this->res->tile->Draw(draw, src);
			}
		}
		//for (int b = 0; b <= ge->screenWidth; b += 50) {
		//	this->res->belt->Draw(bdraw, bsrc);
		//	bdraw.x = b;
		//}
		
		
		draw = ML::Box2D(0, i, ge->screenWidth, ge->screen2DHeight);
		src = ML::Box2D(0, 0, 1280, 720);
		this->res->ray->Draw(draw, src);
	}

	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//以下は基本的に変更不要なメソッド
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//-------------------------------------------------------------------
	//タスク生成窓口
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ゲームエンジンに登録
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//イニシャライズに失敗したらKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//リソースクラスの生成
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}