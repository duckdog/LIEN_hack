#pragma once
#include "appEnv.hpp"
using namespace std;

//���N���b�N�Ń^�C�g�����o�N�� �^�C�g���摜�S���\����N���b�N�Ńu���C�N
if(app_env.isPushButton(Mouse::LEFT))
{

	if (!title_bgm.isPlaying())
	{
		title_bgm.play();
	}
	title_action = true;
	start_count++;
	start_count++;
	if (start_count >= 2 && 0.28 * -title_alpha >= 1)
	{
		texture_bool = false;

	}
	if (!warp_bgm.isPlaying() && 0.3 * -title_alpha >= 1 || title_alpha == 1)
	{
		warp_bgm.play();
	}
}

//�N���b�N��摜�̃A���t�@�l��ω�
if (title_action)
{
	title_alpha -= 0.01;
}

//�摜���\������������A�N���b�N to �n�b�N��W��
if (0.3 * -title_alpha >= 1)
{
	//0��1�𗐐��������ĕW��
	int randompos = random.fromFirstToLast(-Window::WIDTH / 2, Window::WIDTH / 2);
	drawTextureBox(-Window::WIDTH / 2 * (randompos % 10), -Window::HEIGHT * 1.5, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		zero_one,
		Color(1, 1, 1, 1));
	drawTextureBox(-Window::WIDTH / 2 * (randompos % 10), -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		zero_one,
		Color(1, 1, 1, 1));

	//�N���b�N�@to �n�b�N��W��
	box += 0.098;
	drawTextureBox(Window::WIDTH / 2 - 300, -Window::HEIGHT / 2 - 90, 300, 170,
		0, 0, 512, 256,
		click_to_hack,
		Color(1, 1, 1, sin(box)));

	//�摜�\����N���b�N�Ńu���C�N
	if (app_env.isPushButton(LEFT)) display = 1;

}


//�^�C�g���摜�\��
//if (texture_bool)
{
	//�N���b�N�O
	drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		title_lien,
		Color(1, 1, 1, title_alpha));

	//�N���b�N��
	drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		title_blacklien,
		Color(1, 1, 1, 1 * -title_alpha));
	drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		title,

		Color(1, 1, 1, 0.3 * -title_alpha));


}