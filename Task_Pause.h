#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include "GameEngine_Ver3_81.h"

namespace  Pause
{
	//
	const  string  defGroupName("Pause");
	const  string  defName("Pause");
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
		
		DG::Image::SP	img;
	};
	//-------------------------------------------------------------------
	class  Object : public  BTask
	{
		
	public:
		virtual  ~Object();
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		
		static  Object::SP  Create(bool flagGameEnginePushBack_);
		Resource::SP	res;
	private:
		Object();
		bool  B_Initialize();
		bool  B_Finalize();
		bool  Initialize();
		void  UpDate();
		void  Render2D_AF();
		bool  Finalize();
	
	public:

	};
}