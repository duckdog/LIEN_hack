#pragma once
#include "appEnv.hpp"
using namespace std;

//左クリックでタイトル演出起動 タイトル画像全部表示後クリックでブレイク
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

//クリック後画像のアルファ値を変化
if (title_action)
{
	title_alpha -= 0.01;
}

//画像が表示しきったら、クリック to ハックを標示
if (0.3 * -title_alpha >= 1)
{
	//0と1を乱数をつかって標示
	int randompos = random.fromFirstToLast(-Window::WIDTH / 2, Window::WIDTH / 2);
	drawTextureBox(-Window::WIDTH / 2 * (randompos % 10), -Window::HEIGHT * 1.5, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		zero_one,
		Color(1, 1, 1, 1));
	drawTextureBox(-Window::WIDTH / 2 * (randompos % 10), -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		zero_one,
		Color(1, 1, 1, 1));

	//クリック　to ハックを標示
	box += 0.098;
	drawTextureBox(Window::WIDTH / 2 - 300, -Window::HEIGHT / 2 - 90, 300, 170,
		0, 0, 512, 256,
		click_to_hack,
		Color(1, 1, 1, sin(box)));

	//画像表示後クリックでブレイク
	if (app_env.isPushButton(LEFT)) display = 1;

}


//タイトル画像表示
//if (texture_bool)
{
	//クリック前
	drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		title_lien,
		Color(1, 1, 1, title_alpha));

	//クリック後
	drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		title_blacklien,
		Color(1, 1, 1, 1 * -title_alpha));
	drawTextureBox(-Window::WIDTH / 2, -Window::HEIGHT / 2, Window::WIDTH, Window::HEIGHT,
		0, 0, 1024, 512,
		title,

		Color(1, 1, 1, 0.3 * -title_alpha));


}