 #include "input_manager.h"

using namespace DirectX;
using namespace GameLib;

void InputManager::init(HWND hwnd)
{
    // �V���O���g���̎擾
    keyboard = &Keyboard::Get();
    gamePad = &GamePad::Get();

    // �E�B���h�E�n���h���̃Z�b�g�i�K�v�j
    keyboard->SetWindow(hwnd);

    // �Q�[���p�b�h�̏�����ԃN���A
    ZeroMemory(pad, sizeof(pad));

    // �L�[/�p�b�h�̊��蓖�āi���Ȃ��̒�`�ɏ]���āj
    setKeyAssign(0, keyAssign00);
    setJoyAssign(0, joyAssign00);
    // ���̃v���C���[�������l�ɐݒ�c
}

void InputManager::update(HWND hwnd)
{
    auto kbState = keyboard->GetState();
    auto padState = gamePad->GetState(0);

    // ���͏����i���j�c
}

int InputManager::getCursorPosX()
{
    GetCursorPos(&mousePos);
    return mousePos.x;
}

int InputManager::getCursorPosY()
{
    GetCursorPos(&mousePos);
    return mousePos.y;
}
