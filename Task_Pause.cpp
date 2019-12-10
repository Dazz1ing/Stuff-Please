//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Pause.h"

namespace  Pause
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//¥ê¥½¡¼¥¹¤Î½é´ü²½
	bool  Resource::Initialize()
	{
		this->img = DG::Image::Create("./data/image/pause.jpg");
		return true;
	}
	//-------------------------------------------------------------------
	//¥ê¥½¡¼¥¹¤Î²òÊü
	bool  Resource::Finalize()
	{
		this->img.reset();
		return true;
	}
	//-------------------------------------------------------------------
	//¡Ö½é´ü²½¡×¥¿¥¹¥¯À¸À®»þ¤Ë£±²ó¤À¤±¹Ô¤¦½èÍý
	bool  Object::Initialize()
	{
		//¥¹¡¼¥Ñ¡¼¥¯¥é¥¹½é´ü²½
		__super::Initialize(defGroupName, defName, true);
		//¥ê¥½¡¼¥¹¥¯¥é¥¹À¸À®or¥ê¥½¡¼¥¹¶¦Í­
		this->res = Resource::Create();

		//¡ú¥Ç¡¼¥¿½é´ü²½
		this->render2D_Priority[1] = 0.05f;
		//¡ú¥¿¥¹¥¯¤ÎÀ¸À®

		return  true;
	}
	//-------------------------------------------------------------------
	//¡Ö½ªÎ»¡×¥¿¥¹¥¯¾ÃÌÇ»þ¤Ë£±²ó¤À¤±¹Ô¤¦½èÍý
	bool  Object::Finalize()
	{
		//¡ú¥Ç¡¼¥¿¡õ¥¿¥¹¥¯²òÊü


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//¡ú°ú¤­·Ñ¤®¥¿¥¹¥¯¤ÎÀ¸À®
			
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//¡Ö¹¹¿·¡×£±¥Õ¥ì¡¼¥àËè¤Ë¹Ô¤¦½èÍý
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState();

		if (inp.SE.down) {
			//¼«¿È¤Ë¾ÃÌÇÍ×ÀÁ
			this->Kill();
		}
	}
	//-------------------------------------------------------------------
	//¡Ö£²£ÄÉÁ²è¡×£±¥Õ¥ì¡¼¥àËè¤Ë¹Ô¤¦½èÍý
	void  Object::Render2D_AF()
	{
		ML::Box2D draw(0, 0, ge->screenWidth, ge->screenHeight);
		ML::Box2D src(0, 0, 700, 394);
		res->img->Draw(draw, src);
	}

	//¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú
	//°Ê²¼¤Ï´ðËÜÅª¤ËÊÑ¹¹ÉÔÍ×¤Ê¥á¥½¥Ã¥É
	//¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú¡ú
	//-------------------------------------------------------------------
	//¥¿¥¹¥¯À¸À®Áë¸ý
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//¥²¡¼¥à¥¨¥ó¥¸¥ó¤ËÅÐÏ¿
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//¥¤¥Ë¥·¥ã¥é¥¤¥º¤Ë¼ºÇÔ¤·¤¿¤éKill
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
	//¥ê¥½¡¼¥¹¥¯¥é¥¹¤ÎÀ¸À®
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