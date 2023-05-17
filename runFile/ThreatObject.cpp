#include "ThreatObject.h"
#include <iostream>
#include <cstdlib>

ThreatObject::ThreatObject()
{
	frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	move_ = 1;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	rect_.x = SCREEN_WIDTH - 50;
	hp = 10;
	get_shot = false;
	get_supper_shot = false;

	get_sound_ = false;
	sound_ = true;

	get_point = false;

	increase_hp = 0;
	can_show_heart = 1;
	number_random_increase_hp = rand() % 20 + 1;

	success_attack = false;
}

ThreatObject::~ThreatObject()
{

}

bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		if (move_ == 1)
		{
			width_frame_ = rect_.w / 13;
			height_frame_ = rect_.h;
		}
		else
		{
			width_frame_ = rect_.w / 18;
			height_frame_ = rect_.h;
		}
	}

	return ret;
}

void ThreatObject::Show(SDL_Renderer* des)
{
	if (move_ == 1 && hp > 0)
	{
		bool ret = LoadImg("img//SkeletonWalkRealReal.png", des);

		if (ret == true)
		{
			frame_++;
			if (frame_ >= 12)
			{
				frame_ = 0;
			}
		}
	}
	else if (move_ == 0 && hp > 0)
	{
		bool ret = LoadImg("img//SkeletonAttacktest.png", des);
		if (ret == true)
		{
			frame_++;
			if (frame_ >= 17)
			{
				frame_ = 0;
			}
			if (frame_ == 10)
			{
				attack_ = true;
			}
			else attack_ = false;
		}
	}
	else if (hp <= 0)
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
		get_point = true;
		sound_ = false;
		get_sound_ = false;
	}
	if (hp > 0)
	{
		SDL_Rect* current_clip = &frame_clip_[frame_];
	

		if (move_ == 1)
		{
			SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
			cnt = rect_.y;
			SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
			//std::cout << rect_.y + height_frame_ << std::endl;
		}
		else if (move_ == 0)
		{
			SDL_Rect renderQuad = { rect_.x, cnt - 16, width_frame_, height_frame_ };
			SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);

		}
	}
	Free();

}

void ThreatObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{

}

void ThreatObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 20; i++)
		{
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void ThreatObject::DoPlayer()
{
	if( hp > 0)
	{
		if (rect_.x < SCREEN_WIDTH + 10)
		{
			x_val_ = -speed_;
		}
		else
		{
			x_val_ = -THREATSPEED;

		}
		CheckToMap();
	}
}

void ThreatObject::CheckToMap()
{

	if (rect_.x <= 250)
	{
		x_val_ = 0;
		move_ = 0;
	}
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

void ThreatObject::random_increase_hp(SDL_Renderer* des)
{
	if (hp <= 0 && can_show_heart == true)
	{
		std::cout << number_random_increase_hp << std::endl;
		if (number_random_increase_hp < 10)
		{
			increase_hp = 1;
			bool ret = Heart_.LoadImg("img//Heart.png", des);
			Heart_.SetRect(rect_.x, rect_.y);
			Heart_.Render(des);
			Free();
		}
	}
}
