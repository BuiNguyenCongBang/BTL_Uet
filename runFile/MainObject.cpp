#include "MainObject.h"

#include <iostream>

MainObject::MainObject()
{
	hp_ = 100;
	mp_ = 100;
	shot_ = true;
	get_support_ = false;
	time_shot.push_back(0);
	time_get_support.push_back(0);

	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 250;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;

	x_mouse_right = 0;
	y_mouse_right = 0;

	supper_shot = 0;
	ready_supper_shot = 0;

	point = 0;
}

MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_SPACE)
		{
			std::cout << "9999999999" << std::endl;
			std::cout << mp_ << std::endl;
			if (ready_supper_shot == 1)
			{
				ready_supper_shot = 0;
				supper_shot = 0;
			}
			else if (ready_supper_shot == 0)
			{
				ready_supper_shot = 1;
			}
		}
	}
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			BulletObject* p_bullet = new BulletObject();

			//Uint32 buttons = SDL_GetMouseState(&x_mouse_, &y_mouse_);
			x_mouse_ = events.button.x;
			y_mouse_ = events.button.y;
			//std::cout << x_mouse_ << " " << y_mouse_ << std::endl;
			Uint32 time = 0;
			time = SDL_GetTicks();
			time_shot.push_back(time);
			time_get_support.push_back(time);
			shot_ = false;
			//get_support_ = false;
			//(SDL_GetTicks() - time >= 1000 || SDL_GetTicks() - time == 0)
			//std::cout << time_shot[time_shot.size() - 1] << " " << time_shot[time_shot.size() - 2] << std::endl;
			Uint32 cnt = SDL_GetTicks();

			if (supper_shot == 0)
			{
				if ((time_shot[time_shot.size() - 1] - time_shot[time_shot.size() - 2] >= 1000))
				{
					p_bullet->LoadImg("img//player_bullet.png", screen);
					MixHit();

					p_bullet->SetRect(205, 305);
					p_bullet->set_y(285);
					p_bullet->set_mouse(x_mouse_, y_mouse_);

					p_bullet->set_x_val(30);
					p_bullet->set_is_move(true);
					p_bullet->set_supper(false);

					shot_ = true;

					//mp_+=5;
					if (mp_ >= 100)
					{
						mp_ = 100;
						supper_shot = 1;
					}

					//p_bullet_list.push_back(p_bullet);

				}
				else
				{
					time_shot.pop_back();
				}
			}

			/*if (supper_shot == 1)
			{
				std::cout << "supper_shot == 1" << std::endl;
			}
			else std::cout << "supper_shot != 1" << std::endl;
			if (ready_supper_shot == 1)
			{
				std::cout << "ready_supper_shot == 1" << std::endl;
			}
			else std::cout << "ready_supper_shot != 1" << std::endl;
			std::cout << std::endl;*/

			if (supper_shot == 1 && ready_supper_shot == 1)
			{
				if ((time_shot[time_shot.size() - 1] - time_shot[time_shot.size() - 2] >= 700))
				{
					p_bullet->LoadImg("img//player_supper_bullet.png", screen);
					MixHit();

					p_bullet->SetRect(205, 305);
					p_bullet->set_y(285);
					p_bullet->set_mouse(x_mouse_, y_mouse_);

					p_bullet->set_x_val(30);
					p_bullet->set_is_move(true);
					p_bullet->set_supper(true);

					shot_ = true;

					mp_ -= 20;
					if (mp_ < 20)
					{
						supper_shot = 0;
						ready_supper_shot = 0;
					}

					//p_bullet_list.push_back(p_bullet);

				}
				else
				{
					time_shot.pop_back();
				}
			}
			if (supper_shot == 1 && ready_supper_shot == 0)
			{
				supper_shot = 0;
			}
			if (supper_shot == 0 && ready_supper_shot == 1)
			{
				ready_supper_shot = 0;
			}
			p_bullet_list.push_back(p_bullet);

		}

	}
	Free();

}

