#include "obj.h"
#include "map.h"
#include "all.h"
#include "sound.h"

Sprite* ueki;
player play;
extern maps stege;
extern ongaku o;


void obj::init(int &serect_stage)
{
	ueki = sprite_load(L"./Data/Images/ueki_kari.png");
	 motu = false;
	 
	 {
		 position = { 1500,930 };
	 }
	
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
			o.music(8);
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
	if (!play.damege)
	{
		vector.y += play.gravite;

		if (vector.y >= 10)
		{
			vector.y = 10;
		}

		float oldy = position.y;
		position.y += vector.y;
		float deltay = position.y - oldy;

		//床の当たり判定（マップチップとの）
		if (deltay > 0 && !motu)
		{
			if (stege.isfloor(position.x + 48, position.y + 96, sita.x))
			{
				stege.objmaphosedown();
				onGround = true;
			}
		}

		//天井の当たり判定（マップチップとの）
		if (deltay < 0 && !motu)
		{
			if (stege.isceiling(position.x + 48, position.y, sita.x))
			{
				stege.objmaphoseup();
				onGround = true;
			}
		}

		//横の当たり判定（マップチップとの）
		if (!motu)
		{
			for (int i = 0; i < stege.chip_y; i++)
			{
				for (int j = 0; j < stege.chip_x; j++)
				{
					if (stege.tikei[j][i] == 0 || stege.tikei[j][i] == 1)
					{
						if (position.x > play.position.x)
						{
							if (i * 32 + 10 > position.x && i * 32 - 40 < position.x + 32 && j * 32 - 64 > position.y - 32 && j * 32 - 96 < position.y - 16)
							{
								if (i * 32 - 40 < position.x + 32 && j * 32 - 64 > position.y - 32 && j * 32 - 96 < position.y - 16)
								{
									position.x = i * 32 - 75;
									play.position.x = position.x - 40;
								}
							}
						}
						if (position.x < play.position.x)
						{
							if (i * 32 + 10 > position.x && i * 32 < position.x + 50 && j * 32 - 64 > position.y - 32 && j * 32 - 96 < position.y - 16)
							{
								if (i * 32 + 10 > position.x && j * 32 - 64 > position.y - 32 && j * 32 - 96 < position.y - 16)
								{
									position.x = i * 32 + 10;
									play.position.x = position.x + 40;
								}

							}
						}
					}
				}
			}
		}

	}

}

void obj::render()
{
		sprite_render(
			ueki, position.x, position.y,
			1, 1);
}

void obj::game_deinit()
{
	safe_delete(ueki);
}