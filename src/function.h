#pragma onece

//�n�ʐG��Ă邩�ǂ����������݂̂Ŕ���
bool Rand_on(int man_posx, int rand_posx, int rand_sizex)
{
	int man_sizex = 31;
	if (man_posx + man_sizex > rand_posx && man_posx < rand_posx + rand_sizex)
	{
		return false;
	}
	else
	{
		return true;
	}
};

//���ד��̏�Q���̂����蔻��������Ƃ������ׂĔ��� (�ʏ펞)
bool Touch(int man_posx, int man_posy, float enemy_posx, float enemy_posy, int enemy_sizex, float enemy_sizey)
{
	int man_sizex = 31;
	int man_sizey = 59;
	if (man_posx + man_sizex > enemy_posx && man_posx < enemy_posx + enemy_sizex &&
		man_posy + man_sizey > enemy_posy && man_posy < enemy_posy + enemy_sizey)
	{
		return true;
	}
	else
	{
		return false;
	}
};

//���ד��̏�Q���̂����蔻��������Ƃ������ׂĔ��� (BOSS�퓬��)
bool Touch_wall(int man_posx, int man_posy, float enemy_posx, float enemy_posy, int enemy_sizex, float enemy_sizey)
{
	int man_sizex = 74;
	int man_sizey = 46;
	if (man_posx + man_sizex > enemy_posx && man_posx < enemy_posx + enemy_sizex &&
		man_posy + man_sizey > enemy_posy && man_posy < enemy_posy + enemy_sizey)
	{
		return true;
	}
	else
	{
		return false;
	}
};
