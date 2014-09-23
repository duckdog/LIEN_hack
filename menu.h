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


	//�˗���:��b���
	int scroll = 0;
	int icon_posy = -Window::HEIGHT / 2 + 138;
	float icon_col = 1;
	float info_col = 0;
	bool  info_bool = false;
	bool shop_bool = false;
	bool madam_bool = false;
	bool secret_bool = false;

	bool go = false;


	//menu���
	float quest_col = 0.8, talk_col = 0.8, save_col = 0.8;
	bool  quest_bool = false, talk_bool = false, save_bool = false;

	while (display == 1)
	{
		//�E�C���h�E��������I��
		if (!app_env.isOpen()) return;


		//�`�揀��
		app_env.setupDraw();


		//bgm	 
		if (!menu_bgm.isPlaying() && display == 1)
		{
			menu_bgm.play();
		}

	
		//�w�i�F
		app_env.bgColor(Color(1, 1, 1));
		//�}�E�X�|�W�V����
		Vec2f mouse = app_env.mousePosition();

		//menu��ʕ\��
		drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, WIDTH, HEIGHT,
			0, 0, 1200, 512,
			menu,
			Color(1, 1, 1));
		//�˗���,��b�����y���ɃX�N���[��
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

		////////////////////�˗��҉��
		if (quest_bool == true)
		{
			//�\�����͔���
			quest_col = 0;

			//�˗����ʕ\��
			drawTextureBox(-Window::WIDTH / 2, icon_posy, 1000, 300,
				0, 0 + scroll * 300, 1024, 300,
				people,
				Color(1, icon_col, icon_col));

			//�˗���̃A�C�R���Ƀ}�E�X�J�[�\���������Ă����ƃA�C�R����Ԃ��\��
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

			//�A�C�R���N���b�N�ŏ��\��
			if (info_bool)
			{
				int i;
				int box_size = 40;
				info_col += 0.017;

				//�̂킿��킿��\�� �\���ʒu�̓����_���@
				for (i = 0; i < 40; i++){
					drawFillBox((-Window::WIDTH / 2 + 250) + rand() % 470, -Window::HEIGHT / 2 + 120 + rand() % 280,
						box_size, box_size,
						Color(0, 0, 0.8, 0.7));
				}
				//�����e�@�X�N���[���ʒu�Ŕ��f
				switch (scroll)
				{
				case 0:
					//�N���A�O
					if (!sugihei_clear)
					{
						drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 110,
							540, 330,
							0, 0, 540, 330,
							info_kohei,
							Color(1, 1, 1, info_col));
					}
					//�N���A��
					else
					{
						drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 110,
							540, 330,
							0, 0, 540, 330,
							info_clear,
							Color(1, 1, 1, info_col));
					}
					//�\����
					if (info_col >= 1)
					{

						//�����N���b�N��AREYOUREADY?��ʕ\��
						if (go)
						{
							drawTextureBox((-Window::WIDTH / 2 + 260), -Window::HEIGHT / 2 + 150, 500, 200,
								0, 0,
								450, 160,
								areyouready,
								Color(1, 1, 0, 1));
							//OK���N���b�N��break
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
						//��OK�{�^��
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
				//�\����
				if (info_col >= 1)
				{
					//�E���N���b�N�ŕ\��������
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

		///��b�\�����
		if (talk_bool == true)
		{
			go = false;
			//�\�����͔���
			talk_col = 0;

			//��b�\��
			drawTextureBox(-Window::WIDTH / 2, icon_posy, 1000, 300,
				0, 0 + scroll * 300, 1024, 300,
				talk,
				Color(1, icon_col, icon_col));

			//�A�C�R���Ƀ}�E�X�J�[�\���������Ă������Ƃŏ��\��
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

			//�A�C�R���N���b�N�ŏ��\��
			if (shop_bool || madam_bool || secret_bool)
			{
				int i;
				int box_size = 40;
				info_col += 0.017;
				icon_col = 1;

				//���o�F���̂킿��킿��������_���ŕ\��
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

				//�\����
				if (info_col >= 1)
				{
					//�E���N���b�N�ŕ\��������
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



		//�}�E�X�������Ă��Ȃ��Ƃ��͊D�F
		drawFillBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, 400, 95,
			Color(0.3, 0.3, 0.3, quest_col));
		drawFillBox(-Window::WIDTH / 2 + (400 * 1), -Window::HEIGHT / 2, 400, 95,
			Color(0.3, 0.3, 0.3, talk_col));
		drawFillBox(-Window::WIDTH / 2 + (400 * 2), -Window::HEIGHT / 2, 400, 95,
			Color(0.3, 0.3, 0.3, save_col));

		//�˗���
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
		//��b
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
		//�Z�[�u ���@�\�͂��Ă܂���
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