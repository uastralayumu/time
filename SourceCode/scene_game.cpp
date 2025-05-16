//******************************************************************************
//
//      scene_game.cpp
//
//******************************************************************************

#include "all.h"
#include <sstream>
#include <cmath>  // �����v�Z�Ɏg�p

using namespace DirectX;

//------< �萔 >----------------------------------------------------------------
const int PLANT_GROWTH_MAX = 30;
const int PLANT_GROWTH_MIN = 0;
const int UI_DISTANCE_THRESHOLD = 100; // �v���C���[���A���ɋ߂Â�������臒l

enum TimeOfDay {
    MORNING,
    NIGHT
};

//------< �O���[�o���ϐ� >-----------------------------------------------------
std::unique_ptr<Keyboard> keyboard;
std::unique_ptr<Mouse> mouse;
Mouse::ButtonStateTracker mouseTracker;

//------< �ϐ� >----------------------------------------------------------------
int game_state = 0;
int game_timer = 0;
int plant_growth = 0;
int fertilizer_amount = 0;  // �엿��
int herbicide_amount = 0;   // �����ܗ�

bool show_ui_icon = false;
bool show_ui_menu = false;
TimeOfDay current_time = MORNING;

// UI�X�v���C�g�i���j
Sprite* stage;
Sprite* ueki;
Sprite* plant;
Sprite* ui_icon;
Sprite* ui_menu;

// �v���C���[�̍��W�i���̒l�j
float player_x = 700.0f;
float player_y = 950.0f;

// �A���̍��W�i���������̈ʒu�j
float plant_x = 700.0f;
float plant_y = 920.0f;

//--------------------------------------
// �����ݒ�
//--------------------------------------
void game_init()
{
    game_state = 0;
    game_timer = 0;
    plant_growth = 0;
    fertilizer_amount = 0;
    herbicide_amount = 0;
    current_time = MORNING;

    
}

//--------------------------------------
// �U�zUI�̏���
//--------------------------------------
void handle_spraying_ui()
{
    // �v���C���[�ƐA���̋������v�Z
    float dx = player_x - plant_x;
    float dy = player_y - plant_y;
    float dist = std::sqrt(dx * dx + dy * dy);

    // �v���C���[���߂Â����� UI �A�C�R����\��
    show_ui_icon = (dist < UI_DISTANCE_THRESHOLD);

    // UI �A�C�R�����\������Ă��ăN���b�N���ꂽ�烁�j���[��\���i�����͉������j
    if (show_ui_icon && mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED) {
        show_ui_menu = true;
    }

    // ���j���[���\������Ă���Ԃɔ엿/�����ܗʂ�����i�����ł͉��ɐ��l���Œ�j
    if (show_ui_menu) {
        fertilizer_amount = 2; // ���̓���
        herbicide_amount = 1;  // ���̓���
        show_ui_menu = false;  // ���͌�͕���
    }
}

//--------------------------------------
// �� �� ��̐؂�ւ��Ɛ�������
//--------------------------------------
void update_growth_logic()
{
    if (current_time == NIGHT) {
        // �엿�ɂ�鐬������
        plant_growth += fertilizer_amount;
        if (plant_growth > PLANT_GROWTH_MAX) plant_growth = PLANT_GROWTH_MAX;

        // �����܂ɂ�錸������
        plant_growth -= herbicide_amount;
        if (plant_growth < PLANT_GROWTH_MIN) plant_growth = PLANT_GROWTH_MIN;

        // ���Z�b�g
        fertilizer_amount = 0;
        herbicide_amount = 0;

        // ���͒�
        current_time = MORNING;
    }
}

//--------------------------------------
// �X�V����
//--------------------------------------
void game_update()
{
    
  

    switch (game_state)
    {
    case 0:
        stage = sprite_load(L"./Data/Images/stage_kari.png");
        ueki = sprite_load(L"./Data/Images/ueki_kari.png");
        plant = sprite_load(L"./Data/Images/plant_kari.png");
        ui_icon = sprite_load(L"./Data/Images/ui_icon_kari.png");   // ��
        ui_menu = sprite_load(L"./Data/Images/ui_menu_kari.png");   // ��
        GameLib::setBlendMode(Blender::BS_ALPHA);
        game_state++;
        break;

    case 1:
        // �U�zUI����
        handle_spraying_ui();

        // �����E���������i��j
        update_growth_logic();

        // ���Ԑ؂�ւ��̃g���K�[�F�����ł�F�L�[�Ő؂�ւ�
        static bool f_prev = false;
       

        
       
        break;
    }

    game_timer++;
}

//--------------------------------------
// �`�揈��
//--------------------------------------
void game_render()
{
    sprite_render(stage, 0, 0);
    sprite_render(ueki, 700, 950);
    sprite_render(plant, 700, 920 - plant_growth);

    if (show_ui_icon) {
        sprite_render(ui_icon, plant_x + 50, plant_y - 50); // UI�}�[�N
    }

    if (show_ui_menu) {
        sprite_render(ui_menu, 600, 400); // �U�z�ʑI��pUI
    }
}

//--------------------------------------
// �I������
//--------------------------------------
void game_deinit()
{
    safe_delete(stage);
    safe_delete(ueki);
    safe_delete(plant);
    safe_delete(ui_icon);
    safe_delete(ui_menu);
}
