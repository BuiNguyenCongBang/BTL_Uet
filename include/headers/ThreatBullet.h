#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

class ThreatBullet : public BaseObject
{
public:
	ThreatBullet();
	~ThreatBullet();

	//void set_x_val(const int& xVal) { x_val_ = xVal; }
	//void set_y_val(const int& yVal) { y_val_ = yVal; }

	//int get_x_val() const { return x_val_; }
	//int get_y_val() const { return y_val_; }

	//void set_is_move(const bool& isMove) { is_move_ = isMove; }
	//bool get_is_move() const { return is_move_; }

	//void set_mouse(const int& x, const int& y) { x_mouse = x; y_mouse = y; }

	//void set_supper(const bool x) { supper_ = x; }

	//void set_threat(const ThreatObject t) { threat_ = t; }
	//void HandleMove(ThreatObject threat_[], int threat_size, ThreatObject2 threat2_[], int threat2_size);
	void HandleMoveThreat();

	void set_y(float y_) { y = y_; }
	//void HandleInputAction(SDL_Event events, SDL_Renderer* screen);

	void DoPlayer(Map& map_data);

	bool get_hit_target() const { return hit_target_; }

private:
	float x_val_;
	float y_val_;

	float y;

	float x_mouse;
	float y_mouse;
	bool is_move_;

	bool supper_;

	bool hit_target_;

	//ThreatObject threat_;

	unsigned int bullet_dir_;
};