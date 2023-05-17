#include "SupportObject.h"
#include <iostream>

SupportObject::SupportObject()
{
	x_mouse_ = 0;
	y_mouse_ = 0;

	width_frame_ = 0;
	height_frame_ = 0;
	frame_ = 0;

	type_ = 0;
}

SupportObject::~SupportObject()
{

}

bool SupportObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w;
		height_frame_ = rect_.h;
	}

	return ret;
}

void SupportObject::Show(SDL_Renderer* des)
{
	bool ret = true;
	if (type_ == 1)
	{
		ret = LoadImg("sp_img//mine_.png", des);
	}
	else if (type_ == 2)
	{
		ret = LoadImg("sp_img//wall_.png", des);
	}
	else if (type_ == 3)
	{
		ret = LoadImg("sp_img//suppermine_.png", des);
	}
	else
	{
		return;
	}

	std::cout << type_ << std::endl;

	int y_threat[5];
	for (int i = 0; i < 5; i++)
	{
		y_threat[i] = 64 * i + 144 - height_frame_;
	}


	if (ret == true)
	{
		frame_++;
		if (frame_ >= 0)
		{
			frame_ = 0;
		}

	}

	SDL_Rect* current_clip = &frame_clip_[frame_];

	int y = y_mouse_;
	int res = 9999;
	for (int i = 0; i < 5; i++)
	{
		int a = abs(y_mouse_ - y_threat[i]);
		//std::cout << a << " ";
		if (a < res)
		{
			res = a;
			y = y_threat[i];
		}
	}
	//std::cout << y << "\n";


	if (y_mouse_ < 2000)
	{
		rect_.x = x_mouse_;
		rect_.y = y;

		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
	
}
void SupportObject::set_clips()
{
	for (int i = 0; i < 1; i++)
	{
		frame_clip_[i].x = i * width_frame_;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = width_frame_;
		frame_clip_[i].h = height_frame_;
	}
}

void SupportObject::HandleInputAction(SDL_Renderer* screen, int mp, int x, int y)
{
	/*int x = x_mouse_;
	int y = y_mouse_;*/

	if (x >= 460 && x <= 583 && y >= 510 && y <= 628 && mp >= 30)
	{
		type_ = 1;
		LoadImg("sp_img//mine_.png", screen);
	}
	else if (x >= 600 && x <= 720 && y >= 510 && y <= 628 && mp >= 25)
	{
		type_ = 2;
		LoadImg("sp_img//wall_.png", screen);
	}
	else if (x >= 736 && x <= 862 && y >= 510 && y <= 628 && mp >= 60)
	{
		type_ = 3;
		LoadImg("sp_img//suppermine_.png", screen);
	}
	else
	{
		type_ = 0;
	}
}

//void SupportObject::CheckThreat(ThreatObject* Threat, int threat_size)
//{
//	for (int i = 0; i < threat_size; i++)
//	{
//		//if (rect_.y + height_frame_ == )
//	}
//}


