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

//------< �萔 >----------------------------------------------------------------

extern player play;
extern maps stege;
extern obj objs;
//------< �ϐ� >----------------------------------------------------------------

int game_state = 0;    // ���
int game_timer = 0;    // �^�C�}�[



//--------------------------------------
//  �����ݒ�
//--------------------------------------
void game_init()
{

	game_state = 0;
	game_timer = 0;
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
        //////// �����ݒ� ////////
        play.init();
        stege.init();
        objs.init();
       
        game_state++;
    case 1:
        //////// �p�����[�^�̐ݒ� ////////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        game_state++;
        /*fallthrough*/
    case 2:
        //////// �ʏ펞 ////////
        play.update();
        objs.update();
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
    
}

