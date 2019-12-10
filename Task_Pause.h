#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include "GameEngine_Ver3_81.h"

namespace  Pause
{
	//�������˳�����Ƥ륰�롼��̾�ȸ�ͭ̾
	const  string  defGroupName("Pause");	//���롼��̾
	const  string  defName("Pause");	//������̾
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
		//��ͭ�����ѿ��Ϥ������ɲä���
		DG::Image::SP	img;
	};
	//-------------------------------------------------------------------
	class  Object : public  BTask
	{
		//�ѹ��ԲĢ���������������������������������������������������
	public:
		virtual  ~Object();
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//������� ������true�ǥ����������ƥ�ؼ�ư��Ͽ
		static  Object::SP  Create(bool flagGameEnginePushBack_);
		Resource::SP	res;
	private:
		Object();
		bool  B_Initialize();
		bool  B_Finalize();
		bool  Initialize();	//�ֽ�����ץ������������ˣ�������Ԥ�����
		void  UpDate();		//�ּ¹ԡף��ե졼����˹Ԥ�����
		void  Render2D_AF();	//��2D����ף��ե졼����˹Ԥ�����
		bool  Finalize();		//�ֽ�λ�ץ��������ǻ��ˣ�������Ԥ�����
	//�ѹ��ġ�����������������������������������������������������
	public:
		//�ɲä������ѿ����᥽�åɤϤ������ɲä���

	};
}