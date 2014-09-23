#pragma once

#include "appEnv.hpp"
#include "g_variable.h"


void gameover_dis(AppEnv& app_env, int& display)
{
	//gameover
	Texture game_over("res/timeover.png");

	while (display == 3)
	{
		//アプリウインドウが閉じられたらプログラムを終了
		if (!app_env.isOpen()) return;


		//描画準備
		app_env.setupDraw();

		drawTextureBox(-WIDTH / 2, -HEIGHT / 2,
			1200, 500,
			0, 0, 1200, 500,
			game_over,
			Color(1, 1, 1));



		//Dでコンティニュー
		if (app_env.isPushKey('D') && !app_env.isPressKey(GLFW_KEY_UP))
		{
			display = 2;
			break;
		}
		//Aでメニュー画面
		if (app_env.isPushKey('A') && !app_env.isPressKey(GLFW_KEY_UP))
		{
			display = 1;
			break;
		}

		//画面更新
		app_env.update();
	}
	app_env.flushInput();

}