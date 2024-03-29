//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_BaggageAppear.h"
#include  "Task_Baggage.h"
#include  "Task_Stuff.h"
#include  "cstdlib"
#include  "Task_Player.h"
#include  <random>

namespace  BAppear
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
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
		this->timer = 0;
		//★タスクの生成

		return  true;
	}
	//-------------------------------------------------------------------
	//「終了」タスク消滅時に１回だけ行う処理
	bool  Object::Finalize()
	{
		//★データ＆タスク解放


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//★引き継ぎタスクの生成
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		auto p = ge->GetTask_One_GN<Player::Object>("プレイヤ", "仮");
		timer += p->speed / 2.0f;
		srand((unsigned int)time(NULL));
			
		if (timer >= 60) {
			//auto p = ge->GetTask_Group_G<Player::Object>("プレイヤ");
			auto b = Baggage::Object::Create(true);
			//auto s = Stuff::Object::Create(true);
			random_device rn;
			mt19937_64 rnd(rn());
			uniform_int_distribution<unsigned int> range(1, 4);
			switch (rand() % 7) {
			case 0:
				//s->category = Normal;
				b->category = Normal;
				b->categNum = range(rnd);
				break;
			case 1:
				//s->category = Transfer;
				b->category = Transfer;
				b->categNum = range(rnd);
				break;
			case 2:
				//s->category = Hydro;
				b->category = Hydro;
				b->categNum = range(rnd);
				break;
			case 3:
				//s->category = Explosive;
				b->category = Explosive;
				b->categNum = range(rnd);
				break;
			case 4:
				//s->category = Weapon;
				b->category = Weapon;
				b->categNum = range(rnd);
				break;
			case 5:
				//s->category = Drug;
				b->category = Drug;
				b->categNum = range(rnd);
				break;
			case 6:
				//s->category = Overvalue;
				b->category = Overvalue;
				b->categNum = range(rnd);
				b->id = rand();
				break;
			}
			//auto it = p->begin();
			b->pos = ML::Vec2(0, 200);
			//s->pos = ML::Vec2(0, 200);
			//b->moveVec = ML::Vec2(10, 0);
			b->moveVec.x = this->getMoveSpeed();
			//s->moveVec = ML::Vec2(1, 0);
			timer = 0;
		}
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
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