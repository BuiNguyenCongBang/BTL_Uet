#pragma once

#define THREAT_OBJECT_2_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "sound.h"

#define THREAT2SPEED 7

class ThreatObject2 : public BaseObject
{
public:
	ThreatObject2();
	~ThreatObject2();

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void DoPlayer();
	void CheckToMap();
	void set_type_img();

	void set_move(const bool x) { move_ = x; };
	bool get_move() const { return move_; }

	void set_x_bullet(int x) { x_bullet = x; }

	int get_hp() const { return hp; }

	void set_get_shot(bool x) { get_shot = x; }
	bool get_get_shot() const { return get_shot; }

	void set_attack(const bool a) { attack_ = a; }
	bool get_attack() const { return attack_; }

	void HandleMoveBullet();
	void ShowBullet(SDL_Renderer* des);

	bool get_success_attack() const { return success_attack; }
	void set_success_attack(const bool x) { success_attack = x; }

	void set_get_supper_shot(bool x) { get_supper_shot = x; }
	bool get_get_supper_shot() const { return get_supper_shot; }

	//void set_player(const MainObject p) { player = p; }

	void set_get_point2(const bool a) { get_point2 = a; }
	bool get_get_point2() const { return get_point2; }

	void set_speed(int x) { speed = x; }

	bool get_increase_hp() const { return increase_hp; }

	void random_increase_hp(SDL_Renderer* des);
	void set_can_show_heart(const bool x) { can_show_heart = x; }
	bool get_can_show_heart() const { return can_show_heart; }



private:
	float x_val_;
	float y_val_;

	int cnt;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[20];
	int frame_;
	int status_;

	int come_back_time;

	bool move_;

	int hp;

	bool get_shot;
	bool get_supper_shot;

	bool attack_;

	int x_bullet;
	int y_bullet;
	bool success_attack;

	int type_img;

	BaseObject bullet_;
	BaseObject Heart_;

	bool sound_;
	bool get_sound_;

	bool get_point2;
	int speed;

	bool increase_hp;

	int number_random_increase_hp;

	bool can_show_heart;

	//MainObject player;
};