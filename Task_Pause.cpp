//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Pause.h"

namespace  Pause
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソ?スの初期化
	bool  Resource::Initialize()
	{
		this->img = DG::Image::Create("./data/image/pause.jpg");
		return true;
	}
	//-------------------------------------------------------------------
	//リソ?スの解放
	bool  Resource::Finalize()
	{
		this->img.reset();
		return true;
	}
	//-------------------------------------------------------------------
	//「初期化」タスク生成時に１回だけ行う?理
	bool  Object::Initialize()
	{
		//Ⅹ【Ρ【?ιⅩ썽덟꼍
		__super::Initialize(defGroupName, defName, true);
		//κ?【Ⅹ?ιⅩ으윙orκ?【Ⅹ땋階
		this->res = Resource::Create();

		//∪Η【?썽덟꼍
		this->render2D_Priority[1] = 0.05f;
		//∪?Ⅹ?ㅞ으윙

		return  true;
	}
	//-------------------------------------------------------------------
	//≒쉠貫§?Ⅹ?씹鎌샤ㅛ１뀨ㅐㅁ밋ㄶ썼果
	bool  Object::Finalize()
	{
		//∪Η【?∋?Ⅹ?뀝鑑


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//∪과ㄽ롤ㄾ?Ⅹ?ㅞ으윙
			
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//≒뭐옆§１Φμ【?遽ㅛ밋ㄶ썼果
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState();

		if (inp.SE.down) {
			//섐옴ㅛ씹鎌斛읒
			this->Kill();
		}
	}
	//-------------------------------------------------------------------
	//≒２Ｄ꿱§１Φμ【?遽ㅛ밋ㄶ썼果
	void  Object::Render2D_AF()
	{
		ML::Box2D draw(0, 0, ge->screenWidth, ge->screenHeight);
		ML::Box2D src(0, 0, 700, 394);
		res->img->Draw(draw, src);
	}

	//∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪
	//걺꼈ㅟ댑居큭ㅛ揀뭐斛ㅚα?ΓΙ
	//∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪∪
	//-------------------------------------------------------------------
	//?Ⅹ?으윙쥰뫙
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//Ⅲ【?ⅷτⅨτㅛ털臼
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//ⅳΛⅧγιⅳ?ㅛ성함ㅇㅏㅹKill
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
	//κ?【Ⅹ?ιⅩㅞ으윙
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