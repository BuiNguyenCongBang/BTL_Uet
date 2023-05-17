#pragma once

#include "BaseObject.h"
#include "ThreatObject.h"
#include <cmath>

class SupportObject : public BaseObject
{
public:
	SupportObject();
	~SupportObject();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void set_clips();

	void CheckToMap();

	void set_x_mouse(int x) { x_mouse_ = x; }
	void set_y_mouse(int x) { y_mouse_ = x; }

	int get_type() const { return type_; }
	void set_type(const int x) { type_ = x; }

	void HandleInputAction(SDL_Renderer* screen, int mp, int x, int y);

	//void CheckThreat(ThreatObject threat_[], int threat_size);


private:
	int x_mouse_;
	int y_mouse_;
	
	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];

	int frame_;

	int type_;
};
