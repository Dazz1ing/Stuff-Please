//-----------------------------------------------------------------------------
//キャラクタ汎用スーパークラス
//-----------------------------------------------------------------------------
#include "BChara.h"
#include  "MyPG.h"
#include  "Task_Game.h"
#include  "Task_Player.h"

bool BChara::CheckRes() {
	switch (this->category) {
	case Normal:
		if (this->route == Straight) {
			return true;
		}
		break;
	case Transfer:
		if (this->route == Trans)
			return true;
		break;
	case Explosive:
		break;
	case Hydro:
		break;
	case Weapon:
		break;
	case Drug:
		if (this->route == Dog)
			return true;
		break;
	case Overvalue:
		if (this->route == Customs)
			return true;
		break;
	}
	return false;
}


void  BChara::ChangeRoute(Route r) {
	this->route = r;
}

void  BChara::Focus() {

}
void  BChara::XRay() {

}
bool  BChara::CheckDogDrug()
{

	return 0;
}
void  BChara::IncreMoney(Category cat)
{
	auto p = Player::Object::Create(true);
	switch (cat) {
		
	}
}
bool  BChara::CheckNormal()
{
	if (this->category != Normal)
		return false;
	else
		return true;
}

void  BChara::PatrolDog()
{

}

void  BChara::Tax()
{

}

int  BChara::getMoveSpeed() 
{
	auto p = ge->GetTask_One_GN<Player::Object>("プレイヤ", "仮");
	if (ge->mouse) {
		auto inp = ge->mouse->GetState();
		if (inp.wheel > 0)
			p->speed += 0.25f;
		else if (inp.wheel < 0)
			p->speed -= 0.25f;
	}
	if (p->speed > 10)
		p->speed = 10.0f;
	if (p->speed < -10)
		p->speed = -10.0f;
	return p->speed;
}