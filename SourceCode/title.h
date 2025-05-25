#pragma once
#include "all.h"

class title
{
public:
	title();
	~title();

	void init();
	void update(int *game_title);
	void render();
	void deinit();

private:
	Sprite* sprtitle;
	Sprite* hazime[2];
	Sprite* sonota[2];
	bool game_title;
	const DirectX::XMFLOAT2 hazimepos = { 830,670 };
	const DirectX::XMFLOAT2 sonotapos = { 730,780 };
	bool hazimenoue = false;
	bool sonotanoue = false;
	bool musichazimaru = false;

};

