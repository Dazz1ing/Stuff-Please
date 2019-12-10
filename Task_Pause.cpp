//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Pause.h"

namespace  Pause
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//�꥽�����ν����
	bool  Resource::Initialize()
	{
		this->img = DG::Image::Create("./data/image/pause.jpg");
		return true;
	}
	//-------------------------------------------------------------------
	//�꥽�����β���
	bool  Resource::Finalize()
	{
		this->img.reset();
		return true;
	}
	//-------------------------------------------------------------------
	//�ֽ�����ץ������������ˣ�������Ԥ�����
	bool  Object::Initialize()
	{
		//�����ѡ����饹�����
		__super::Initialize(defGroupName, defName, true);
		//�꥽�������饹����or�꥽������ͭ
		this->res = Resource::Create();

		//���ǡ��������
		this->render2D_Priority[1] = 0.05f;
		//��������������

		return  true;
	}
	//-------------------------------------------------------------------
	//�ֽ�λ�ץ��������ǻ��ˣ�������Ԥ�����
	bool  Object::Finalize()
	{
		//���ǡ���������������


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//�������Ѥ�������������
			
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//�ֹ����ף��ե졼����˹Ԥ�����
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState();

		if (inp.SE.down) {
			//���Ȥ˾�������
			this->Kill();
		}
	}
	//-------------------------------------------------------------------
	//�֣�������ף��ե졼����˹Ԥ�����
	void  Object::Render2D_AF()
	{
		ML::Box2D draw(0, 0, ge->screenWidth, ge->screenHeight);
		ML::Box2D src(0, 0, 700, 394);
		res->img->Draw(draw, src);
	}

	//������������������������������������������������������������������������������������
	//�ʲ��ϴ���Ū���ѹ����פʥ᥽�å�
	//������������������������������������������������������������������������������������
	//-------------------------------------------------------------------
	//�������������
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//�����२�󥸥����Ͽ
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//���˥���饤���˼��Ԥ�����Kill
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
	//�꥽�������饹������
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