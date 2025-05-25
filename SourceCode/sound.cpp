#include "sound.h"

void ongaku::init()
{
	music::load(14, L"./Data/Sound/BGM_1.wav");
	music::load(15, L"./Data/Sound/BGM_2.wav");
	music::load(16, L"./Data/Sound/BGM_3.wav");
	music::load(1, L"./Data/Sound/SE_01.wav");
	music::load(2, L"./Data/Sound/SE_02.wav");
	music::load(3, L"./Data/Sound/SE_03.wav");
	music::load(4, L"./Data/Sound/SE_04.wav");
	music::load(5, L"./Data/Sound/SE_05.wav");
	music::load(6, L"./Data/Sound/SE_06.wav");
	music::load(7, L"./Data/Sound/SE_07.wav");
	music::load(8, L"./Data/Sound/SE_08.wav");
	music::load(9, L"./Data/Sound/SE_09.wav");
	music::load(10, L"./Data/Sound/SE_10.wav");
	music::load(11, L"./Data/Sound/SE_11.wav");
	music::load(12, L"./Data/Sound/SE_12.wav");
	/*music::load(13, L"./Data/Sound/SE_13.wav");*/
}

void ongaku::music(int senkyaku)
{
	if (senkyaku < 14)	music::play(senkyaku, false);
	else music::play(senkyaku, true);
	
}