#pragma once

#include "appEnv.hpp"
#include "g_variable.h"


void menu_dis(AppEnv& app_env,
	             int& display,  bool& sugihei_clear)
{
	Media yes_bgm("res/yes_bgm.wav");
	Media no_bgm("res/no_bgm.wav");
	Media menu_bgm("res/menu_bgm.wav");

	Texture menu("res/menu.png");
	Texture people("res/people.png");
	Texture talk("res/talk.png");
	Texture info_kohei("res/info_kohei.png");
	Texture info_clear("res/clear_sugihei.png");
	Texture info_lock("res/info_lock.png");
	Texture word("res/word.png");
	Texture areyouready("res/areyouready.png");


	//依頼主:会話画面
	int scroll = 0;
	int icon_posy = -Window::HEIGHT / 2 + 138;
	float icon_col = 1;
	float info_col = 0;
	bool  info_bool = false;
	bool shop_bool = false;
	bool madam_bool = false;
	bool secret_bool = false;

	bool go = false;


	//menu画面
	float quest_col = 0.8, talk_col = 0.8, save_col = 0.8;
	bool  quest_bool = false, talk_bool = false, save_bool = false;

	while (display == 1)
	{
		//ウインドウが閉じたら終了
		if (!app_env.isOpen()) return;


		//描画準備
		app_env.setupDraw();


		//bgm	 
		if (!menu_bgm.isPlaying() && display == 1)
		{
			menu_bgm.play();
		}

	
		//背景色
		app_env.bgColor(Color(1, 1, 1));
		//マウスポジション
		Vec2f mouse = app_env.mousePosition();

		//menu画面表示
		drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, WIDTH, HEIGHT,
			0, 0, 1200, 512,
			menu,
			Color(1, 1, 1));
		//依頼主,会話相手をy軸にスクロール
		if (app_env.isPushKey(GLFW_KEY_UP) && scroll != 0)
		{
			scroll--;
			info_col = 0;
			go = false;
			info_bool = false;
			shop_bool = false;
			madam_bool = false;
			secret_bool = false;
		}
		if (app_env.isPushKey(GLFW_KEY_DOWN) && scroll != 2)
		{
			scroll++;
			info_col = 0;
			go = false;
			info_bool = false;
			shop_bool = false;
			madam_bool = false;
			secret_bool = false;
		}

		////////////////////依頼者画面
		if (quest_bool == true)
		{
			//表示中は白く
			quest_col = 0;

			//依頼主画面表示
			drawTextureBox(-Window::WIDTH / 2, icon_posy, 1000, 300,
				0, 0 + scroll * 300, 1024, 300,
				people,
				Color(1, icon_col, icon_col));

			//依頼主のアイコンにマウスカーソルを持っていくとアイコンを赤く表示
			if (-Window::WIDTH / 2 < mouse.x() && mouse.x() < -Window::WIDTH / 2 + 300
				&& icon_posy < mouse.y() && mouse.y() < icon_posy + 300
				&& !info_bool)
			{
				icon_col = 0.5;
				int box_size = 40;
				if (app_env.isPushButton(LEFT))
				{
					info_bool = true;
					if (!yes_bgm.isPlaying())
					{
						yes_bgm.play();
					}
				}
			}
			else
			{
				icon_col = 1;
			}

			//アイコンクリックで情報表示
			if (info_bool)
			{
				int i;
				int box_size = 40;
				info_col += 0.017;

				//青のわちゃわちゃ表示 表示位置はランダム　
				for (i = 0; i < 40; i++){
					drawFillBox((-Window::WIDTH / 2 + 250) + rand() % 470, -Window::HEIGHT / 2 + 120 + rand() % 280,
						box_size, box_size,
						Color(0, 0, 0.8, 0.7));
				}
				//情報内容　スクロール位置で判断
				switch (scroll)
				{
				case 0:
					//クリア前
					if (!sugihei_clear)
					{
						drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 110,
							540, 330,
							0, 0, 540, 330,
							info_kohei,
							Color(1, 1, 1, info_col));
					}
					//クリア後
					else
					{
						drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 110,
							540, 330,
							0, 0, 540, 330,
							info_clear,
							Color(1, 1, 1, info_col));
					}
					//表示後
					if (info_col >= 1)
					{

						//左下クリックでAREYOUREADY?画面表示
						if (go)
						{
							drawTextureBox((-Window::WIDTH / 2 + 260), -Window::HEIGHT / 2 + 150, 500, 200,
								0, 0,
								450, 160,
								areyouready,
								Color(1, 1, 0, 1));
							//OKをクリックでbreak
							if ((-Window::WIDTH / 2 + 250) < mouse.x() && mouse.x() < -Window::WIDTH / 2 + 350
								&& -Window::HEIGHT / 2 + 100 < mouse.y() && mouse.y() < -Window::HEIGHT / 2 + 150
								&& app_env.isPushButton(LEFT))
							{
								go = false;
								info_bool = false;
								if (!sugihei_clear)
								{
									menu_bgm.stop();
									display = 2;
									break;
								}
								else
								{
									display = 4;
								}
								if (!yes_bgm.isPlaying())
								{
									yes_bgm.play();
								}
							}
						}
						//左OKボタン
						if (!sugihei_clear)
							drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 100,
							100, 50,
							30, 260, 160, 90,
							word,
							Color(1, 1, 0, 1));
						if ((-Window::WIDTH / 2 + 250) < mouse.x() && mouse.x() < -Window::WIDTH / 2 + 350
							&& -Window::HEIGHT / 2 + 100 < mouse.y() && mouse.y() < -Window::HEIGHT / 2 + 150
							&& app_env.isPushButton(LEFT))
						{
							go = true;
							if (!yes_bgm.isPlaying())
							{
								yes_bgm.play();
							}
						}

					}
					break;
				case 1:
					drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 110,
						540, 330,
						0, 0, 540, 330,
						info_lock,
						Color(1, 1, 1, info_col));
					break;
				case 2:
					drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 110,
						540, 330,
						0, 0, 540, 330,
						info_lock,
						Color(1, 1, 1, info_col));

				}
				//表示後
				if (info_col >= 1)
				{
					//右下クリックで表示を消す
					drawTextureBox((-Window::WIDTH / 2 + 700), -Window::HEIGHT / 2 + 100,
						100, 50,
						30, 130, 170, 90,
						word,
						Color(1, 0, 0, 1));
					if ((-Window::WIDTH / 2 + 700) < mouse.x() && mouse.x() < -Window::WIDTH / 2 + 800
						&& -Window::HEIGHT / 2 + 100 < mouse.y() && mouse.y() < -Window::HEIGHT / 2 + 150
						&& app_env.isPushButton(LEFT))
					{
						info_col = 0;
						info_bool = false;
						go = false;
						if (!no_bgm.isPlaying())
						{
							no_bgm.play();
						}
					}
				}
			}


		}

		///会話表示画面
		if (talk_bool == true)
		{
			go = false;
			//表示中は白く
			talk_col = 0;

			//会話表示
			drawTextureBox(-Window::WIDTH / 2, icon_posy, 1000, 300,
				0, 0 + scroll * 300, 1024, 300,
				talk,
				Color(1, icon_col, icon_col));

			//アイコンにマウスカーソルを持っていくことで情報表示
			if (-Window::WIDTH / 2 < mouse.x() && mouse.x() < -Window::WIDTH / 2 + 300
				&& icon_posy < mouse.y() && mouse.y() < icon_posy + 300
				&& !info_bool)
			{
				icon_col = 0.5;
				int box_size = 40;
				if (app_env.isPushButton(LEFT))
				{
					if (scroll == 0)
					{
						shop_bool = true;
					}
					else if (scroll == 1)
					{
						madam_bool = true;
					}
					else if (scroll == 2)
					{
						secret_bool = true;
					}
				}
			}
			else
			{
				icon_col = 1;
			}

			//アイコンクリックで情報表示
			if (shop_bool || madam_bool || secret_bool)
			{
				int i;
				int box_size = 40;
				info_col += 0.017;
				icon_col = 1;

				//演出：黒のわちゃわちゃをランダムで表示
				for (i = 0; i < 40; i++){
					drawFillBox((-Window::WIDTH / 2 + 250) + rand() % 470, -Window::HEIGHT / 2 + 120 + rand() % 280,
						box_size, box_size,
						Color(0, 0, 0, 0.7));

				}

				drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 110,
					540, 330,
					0, 0, 540, 330,
					info_lock,
					Color(0.7, 0.7, 0.7, info_col));

				//表示後
				if (info_col >= 1)
				{
					//右下クリックで表示を消す
					drawFillBox((-Window::WIDTH / 2 + 700), -Window::HEIGHT / 2 + 100, 100, 50,
						Color(1, 0, 0, 1));

					drawTextureBox((-Window::WIDTH / 2 + 700), -Window::HEIGHT / 2 + 100,
						100, 50,
						30, 130, 170, 90,
						word,
						Color(1, 0, 0, 1));
					if ((-Window::WIDTH / 2 + 700) < mouse.x() && mouse.x() < -Window::WIDTH / 2 + 800
						&& -Window::HEIGHT / 2 + 100 < mouse.y() && mouse.y() < -Window::HEIGHT / 2 + 150
						&& app_env.isPushButton(LEFT))
					{
						info_col = 0;
						shop_bool = false;
						madam_bool = false;
						secret_bool = false;
					}
				}
			}
		}



		//マウスを持ってかないときは灰色
		drawFillBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, 400, 95,
			Color(0.3, 0.3, 0.3, quest_col));
		drawFillBox(-Window::WIDTH / 2 + (400 * 1), -Window::HEIGHT / 2, 400, 95,
			Color(0.3, 0.3, 0.3, talk_col));
		drawFillBox(-Window::WIDTH / 2 + (400 * 2), -Window::HEIGHT / 2, 400, 95,
			Color(0.3, 0.3, 0.3, save_col));

		//依頼主
		if (-Window::WIDTH / 2 < mouse.x() && mouse.x() < -Window::WIDTH / 2 + 400
			&& -Window::HEIGHT / 2 < mouse.y() && mouse.y() < -Window::HEIGHT / 2 + 100)
		{
			quest_col = 0;
			if (app_env.isPushButton(LEFT))
			{
				quest_bool = true;
				talk_bool = false;
				save_bool = false;

				info_bool = false;
				info_col = 0;
			}
		}
		else
		{
			quest_col = 0.8;

		}
		//会話
		if (-Window::WIDTH / 2 + (400 * 1) < mouse.x() && mouse.x() < -Window::WIDTH / 2 + (400 * 2)
			&& -Window::HEIGHT / 2 < mouse.y() && mouse.y() < -Window::HEIGHT / 2 + 100)
		{
			talk_col = 0;
			if (app_env.isPushButton(LEFT))
			{
				quest_bool = false;
				talk_bool = true;
				save_bool = false;

				shop_bool = false;
				madam_bool = false;
				secret_bool = false;
				info_bool = false;
				info_col = 0;

			}
		}
		else
		{
			talk_col = 0.8;
		}
		//セーブ ※機能はつけてません
		if (-Window::WIDTH / 2 + (400 * 2) < mouse.x() && mouse.x() < -Window::WIDTH / 2 + (400 * 3)
			&& -Window::HEIGHT / 2 < mouse.y() && mouse.y() < -Window::HEIGHT / 2 + 100)
		{
			save_col = 0;
			if (app_env.isPushButton(LEFT))
			{
				quest_bool = false;
				talk_bool = false;
				save_bool = true;
			}
		}
		else
		{
			save_col = 0.8;
		}
		std::cout << display << std::endl;

		app_env.update();
	}
	app_env.flushInput();

}