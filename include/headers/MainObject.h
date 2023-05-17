#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ThreatObject.h"
#include "ThreatObject2.h"
#include "sound.h"


class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void DoPlayer();
	void CheckToMap();
	void CenterEntityOnMap();

	bool HandleBullet(SDL_Renderer* des, ThreatObject threat_[], int threat_size, ThreatObject2 threat2_[], int threat2_size);
	void show_bullet(SDL_Renderer* des);

	void HandleSupport(SDL_Renderer* des);

	void HandleHp(ThreatObject threat);
	void HandleHp2(ThreatObject2 threat);
	void HandleMp(ThreatObject threat);

	void set_mp(const int x) { mp_ = x; }
	int get_mp() const { return mp_; }


	void set_hp(const int x) { hp_ = x; }
	int get_hp() const { return hp_; }

	void show_hp(SDL_Renderer* des);
	void show_mp(SDL_Renderer* des);

	void set_mouse(int x, int y) { x_mouse_ = x; y_mouse_ = y; }
	int get_x_mouse() const { return x_mouse_; }
	int get_y_mouse() const { return y_mouse_; }

	void set_supper_shot(const bool x) { supper_shot = x; }

	void SetPoint(ThreatObject threat_[], int threat_size, ThreatObject2 threat2_[], int threat2_size);
	int get_point() const { return point; }
	void set_point(const int a) { point = a; }

private:
	int hp_;
	int mp_;

	float x_val_;
	float y_val_;

	float x_pos_;		// vị trí hiển thị nhân vật
	float y_pos_;		// vị trí hiển thị nhân vật

	SDL_Rect rect_;

	int width_frame_;
	int height_frame_;

	int x_mouse_;
	int y_mouse_;

	int x_mouse_right;
	int y_mouse_right;

	std::vector<Uint32> time_shot;
	std::vector<Uint32> time_get_support;

	std::vector <BulletObject*> p_bullet_list;

	SDL_Rect frame_clip_[8];

	int frame_;
	int status_;

	BulletObject p_bullet;

	bool shot_;
	bool get_support_;

	SupportObject* support_ = new SupportObject;

	std::vector <SupportObject*> p_support_list;

	bool supper_shot;
	bool ready_supper_shot;

	int point;
};