bool MainObject::HandleBullet(SDL_Renderer* des, ThreatObject threat_[], int threat_size, ThreatObject2 threat2_[], int threat2_size)
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list.at(i);
		//std::cout << p_bullet_list.size() << std::endl;
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true && hp_ > 0 )
			{
				p_bullet->HandleMove(threat_, threat_size, threat2_, threat2_size);
				p_bullet->Render(des);
				if (p_bullet->get_hit_target() == true && supper_shot == 0)
				{
					mp_ += 5;
					if (mp_ >= 100)
					{
						mp_ = 100;
					}
				}
				if (p_bullet->get_get_heart() == true)
				{
					hp_ += 5;
					p_bullet->set_get_heart(false);
				}
			}
			else
			{
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if (p_bullet == NULL)
				{
					delete p_bullet;
					free(p_bullet);
					p_bullet = NULL;
				}
			}
		}
	}
	return 1;
}

void MainObject::show_bullet(SDL_Renderer* des)
{
	p_bullet.Render(des);
}

void MainObject::HandleHp(ThreatObject threat_)
{
	if (threat_.get_attack() == true)
	{
		hp_ -= 2;
		threat_.set_attack(false);
	}
	//std::cout << hp_ << std::endl;
}

void MainObject::HandleHp2(ThreatObject2 threat2_)
{
	if (threat2_.get_success_attack() == true)
	{
		hp_ -= 5;
		threat2_.set_success_attack(false);
	}

	//std::cout << hp_ << std::endl;
}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		if (hp_ > 0)
		{
			width_frame_ = 150;
			height_frame_ = 150;
		}
		else if (hp_ <= 0)
		{
			width_frame_ = 150 ;
			height_frame_ = 150;
		}
	}
	return ret;
}

void MainObject::Show(SDL_Renderer* des)
{
	bool ret = LoadImg("img//MainReal.png", des);
	if (ret == true)
	{
		frame_++;
		if (frame_ >= 0)
		{
			frame_ = 0;
		}
	}

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { 90, 220, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	Free();

}

void MainObject::set_clips()
{
	int cnt = 0;
	if (hp_ > 0) cnt = 1;
	else cnt = 6;
	for (int i = 0; i < 6; i++)
	{
		frame_clip_[i].x = i * width_frame_;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = width_frame_;
		frame_clip_[i].h = height_frame_;
	}
}

void MainObject::show_hp(SDL_Renderer* des)
{
	SDL_Rect rect__ = { 171, 557, 202, 12 };
	SDL_RenderDrawRect(des, &rect__);
	if (hp_ < 0)
	{
		hp_ = 0;
	}
	if (hp_ > 100)
	{
		hp_ = 100;
	}
	SDL_Rect rect = { 172, 558, hp_*2, 10 };
	SDL_SetRenderDrawColor(des, 255, 0, 0, 255);
	SDL_RenderFillRect(des, &rect);
}

void MainObject::show_mp(SDL_Renderer* des)
{
	SDL_Rect rect__ = { 171, 594, 202, 12 };
	SDL_RenderDrawRect(des, &rect__);
	
	SDL_Rect rect = { 172, 595, mp_*2, 10 };
	if (ready_supper_shot == 0)
	{
		SDL_SetRenderDrawColor(des, 0, 0, 255, 128);

	}
	else if (ready_supper_shot == 1)
	{
		SDL_SetRenderDrawColor(des, 255, 255, 255, 255);
	}
	SDL_RenderFillRect(des, &rect);
}

void MainObject::SetPoint(ThreatObject threat_[], int threat_size, ThreatObject2 threat2_[], int threat2_size)
{
	for (int i = 0; i < threat_size; i++)
	{
		if (threat_[i].get_get_point() == true)
		{
			point += 2;
			threat_[i].set_get_point(false);
		}
	}

	for (int i = 0; i < threat2_size; i++)
	{
		if (threat2_[i].get_get_point2() == true)
		{
			point += 5;
			threat2_[i].set_get_point2(false);
		}
	}
}