//
// アプリ雛形
//

#include "appEnv.hpp"
#include "function.h"
using namespace std;


// アプリのウインドウサイズ
enum Window {
	WIDTH = 1200,
	HEIGHT = 500
};


// 
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

	//ジャンプ
	struct Jump
	{
		float y;
		float vy;

		bool jumping;
	};


	const float jump_power = 12.0f;
	const float gravity = -0.8f;
	int display = 2;

	


	
// タイトル画面////////////////////////////////////////////////////////////////
	
	{
		Media main_bgm("res/main_bgm.wav");
		Media menu_bgm("res/menu_bgm.wav");
		Media boss_bgm("res/boss_bgm.wav");
		Media warp_bgm("res/warp.wav");
		Media yes_bgm ("res/yes_bgm.wav");
		Media no_bgm  ("res/no_bgm.wav");
		Media dog_bgm ("res/dog_bgm.wav");
		Media bomb_bgm("res/bomb.wav");
		Media item_bgm("res/item_get.wav");
		Media warning("res/warning.wav");
		
		Media walk_bgm("res/walk_sound.wav");
		Media hacking_bgm("res/hacking.wav");
		Media comp_bgm("res/item_comp.wav");
		Media loap_bgm("res/loap.wav");
		Media wipe_bgm("res/wipe.wav");
		Media gameover_bgm("res/gameover.wav");
		Media down_bgm("res/down.wav");
     	Media title_bgm("res/title_bgm.wav");
		Media clear_bgm("res/clear_bgm.wav");
	


		Texture title_blacklien("res/title_blackLIEN.png");          //タイトル演出前
		Texture title_lien("res/title_LIEN.png");                    //タイトル演出後
		Texture title("res/title.png");                              //上に同じ    
		Texture click_to_hack("res/click_to_hack.png");              //クリックしたらスタート
		Texture zero_one("res/01.png");                               //01表示



		//乱数発生器
		Random random;

		float box          = 0;              //背景演出用
		float title_alpha  = 1;              //   ↓
		bool  title_action = false;          //   ↓
		bool  texture_bool = true;          //ここまで
		int   start_count  = 0;              //クリックカウント値記憶
		int   move         = 0;

		


//メニュー画面//////////////////////////////////////////////////////////////
		
		
	    
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

		bool sugihei_clear = false;
		bool shop_bool = false;
		bool madam_bool = false;
		bool secret_bool = false;

		bool go = false;


		//menu画面
		float quest_col = 0.8, talk_col = 0.8, save_col = 0.8;
		bool  quest_bool = false, talk_bool = false, save_bool = false;

///本編//////////////////////////////////////////////////////////////////////////////////
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
		Texture game_over("res/timeover.png");
		Texture thankyou("res/thankyou.png");
		//メインキャラ
		int   man_sizex = 31, man_sizey = 59;   //表示サイズ
		float man_posx = 500.0, man_posy = 0.0; //表示位置
		int   man_move = 0, value = 0;          //モーション用変数
		int   v = 5;                            //速度
		int   siren = 0;
		float n_gravity = 0.01;
		float life = 3 * 60 * 60;
		bool  down_man = false;
		bool  no_move = false;
		bool  see_left = false;                 //視線方向
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

		//地面
		float scroll_count = -1;
		float side_scroll = 0;
		float rand_posy = 0;
		int   rand_x = 800;
		float t = 1;
		bool  down = false;
		int   word_count = 37;

		//アイテム   
		float obj_pos = 0;
		float date_sizex = 210;
		float date_sizey = 240;
		int   get_count = 0;
		int m_sound_count = 0;

		//s障害物
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

		//BOSSアクション用
		int boss_action = 0;
		int wall_posy = 0;
		int wall_posy2 = 0;
		int wall_posy3 = 0;
		int nomove_count = 0;
		int end_efect = 0;
		bool boss = false;

		//clear後
		int man_action = 0;
		//gameover
		int sound_count = 0;


		//背景色
		app_env.bgColor(Color(0, 0, 0));

		//ジャンプ
		Jump jump = {
			0.0f,
			0.0f,
			false
		};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	while (1)
		{

			//アプリウインドウが閉じられたらプログラムを終了
			if (!app_env.isOpen()) return 0;


			//描画準備
			app_env.setupDraw();

			switch (display)
			{


			case 0: {
						
						//左クリックでタイトル演出起動 タイトル画像全部表示後クリックでブレイク
						if (app_env.isPushButton(Mouse::LEFT))
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
			}
				break;
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 1:
			{

					  //bgm
					  title_bgm.stop();
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
						  scroll -= 300;
						  info_col = 0;
						  go = false;
						  info_bool = false;
						  shop_bool = false;
						  madam_bool = false;
						  secret_bool = false;
					  }
					  if (app_env.isPushKey(GLFW_KEY_DOWN) && scroll != 600)
					  {
						  scroll += 300;
						  info_col = 0;
						  go        = false;
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
							  0, 0 + scroll, 1024, 300,
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
											  0,0,
											  450,160,
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
												  display = 2;
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
							  case 300:
								  drawTextureBox((-Window::WIDTH / 2 + 250), -Window::HEIGHT / 2 + 110,
									  540, 330,
									  0, 0, 540, 330,
									  info_lock,
									  Color(1, 1, 1, info_col));
								  break;
							  case 600:
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
									  30,130,170,90,
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
							  0, 0 + scroll, 1024, 300,
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
								  else if (scroll == 300)
								  {
									  madam_bool = true;
								  }
								  else if (scroll == 600)
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
					  drawFillBox(-Window::WIDTH / 2, -Window::HEIGHT / 2,400, 95,
						  Color(0.3, 0.3, 0.3, quest_col));
					  drawFillBox(-Window::WIDTH / 2 + (400 * 1), -Window::HEIGHT / 2, 400, 95,
						  Color(0.3, 0.3, 0.3, talk_col));
					  drawFillBox(-Window::WIDTH / 2 + (400 * 2), -Window::HEIGHT / 2, 400, 95,
						  Color(0.3, 0.3, 0.3, save_col));

					  //依頼主
					  if (-Window::WIDTH / 2 < mouse.x() && mouse.x() < -Window::WIDTH / 2 + 400
						  &&  -Window::HEIGHT / 2 < mouse.y() && mouse.y() < -Window::HEIGHT / 2 + 100)
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
					  if (-Window::WIDTH / 2 + (400 * 1)  < mouse.x() && mouse.x() < -Window::WIDTH / 2 + (400 * 2)
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
					  //セーブ
					  if (-Window::WIDTH / 2 + (400 * 2)  < mouse.x() && mouse.x() < -Window::WIDTH / 2 + (400 * 3)
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

			}
			break;
			

			////////////////////////////////////////////////////////////////////////////////
			
			case 2:
			{
					  menu_bgm.stop();
					  ///BGM
					  //main_bgm
					  if (!main_bgm.isPlaying())
					  {
						  main_bgm.play();
					  }
					  //dog
					  if ( boss)
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
						  app_env.isPressKey(GLFW_KEY_RIGHT))&&
						  !boss && !down && !jump.jumping )
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
						  if ( 8 == item &&!comp_bgm.isPlaying())
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
					  //マウスポジション
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

					  /////////////////本編障害物、アイテム、画像表示等


					  if (scroll_count == -1)
					  {
						  //bgm音量調整
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
						
						  //ゲーム内時間
						  time += 1;
						  main_bgm.gain(0.5);
						  wipe_bgm.stop();
						  ///////icon表示
						  //左のキャラアイコン
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

						  //右のキャラアイコン
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


						  //障害物1 キャラクターが逆方向を向いてたら通行可能に
						  drawTextureBox(0 + 100 * std::sin(time / 100), rand_posy, 100, 250, stop_bar, 666, 150, 300, enemy, Color(1, 1, 1));
						  if (scroll_count == 0)
						  {
							  if (Touch(man_posx, man_posy + jump.y, 0 + 100 * std::sin(time / 100), rand_posy, 100, 250))
							  {
								  //右を向いてたら左側に速度を
								  if (!see_left)
								  {

									  man_posx -= v + 1;

								  }
								  //左を向いてたら右側に速度を
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

						  //スイッチ　兼　ワープ
						  drawTextureBox(400, rand_posy - 300,
							  50, 50,
							  490, 736, 179, 178,
							  enemy,
							  Color(ww, 1, ww));
						  // ワープ出口
						  drawTextureBox(-200, rand_posy - 300,
							  50, 50, 490, 736,
							  179, 178,
							  enemy,
							  Color(ww, 1, ww));
						  //踏んでるときだけ壁消滅
						  if (!on)drawTextureBox(-100, rand_posy - 300,
							  30, 100, 325, 655,
							  75, 367,
							  enemy,
							  Color(1, 0, 1));
						  if (Touch(man_posx, man_posy + jump.y, 400, rand_posy - 300, 50, 50))
						  {
							  //ある程度のたかさでジャンプ位置で着地
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
							  //台にあたったらワープ（右向き）
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
							  //上に同じ（左向き）
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



						  //通せん坊
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


						  ///ステージ地面表示
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
							  //7スタンプ
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
							  //全てのアイテム獲得していれば表示
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
									  0, 55,512, 50,
									  word2,
									  Color(0, 0, 0));

							  }
							  //11ラスト
							  drawTextureBox(-WIDTH / 2 + 140 - side_scroll, -man_sizey - 3300 + rand_posy,
								  word_count * 12, man_sizey, 0, 360,
								  word_count * 12, 40, talk_date, Color(1, 1, 1));



						  }
						  //地面：アイテム：段ごとのアイテムの当たり判定
						  {
							  //１段目(scroll_countは"0"スタート)おい、なにしている
							  if (Rand_on(man_posx, 140 + -WIDTH / 2, word_count * 18) && scroll_count == 0)
							  {
								  down = true;
								  scroll_count++;
							  }
							  //アイテム
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
							  //２段目　わるい、とりこんでいた
							  if (Rand_on(man_posx, -WIDTH / 2 + 1060 - word_count * 21, word_count * 21) && scroll_count == 1)
							  {
								  down = true;
								  scroll_count++;
							  }
							  //アイテム2
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
							  //3段目　場所と
							  if (Rand_on(man_posx, 140 + -WIDTH / 2, word_count * 8) && scroll_count == 2 && rand_posy == 600)
							  {
								  down = true;
								  scroll_count++;
							  }
							  //アイテム3
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
							  //4段目　暗証番号だろ
							  if (Rand_on(man_posx, 140 + -WIDTH / 2, word_count * 8) && scroll_count == 3 && rand_posy >= 900)
							  {
								  down = true;
								  scroll_count++;

							  }
							  //アイテム4
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
							  //5段目　じょうだんですよ
							  if (Rand_on(man_posx, -WIDTH / 2 + 1060 - word_count * 13, word_count * 13) && scroll_count == 4 && rand_posy == 1200)
							  {
								  down = true;
								  scroll_count++;
							  }
							  //アイテム5
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
							  //	レーザー光線
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
							  //解除ボタン 順番通りにふれると解除
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
							  


							  //6段目　早くしろ…
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
							  //アイテム6
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
							  //土台
							  drawTextureBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -man_sizey - 1500 + rand_posy,
								  100, man_sizey,
								  0, 280, 100, 70,
								  hp_etc,
								  Color(1, 1, 1));
							  //はしご（綱の予定）台にのったらはしご出現
							  if (!Rand_on(man_posx, -WIDTH / 2 + 140 + word_count * 10 + 100, 10)
								  && (scroll_count == 5 || scroll_count == 9)
								  && !down)
							  {

								  //綱
								  drawTextureBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -2700 + rand_posy,
									  10, 1200,
									  300, 110,
									  50, 500,
									  hp_etc,
									  Color(1, 1, 1));

								  //綱をつかんでないときは横に動ける
								  if (rand_posy == 1500 || rand_posy == 2700)
								  {
									  get = false;
									  no_move = false;
									  if (scroll_count == 5)
									  {
										  loap_size = 0;
									  }
								  }
								  //つかんでるときのキャラクター画像
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

								  //下る
								  if (app_env.isPressKey(GLFW_KEY_DOWN) && rand_posy < 2700 && !down)
								  {
									  no_move = true;
									  rand_posy += 5;
									  loap_size += 5;
								  }
								  //登る
								  if (app_env.isPressKey(GLFW_KEY_UP) && rand_posy > 1500 && !down)
								  {
									  no_move = true;
									  rand_posy -= 5;
									  loap_size -= 5;
								  }

								  //下る
								  if (app_env.isPressKey(GLFW_KEY_DOWN) && rand_posy < 2700 ||
									  app_env.isPressKey(GLFW_KEY_UP) && rand_posy > 1500  && !down)
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
							  //通常時綱をつかんでないと定義
							  else
							  {
								  get = false;
							  }
							  if (rand_posy == 2700 && loap_size > 1199)
							  {
								  drawFillBox(-WIDTH / 2 + 140 + word_count * 10 + 100, -man_sizey - 1500 + rand_posy,
									  10, 10 + loap_size, Color(0.5, 0.5, 0.5));
							  }

							  //ふつーに落ちたらやり直し
							  if (scroll_count == 6 || scroll_count == 7 || scroll_count == 8)
							  {
								  down = true;
								  scroll_count++;
							  }
							  //強制で初期値へワープ
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

							  //マップの近くによるとハックボタン表示
							  //7～8 段分　map
							  drawTextureBox(-WIDTH / 2 + 660, -man_sizey - 2400 + rand_posy, 500, 500, 0, 0, 750, 1000, map, Color(map_col, map_col, map_col));
							  if (Touch(man_posx, man_posy + jump.y, -WIDTH / 2 + 560, -man_sizey - 2400 + rand_posy, 500, 500) && scroll_count == 5)
							  {
								  //押してるとき
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
								  //押してないとき
								  if (!app_env.isPressKey('W') && map_col < 1)
								  {
									  hacking_bgm.stop();
									  drawTextureBox(man_posx, man_posy + jump.y + 50, 100, 60, 0, 0, 400, 60, hack_logo, Color(1, 1, 1, std::abs(::sin(time / 100))));
								  }

							  }
							  //ハック完了
							  if (map_col > 1)
							  {
								  //カウントに＋１
								  map_count = 1;
								  if (!item_bgm.isPlaying()&& m_sound_count == 0)
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
							  //セキュティポリスの弾発射。
							  if (bullet < 2500)
							  {
								  bullet += 12;
							  }
							  else
							  {
								  bullet = 0;
							  }
							  //とんでくる弾のあたり判定
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
								  //弾にあたったら、ランダムで上の段に強制移動
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

							  

							  ////セキュリティポリス表示
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

							  //9段目

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
							  //アイテム7
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
							  cout << scroll_count << endl;
							  //10段目
							  if (Rand_on(man_posx, -WIDTH / 2 + 1060 - word_count * 12, word_count * 12)
								  && scroll_count == 10
								  && rand_posy == 3000
								  && !boss)
							  {
								  down = true;
								  scroll_count++;
							  }
							  //アイテム8
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
							  //11段目 ゴール付近演出
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

								  //行動範囲制限
								  if (man_posx > -WIDTH / 2 + (140 + word_count * 12 - man_sizex) && rand_posy == 3300)
								  {
									  man_posx = -WIDTH / 2 + (140 + word_count * 12 - man_sizex);
								  }


							  }
							  //ゴール条件満たせていればふれればボス突入
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
									  //画面左下からボス出現	
									  drawTextureBox(-WIDTH / 2, 3000 - rand_posy + 30 * sin(enemy_action / 30),
										  140, 200,
										  230 * ((enemy_action / 70) % 3), 30, 230, 370,
										  enemy,
										  Color(1, 1, 1));
									  //弾
									  drawTextureBox(-WIDTH / 2, 3000 - rand_posy - 50,
										  140, 150,
										  0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165,
										  enemy,
										  Color(1, 1, 1));

									  //映画？みたいな黒枠表示
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

							  ///////////////////////////////////////////////////////////////////////ボス出現	
							  if (boss)
							  {
								  //bgm
								  warning.stop();

								  time -= 1;
								  //BOSS専用キャラ動作・上下方向移動可能
								  //右方向キーで右へ 
								  if (nomove_count == 0)
								  {
									  //右方向キーで右へ 
									  if (app_env.isPressKey(GLFW_KEY_RIGHT) && man_posx < WIDTH / 2 - (man_sizey + 15))
									  {
										  man_posx += v;
										  value += 1;
										  man_move = (value / 7) % 4;
										  see_left = false;
									  }

									  //左方向キーで左へ
									  if (app_env.isPressKey(GLFW_KEY_LEFT) && man_posx  > -WIDTH / 2)
									  {
										  man_posx -= v;
										  value += 1;
										  man_move = (value / 7) % 4;
										  see_left = true;
									  }
									  //上方向キーで上へ 
									  if (app_env.isPressKey(GLFW_KEY_UP) && man_posy < 150 - (man_sizex + 15))
									  {
										  man_posy += v;
										  value += 1;
										  man_move = (value / 7) % 4;
										  see_left = false;
									  }

									  //下方向キーで下へ
									  if (app_env.isPressKey(GLFW_KEY_DOWN) && man_posy > -HEIGHT / 2 + 50)
									  {
										  man_posy -= v;
										  value += 1;
										  man_move = (value / 7) % 4;
										  see_left = true;
									  }
								  }
								  //横スクロール開始　メインキャラ左に少しずつ強制移動
								  if (WIDTH / 2 - (side_scroll / 3 - 60 * 15) * 3 >= 0)
								  {
									  side_scroll += 3;
									  man_posx -= 1;
								  }
								  else
								  {
									  man_posx += 10;

								  }

								  ///BOSS背景
								  if (-side_scroll + WIDTH / 2 >= -WIDTH / 2)
								  {
									  //中心の背景
									  drawTextureBox(-side_scroll + WIDTH / 2, -HEIGHT / 2,
										  1200, 400,
										  0, 0, 512, 512,
										  boss_bg,
										  Color(1, 1, 1));

									  //上下の壁表示
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
									  //逃げろ！！
									  drawTextureBox(-90,0 + 20 * sin(enemy_action/30),230,85,
										  0,0,185, 55,
										  word2,
										  Color(1,1,1));
								  }
								  else
								  {
									  drawTextureBox(-WIDTH / 2, -HEIGHT / 2,
										  1200, 400,
										  0 + ((int)side_scroll % 1200) / 2, 0, 512, 512,
										  boss_bg,
										  Color(1, 1, 1));
									  //上下の壁表示
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


								  //BOSS表示
								  drawTextureBox(-WIDTH / 2 + side_scroll / 30, 3000 - rand_posy + 30 * sin(enemy_action / 30),
									  140, 200, 230 * ((enemy_action / 70) % 3),
									  30, 230, 370,
									  enemy,
									  Color(1, 1, 1));
								  //弾表示
								  drawTextureBox(-WIDTH / 2 + side_scroll / 30, 3000 - rand_posy - 100,
									  140, 200,
									  0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165,
									  enemy,
									  Color(1, 1, 1));
								  //障害物の壁の位置をランダムに代入
								  if (side_scroll > 1200)
								  {
									  //障害物の壁、弾が一定までいったら初期値に戻るように設定
									  if (boss_action < 2500 && side_scroll / 3 < 60 * 17)
									  {
										  boss_action += 12;
									  }
									  else
									  {
										  boss_action = 0;
									  }

									  //ランダムで弾の位置を代入
									  if (WIDTH / 2 - bullet >= WIDTH / 2)
									  {
										  wall_posy = rand();
										  wall_posy2 = rand();
										  wall_posy3 = rand();
									  }
									  //壁を表示
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
									  //弾発射
									  drawTextureBox(-WIDTH / 2 + boss_action / 1.4, -HEIGHT / 2 + 50 + (wall_posy3 % 250) + 50 * sin(enemy_action / 20),
										  50, 50,
										  0 + ((enemy_action / 8) % 3) * 210, 445, 210, 165,
										  enemy,
										  Color(1, 1, 1));
									  //あたり判定
									  //壁一個目
									  if (Touch_wall(man_posx, man_posy, WIDTH / 2 - boss_action / 1.4, -HEIGHT / 2 + 50 + (wall_posy % 200), 39, 110) 
										  && side_scroll / 3 < 60 * 17)
									  {
										  man_posx = WIDTH / 2 - boss_action / 1.4 - (man_sizey + 15);
									  }
									  //壁二個目
									  if (Touch_wall(man_posx, man_posy, WIDTH / 2 - boss_action / 1.4 + 400, -HEIGHT / 2 + 50 + (wall_posy2 % 150), 39, 110)
										  && side_scroll / 3 < 60 * 15)
									  {
										  man_posx = WIDTH / 2 - boss_action / 1.4 + 400 - (man_sizey + 15);
									  }
									  //弾　あたったら０．５秒停止
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
									  //15秒にげきったらクリア
									  if (side_scroll / 3 > 60 * 15)
									  {
										  
										  if (!hacking_bgm.isPlaying())
										  {
											  boss_bgm.gain(0.3);
											  hacking_bgm.play();
											  hacking_bgm.pitch(100);
										  }
										  //爆弾
										  // 明るさを回転角から決める
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
											  //煙を標示
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
											  drawTextureBox(-WIDTH / 2 + 350, -HEIGHT/2,
												  512, 512,
												  0, 0, 1024, 1024,
												  bomb_word,
												  Color(1, 1, 1),
												  0,
												  Vec2f(1, 1),
												  Vec2f(0, 0));
											  //煙を画面いっぱい一つ表示
											  drawTextureBox(-WIDTH / 2 - 200, -HEIGHT / 2 - 200,
												  1600, 800,
												  0, 0, 1024, 1024,
												  bomb,
												  Color(1, 1, 1, (float)end_efect/1000 ),
												  0,
												  Vec2f(1, 1),
												  Vec2f(0, 0));
											  //画面中心にクリア画面表示
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
												  else if (man_action >=1000)
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

											  //クリア画面
											  if (app_env.isPushKey('A'))
											  {
												  
												  go = false;
												  info_bool = false;
												  sugihei_clear = true;
												  display = 1;
												 
												  
											  }
										  }

									  }


								  }
							  }
						  }
					  }
					  ////////////////キャラクター動作


					  //メインキャラ表示 （右向きの時は右、左の時は左をみる)
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


					  ////サイレン
					  // 明るさを回転角から決める
					  float color = fabs(std::sin(time / 30)) * 0.5 + 0.5;

					  drawTextureBox(WIDTH / 2 - 85, -HEIGHT / 2 + 85,
						  66.6, 36,
						  200 + siren, 20, 80, 70,
						  hp_etc,
						  Color(color, color, color));

					  //hp(timer)表示
					  drawTextureBox(WIDTH / 2 - 100, -HEIGHT / 2,
						  100, 100,
						  0, 0, 170, 170,
						  hp_etc,
						  Color( r, g ,b));

					  //時間の針
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
						  gameover_bgm.play();
					  }

					  //アイテム数表示
					  //date×個数
					  drawTextureBox(WIDTH / 2 - date_sizex / 4 - 200, -HEIGHT / 2, date_sizex / 4, date_sizey / 4,
						  0, 0, date_sizex, date_sizey,
						  date,
						  Color(0.5, 0.5, 0.5));
					  //”×”
					  drawTextureBox(WIDTH / 2 - date_sizex / 4 - 150, -HEIGHT / 2,
						  14, 14,
						  6, 423, 14, 14,
						  hp_etc,
						  Color(1, 1, 1));
					  //"数字" date取得後、＋１
					  drawTextureBox(WIDTH / 2 - date_sizex / 4 - 130, -HEIGHT / 2,
						  22, 27,
						  1 * 21 * item, 387, 22, 27,
						  hp_etc,
						  Color(1, 1, 1));
					  //map×個数
					  drawTextureBox(WIDTH / 2 - date_sizex / 4 - 350, -HEIGHT / 2,
						  date_sizex / 4, date_sizey / 4, 0, 0,
						  750, 1000,
						  map,
						  Color(0.5, 0.5, 0.5));
					  //”×”
					  drawTextureBox(WIDTH / 2 - date_sizex / 4 - 300, -HEIGHT / 2,
						  14, 14,
						  6, 423, 14, 14,
						  hp_etc,
						  Color(1, 1, 1));
					  //"数字"hack成功後　＋　１
					  drawTextureBox(WIDTH / 2 - date_sizex / 4 - 280, -HEIGHT / 2,
						  22, 27,
						  1 * 22 * (map_count), 387, 22, 27,
						  hp_etc,
						  Color(1, 1, 1));
					  //drawTextureBox();

					  //なんか電脳世界っぽく四角いのをキャラ周りに表示
					  drawFillBox(man_posx + rand() % (man_sizex + 30) - 30,
						  man_posy + jump.y + rand() % man_sizey,
						  10, 10, Color(0, 0.5, 0.5, 2 - time / 100));
					  drawFillBox(man_posx + rand() % (man_sizex + 20) * 2 - 20,
						  man_posy + jump.y + rand() % man_sizey * 2,
						  10, 10, Color(0, 0.5, 0.5, 2 - time / 100));

					  //方向キーをおしてないときは、棒立ち
					  if (!app_env.isPressKey(GLFW_KEY_LEFT) || !app_env.isPressKey(GLFW_KEY_RIGHT) 
						  && !get)
					  {
						  man_move = 0;
					  }

					  //ボス戦ではないときの動き
					  if (!boss)
					  {
						  if (!no_move)
						  {
							  //移動制限左
							  if (man_posx < -WIDTH / 2 + 140)
							  {
								  man_posx = -WIDTH / 2 + 140;
							  }
							  //移動制限右
							  if (man_posx > WIDTH / 2 - 160)
							  {
								  man_posx = WIDTH / 2 - 160;
							  }
							  //右方向キーで右へ 
							  if (app_env.isPressKey(GLFW_KEY_RIGHT))
							  {

								  man_posx += v;
								  value += 1;
								  man_move = (value / 7) % 4;
								  see_left = false;
							  }

							  //左方向キーで左へ
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
							  //ジャンプ
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

						  
						  //デバッグキー強制場所移動
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
							  gameover_bgm.play();
						  }
						
						  // ジャンプ中の動作
						  // TIPS:等加速運動の法則を利用
						  // s = v0 * t + 0.5 * a * t^2
						  // v = v0 + a * t
						  if (jump.jumping) {
							  jump.y += jump.vy + 0.5 * gravity;
							  jump.vy += gravity;

							  // 着地
							  if (jump.y <= 0.0) {
								  man_posy = 0;
								  jump.y = 0.0f;
								  jump.jumping = false;
							  }
						  }
						  //落ちる
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
		

						  //台から落ちるときようの重力
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
			}
			break;
			
			//game_over
			case 3:
			{
					  drawTextureBox(-WIDTH / 2, - HEIGHT / 2,
						  1200, 500,
						  0, 0, 1200, 500,
						  game_over,
						  Color(1, 1, 1));
					  
					  //bgm
					  main_bgm.stop();
					  walk_bgm.stop();


					  //画像表示
					  //クリックしたらやり直し
					  //クリックしたらメニュー
					  //本編の初期化

					  man_posx = 500.0, man_posy = 0.0;
					  man_move = 0, value = 0;
					  v = 5;
					  siren = 0;
					  n_gravity = 0.01;
					  life = 3 * 60 * 60;
					  down_man = false;
					  no_move = false;
					  see_left = false;
					  get = false;
					  n = 0;
					  item_count[0] = 1;
					  item_count[1] = 1;
					  item_count[2] = 1;
					  item_count[3] = 1;
					  item_count[4] = 1;
					  item_count[5] = 1;
					  item_count[6] = 1;
					  item_count[7] = 1;
					  r = 0;
					  g = 0;
					  b = 1;

					  item = 0;
					  map_count = 0;
					  //地面
					  scroll_count = -1;
					  side_scroll = 0;
					  rand_posy = 0;
					  t = 1;
					  down = false;
					  //アイテム    
					  get_count = 0;
					  //s障害物
					  enemy_action = 0;
					  time = 0;
					  ww = 1;
					  on = false;
					  map_load = 0;
					  map_col = 0;
					  loap_size = 0;

					  bullet = 0;
					  stop_bar = 0;
					  bar_col = 1;
					  unlock = 0;
					  bgm_count = 0;


					  //BOSSアクション用
					  boss_action = 0;
					  wall_posy = 0;
					  wall_posy2 = 0;
					  wall_posy3 = 0;
					  nomove_count = 0;
					  end_efect = 0;
					  boss = false;
					  
					  info_bool = false;
					  info_col = 0;
					  go = false;
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


