#pragma onece



// アプリのウインドウサイズ
enum Window {
	WIDTH = 1200,
	HEIGHT = 500
};


//ジャンプ
struct Jump
{
	float y;
	float vy;

	bool jumping;
};
const float jump_power = 12.0f;
const float gravity = -0.8f;

//画面変更用の変数　switch文にて使用
int display = 0;

