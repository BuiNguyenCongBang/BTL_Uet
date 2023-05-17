#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "iostream"

BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;

	y = 0;

	x_mouse = 0;
	y_mouse = 0;

	is_move_ = 0;

	hit_target_ = false;
	hited_target_ = false;

}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(ThreatObject threat_[], int threat_size, ThreatObject2 threat2_[], int threat2_size)
{
	//std::cout << x_mouse << " " << y_mouse << "     ";
	rect_.x += x_val_;
	float cnt = 1.0 * x_val_ * (y_mouse - 295) / (x_mouse - 205);
	y += cnt;
	//rect_.y += cnt;
	rect_.y = round(y);
	//std::cout << rect_.x << " " << rect_.y << " " << cnt << " " << y << std::endl;

	for (int i = 0; i < threat_size; i++)
	{
		int x_threat = threat_[i].GetRect().x;
		int y_threat = threat_[i].GetRect().y;

		if (rect_.x > SCREEN_WIDTH || rect_.y > SCREEN_HEIGHT)
		{
			is_move_ = false;
		}

		if (rect_.x >= x_threat && x_threat + 64 >= rect_.x && rect_.y >= y_threat && y_threat + 64 >= rect_.y && threat_[i].get_hp() > 0)
		{
			is_move_ = false;
			hit_target_ = true;
			if (supper_ == 0 && hited_target_ == false)
			{
				threat_[i].set_get_shot(true);
				hited_target_ = true;
			}
			else if (supper_ == 1 && hited_target_ == false)
			{
				threat_[i].set_get_supper_shot(true);
				hited_target_ = true;
			}
		}

		if (threat_[i].get_increase_hp() == 1 && threat_[i].get_can_show_heart() == true)
		{
			if (rect_.x >= x_threat && x_threat + 64 >= rect_.x && rect_.y >= y_threat && y_threat + 64 >= rect_.y)
			{
				get_heart = 1;
				threat_[i].set_can_show_heart(false);
				is_move_ = false;
			}
		}
	}


	for (int i = 0; i < threat2_size; i++)
	{
		int x_threat = threat2_[i].GetRect().x;
		int y_threat = threat2_[i].GetRect().y;

		if (rect_.x >= x_threat && x_threat + 64 >= rect_.x && rect_.y >= y_threat && y_threat + 60 >= rect_.y && threat2_[i].get_hp() > 0)
		{
			std::cout << " yes" << std::endl;
			is_move_ = false;
			hit_target_ = true;
			if (supper_ == 0 && hited_target_ == false)
			{
				threat2_[i].set_get_shot(true);
				hited_target_ = true;
			}
			else if (supper_ == 1 && hited_target_ == false)
			{
				threat2_[i].set_get_supper_shot(true);
				hited_target_ = true;
			}
		}

		if (threat2_[i].get_increase_hp() == 1 && threat2_[i].get_can_show_heart() == true)
		{
			if (rect_.x >= x_threat && x_threat + 64 >= rect_.x && rect_.y >= y_threat && y_threat + 64 >= rect_.y)
			{
				get_heart = 1;
				threat2_[i].set_can_show_heart(false);
				is_move_ = false;
			}
		}
	}

}

void BulletObject::HandleMoveThreat()
{

}
