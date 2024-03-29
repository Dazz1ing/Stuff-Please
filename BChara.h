#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//キャラクタ汎用スーパークラス
//-----------------------------------------------------------------------------
#include "GameEngine_Ver3_81.h"

class BChara : public BTask
{
	//変更不可◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
public:
	typedef shared_ptr<BChara>		SP;
	typedef weak_ptr<BChara>		WP;
public:
	//変更可◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇
	//キャラクタ共通メンバ変数
	ML::Vec2    pos;		//キャラクタ位置
	ML::Box2D   hitBase;	//あたり判定範囲
	ML::Vec2	moveVec;	//移動ベクトル
	int			moveCnt;	//行動カウンタ
	ML::Vec2	selectZone;
	ML::Vec2	mpos;
	ML::Vec2	raypos;

	enum Category
	{
		Normal,
		Transfer,
		Explosive,
		Hydro,
		Weapon,
		Drug,
		Overvalue
	};
	enum Route 
	{
		Straight,
		Up,
		Down,
		Dog,
		Customs,
		Trans
	};
	Category	category;
	Category	selectCat;
	int			categNum;
	Route		route;
	int			shape;
	bool		focus;
	bool		xRay;
	int			id;
	/*enum Angle_LR { Left, Right };
	Angle_LR	angle_LR;
	WP			target;
	//キャラクタの行動状態フラグ
	enum Motion
	{
		Unnon = -1,	//	無効(使えません）
		Stand,		//	停止
		Walk,		//	歩行
		Attack,		//	攻撃
		Jump,		//	ジャンプ
		Fall,		//	落下
		TakeOff,	//	飛び立つ瞬間
		Landing,	//	着地
	};
	Motion			motion;			//	現在の行動を示すフラグ
	int				animCnt;		//アニメーションカウンタ
	float			jumpPow;		//	ジャンプ初速
	float			maxFallSpeed;	//	落下最大速度
	float			gravity;		//	フレーム単位の加算量
	float			maxSpeed;		//	左右方向への移動の加算量
	float			addSpeed;		//	左右方向への移動の加算量
	float			decSpeed;		//	左右方向への移動の減衰量

	*/

	//メンバ変数に最低限の初期化を行う
	//★★メンバ変数を追加したら必ず初期化も追加する事★★
	BChara()
		: pos(0, 0)
		, hitBase(0, 0, 0, 0)
		, moveVec(0, 0)
		, moveCnt(0)
		, category(Normal)
		, selectCat(Normal)
		, route(Straight)
		, shape(0)
		, focus(0)
		, xRay(0)
		, id(0)
		, raypos(0,0)
	{
	}
	virtual  ~BChara() {}

	//キャラクタ共通メソッド
	//めり込まない移動処理
	virtual  bool  CheckRes();
	virtual  bool  CheckNormal();
	virtual  bool  CheckDogDrug();
	virtual  void  IncreMoney(Category cat);
	virtual  void  ChangeRoute(Route r);
	virtual  void  PatrolDog();
	virtual  void  Tax();
	virtual  void  Focus();
	virtual  void  XRay();
	virtual  int   getMoveSpeed();
	
	//bool  UpdateMotion(Motion  nm_);

	//	アニメーション情報構造体
	struct DrawInfo {
		ML::Box2D		draw, src;
		ML::Color		color;
	};
};
