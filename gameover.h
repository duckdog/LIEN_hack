#pragma once

#include "appEnv.hpp"
#include "g_variable.h"


void gameover_dis(AppEnv& app_env, int& display)
{
	//gameover
	Texture game_over("res/timeover.png");

	while (display == 3)
	{
		//�A�v���E�C���h�E������ꂽ��v���O�������I��
		if (!app_env.isOpen()) return;


		//�`�揀��
		app_env.setupDraw();

		drawTextureBox(-WIDTH / 2, -HEIGHT / 2,
			1200, 500,
			0, 0, 1200, 500,
			game_over,
			Color(1, 1, 1));



		//D�ŃR���e�B�j���[
		if (app_env.isPushKey('D') && !app_env.isPressKey(GLFW_KEY_UP))
		{
			display = 2;
			break;
		}
		//A�Ń��j���[���
		if (app_env.isPushKey('A') && !app_env.isPressKey(GLFW_KEY_UP))
		{
			display = 1;
			break;
		}

		//��ʍX�V
		app_env.update();
	}
	app_env.flushInput();

}