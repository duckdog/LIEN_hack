#pragma onece



// �A�v���̃E�C���h�E�T�C�Y
enum Window {
	WIDTH = 1200,
	HEIGHT = 500
};


//�W�����v
struct Jump
{
	float y;
	float vy;

	bool jumping;
};
const float jump_power = 12.0f;
const float gravity = -0.8f;

//��ʕύX�p�̕ϐ��@switch���ɂĎg�p
int display = 0;

