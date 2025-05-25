//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< �C���N���[�h >-----------------------------------------------------------
#include "all.h"
#include <sstream>
#include <memory>
#include <sstream>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include"map.h"
#include "obj.h"
#include "title.h"
#include "sound.h"
#include "serect.h"

//------< �萔 >----------------------------------------------------------------

extern player play;
extern maps stege;
extern obj objs;
extern ongaku o;
title t;
serect s;

//------< �ϐ� >----------------------------------------------------------------

int game_state = 0;    // ���
int game_timer = 0;    // �^�C�}�[
int game_title = 0;
int serect_state = 0;


//--------------------------------------
//  �����ݒ�
//--------------------------------------
void game_init()
{
    serect_state = 0;
	game_state = 0;
	game_timer = 0;
    game_title = 0;
}

//--------------------------------------
//  �X�V����
//--------------------------------------
void game_update()
{
    using namespace input;

    switch (game_state)
    {
    case 0:
        //////// �p�����[�^�̐ݒ� ////////
        GameLib::setBlendMode(Blender::BS_ALPHA);
        o.init();
        game_state++;
    case 1:
   
        t.init();
        game_state++;
    case 2:
        t.update(&game_title);
        t.render();
        if (game_title == 1)
        {
            game_state = 5;
            serect_state = 0;
        }
        if (game_title == 2) game_state++;
        if (game_title > 0) t.deinit();
        break;
    case 3:
        s.init();
        game_state++;
    case 4:
        s.update(&serect_state,&game_state);
        s.render();
        if (game_state == 5) s.deinit();
        break;
    case 5:

        //////// �����ݒ� ////////
        play.init(serect_state);
        stege.init(serect_state);
        objs.init(serect_state);
       
        game_state++;
    case 6:
        //////// �ʏ펞 ////////
        play.update();
        objs.update();
        stege.re(&game_state);
        game_render();
        //stege.update();
        break;
    }

    game_timer++;
}

//--------------------------------------
//  �`�揈��
//--------------------------------------
void game_render()
{
    GameLib::clear(0.0, 0.0, 0.0);
    stege.render();
    play.render();
    objs.render();
}

//--------------------------------------
//  �I������
//--------------------------------------
void game_deinit()
{
    stege.game_deinit();
    play.game_deinit();
    objs.game_deinit();
}

