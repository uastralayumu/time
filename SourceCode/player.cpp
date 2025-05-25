#include "player.h"
#include "map.h"
#include "obj.h"
#include <DirectXMath.h>

maps stege;
obj objs;
ongaku o;
Sprite* sprplayer;
Sprite* playmove;
Sprite* playjamp;
Sprite* playdamege;

void player::init(int&serect_stege)
{
	sprplayer = sprite_load(L"./Data/Images/chara_kari.png");
	playmove = sprite_load(L"./Data/Images/chara_move.png");
	playjamp = sprite_load(L"./Data/Images/chara_jamp.png");
	playdamege = sprite_load(L"./Data/Images/chara_damage.png");
	if (serect_stege >= 0)
	{
		position = { 1000.0f,930.0f };
	}
	move = 0;
	timer = 0;
	movetimer = 0;
	jamptimer = 0;
	jampmovetimer = 0;
	damege = false;
	damagetimer = 0;
	damagemove = 0;
	damagemusic = false;
	sayuu = true;
}

void player::update()
{
	if (damege)
	{
		if (!damagemusic)
		{
			o.music(4);
			damagemusic = true;
		}
		damagetimer++;
		if (damagetimer > 7)
		{
			damagetimer = 0;
			damagemove++;
			if (damagemove > 5)
			{
				position = { 1000.0f,930.0f };
				vector = { 0,0 };
				objs.motu = false;
				damege = false;
				damagemove = 0;
				damagemusic = false;
			}
		}
	}
	else
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

		//床の当たり判定（マップチップとの）
		if (deltay > 0)
		{
			if (stege.isfloor(position.x + 48, position.y + 92, asi.x))
			{
				stege.playmaphosedown();
				onGround = true;
			}
		}

		//天井の当たり判定（マップチップとの）
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
		//右方向に移動
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

		//左方向に移動
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

		//右の当たり判定（マップチップとの）
		if (deltax > 0)
		{
			if (stege.iswall(position.x + 64, position.y + 32, asi.x))
			{
				stege.playmaphoseright();
				kabeflag = true;
			}
		}

		//左の当たり判定（マップチップとの）
		if (deltax < 0)
		{
			if (stege.iswall(position.x + 32, position.y + 32, asi.x))
			{
				stege.playmaphoseleft();
				kabeflag = true;
			}
		}

		//植木鉢との当たり判定
		if (objs.motu)
		{
			if (position.x < 32)
			{
				position.x = 32;
			}
			if (position.x > SCREEN_W - 130)
			{
				position.x = SCREEN_W - 130;
			}
		}
		if (position.x < -32) position.x = -32;
		if (position.x > SCREEN_W - 75) position.x = SCREEN_W - 75;

		stege.update();

		//ジャンプ
		if (TRG(0) & PAD_UP && onGround)
		{
			vector.y -= 13.0f;
			onGround = FALSE;
		}

		//プレイヤーが空中におる時
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

		if (move == 0)
		{
			taikitimer++;
			if (taikitimer > 35)
			{
				taikimovetimer++;
				taikitimer = 0;
				if (taikimovetimer > 5) taikimovetimer = 0;
			}
		}

		damege = stege.state();
	}
	
}

void player::render()
{
	if (sayuu)
	{
		if (!damege)
		{
			switch (move)
			{
			case 0:
				sprite_render(
					sprplayer,
					position.x, position.y,
					size.x, size.y,
					taikimovetimer * 96, 0,
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
			sprite_render(
				playdamege,
				position.x, position.y,
				size.x, size.y,
				damagemove * 96,0,
				96,96,
				0,0,
				ToRadian(0)
			);
		}
	}
	else
	{
		if (!damege)
		{
			switch (move)
			{
			case 0:
				sprite_render(
					sprplayer,
					position.x + 96, position.y,
					size.x * -1, size.y,
					taikimovetimer * 96, 0,
					96, 96,
					0, 0,
					ToRadian(0)
				);
				break;
			case 1:
				sprite_render(
					playmove,
					position.x + 96, position.y,
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
					position.x + 96, position.y,
					size.x * -1, size.y,
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
			sprite_render(
				playdamege,
				position.x + 96, position.y,
				size.x * -1, size.y,
				damagemove * 96, 0,
				96, 96,
				0, 0,
				ToRadian(0)
			);
		}
	}
	
}

void player::game_deinit()
{
	safe_delete(sprplayer);
	safe_delete(playmove);
	safe_delete(playjamp);
}
