#include "ThreatObject2.h"
#include "BaseObject.h"
#include <iostream>
#include <cstdlib>

ThreatObject2::ThreatObject2()
{
	frame_ = 1;
	x_val_ = 0;
	y_val_ = 0;
	move_ = 1;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	come_back_time = 0;
	rect_.x = SCREEN_WIDTH - 50;
	hp = 20;
	get_shot = false;
	get_supper_shot = false;
	type_img = 0;
	x_bullet = 590;
	y_bullet = 0;
	success_attack = false;
	get_supper_shot = false;
	get_sound_ = false;
	sound_ = true;

	get_point2 = false;

	increase_hp = 0;
	can_show_heart = true;
	number_random_increase_hp = rand() % 15 + 1;
}

ThreatObject2::~ThreatObject2()
{

}

bool ThreatObject2::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		if (move_ == 1)
		{
			width_frame_ = rect_.w / 8;
			height_frame_ = rect_.h;
		}
		else
		{
			width_frame_ = rect_.w / 8;
			height_frame_ = rect_.h;
		}
	}

	return ret;
}

void ThreatObject2::set_type_img()
{
	if (move_ == 1 && hp > 0)
	{
		type_img = 1;
	}
	else if (move_ == 0 && hp > 0)
	{
		type_img = 2;
	}
	else if (hp <= 0)
	{
		attack_ = false;
	}
}

void ThreatObject2::Show(SDL_Renderer* des)
{
	//SDL_RenderClear(des);
	set_type_img();
	if (type_img == 1)
	{
		bool ret = LoadImg("img//goku_left.png", des);

		if (ret == true)
		{
			frame_++;
			if (frame_ >= 8)
			{
				frame_ = 1;
			}
		}
	}
	else if (type_img == 2)
	{
		bool ret = LoadImg("img//goku_shot_left.png", des);

		if (ret == true)
		{
			frame_++;
			if (frame_ >= 8)
			{
				frame_ = 1;

			}
			if (frame_ == 7)
			{
				attack_ = true;
			}
			else attack_ = false;
		}
	}
	if (hp <= 0)
	{
		attack_ = false;
		if (sound_ == true)
		{
			get_sound_ = true;
		}
	}
	if (get_sound_ == true)
	{
		MixGetCoin();
		sound_ = false;
		get_sound_ = false;
		get_point2 = true;
	}

	if (hp > 0)
	{
		SDL_Rect* current_clip = &frame_clip_[frame_];

		if (move_ == 1)
		{
			SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
			cnt = rect_.y;
			SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
		}
		else if (move_ == 0)
		{
			SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
			SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
		}
	}
	Free();
}

void ThreatObject2::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void ThreatObject2::DoPlayer()
{
	if (hp > 0)
	{
		if (rect_.x < SCREEN_WIDTH + 10)
		{
			x_val_ = -speed;
		}
		else
		{
			x_val_ = -THREAT2SPEED;

		}
		//x_val_ = -THREAT2SPEED;
		CheckToMap();
	}
}

void ThreatObject2::CheckToMap()
{
	if (rect_.x <= 800)
	{
		x_val_ = 0;
		move_ = 0;
	}
	//std::cout << x_val_ << std::endl;
	rect_.x += x_val_;

	if (get_shot == true)
	{
		hp -= 1;
		get_shot = false;
	}
	if (get_supper_shot == true)
	{
		hp -= 10;
		get_supper_shot = false;
	}
}

void ThreatObject2::HandleMoveBullet()
{

}

void ThreatObject2::ShowBullet(SDL_Renderer* des)
{
	if (attack_ = true && move_ == 0 && hp > 0)
	{
		bool ret = bullet_.LoadImg("img//kameL.png", des);
		bullet_.SetRect(x_bullet, rect_.y + 20);
		x_bullet -= 20;
		if (x_bullet < 230)
		{
			x_bullet = 750;
			success_attack = true;
		}
	
		bullet_.Render(des);
		Free();
	}

}

void ThreatObject2::random_increase_hp(SDL_Renderer* des)
{
	if(hp <= 0 && can_show_heart == true)
	{
		std::cout << number_random_increase_hp << std::endl;
		if (number_random_increase_hp < 15)
		{
			increase_hp = 1;
			bool ret = Heart_.LoadImg("img//Heart.png", des);
			Heart_.SetRect(rect_.x, rect_.y);
			Heart_.Render(des);
			Free();
		}
	}
}
