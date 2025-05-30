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
	suu(serect_stage);
	
}

void obj::suu(int& serect_stage)
{
	
	switch (serect_stage)
	{
	case 0:
		uekikosuu = 2;
		position[0] = {1500,930};
		position[1] = {500,930};

	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	}
}

void obj::atrihantei()
{
	for (int i = 0; i < uekikosuu; i++)
	{
		if (TRG(0) & PAD_TRG4 && motu[i] == true)
		{
			motu[i] = false;
		}
		else if (position[i].x <= play.position.x + 48 && position[i].x + 48 >= play.position.x
			&& position[i].y < play.position.y + 38 && position[i].y + 72  > play.position.y
			&& motu[i] == false)
		{
			if (TRG(0) & PAD_TRG4)
			{
				o.music(8);
				motu[i] = true;
			}
			if (position[i].x <= play.position.x + 48 && position[i].x >= play.position.x + 37) play.position.x = position[i].x - 48;
			if (position[i].x + 48 >= play.position.x && position[i].x + 37 <= play.position.x) play.position.x = position[i].x + 48;
			if (position[i].x <= play.position.x + 47 && position[i].x + 47 >= play.position.x && position[i].y <= play.position.y + 38 && position[i].y >= play.position.y + 28)
			{
				play.position.y = position[i].y - 38;
				play.vector.y = 0.0f;
				play.onGround = TRUE;
			}
			if (position[i].x <= play.position.x + 47 && position[i].x + 47 >= play.position.x && position[i].y + 75 >= play.position.y && position[i].y + 60 <= play.position.y)
			{
				play.position.y = position[i].y + 75;
				play.vector.y = 0.0f;
			}
		}
	}
	for(int i = 0;i < uekikosuu;i++)
	{
		if (motu[i] == true)
		{
			position[i].x = play.position.x + 48;
			position[i].y = play.position.y - 16;
			vector[i].y = 0;
			if (!play.sayuu)
			{
				position[i].x -= left;
			}
		}
	}
}

void obj::update()
{

	if (!play.damege)
	{
		for (int o = 0; o < uekikosuu; o++)
		{
			vector[o].y += play.gravite;

			if (vector[o].y >= 10)
			{
				vector[o].y = 10;
			}


			float oldy = position[o].y;
			position[o].y += vector[o].y;
			float deltay = position[o].y - oldy;

			//床の当たり判定（マップチップとの）
			if (deltay > 0 && !motu[o])
			{
				if (stege.isfloor(position[o].x + 48, position[o].y + 96, sita.x))
				{
					stege.objmaphosedown(o);
					onGround = true;
				}
			}

			//天井の当たり判定（マップチップとの）
			if (deltay < 0 && !motu[o])
			{
				if (stege.isceiling(position[o].x + 48, position[o].y, sita.x))
				{
					stege.objmaphoseup(o);
					onGround = true;
				}
			}

			//横の当たり判定（マップチップとの）
			if (!motu[o])
			{
				for (int i = 0; i < stege.chip_x; i++)
				{
					for (int j = 0; j < stege.chip_y; j++)
					{
						if (stege.tikei[j][i] == 0 || stege.tikei[j][i] == 1)
						{
							if (position[o].x > play.position.x)
							{
								if (i * 32 + 10 > position[o].x && i * 32 - 40 < position[o].x + 32 && j * 32 - 64 > position[o].y - 32 && j * 32 - 96 < position[o].y - 16)
								{
									if (i * 32 - 40 < position[o].x + 32 && j * 32 - 64 > position[o].y - 32 && j * 32 - 96 < position[o].y - 16)
									{
										position[o].x = i * 32 - 75;
										play.position.x = position[o].x - 40;
									}
								}
							}
							if (position[o].x < play.position.x)
							{
								if (i * 32 + 10 > position[o].x && i * 32 < position[o].x + 50 && j * 32 - 64 > position[o].y - 32 && j * 32 - 96 < position[o].y - 16)
								{
									if (i * 32 + 10 > position[o].x && j * 32 - 64 > position[o].y - 32 && j * 32 - 96 < position[o].y - 16)
									{
										position[o].x = i * 32 + 10;
										play.position.x = position[o].x + 40;
									}

								}
							}
						}
					}
				}
			}
		}
	}

	for (int o = 0; o < uekikosuu - 1; o++)
	{
		for (int u = o + 1; u < uekikosuu; u++)
		{
			if (position[o].x == position[u].x && position[o].y == position[u].y)
			{
				position[o].x += 10;
			}
		}
	}

}

void obj::render()
{
	for (int i = 0; i < uekikosuu; i++)
	{
		sprite_render(
			ueki, position[i].x, position[i].y,
			1, 1);
	}
}

void obj::game_deinit()
{
	safe_delete(ueki);
}