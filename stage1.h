#pragma once

#include "appEnv.hpp"
#include "function.h"
#include "g_variable.h"




void stage1(AppEnv& app_env,Media& gameover_bgm,
	           int& display, bool& sugihei_clear)
{

	Media clear_bgm("res/clear_bgm.wav");
	Media down_bgm("res/down.wav");
	Media boss_bgm("res/boss_bgm.wav");
	Media warp_bgm("res/warp.wav");
	Media main_bgm("res/main_bgm.wav");
	Media dog_bgm("res/dog_bgm.wav");
	Media bomb_bgm("res/bomb.wav");
	Media item_bgm("res/item_get.wav");
	Media warning("res/warning.wav");
	Media walk_bgm("res/walk_sound.wav");
	Media hacking_bgm("res/hacking.wav");
	Media comp_bgm("res/item_comp.wav");
	Media loap_bgm("res/loap.wav");
	Media wipe_bgm("res/wipe.wav");


	Texture man("res/man.png");
	Texture man2("res/tunaoti.png");
	Texture man3("res/fly.png");
	Texture man4("res/man3.png");
	Texture talk_plate("res/talk_plate.png");
	Texture talk_date("res/talk_stage1.png");
	Texture main_bg("res/main_bg.png");
	Texture word2("res/word2.png");
	Texture stamp("res/stamp.png");
	Texture map("res/map.png");
	Texture hack_logo("res/hack_logo.png");
	Texture date("res/date.png");
	Texture icon("res/icon.png");
	Texture enemy("res/enemy3.png");
	Texture mission_list("res/mission.png");
	Texture hp_etc("res/hp_etc.png");
	Texture wall("res/block.png");
	Texture boss_bg("res/boss_bg.png");
	Texture bomb("res/bom.png");
	Texture bomb_word("res/bom_word.png");
	Texture clear("res/clear.png");
	Texture clear_ward("res/clear_ward.png");
	//���C���L����
	int   man_sizex = 31, man_sizey = 59;   //�\���T�C�Y
	float man_posx = 500.0, man_posy = 0.0; //�\���ʒu
	int   man_move = 0, value = 0;          //���[�V�����p�ϐ�
	int   v = 5;                            //���x
	int   siren = 0;
	float n_gravity = 0.01;
	float life = 3 * 60 * 60;
	bool  down_man = false;
	bool  no_move = false;
	bool  see_left = false;                 //��������
	bool  get = false;
	int r = 0;
	int g = 0;
	int b = 1;

	int n = 0;
	int item_count[] =
	{
		1, 1, 1,
		1, 1, 1,
		1, 1
	};

	int item = 0;
	int map_count = 0;

	//�n��
	float scroll_count = -1;
	float side_scroll = 0;
	float rand_posy = 0;
	int   rand_x = 800;
	float t = 1;
	bool  down = false;
	int   word_count = 37;

	//�A�C�e��   
	float obj_pos = 0;
	float date_sizex = 210;
	float date_sizey = 240;
	int   get_count = 0;
	int m_sound_count = 0;

	//s��Q��
	int   enemy_action = 0;
	float time = 0;
	float ww = 1;
	bool on = false;
	float map_load = 0;
	float map_col = 0;
	int loap_size = 0;
	float bullet = 0;
	int stop_bar = 0;
	float bar_col = 1;
	int unlock = 0;
	int   bgm_count = 0;

	//BOSS�A�N�V�����p
	int boss_action = 0;
	int wall_posy = 0;
	int wall_posy2 = 0;
	int wall_posy3 = 0;
	int nomove_count = 0;
	int end_efect = 0;
	bool boss = false;

	//clear��
	int man_action = 0;
	//gameover
	int sound_count = 0;


	//�w�i�F
	app_env.bgColor(Color(0, 0, 0));

	//�W�����v
	Jump jump = {
		0.0f,
		0.0f,
		false
	};
	while(display == 2)
	{

		//�E�C���h�E��������I��
		if (!app_env.isOpen()) return;

		//�`�揀��
		app_env.setupDraw();

		///BGM
		//main_bgm
		if (!main_bgm.isPlaying())
		{
			main_bgm.play();
		}
		//dog
		if (boss)
		{
			if (!dog_bgm.isPlaying())
			{
				dog_bgm.play();
				dog_bgm.gain(0.3);
				dog_bgm.pitch(0.8);
			}
		}
		//walk_bgm
		if ((app_env.isPressKey(GLFW_KEY_LEFT) ||
			app_env.isPressKey(GLFW_KEY_RIGHT)) &&
			!boss && !down && !jump.jumping)
		{
			if (!walk_bgm.isPlaying())
			{
				walk_bgm.play();
				walk_bgm.gain(0.3);
				walk_bgm.pitch(2);
			}
		}
		else
		{
			walk_bgm.stop();
		}
		//item_get
		if (item == 1 + n &&!item_bgm.isPlaying())
		{
			if (8 > item)
			{
				item_bgm.play();
				n++;
			}
			if (8 == item &&!comp_bgm.isPlaying())
			{
				comp_bgm.play();
				n++;
			}
		}
		//boss_bgm
		if (boss)
		{
			main_bgm.stop();
			if (!boss_bgm.isPlaying())
			{
				boss_bgm.play();
			}
		}
		//�}�E�X�|�W�V����
		Vec2f mouse = app_env.mousePosition();

		drawTextureBox(-WIDTH / 2, -HEIGHT / 2, 1500, 500,
			0, 0 + rand_posy / 30,
			2048, 500,
			main_bg,
			Color(1, 1, 1));

		enemy_action += 1;
		drawFillBox(-WIDTH + 10, HEIGHT / 2 - 10, life / 10 - time / 10, 10, Color(0, 0, 1));
		if (life / 3  < time)
		{
			drawFillBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, Color(1, 0, 0, std::abs(::sin(time / 100))));
		}

		/////////////////�{�ҏ�Q���A�A�C�e���A�摜�\����


		if (scroll_count == -1)
		{
			//bgm���ʒ���
			main_bgm.gain(0.1);
			man_posy = -HEIGHT / 2 + man_sizey;
			//0 mision List
			drawTextureBox(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, WIDTH, HEIGHT,
				mission_list,
				Color(1, 1, 1, 1 - time / 100));

			if (man_posx < -400)
			{
				if (!wipe_bgm.isPlaying())
				{
					wipe_bgm.play();
				}
				time += 1;
				drawFillBox(-WIDTH / 2 + rand() % WIDTH, -HEIGHT / 2 + rand() % HEIGHT * 2, 100, 100, Color(0, 1, 1));
				drawFillBox(-WIDTH / 2 + rand() % WIDTH, -HEIGHT / 2 + rand() % HEIGHT * 1.5, 100, 100, Color(0, 0, 1));
				drawFillBox(-WIDTH / 2 + rand() % WIDTH, -HEIGHT / 2 + rand() % HEIGHT * 1.1, 100, 100, Color(0, 1, 1));
				drawFillBox(-WIDTH / 2 + rand() % WIDTH, -HEIGHT / 2 + rand() % HEIGHT / 2, 100, 100, Color(0, 0, 0));
				drawFillBox(-WIDTH / 2 + rand() % WIDTH, -HEIGHT / 2 + rand() % HEIGHT, 100, 100, Color(0, 0, 0));
				drawFillBox(-WIDTH / 2 + rand() % WIDTH, -HEIGHT / 2 + rand() % HEIGHT, 100, 100, Color(0, 0, 0));
				drawFillBox(-WIDTH / 2 + rand() % WIDTH, -HEIGHT / 2 + rand() % HEIGHT, 100, 100, Color(0, 0, 0));
				drawFillBox(-WIDTH / 2 + rand() % WIDTH, -HEIGHT / 2 + rand() % HEIGHT, 100, 100, Color(0, 0, 0));
				if (1 - time / 100 < 0)
				{
					scroll_count++;
					man_posx = -250;
					man_posy = 200;
					down_man = true;
				}
			}
			else
			{
				wipe_bgm.pause();
			}
		}
		else
		{

			//�Q�[��������
			time += 1;
			main_bgm.gain(0.5);
			wipe_bgm.stop();
			///////icon�\��

			//���̃L�����A�C�R��
			drawTextureBox(-WIDTH / 2, +rand_posy - man_sizey,
				140, 100, 0, 0, 140, 100,
				icon,
				Color(1, 1, 1));
			drawTextureBox(-WIDTH / 2, -600 + rand_posy - man_sizey,
				140, 100, 0, 0, 140, 100,
				icon,
				Color(1, 1, 1));
			drawTextureBox(-WIDTH / 2, -900 + rand_posy - man_sizey,
				140, 100, 0, 0, 140, 100,
				icon,
				Color(1, 1, 1));
			drawTextureBox(-WIDTH / 2, -1500 + rand_posy - man_sizey,
				140, 100, 0, 0, 140, 100,
				icon,
				Color(1, 1, 1));
			drawTextureBox(-WIDTH / 2, -2700 + rand_posy - man_sizey,
				140, 100, 0, 0, 140, 100,
				icon,
				Color(1, 1, 1));
			drawTextureBox(-WIDTH / 2 - side_scroll, -3300 + rand_posy - man_sizey,
				140, 100, 0, 0, 140, 100,
				icon,
				Color(1, 1, 1));

			//�E�̃L�����A�C�R��
			drawTextureBox(WIDTH / 2 - 140, -300 + rand_posy - man_sizey,
				140, 100, 0, 101, 140, 100,
				icon,
				Color(1, 1, 1));
			drawTextureBox(WIDTH / 2 - 140, -1200 + rand_posy - man_sizey,
				140, 100, 0, 101, 140, 100,
				icon,
				Color(1, 1, 1));
			drawTextureBox(WIDTH / 2 - 140 - side_scroll, -3000 + rand_posy - man_sizey,
				140, 100, 0, 101, 140, 100,
				icon,
				Color(1, 1, 1));


			//��Q��1 �L�����N�^�[���t�����������Ă���ʍs�\��
			drawTextureBox(0 + 100 * std::sin(time / 100), rand_posy, 100, 250, stop_bar, 666, 150, 300, enemy, Color(1, 1, 1));
			if (scroll_count == 0)
			{
				if (Touch(man_posx, man_posy + jump.y, 0 + 100 * std::sin(time / 100), rand_posy, 100, 250))
				{
					//�E�������Ă��獶���ɑ��x��
					if (!see_left)
					{

						man_posx -= v + 1;

					}
					//���������Ă���E���ɑ��x��
					else
					{
						man_posx += v + 1;

					}
				}
				if (!see_left)
				{
					stop_bar = 0;
				}
				else
				{
					stop_bar = 150;
				}
			}

			//�X�C�b�`�@���@���[�v
			drawTextureBox(400, rand_posy - 300,
				50, 50,
				490, 736, 179, 178,
				enemy,
				Color(ww, 1, ww));
			// ���[�v�o��
			drawTextureBox(-200, rand_posy - 300,
				50, 50, 490, 736,
				179, 178,
				enemy,
				Color(ww, 1, ww));
			//����ł�Ƃ������Ǐ���
			if (!on)drawTextureBox(-100, rand_posy - 300,
				30, 100, 325, 655,
				75, 367,
				enemy,
				Color(1, 0, 1));
			if (Touch(man_posx, man_posy + jump.y, 400, rand_posy - 300, 50, 50))
			{
				//������x�̂������ŃW�����v�ʒu�Œ��n
				if (jump.jumping && jump.y >= rand_posy - 260)
				{
					ww = 0;
					jump.jumping = false;
					on = true;
					bar_col -= 0.01;
					if (bar_col <= 0)
					{
						bar_col = 0;
					}
				}
				//��ɂ��������烏�[�v�i�E�����j
				else if (!see_left  && !on)
				{
					//bgm
					if (!warp_bgm.isPlaying())
					{
						warp_bgm.play();
					}
					man_posx = -200 - man_sizex;
					jump.jumping = false;
					down_man = true;

				}
				//��ɓ����i�������j
				else if (see_left  && !on)
				{
					man_posx = -200 - man_sizex;
					jump.jumping = false;
					down_man = true;

				}

			}
			else
			{
				down_man = true;
				on = false;
				ww = 1;
			}



			//�ʂ���V
			if (Touch(man_posx, man_posy + jump.y, -100, rand_posy - 300, 30, 100))
			{
				if (!see_left)
				{
					man_posx = -100 - man_sizex;

				}
				else
				{
					man_posx = -70;

				}

			}


			///�X�e�[�W�n�ʕ\��
			{
				//1
				drawTextureBox(-WIDTH / 2 + 140, -man_sizey + rand_posy,
					word_count * 18, man_sizey,
					0, 0, word_count * 18, 40,
					talk_date,
					Color(1, 1, 1));
				//2
				drawTextureBox(-WIDTH / 2 + 1060 - word_count * 21, -man_sizey - 300 + rand_posy,
					word_count * 21, man_sizey,
					0, 40, word_count * 21, 40,
					talk_date,
					Color(1, 1, 1));
				//3
				drawTextureBox(-WIDTH / 2 + 140, -man_sizey - 600 + rand_posy,
					word_count * 8, man_sizey,
					0, 80, word_count * 8, 40,
					talk_date,
					Color(1, 1, 1));
				//4
				drawTextureBox(-WIDTH / 2 + 140, -man_sizey - 900 + rand_posy,
					word_count * 8, man_sizey,
					0, 120, word_count * 8, 40,
					talk_date,
					Color(1, 1, 1));
				//5
				drawTextureBox(-WIDTH / 2 + 1060 - word_count * 13, -man_sizey - 1200 + rand_posy,
					word_count * 13, man_sizey,
					0, 160, word_count * 13, 40,
					talk_date,
					Color(1, 1, 1));
				//6
				drawTextureBox(-WIDTH / 2 + 140, -man_sizey - 1500 + rand_posy,
					word_count * 10, man_sizey,
					0, 200, word_count * 10, 40,
					talk_date,
					Color(1, 1, 1));
				drawFillBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -man_sizey - 1500 + rand_posy,
					100, man_sizey,
					Color(1, 1, 1));
				//7�X�^���v
				drawTextureBox(-WIDTH / 2 + 660, -man_sizey - 1900 + rand_posy,
					400, 400, 0, 0,
					1024, 1024,
					stamp,
					Color(1, 1, 1));
				//8map
				drawTextureBox(-WIDTH / 2 + 660, -man_sizey - 2400 + rand_posy,
					500, 500, 0, 0,
					750, 1000,
					map,
					Color(1, 1, 1));
				//9
				if (map_col < 1)
				{
					int i;
					for (i = 0; i * 50 < WIDTH; ++i){
						drawTextureBox(-WIDTH / 2 + (i * 50), -man_sizey - 2700 + rand_posy,
							50, 50,
							490, 736, 179, 178,
							enemy,
							Color(ww, 1, ww));
					}
				}
				else
				{
					drawTextureBox(-WIDTH / 2 + 140, -man_sizey - 2700 + rand_posy,
						word_count * 10, man_sizey,
						0, 240, word_count * 10, 40,
						talk_date,
						Color(1, 1, 1));
					drawTextureBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -man_sizey - 2700 + rand_posy,
						100, man_sizey,
						0, 280, 100, 70,
						hp_etc,
						Color(1, 1, 1));
				}
				//10
				drawTextureBox(-WIDTH / 2 + 1060 - word_count * 12 - side_scroll, -man_sizey - 3000 + rand_posy,
					word_count * 12, man_sizey, 0, 280,
					word_count * 12, 40,
					talk_date,
					Color(1, 1, 1));
				//�S�ẴA�C�e���l�����Ă���Ε\��
				if (item == 8)
				{
					drawTextureBox(-WIDTH / 2 + 1060 - word_count * 12 - side_scroll, -man_sizey - 3000 - man_sizey + rand_posy,
						word_count * 12, man_sizey, 0, 320,
						word_count * 12, 40,
						talk_date, Color(1, 1, 1));
				}
				else
				{
					drawTextureBox(-WIDTH / 2 + 1060 - word_count * 12 - side_scroll, -man_sizey - 3000 - man_sizey + rand_posy,
						word_count * 12, man_sizey, 0, 320,
						word_count * 12, 40,
						wall,
						Color(1, 1, 1));
					drawTextureBox(-WIDTH / 2 + 1060 - word_count * 12 - side_scroll, -man_sizey - 3000 - man_sizey + rand_posy,
						word_count * 12, man_sizey,
						0, 55, 512, 50,
						word2,
						Color(0, 0, 0));

				}
				//11���X�g
				drawTextureBox(-WIDTH / 2 + 140 - side_scroll, -man_sizey - 3300 + rand_posy,
					word_count * 12, man_sizey, 0, 360,
					word_count * 12, 40, talk_date, Color(1, 1, 1));



			}
			//�n�ʁF�A�C�e���F�i���Ƃ̃A�C�e���̓����蔻��
			{
				//�P�i��(scroll_count��"0"�X�^�[�g)�����A�Ȃɂ��Ă���
				if (Rand_on(man_posx, 140 + -WIDTH / 2, word_count * 18) && scroll_count == 0)
				{
					down = true;
					scroll_count++;
				}
				//�A�C�e��
				if (item_count[0])
				{
					if (!Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + word_count * 16,
						rand_posy + abs(16 * sin(time / 50)), date_sizex / 4, date_sizey / 4))
					{
						drawTextureBox(-WIDTH / 2 + word_count * 16, rand_posy + abs(16 * sin(time / 50)),
							date_sizex / 4, date_sizey / 4, 0, 0,
							date_sizex, date_sizey,
							date,
							Color(1, 1, 1));
					}
					else
					{
						item_count[0] = 0;
						item++;
					}
				}
				//�Q�i�ځ@��邢�A�Ƃ肱��ł���
				if (Rand_on(man_posx, -WIDTH / 2 + 1060 - word_count * 21, word_count * 21) && scroll_count == 1)
				{
					down = true;
					scroll_count++;
				}
				//�A�C�e��2
				if (item_count[1])
				{
					if (!Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 1060 - word_count * 21,
						-300 + rand_posy + abs(16 * sin(time / 50)), date_sizex / 4, date_sizey / 4))
					{
						drawTextureBox(-WIDTH / 2 + 1060 - word_count * 21, -300 + rand_posy + abs(16 * sin(time / 50)),
							date_sizex / 4, date_sizey / 4,
							0, 0, date_sizex, date_sizey,
							date,
							Color(1, 1, 1));
					}
					else
					{
						item_count[1] = 0;
						item++;
					}
				}
				//3�i�ځ@�ꏊ��
				if (Rand_on(man_posx, 140 + -WIDTH / 2, word_count * 8) && scroll_count == 2 && rand_posy == 600)
				{
					down = true;
					scroll_count++;
				}
				//�A�C�e��3
				if (item_count[2])
				{
					if (!Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + word_count * 10,
						-800 + rand_posy + abs(16 * sin(time / 50)), date_sizex / 4, date_sizey / 4))
					{
						drawTextureBox(-WIDTH / 2 + word_count * 10, -800 + rand_posy + abs(16 * sin(time / 50)),
							date_sizex / 4, date_sizey / 4, 0, 0, date_sizex, date_sizey, date, Color(1, 1, 1));
					}
					else
					{
						item_count[2] = 0;
						item++;
					}
				}
				//4�i�ځ@�Ïؔԍ�����
				if (Rand_on(man_posx, 140 + -WIDTH / 2, word_count * 8) && scroll_count == 3 && rand_posy >= 900)
				{
					down = true;
					scroll_count++;

				}
				//�A�C�e��4
				if (item_count[3])
				{
					if (!Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + word_count * 16,
						-1100 + rand_posy + abs(16 * sin(time / 50)), date_sizex / 4, date_sizey / 4))
					{
						drawTextureBox(-WIDTH / 2 + word_count * 16, -1100 + rand_posy + abs(16 * sin(time / 50)),
							date_sizex / 4, date_sizey / 4, 0, 0, date_sizex, date_sizey, date, Color(1, 1, 1));
					}
					else
					{
						item_count[3] = 0;
						item++;
					}
				}
				//5�i�ځ@���傤����ł���
				if (Rand_on(man_posx, -WIDTH / 2 + 1060 - word_count * 13, word_count * 13) && scroll_count == 4 && rand_posy == 1200)
				{
					down = true;
					scroll_count++;
				}
				//�A�C�e��5
				if (item_count[4])
				{
					if (!Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 1060 - word_count * 1,
						-1200 + rand_posy + abs(16 * sin(time / 50)), date_sizex / 4, date_sizey / 4))
					{
						drawTextureBox(-WIDTH / 2 + 1060 - word_count * 1, -1200 + rand_posy + abs(16 * sin(time / 50)),
							date_sizex / 4, date_sizey / 4, 0, 0, date_sizex, date_sizey, date, Color(1, 1, 1));
					}
					else
					{
						item_count[4] = 0;
						item++;
					}
				}
				//	���[�U�[����
				if (unlock != 3)
				{
					int i;

					for (i = 0; i * 5 <= date_sizey / 3; ++i){
						drawFillBox(-WIDTH / 2 + 1060 - word_count * 1 - 20, -1200 + rand_posy + abs(16 * sin(time / 50)) + (5 * i),
							date_sizex / 4 + 20, 3,
							Color(1, 0, 0, 0.7));
					}
					if (Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 1060 - word_count * 1 - 20, -1200 + rand_posy + abs(16 * sin(time / 50)),
						date_sizex / 4 + 20, 5 * i))
					{
						man_posx = 0;
						man_posy = 200;
						down_man = true;
						warp_bgm.play();
					}
				}
				//�����{�^�� ���Ԓʂ�ɂӂ��Ɖ���
				drawTextureBox(0, -1200 + rand_posy, 30, 30,         //2
					1 * 21 * 2, 387, 22, 27,
					hp_etc,
					Color(unlock * 0.5, unlock * 0.3, unlock * 0.3));
				drawTextureBox(0 + 100, -1200 + rand_posy, 30, 30,   //3
					1 * 21 * 3, 387, 22, 27,
					hp_etc,
					Color(unlock * 0.5, unlock * 0.3, unlock * 0.3));
				drawTextureBox(0 + 200, -1200 + rand_posy, 30, 30,   //1
					1 * 21 * 1, 387, 22, 27,
					hp_etc,
					Color(unlock * 0.5, unlock * 0.3, unlock * 0.3));
				if (Touch(man_posx, man_posy + jump.y, 0, -1200 + rand_posy, 30, 30))
				{
					if (unlock == 1 || unlock == 2)
					{
						unlock = 2;
					}
					else
					{
						unlock = 0;
					}
				}
				if (Touch(man_posx, man_posy + jump.y, 200, -1200 + rand_posy, 30, 30))
				{
					if (unlock == 2 || unlock == 3)
					{
						unlock = 3;
						if (!comp_bgm.isPlaying() && bgm_count == 0)
						{
							comp_bgm.play();
							bgm_count = 1;
						}
					}
					else
					{
						unlock = 0;
					}
				}
				if (Touch(man_posx, man_posy + jump.y, 100, -1200 + rand_posy, 30, 30))
				{
					if (unlock == 0 || unlock == 1)
					{
						unlock = 1;
					}
					else
					{
						unlock = 0;
					}
				}



				//6�i�ځ@��������c
				if (Rand_on(man_posx, -WIDTH / 2 + 140, word_count * 10) && scroll_count == 5 && rand_posy == 1500 &&
					Rand_on(man_posx, -WIDTH / 2 + 140 + word_count * 10 + 100, 100) && scroll_count == 5 && rand_posy == 1500 && !jump.jumping)
				{
					down = true;
					scroll_count++;
				}
				else if (rand_posy == 1500)
				{
					scroll_count = 5;
				}
				//�A�C�e��6
				if (item_count[5])
				{
					if (!Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 140 + word_count * 10 + 100,
						-1500 + rand_posy + abs(16 * sin(time / 50)), date_sizex / 4, date_sizey / 4))
					{
						drawTextureBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -1500 + rand_posy + abs(16 * sin(time / 50)),
							date_sizex / 4, date_sizey / 4, 0, 0, date_sizex, date_sizey, date, Color(1, 1, 1));
					}
					else
					{
						item_count[5] = 0;
						item++;
					}
				}
				//�y��
				drawTextureBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -man_sizey - 1500 + rand_posy,
					100, man_sizey,
					0, 280, 100, 70,
					hp_etc,
					Color(1, 1, 1));
				//�͂����i�j�̗\��j��ɂ̂�����͂����o��
				if (!Rand_on(man_posx, -WIDTH / 2 + 140 + word_count * 10 + 100, 10)
					&& (scroll_count == 5 || scroll_count == 9)
					&& !down)
				{

					//�j
					drawTextureBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -2700 + rand_posy,
						10, 1200,
						300, 110,
						50, 500,
						hp_etc,
						Color(1, 1, 1));

					//�j������łȂ��Ƃ��͉��ɓ�����
					if (rand_posy == 1500 || rand_posy == 2700)
					{
						get = false;
						no_move = false;
						if (scroll_count == 5)
						{
							loap_size = 0;
						}
					}
					//����ł�Ƃ��̃L�����N�^�[�摜
					if (rand_posy > 1500 && rand_posy < 2700 && !jump.jumping)
					{
						man_posx = -WIDTH / 2 + 140 + word_count * 10 + 90;
						get = true;
						drawTextureBox(man_posx, man_posy + jump.y, man_sizex,
							man_sizey, 0, 0,
							man_sizex * 3, man_sizey * 3,
							man2, Color(1, 1, 1));

					}
					else
					{
						get == false;
					}

					//����
					if (app_env.isPressKey(GLFW_KEY_DOWN) && rand_posy < 2700 && !down)
					{
						no_move = true;
						rand_posy += 5;
						loap_size += 5;
					}
					//�o��
					if (app_env.isPressKey(GLFW_KEY_UP) && rand_posy > 1500 && !down)
					{
						no_move = true;
						rand_posy -= 5;
						loap_size -= 5;
					}

					//����
					if (app_env.isPressKey(GLFW_KEY_DOWN) && rand_posy < 2700 ||
						app_env.isPressKey(GLFW_KEY_UP) && rand_posy > 1500 && !down)
					{
						if (!loap_bgm.isPlaying())
						{
							loap_bgm.play();
							loap_bgm.gain(0.5);
							loap_bgm.pitch(5.5);
						}
					}
					else
					{
						loap_bgm.stop();
					}


				}
				//�ʏ펞�j������łȂ��ƒ�`
				else
				{
					get = false;
				}
				if (rand_posy == 2700 && loap_size > 1199)
				{
					drawFillBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -man_sizey - 1500 + rand_posy,
						10, 10 + loap_size, Color(0.5, 0.5, 0.5));
				}

				//�ӂ[�ɗ��������蒼��
				if (scroll_count == 6 || scroll_count == 7 || scroll_count == 8)
				{
					down = true;
					scroll_count++;
				}
				//�����ŏ����l�փ��[�v
				if (rand_posy == 9 * 300 && map_col < 1)
				{
					if (!warp_bgm.isPlaying())
					{
						warp_bgm.play();
					}
					scroll_count = 5;
					rand_posy = 1500;
					man_posx = -100;
					no_move = false;
				}

				//�}�b�v�̋߂��ɂ��ƃn�b�N�{�^���\��
				//7�`8 �i���@map
				drawTextureBox(-WIDTH / 2 + 660, -man_sizey - 2400 + rand_posy, 500, 500, 0, 0, 750, 1000, map, Color(map_col, map_col, map_col));
				if (Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 560, -man_sizey - 2400 + rand_posy, 500, 500) && scroll_count == 5)
				{
					//�����Ă�Ƃ�
					if (app_env.isPressKey('W') && map_col < 1)
					{
						drawTextureBox(man_posx, man_posy + jump.y + 50, 100, 60, 0, 60, 400, 60, hack_logo, Color(1, 1, 1, std::abs(::sin(time / 100))));
						map_col += 0.006;
						if (!hacking_bgm.isPlaying())
						{
							hacking_bgm.play();
							hacking_bgm.pitch(2);
						}

					}
					//�����ĂȂ��Ƃ�
					if (!app_env.isPressKey('W') && map_col < 1)
					{
						hacking_bgm.stop();
						drawTextureBox(man_posx, man_posy + jump.y + 50, 100, 60, 0, 0, 400, 60, hack_logo, Color(1, 1, 1, std::abs(::sin(time / 100))));
					}

				}
				//�n�b�N����
				if (map_col > 1)
				{
					//�J�E���g�Ɂ{�P
					map_count = 1;
					if (!item_bgm.isPlaying() && m_sound_count == 0)
					{
						item_bgm.play();
						m_sound_count++;
					}

					drawTextureBox(-WIDTH / 2 + 660, -man_sizey - 2150 + rand_posy,
						500, 60,
						0, 120, 400, 60,
						hack_logo,
						Color(1, 1, 1));

					if (rand_posy == 2700)
					{
						scroll_count = 9;

					}
				}
				//�Z�L���e�B�|���X�̒e���ˁB
				if (bullet < 2500)
				{
					bullet += 12;
				}
				else
				{
					bullet = 0;
				}
				//�Ƃ�ł���e�̂����蔻��
				if (Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet, -1600 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet - 750, -1700 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet - 900, -1800 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet, -1900 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet - 750, -2000 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet - 800, -2100 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet, -2200 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet - 1000, -2300 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet - 1400, -2400 + rand_posy, 100, 100) ||
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + bullet - 1320, -2500 + rand_posy, 100, 100))
				{
					//�e�ɂ���������A�����_���ŏ�̒i�ɋ����ړ�
					//warp_bgm
					if (!warp_bgm.isPlaying())
					{
						warp_bgm.play();
					}
					scroll_count = rand() % 4;
					rand_posy = scroll_count * 300;
					man_posy = 0;
					jump.y = 0;
					no_move = false;
					if (scroll_count == 0 || scroll_count == 2 || scroll_count == 3)
					{
						man_posx = -WIDTH / 2 + 140;
					}
					else if (scroll_count == 1 || scroll_count == 4)
					{
						man_posx = WIDTH / 2 - 160;
					}
				}



				////�Z�L�����e�B�|���X�\��
				//drawTextureBox(-WIDTH / 2, -1500 + rand_posy + 30 * sin(enemy_action / 30),
				// 140, 200, 230 * ((enemy_action / 70) % 3),
				// 30, 230, 370,
				// enemy,
				// Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet, -1600 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet - 750, -1700 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet - 900, -1800 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet, -1900 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet - 750, -2000 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet - 800, -2100 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet, -2200 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet - 1000, -2300 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet - 1400, -2400 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));
				drawTextureBox(-WIDTH / 2 + bullet - 1320, -2500 + rand_posy, 100, 100, 0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165, enemy, Color(1, 1, 1));

				//9�i��

				if (Rand_on(man_posx, -WIDTH / 2 + 140, word_count * 10)
					&& scroll_count == 9
					&& rand_posy == 2700
					&& Rand_on(man_posx, -WIDTH / 2 + 140 + word_count * 10 + 100, 100)
					&& !jump.jumping
					&& map_col > 1)

				{
					down = true;
					scroll_count++;
				}
				//�A�C�e��7
				if (item_count[6])
				{
					if (!Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 140 + word_count * 10 + 100,
						-2700 + rand_posy + abs(16 * sin(time / 50)), date_sizex / 4, date_sizey / 4))
					{
						drawTextureBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -2700 + rand_posy + abs(16 * sin(time / 50)),
							date_sizex / 4, date_sizey / 4, 0, 0, date_sizex, date_sizey, date, Color(1, 1, 1));
					}
					else
					{
						item_count[6] = 0;
						item++;
					}
				}
			//	std::cout << scroll_count << std::endl;
				//10�i��
				if (Rand_on(man_posx, -WIDTH / 2 + 1060 - word_count * 12, word_count * 12)
					&& scroll_count == 10
					&& rand_posy == 3000
					&& !boss)
				{
					down = true;
					scroll_count++;
				}
				//�A�C�e��8
				if (item_count[7])
				{
					if (!Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 140 + word_count * 10 + 100,
						-3000 + rand_posy + abs(16 * sin(time / 50)), date_sizex / 4, date_sizey / 4))
					{
						drawTextureBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -3000 + rand_posy + abs(16 * sin(time / 50)),
							date_sizex / 4, date_sizey / 4, 0, 0, date_sizex, date_sizey, date, Color(1, 1, 1));
					}
					else
					{
						item_count[7] = 0;
						item++;
					}
				}
				//11�i�� �S�[���t�߉��o
				if (!boss)
				{

					drawFillBox(-WIDTH / 2 + 140, -3300 + rand_posy + (enemy_action % 51),
						10, 10,
						Color(1, 1, 1, 0.5));
					drawFillBox(-WIDTH / 2 + 150, -3280 + rand_posy + (enemy_action % 54),
						10, 10,
						Color(1, 1, 1, 0.5));
					drawFillBox(-WIDTH / 2 + 160, -3280 + rand_posy + (enemy_action % 52),
						10, 10,
						Color(1, 1, 1, 0.5));
					drawFillBox(-WIDTH / 2 + 150, -3290 + rand_posy + (enemy_action % 55),
						10, 10,
						Color(1, 1, 1, 0.5));
					drawFillBox(-WIDTH / 2 + 170, -3300 + rand_posy + (enemy_action % 50),
						10, 10,
						Color(1, 1, 1, 0.5));

					drawFillBox(-WIDTH / 2 + 180, -3300 + rand_posy + (enemy_action % 53),
						10, 10,
						Color(1, 1, 1, 0.5));
					drawFillBox(-WIDTH / 2 + 185, -3280 + rand_posy + (enemy_action % 52),
						10, 10,
						Color(1, 1, 1, 0.5));
					drawFillBox(-WIDTH / 2 + 165, -3280 + rand_posy + (enemy_action % 56),
						10, 10,
						Color(1, 1, 1, 0.5));
					drawFillBox(-WIDTH / 2 + 135, -3290 + rand_posy + (enemy_action % 51),
						10, 10,
						Color(1, 1, 1, 0.5));
					drawFillBox(-WIDTH / 2 + 145, -3300 + rand_posy + (enemy_action % 48),
						10, 10,
						Color(1, 1, 1, 0.5));

					//�s���͈͐���
					if (man_posx > -WIDTH / 2 + (140 + word_count * 12 - man_sizex) && rand_posy == 3300)
					{
						man_posx = -WIDTH / 2 + (140 + word_count * 12 - man_sizex);
					}


				}
				//�S�[�������������Ă���΂ӂ��΃{�X�˓�
				if (//item == 8 && map_count == 1 &&
					Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 140, -3300 + rand_posy, 50, 100))
				{
					if (rand_posy >= 3100)
					{
						rand_posy -= 1;
						man_posy -= 1;
						no_move = true;
						//bgm 
						main_bgm.stop();
						if (!warning.isPlaying())
						{
							warning.play();
						}

						time -= 1;
						//��ʍ�������{�X�o��	
						drawTextureBox(-WIDTH / 2, 3000 - rand_posy + 30 * sin(enemy_action / 30),
							140, 200,
							230 * ((enemy_action / 70) % 3), 30, 230, 370,
							enemy,
							Color(1, 1, 1));
						//�e
						drawTextureBox(-WIDTH / 2, 3000 - rand_posy - 50,
							140, 150,
							0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165,
							enemy,
							Color(1, 1, 1));

						//�f��H�݂����ȍ��g�\��
						drawFillBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, man_sizey, Color(0, 0, 0));
						drawFillBox(-WIDTH / 2, HEIGHT / 2 - man_sizey, WIDTH, man_sizey, Color(0, 0, 0));
					}
					else
					{
						boss = true;
						no_move = false;
						time -= 1;
					}

				}

				///////////////////////////////////////////////////////////////////////�{�X�o��	
				if (boss)
				{
					//bgm
					warning.stop();

					time -= 1;
					//BOSS��p�L��������E�㉺�����ړ��\
					//�E�����L�[�ŉE�� 
					if (nomove_count == 0)
					{
						//�E�����L�[�ŉE�� 
						if (app_env.isPressKey(GLFW_KEY_RIGHT) && man_posx < WIDTH / 2 - (man_sizey + 15))
						{
							man_posx += v;
							value += 1;
							man_move = (value / 7) % 4;
							see_left = false;
						}

						//�������L�[�ō���
						if (app_env.isPressKey(GLFW_KEY_LEFT) && man_posx  > -WIDTH / 2)
						{
							man_posx -= v;
							value += 1;
							man_move = (value / 7) % 4;
							see_left = true;
						}
						//������L�[�ŏ�� 
						if (app_env.isPressKey(GLFW_KEY_UP) && man_posy < 150 - (man_sizex + 15))
						{
							man_posy += v;
							value += 1;
							man_move = (value / 7) % 4;
							see_left = false;
						}

						//�������L�[�ŉ���
						if (app_env.isPressKey(GLFW_KEY_DOWN) && man_posy > -HEIGHT / 2 + 50)
						{
							man_posy -= v;
							value += 1;
							man_move = (value / 7) % 4;
							see_left = true;
						}
					}
					//���X�N���[���J�n�@���C���L�������ɏ����������ړ�
					if (WIDTH / 2 - (side_scroll / 3 - 60 * 15) * 3 >= 0)
					{
						side_scroll += 3;
						man_posx -= 1;
					}
					else
					{
						man_posx += 10;

					}

					///BOSS�w�i
					if (-side_scroll + WIDTH / 2 >= -WIDTH / 2)
					{
						//���S�̔w�i
						drawTextureBox(-side_scroll + WIDTH / 2, -HEIGHT / 2,
							1200, 400,
							0, 0, 512, 512,
							boss_bg,
							Color(1, 1, 1));

						//�㉺�̕Ǖ\��
						drawTextureBox(-side_scroll + WIDTH / 2, 150,
							1200, 200,
							300 + ((int)side_scroll % 50) / 10, 100, 3, 400,
							hp_etc,
							Color(1, 1, 1));
						drawTextureBox(-side_scroll + WIDTH / 2, -HEIGHT / 2,
							1200, 50,
							300 + ((int)side_scroll % 50) / 10, 100, 3, 400,
							hp_etc,
							Color(1, 1, 1));
						//������I�I
						drawTextureBox(-90, 0 + 20 * sin(enemy_action / 30), 230, 85,
							0, 0, 185, 55,
							word2,
							Color(1, 1, 1));
					}
					else
					{
						drawTextureBox(-WIDTH / 2, -HEIGHT / 2,
							1200, 400,
							0 + ((int)side_scroll % 1200) / 2, 0, 512, 512,
							boss_bg,
							Color(1, 1, 1));
						//�㉺�̕Ǖ\��
						drawTextureBox(-WIDTH / 2, 150,
							1200, 200,
							300 + ((int)side_scroll % 50) / 10, 100, 3, 400,
							hp_etc,
							Color(1, 1, 1));
						drawTextureBox(-WIDTH / 2, -HEIGHT / 2,
							1200, 50,
							300 + ((int)side_scroll % 50) / 10, 100, 3, 400,
							hp_etc,
							Color(1, 1, 1));
					}


					//BOSS�\��
					drawTextureBox(-WIDTH / 2 + side_scroll / 30, 3000 - rand_posy + 30 * sin(enemy_action / 30),
						140, 200, 230 * ((enemy_action / 70) % 3),
						30, 230, 370,
						enemy,
						Color(1, 1, 1));
					//�e�\��
					drawTextureBox(-WIDTH / 2 + side_scroll / 30, 3000 - rand_posy - 100,
						140, 200,
						0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165,
						enemy,
						Color(1, 1, 1));
					//��Q���̕ǂ̈ʒu�������_���ɑ��
					if (side_scroll > 1200)
					{
						//��Q���̕ǁA�e�����܂ł������珉���l�ɖ߂�悤�ɐݒ�
						if (boss_action < 2500 && side_scroll / 3 < 60 * 17)
						{
							boss_action += 12;
						}
						else
						{
							boss_action = 0;
						}

						//�����_���Œe�̈ʒu����
						if (WIDTH / 2 - bullet >= WIDTH / 2)
						{
							wall_posy = rand();
							wall_posy2 = rand();
							wall_posy3 = rand();
						}
						//�ǂ�\��
						drawTextureBox(WIDTH / 2 - boss_action / 1.4, -HEIGHT / 2 + 50 + (wall_posy % 200),
							39, 110,
							0, 0, 39, 110,
							wall,
							Color(1, 1, 1));
						drawTextureBox(WIDTH / 2 - boss_action / 1.4 + 400, -HEIGHT / 2 + 50 + (wall_posy2 % 150),
							39, 110,
							0, 0, 39, 110,
							wall,
							Color(1, 1, 1));
						//�e����
						drawTextureBox(-WIDTH / 2 + boss_action / 1.4, -HEIGHT / 2 + 50 + (wall_posy3 % 250) + 50 * sin(enemy_action / 20),
							50, 50,
							0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165,
							enemy,
							Color(1, 1, 1));
						//�����蔻��
						//�ǈ��
						if (Touch_wall(man_posx, man_posy, WIDTH / 2 - boss_action / 1.4, -HEIGHT / 2 + 50 + (wall_posy % 200), 39, 110)
							&& side_scroll / 3 < 60 * 17)
						{
							man_posx = WIDTH / 2 - boss_action / 1.4 - (man_sizey + 15);
						}
						//�Ǔ��
						if (Touch_wall(man_posx, man_posy, WIDTH / 2 - boss_action / 1.4 + 400, -HEIGHT / 2 + 50 + (wall_posy2 % 150), 39, 110)
							&& side_scroll / 3 < 60 * 15)
						{
							man_posx = WIDTH / 2 - boss_action / 1.4 + 400 - (man_sizey + 15);
						}
						//�e�@����������O�D�T�b��~
						if (Touch_wall(man_posx, man_posy,
							-WIDTH / 2 + boss_action / 1.4, -HEIGHT / 2 + 50 + (wall_posy3 % 250) + 50 * sin(enemy_action / 20), 50, 50))
						{

							nomove_count++;
						}
						if (nomove_count > 0)
						{
							man_posx += rand() % 2;
							man_posy += rand() % 2;
							nomove_count++;
							if (nomove_count > 40)
							{
								nomove_count = 0;
							}
						}
						//15�b�ɂ���������N���A
						if (side_scroll / 3 > 60 * 15)
						{

							if (!hacking_bgm.isPlaying())
							{
								boss_bgm.gain(0.3);
								hacking_bgm.play();
								hacking_bgm.pitch(100);
							}
							//���e
							// ���邳����]�p���猈�߂�
							float color = fabs(std::sin(enemy_action / 3)) * 0.5;
							drawTextureBox(WIDTH / 2 - (side_scroll / 3 - 60 * 15) * 3, -200,
								200, 300,
								0 + 230 * ((int)enemy_action % 2), 0, 230, 380,
								man4,
								Color(1 - color, color, color));
							if (man_posx > WIDTH / 2)
							{

								//bgm
								dog_bgm.stop();
								hacking_bgm.stop();
								boss_bgm.stop();
								if (!bomb_bgm.isPlaying())
								{
									bomb_bgm.play();
									bomb_bgm.gain(10);
									bomb_bgm.pitch(0.09);
								}


								end_efect += 3;

								int i;
								//����W��
								for (i = 0; i < 30; i++){
									drawTextureBox(-WIDTH / 2 - 200 + rand() % WIDTH, -HEIGHT / 2,
										512, 512,
										0, 0, 1024, 1024,
										bomb,
										Color(1, 1, 1),
										0,
										Vec2f(1, 1),
										Vec2f(0, 0));
								}


								//booooooom!
								drawTextureBox(-WIDTH / 2 + 350, -HEIGHT / 2,
									512, 512,
									0, 0, 1024, 1024,
									bomb_word,
									Color(1, 1, 1),
									0,
									Vec2f(1, 1),
									Vec2f(0, 0));
								//������ʂ����ς���\��
								drawTextureBox(-WIDTH / 2 - 200, -HEIGHT / 2 - 200,
									1600, 800,
									0, 0, 1024, 1024,
									bomb,
									Color(1, 1, 1, (float)end_efect / 1000),
									0,
									Vec2f(1, 1),
									Vec2f(0, 0));
								//��ʒ��S�ɃN���A��ʕ\��
								if (end_efect > 1000)
								{
									man_action += 1;
									man_action *= 1.079;
									bomb_bgm.stop();
									if (man_action == 1)
									{
										clear_bgm.play();
										man_action = 10;
									}
									else if (man_action >= 1000)
									{
										man_action = 1000;
										drawTextureBox(0, -HEIGHT / 2 - 100,
											500, 500,
											0, 0, 512, 512,
											clear_ward,
											Color(1, 1, 1));
									}

									drawTextureBox(WIDTH / 2 - man_action, -HEIGHT / 2,
										500, 500,
										0, 0, 512, 512,
										clear,
										Color(1, 1, 1, 1));
								}

								//�N���A���
								if (app_env.isPushKey('A'))
								{

									///*	  go = false;
									//	  info_bool = false;*/
									sugihei_clear = true;
									display = 1;
									break;


								}
							}

						}


					}
				}
			}
		}
		////////////////�L�����N�^�[����


		//���C���L�����\�� �i�E�����̎��͉E�A���̎��͍����݂�)
		if (!see_left && !jump.jumping && !down && !get)
		{
			if (!boss)
			{

				drawTextureBox(man_posx, man_posy + jump.y, man_sizex, man_sizey,
					0 + man_move * (man_sizex + 1), man_sizey, man_sizex, man_sizey,
					man,
					Color(1, 1, 1));

			}
			else
			{

				drawTextureBox(man_posx, man_posy,
					man_sizey + 15, man_sizex + 15,
					(enemy_action % 3) * 150, 100, 150, 100,
					man3,
					Color(1, 1, 1));
			}
		}
		else if (see_left && !jump.jumping  && !down && !get)
		{
			if (!boss)
			{

				drawTextureBox(man_posx, man_posy + jump.y, man_sizex, man_sizey,
					0 + man_move * (man_sizex + 1), 0, man_sizex, man_sizey,
					man,
					Color(1, 1, 1));

			}
			else
			{
				drawTextureBox(man_posx, man_posy,
					man_sizey + 15, man_sizex + 15,
					(enemy_action % 3) * 150, 100, 150, 100,
					man3,
					Color(1, 1, 1));
			}
		}
		if (jump.jumping == true || down == true)
		{
			drawTextureBox(man_posx, man_posy + jump.y, man_sizex, man_sizey,
				0, man_sizey * 2, man_sizex + 6, man_sizey,
				man,
				Color(1, 1, 1));

		}


		////�T�C����
		// ���邳����]�p���猈�߂�
		float color = fabs(std::sin(time / 30)) * 0.5 + 0.5;

		drawTextureBox(WIDTH / 2 - 85, -HEIGHT / 2 + 85,
			66.6, 36,
			200 + siren, 20, 80, 70,
			hp_etc,
			Color(color, color, color));

		//hp(timer)�\��
		drawTextureBox(WIDTH / 2 - 100, -HEIGHT / 2,
			100, 100,
			0, 0, 170, 170,
			hp_etc,
			Color(r, g, b));

		//���Ԃ̐j
		drawTextureBox(WIDTH / 2 - 50, -HEIGHT / 2 + 45,
			33, 49,
			0, 180, 50, 85,
			hp_etc,
			Color(1, 1, 1),
			M_PI * -time / 500,
			Vec2f(1, 1),
			Vec2f(16.5, 7));
		if (M_PI * -time / 500 <= -M_PI * 2 &&
			M_PI * -time / 500 >= -M_PI * 4 && scroll_count >= 0)
		{
			siren = 90;
			b = 0;
			g = 1;
			r = 1;
		}
		else if (M_PI * -time / 500 <= -M_PI * 4 &&
			M_PI * -time / 500 >= -M_PI * 6 && scroll_count >= 0)
		{
			siren = 180;
			g = 0;

		}
		else if (M_PI * -time / 500 <= -M_PI * 6 && scroll_count >= 0)
		{
			display = 3;
			//bgm
			main_bgm.stop();
			walk_bgm.stop();
			gameover_bgm.play();
			break;
		}

		//�A�C�e�����\��
		//date�~��
		drawTextureBox(WIDTH / 2 - date_sizex / 4 - 200, -HEIGHT / 2, date_sizex / 4, date_sizey / 4,
			0, 0, date_sizex, date_sizey,
			date,
			Color(0.5, 0.5, 0.5));
		//�h�~�h
		drawTextureBox(WIDTH / 2 - date_sizex / 4 - 150, -HEIGHT / 2,
			14, 14,
			6, 423, 14, 14,
			hp_etc,
			Color(1, 1, 1));
		//"����" date�擾��A�{�P
		drawTextureBox(WIDTH / 2 - date_sizex / 4 - 130, -HEIGHT / 2,
			22, 27,
			1 * 21 * item, 387, 22, 27,
			hp_etc,
			Color(1, 1, 1));
		//map�~��
		drawTextureBox(WIDTH / 2 - date_sizex / 4 - 350, -HEIGHT / 2,
			date_sizex / 4, date_sizey / 4, 0, 0,
			750, 1000,
			map,
			Color(0.5, 0.5, 0.5));
		//�h�~�h
		drawTextureBox(WIDTH / 2 - date_sizex / 4 - 300, -HEIGHT / 2,
			14, 14,
			6, 423, 14, 14,
			hp_etc,
			Color(1, 1, 1));
		//"����"hack������@�{�@�P
		drawTextureBox(WIDTH / 2 - date_sizex / 4 - 280, -HEIGHT / 2,
			22, 27,
			1 * 22 * (map_count), 387, 22, 27,
			hp_etc,
			Color(1, 1, 1));
		//drawTextureBox();

		//�Ȃ񂩓d�]���E���ۂ��l�p���̂��L��������ɕ\��
		drawFillBox(man_posx + rand() % (man_sizex + 30) - 30,
			man_posy + jump.y + rand() % man_sizey,
			10, 10, Color(0, 0.5, 0.5, 2 - time / 100));
		drawFillBox(man_posx + rand() % (man_sizex + 20) * 2 - 20,
			man_posy + jump.y + rand() % man_sizey * 2,
			10, 10, Color(0, 0.5, 0.5, 2 - time / 100));

		//�����L�[�������ĂȂ��Ƃ��́A�_����
		if (!app_env.isPressKey(GLFW_KEY_LEFT) || !app_env.isPressKey(GLFW_KEY_RIGHT)
			&& !get)
		{
			man_move = 0;
		}

		//�{�X��ł͂Ȃ��Ƃ��̓���
		if (!boss)
		{
			if (!no_move)
			{
				//�ړ�������
				if (man_posx < -WIDTH / 2 + 140)
				{
					man_posx = -WIDTH / 2 + 140;
				}
				//�ړ������E
				if (man_posx > WIDTH / 2 - 160)
				{
					man_posx = WIDTH / 2 - 160;
				}
				//�E�����L�[�ŉE�� 
				if (app_env.isPressKey(GLFW_KEY_RIGHT))
				{

					man_posx += v;
					value += 1;
					man_move = (value / 7) % 4;
					see_left = false;
				}

				//�������L�[�ō���
				if (app_env.isPressKey(GLFW_KEY_LEFT))
				{
					man_posx -= v;
					value += 1;
					man_move = (value / 7) % 4;
					see_left = true;
				}
				if (app_env.isPressKey(GLFW_KEY_LEFT) && app_env.isPressKey(GLFW_KEY_RIGHT))
				{
					man_move = 0;

				}
				//�W�����v
				if (app_env.isPushKey('A') && !app_env.isPressKey(GLFW_KEY_UP))
				{
					if (!jump.jumping)
					{
						jump.jumping = true;
						jump.vy = jump_power;
					}
				}
			}
			if (app_env.isPressKey(GLFW_KEY_UP) && down)
			{
				man_posy += n_gravity;
			}


			//�f�o�b�O�L�[�����ꏊ�ړ�
			if (app_env.isPushKey('1') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 1;
				rand_posy = 1 * 300;
			}
			if (app_env.isPushKey('2') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 2;
				rand_posy = 2 * 300;
				//display = 3;
			} if (app_env.isPushKey('3') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 3;
				rand_posy = 3 * 300;
			}
			if (app_env.isPushKey('4') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 4;
				rand_posy = 4 * 300;
				//display = 3;
			} if (app_env.isPushKey('5') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 5;
				rand_posy = 5 * 300;
			}
			if (app_env.isPushKey('6') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 6;
				rand_posy = 6 * 300;
				//display = 3;
			} if (app_env.isPushKey('7') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 7;
				rand_posy = 7 * 300;
			}
			if (app_env.isPushKey('8') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 8;
				rand_posy = 8 * 300;
				//display = 3;
			} if (app_env.isPushKey('9') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 9;
				rand_posy = 9 * 300;
			}
			if (app_env.isPushKey('0') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 10;
				rand_posy = 10 * 300;
				//display = 3;
			}
			if (app_env.isPushKey('-') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 11;
				rand_posy = 11 * 300;
			}
			if (app_env.isPushKey('T') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				scroll_count = 0;
				rand_posy = 0 * 300;
				//display = 3;
			}
			if (app_env.isPushKey('Y') && !app_env.isPressKey(GLFW_KEY_UP))
			{
				display = 3;
				//bgm
				main_bgm.stop();
				walk_bgm.stop();
				gameover_bgm.play();
			}

			// �W�����v���̓���
			// TIPS:�������^���̖@���𗘗p
			// s = v0 * t + 0.5 * a * t^2
			// v = v0 + a * t
			if (jump.jumping) {
				jump.y += jump.vy + 0.5 * gravity;
				jump.vy += gravity;

				// ���n
				if (jump.y <= 0.0) {
					man_posy = 0;
					jump.y = 0.0f;
					jump.jumping = false;
				}
			}
			//������
			if (down)
			{

				t += 0.064;
				rand_posy += 0.5 * gravity + t * t;
				v = 3;
				if (rand_posy > 300 * scroll_count)
				{
					rand_posy = 300 * scroll_count;

					t = 1;
					down = false;
					v = 4;
				}

			}


			//�䂩�痎����Ƃ��悤�̏d��
			if (down_man&& man_posy + jump.y > 0 && !on && !jump.jumping)
			{
				t += 0.09;
				man_posy -= 0.5 * gravity + t * t;
				if (man_posy + jump.y < 0)
				{
					down_man = false;
					man_posy = 0;
					jump.y = 0;
					t = 1;
				}
			}
		}
		app_env.update();
	}
	app_env.flushInput();
}