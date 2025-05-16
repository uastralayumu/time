#include "player.h"
#include "map.h"
#include "obj.h"
#include <DirectXMath.h>

maps stege;
obj objs;
Sprite* sprplayer;
Sprite* playmove;
Sprite* playjamp;

void player::init()
{
	sprplayer = sprite_load(L"./Data/Images/chara_kari.png");
	playmove = sprite_load(L"./Data/Images/chara_move.png");
	playjamp = sprite_load(L"./Data/Images/chara_jamp.png");
}

void player::update()
{
	onGround = FALSE;
	vector.y += gravite;

	if (vector.y >= 10)
	{
		vector.y = 10;
	}

	float oldy = position.y;
	position.y += vector.y;
	float deltay = position.y - oldy;

	if (deltay > 0)
	{
		if (stege.isfloor(position.x + 48, position.y + 92, asi.x))
		{
			stege.playmaphosedown();
			onGround = true;
		}
	}

	if (deltay < 0)
	{
		if (stege.isceiling(position.x + 48, position.y, asi.x))
		{
			stege.playmaphoseup();
			onGround = true;
		}
	}

	float nisevector = vector.x;
	move = 0;
	if (GetAsyncKeyState('D') & 0x8000)
	{
		vector.x += 1.0f;
		sayuu = TRUE;
		move = 1;
		timer++;
		if (timer > 13)
		{
			movetimer++;
			timer = 0;
		}
		if (movetimer > 3) movetimer = 0;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		vector.x -= 1.0f;
		sayuu = FALSE;
		move = 1;
		timer++;
		if (timer > 13)
		{
			movetimer++;
			timer = 0;
		}
		if (movetimer > 3) movetimer = 0;
	}
	if (nisevector == vector.x) vector.x = 0.0f;
	objs.atrihantei();

	if (vector.x > 7.0f) vector.x = 7.0f;
	if (vector.x < -7.0f) vector.x = -7.0f;
	float oldx = position.x;
	position.x += vector.x;
	float deltax = position.x - oldx;

	bool kabeflag = false;

	if (deltax > 0)
	{
		if (stege.iswall(position.x + 64,position.y + 32,asi.x))
		{
			stege.playmaphoseright();
			kabeflag = true;
		}
	}

	if (deltax < 0)
	{
		if (stege.iswall(position.x + 32, position.y + 32, asi.x))
		{
			stege.playmaphoseleft();
			kabeflag = true;
		}
	}

	stege.update();
	

	if (TRG(0) & PAD_UP && onGround)
	{
		vector.y -= 13.0f;
		onGround = FALSE;
	}
	
	if (!onGround)
	{
		move = 2;
		jamptimer++;
		if (jamptimer > 8)
		{
			jampmovetimer++;
			jamptimer = 0;
			if (jampmovetimer > 6) jampmovetimer = 0;
		};
	}
}

void player::render()
{
	if (sayuu)
	{
		switch (move)
		{
		case 0:
			sprite_render(
				sprplayer,
				position.x, position.y,
				size.x, size.y,
				0, 0,
				96, 96,
				0, 0,
				ToRadian(0)
			);
			break;
		case 1:
			sprite_render(
				playmove,
				position.x, position.y,
				size.x, size.y,
				movetimer * 96, 0,
				96, 96,
				0, 0,
				ToRadian(0)
			);
			break;
		case 2:
			sprite_render(
				playjamp,
				position.x, position.y,
				size.x, size.y,
				jampmovetimer * 96, 0,
				96, 96,
				0, 0,
				ToRadian(0)
			);
			break;
		}
	}
	else
	{
		switch (move)
		{
		case 0:
			sprite_render(
				sprplayer,
				position.x + 100, position.y,
				size.x * -1, size.y,
				0, 0,
				96, 96,
				0, 0,
				ToRadian(0)
			);
			break;
		case 1:
			sprite_render(
				playmove,
				position.x + 100, position.y,
				size.x * -1, size.y,
				movetimer * 96, 0,
				96, 96,
				0, 0,
				ToRadian(0)
			);
			break;
		case 2:
			sprite_render(
				playjamp,
				position.x + 100, position.y,
				size.x * -1, size.y,
				jampmovetimer * 96, 0,
				96, 96,
				0, 0,
				ToRadian(0)
			);
			break;
		}
	}
	
}