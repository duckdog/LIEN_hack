#pragma onece


//�n�ʂɂ̂��Ă邩�������݂̂Ŕ���
bool Rand_on(int man_posx, int rand_posx, int rand_sizex);

//���ד��̏�Q���̂����蔻��������Ƃ������ׂĔ��� (�ʏ펞)
bool Touch(int man_posx, int man_posy, float enemy_posx, float enemy_posy, int enemy_sizex, float enemy_sizey);

//���ד��̏�Q���̂����蔻��������Ƃ������ׂĔ��� (BOSS�퓬��)
bool Touch_wall(int man_posx, int man_posy, float enemy_posx, float enemy_posy, int enemy_sizex, float enemy_sizey);
