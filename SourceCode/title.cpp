#include "title.h"
extern ongaku o;
title::title()
{

}

void title::init()
{
	sprtitle = sprite_load(L"./Data/Images/title.png");
	hazime[0] = sprite_load(L"./Data/Images/title_botton_1.png");
	hazime[1] = sprite_load(L"./Data/Images/title_botton_2.png");
	sonota[0] = sprite_load(L"./Data/Images/title_botton_3.png");
	sonota[1] = sprite_load(L"./Data/Images/title_botton_4.png");
	o.music(16);
}

void title::update(int *game_title)
{
	int cx = getCursorPosX();
	int cy = getCursorPosY();
	*game_title = 0;
	if(cx >= hazimepos.x && cx <= hazimepos.x + 300 && cy >= hazimepos.y - 15 && cy <= hazimepos.y + 65 )
	{
		
		if(!musichazimaru)o.music(2);
		musichazimaru = true;
		hazimenoue = true;
		if (TRG(0) & PAD_START)
		{
			music::stop(16);
			o.music(1);
			*game_title = 1;
		}
	}
	else if (cx >= sonotapos.x && cx <= sonotapos.x + 470 && cy >= sonotapos.y - 15 && cy <= sonotapos.y + 65)
	{
		if (!musichazimaru)o.music(2);
		musichazimaru = true;
		 sonotanoue = true;
		if(TRG(0) & PAD_START)*game_title = 2;
	}
	else
	{
		hazimenoue = false;
		musichazimaru = false;
		 sonotanoue = false;
	}
}

void title::render()
{
	sprite_render(sprtitle, 0, 0);
	if (!hazimenoue)
	{
		sprite_render(hazime[0],hazimepos.x, hazimepos.y);
	}
	else
	{
		sprite_render(hazime[1], hazimepos.x, hazimepos.y);
	}
	if (!sonotanoue)
	{
		sprite_render(sonota[0], sonotapos.x, sonotapos.y);
	}
	else
	{
		sprite_render(sonota[1], sonotapos.x, sonotapos.y);
	}
}

void title::deinit()
{
	safe_delete(sprtitle);
	safe_delete(hazime[0]);
	safe_delete(hazime[1]);
	safe_delete(sonota[0]);
	safe_delete(sonota[1]);
}

title::~title()
{
}