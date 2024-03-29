//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Baggage.h"
#include  "Task_Player.h"
#include  <random>
#include  "Task_XRay.h"
#include  <math.h>

namespace  Baggage
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		this->bagImg = DG::Image::Create("./data/image/bag1.png");
		this->bagImgRay = DG::Image::Create("./data/image/bag_ray1.png");

		this->weap1 = DG::Image::Create("./data/image/weapon/pistol.png");
		this->weap2 = DG::Image::Create("./data/image/weapon/militaryknife.png");
		this->weap3 = DG::Image::Create("./data/image/weapon/katana.png");
		this->weap4 = DG::Image::Create("./data/image/weapon/golf.png");
		
		this->lock1 = DG::Image::Create("./data/image/customs/lock1.png");
		this->lock2 = DG::Image::Create("./data/image/customs/lock2.png");
		this->lock3 = DG::Image::Create("./data/image/customs/lock3.png");
		this->lock4 = DG::Image::Create("./data/image/customs/lock4.png");
		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
		this->bagImg.reset();
		this->bagImgRay.reset();

		this->weap1.reset();
		this->weap2.reset();
		this->weap3.reset();
		this->weap4.reset();

		this->lock1.reset();
		this->lock2.reset();
		this->lock3.reset();
		this->lock4.reset();
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
	
		this->controller = ge->in1;
		this->render2D_Priority[1] = 0.3f;
		this->pos = ML::Vec2(0, 0);
		this->mpos = ML::Vec2(0, 0);
		this->hitBase = ML::Box2D(-30, -20, 60, 40);
		this->moveVec = ML::Vec2(5, 0);
		this->s_id = rand() % 4 + 1;
		this->raypos.x = -500;
		this->raypos.y = 300;
		
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
		this->moveVec.x = this->getMoveSpeed();
		pos += this->moveVec;
		auto  in2 = this->controller->GetState();
		auto  kbd = ge->in1->GetState();
		if (ge->mouse) {
			auto inp = ge->mouse->GetState();
			
			if (inp.LB.down) {
				
				this->mpos.x = inp.pos.x;
				this->mpos.y = inp.pos.y;
				if (this->mpos.x >= (this->pos.x-this->hitBase.w/2)&& this->mpos.x <= (this->pos.x+(this->hitBase.w/2))
				&& this->mpos.y >= this->pos.y-this->hitBase.h/2&& this->mpos.y <= this->pos.y+(this->hitBase.h/2)) {
					this->focus = true;
				}
				else
				{
					this->focus = false;
				}

				
			}
			/*if (kbd.B1.on) {
				this->moveVec = ML::Vec2(1, 0);
				ML::Box2D me = this->hitBase.OffsetCopy(this->pos);
				ML::Box2D ray(-100, -75, 200, 150);
				ray.Offset(inp.pos.x, inp.pos.y);
				if (ray.Hit(me)) {
					this->xRay = true;
				}
				else {
					this->xRay = false;
				}
			}
			else {
				this->moveVec = ML::Vec2(10, 0);
			}*/
			
		}

		auto ray = ge->GetTask_One_G<XRay::Object>("XRay");
		ML::Box2D me = this->hitBase.OffsetCopy(this->pos);
		ML::Box2D xray = ray->hitbase;
		xray.Offset(ray->x, ray->y);
		if (xray.Hit(me)) {
			this->xRay = true;
			this->raypos += this->moveVec*2.5f;
		}
		else {
			this->xRay = false;
		}

		if (this->focus) {
			if (in2.LStick.U.down)	this->ChangeRoute(Up);
			if (in2.LStick.D.down)	this->ChangeRoute(Down);
			if (in2.LStick.R.down)	this->ChangeRoute(Straight);
			
		}
		if (this->pos.x > 480) {
			if (this->CheckNormal())	this->IncreMoney(this->category);

		}
		/*if (this->pos.x >= 400) {
			switch (this->route) {
			case Up:
				this->moveVec = ML::Vec2(0, -10);
				break;
			case Down:
				this->moveVec = ML::Vec2(0, 10);
				break;
			case Straight:
				this->moveVec = ML::Vec2(10, 0);
				break;
			default:
				break;
			}
		}*/
		if (this->pos.x > ge->screenWidth)
			this->Kill();
		
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{

		ML::Box2D draw(-30, -20, 60, 40);
		draw.Offset(this->pos.x, this->pos.y);
		ML::Box2D src(0, 0, 192, 130);
		if (this->xRay == true) {
			draw.h *= 5;
			draw.w *= 5;
			draw.Offset(this->raypos.x, this->raypos.y);
			this->res->bagImgRay->Draw(draw, src);
			switch (this->category) {
			case Normal:
				break;
			case Weapon:
				
				ML::Box2D src(0,0,500,500);
				switch (this->categNum) {
				case 1:
					this->res->weap1->Draw(draw, src);
					break;
				case 2:
					this->res->weap2->Draw(draw, src);
					break;
				case 3:
					this->res->weap3->Draw(draw, src);
					break;
				case 4:
					this->res->weap4->Draw(draw, src);
					break;
				}
				break;
			/*case Hydro:
				break;
			case Transfer:
				break;
			case Explosive:
				break;
			case Drug:
				break;*/
			}
		}
		else {
			this->res->bagImg->Draw(draw, src);
			if (this->category == Overvalue) {
				random_device rn;
				mt19937_64 rnd(rn());
				uniform_int_distribution<unsigned int> range(1, 4);
				ML::Box2D src(0, 0, 250, 250);
				switch (this->categNum) {
				case 1:
					this->res->lock1->Draw(draw, src);
					break;
				case 2:
					this->res->lock2->Draw(draw, src);
					break;
				case 3:
					this->res->lock3->Draw(draw, src);
					break;
				case 4:
					this->res->lock4->Draw(draw, src);
					break;
				}
			}
		}
		
		
	}

	void Object::bagAngle() {
		random_device rn;
		mt19937_64 rnd(rn());
		uniform_int_distribution<unsigned int> range(1, 4);

	}

	unsigned int getID()
	{
		random_device rn;
		mt19937_64 rnd(rn());
		uniform_int_distribution<unsigned int> range(1, 65535);
		return range(rnd);
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