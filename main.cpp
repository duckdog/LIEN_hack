//
// アプリ雛形
//

#include "g_variable.h"
#include "appEnv.hpp"
#include "function.h"
#include "title.h"
#include "menu.h"
#include "stage1.h"
#include "gameover.h"

using namespace std;



// メインプログラム
// 
int main() {
	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT,
		false,//フルスクリーンモード
		true
		);

	//ウインドウの位置変更を変える
	app_env.windowPosition(Vec2i(500, 500));

	int stage_key[2] = { 0, 0 };

	/* セーブデータ
	  std::ofstream savedate("save_txt");
	  if (savedate) savedate
	  << "stage2_key " << stage_key[0]
	  << "stage3_key " << stage_key[1];*/

	//背景色
	app_env.bgColor(Color(0, 1, 0.2));

	

	
	
	{
		//bgm
		Media warp_bgm("res/warp.wav");
		Media gameover_bgm("res/gameover.wav");	
	
		//隠し要素
		Texture thankyou("res/thankyou.png");

		//乱数発生器
		Random random;

		//＜stage1＞すぎへいの依頼をクリアしたかしてないかを判断
		bool sugihei_clear = false;
		
		

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	while (1)
		{

			//アプリウインドウが閉じられたらプログラムを終了
			if (!app_env.isOpen()) return 0;


			//描画準備
			app_env.setupDraw();

			switch (display)
			{

			//タイトル処理
			case 0: {
					
						title_dis(app_env,warp_bgm,random);
						display++;
						
						
			}
				break;
			//メニュー画面処理
			case 1:
			{
					  //メニュー画面処理
					  menu_dis(app_env, display,sugihei_clear);

			}
			break;

			//ゲーム本編処理
			case 2:
			{
					  stage1(app_env, gameover_bgm,
						  display,sugihei_clear);
				
					
			}
			break;
			
			//ゲームオーバー処理
			case 3:
			{
					  gameover_dis(app_env, display);
			}
				break;
		    //おまけ。隠し要素
			case 4:
			{
					  drawTextureBox(-600, -250, 1200, 500,
						  0, 0, 1200, 500,
						  thankyou,
						  Color(1, 1, 1));
				if (app_env.isPushKey('D') && !app_env.isPressKey(GLFW_KEY_UP))
				{

					display = 2;
				}
				if (app_env.isPushKey('A') && !app_env.isPressKey(GLFW_KEY_UP))
				{

					display = 1;
				}
			}
				break;
        }
		
			//画面更新
			app_env.update();
		}
	
		app_env.flushInput();
	}
	

}


// アプリ終了


