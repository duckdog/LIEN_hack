#pragma onece


//地面にのってるかをｘ軸のみで判定
bool Rand_on(int man_posx, int rand_posx, int rand_sizex);

//かべ等の障害物のあたり判定をｘ軸とｙ軸を比べて判定 (通常時)
bool Touch(int man_posx, int man_posy, float enemy_posx, float enemy_posy, int enemy_sizex, float enemy_sizey);

//かべ等の障害物のあたり判定をｘ軸とｙ軸を比べて判定 (BOSS戦闘時)
bool Touch_wall(int man_posx, int man_posy, float enemy_posx, float enemy_posy, int enemy_sizex, float enemy_sizey);
