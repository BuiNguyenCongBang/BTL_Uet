#pragma once

#define THREAT_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "SupportObject.h"
#include "sound.h"

#define THREATSPEED 5

class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void DoPlayer();
	void CheckToMap();

	void set_move(bool x) { move_ = x; }
	bool get_move() const { return move_; }

	int get_hp() const { return hp; }

	void set_get_shot(bool x) { get_shot = x; }
	bool get_get_shot() const { return get_shot; }

	void set_get_supper_shot(bool x) { get_supper_shot = x; }
	bool get_get_supper_shot() const { return get_supper_shot; }

	void set_attack(const bool a) { attack_ = a;}
	bool get_attack() const { return attack_; }

	void set_get_point(const bool a) { get_point = a; }
	bool get_get_point() const { return get_point; }

	void set_speed(const int x) { speed_ = x; }

	void set_increase_hp();

	void random_increase_hp(SDL_Renderer* des);

	bool get_increase_hp() const { return increase_hp; }

	void set_can_show_heart(const bool x) { can_show_heart = x; }
	bool get_can_show_heart() const { return can_show_heart; }


	//void set_player(const MainObject p) { player = p; }
private:
	float x_val_;
	float y_val_;

	int cnt;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[20];
	int frame_;
	int status_;

	int speed_;


	bool move_;

	int hp;

	bool get_shot;
	bool get_supper_shot;

	bool attack_;

	bool get_sound_;
	bool sound_;
	bool get_point;

	bool success_attack;

	//MainObject player;

	bool increase_hp;
	bool can_show_heart;

	int number_random_increase_hp;
	BaseObject Heart_;
};