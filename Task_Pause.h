#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include "GameEngine_Ver3_81.h"

namespace  Pause
{
	//?Ⅹ?ㅛ념ㅺ툭ㅖㅻⅠλ【Ψ潔ㅘ맨階潔
	const  string  defGroupName("Pause");	//Ⅰλ【Ψ潔
	const  string  defName("Pause");	//?Ⅹ?潔
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
		//땋階ㅉㅻ揀웃ㅟㅃㅃㅛ케꼴ㅉㅻ
		DG::Image::SP	img;
	};
	//-------------------------------------------------------------------
	class  Object : public  BTask
	{
		//揀뭐꼼⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒⇒
	public:
		virtual  ~Object();
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//으윙쥰뫙 과웃ㅟtrueㅗ?Ⅹ?ⅧⅩΖ?ㅨ섐튼털臼
		static  Object::SP  Create(bool flagGameEnginePushBack_);
		Resource::SP	res;
	private:
		Object();
		bool  B_Initialize();
		bool  B_Finalize();
		bool  Initialize();	//≒썽덟꼍§?Ⅹ?으윙샤ㅛ１뀨ㅐㅁ밋ㄶ썼果
		void  UpDate();		//≒셋밋§１Φμ【?遽ㅛ밋ㄶ썼果
		void  Render2D_AF();	//≒2D꿱§１Φμ【?遽ㅛ밋ㄶ썼果
		bool  Finalize();		//≒쉠貫§?Ⅹ?씹鎌샤ㅛ１뀨ㅐㅁ밋ㄶ썼果
	//揀뭐꼼￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢￢
	public:
		//케꼴ㅇㅏㄴ揀웃…α?ΓΙㅟㅃㅃㅛ케꼴ㅉㅻ

	};
}