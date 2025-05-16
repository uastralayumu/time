#include "obj.h"
#include "map.h"
#include "all.h"

Sprite* ueki;
player play;
extern maps stege;

void obj::init()
{
	ueki = sprite_load(L"./Data/Images/ueki_kari.png");
}

void obj::atrihantei()
{
	if (TRG(0) & PAD_TRG4 && motu == true)
	{
		motu = false;
	}
	else if (position.x <= play.position.x + 48 && position.x + 48 >= play.position.x
		&& position.y < play.position.y + 38 && position.y + 72  > play.position.y
		&& motu == false)
	{
		if (TRG(0) & PAD_TRG4)
		{
			motu = true;
		}
		if (position.x <= play.position.x + 48 && position.x >= play.position.x + 37) play.position.x = position.x - 48;
		if (position.x + 48 >= play.position.x && position.x + 37 <= play.position.x) play.position.x = position.x + 48;
		if (position.x <= play.position.x + 47 && position.x + 47 >= play.position.x && position.y <= play.position.y + 38 && position.y >= play.position.y +28)
		{
			play.position.y = position.y - 38;
			play.vector.y = 0.0f;
			play.onGround = TRUE;
		}
		if (position.x <= play.position.x + 47 && position.x + 47 >= play.position.x && position.y + 75 >= play.position.y  && position.y + 60 <= play.position.y )
		{
			play.position.y = position.y + 75;
			play.vector.y = 0.0f;
		}
	}


	if (motu == true)
	{
		position.x = play.position.x + 48;
		position.y = play.position.y - 16;
		vector.y = 0;
		if (!play.sayuu)
		{
			position.x -= left;
		}
	}
}

void obj::update()
{
	vector.y += play.gravite;

	if (vector.y >= 10)
	{
		vector.y = 10;
	}

	float oldy = position.y;
	position.y += vector.y;
	float deltay = position.y - oldy;

	if (deltay > 0 && !motu)
	{
		if (stege.isfloor(position.x + 48, position.y + 96, sita.x))
		{
			stege.objmaphosedown();
			onGround = true;
		}
	}

	if (deltay < 0 && !motu)
	{
		if (stege.isceiling(position.x + 48, position.y, sita.x))
		{
			stege.objmaphoseup();
			onGround = true;
		}
	}
	if (vector.x > 7.0f) vector.x = 7.0f;
	if (vector.x < -7.0f) vector.x = -7.0f;
	float oldx = position.x;
	position.x += vector.x;
	float deltax = position.x - oldx;

	bool kabeflag = false;

	if (deltax > 0 && !motu)
	{
		if (stege.iswall(position.x + 64, position.y + 32, sita.x))
		{
			stege.objmaphoseright();
			kabeflag = true;
		}
	}

	if (deltax < 0 && !motu)
	{
		if (stege.iswall(position.x + 32, position.y + 32, sita.x))
		{
			stege.objmaphoseleft();
			kabeflag = true;
		}
	}

}

void obj::render()
{
		sprite_render(
			ueki, position.x, position.y,
			1, 1);
}