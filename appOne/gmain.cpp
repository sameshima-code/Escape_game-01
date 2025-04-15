#include"libOne.h"
#define STAGE_WIDTH 10
#define STAGE_HEIGHT 10
struct PLAYER {
    int player_x = 2;
    int player_y = 2;
	int last_player_x = 0;
	int last_player_y = 0;
	int use_x = 0;
	int use_y = 0;
	char direction = 0;
	int use_point[10][10] = { 0 };
	bool Not_move = 0;
};
struct STAGE {
	int map[10][10] = { 0 };
	const enum { WALL, FLOOR, GIMMICK , DOOR , WINDOW};
	float size = 100;
};
struct OTHER {
	bool point = 0;
};
struct GIMMICK {
	bool search_flower = 0;
	bool broke_window = 0;
	char gimmick_No = 0;
	bool gimmick_No1 = 0;
	bool gimmick_No2 = 0;
	bool gimmick_No3 = 0;
	bool gimmick_No4 = 0;
	bool gimmick_No5 = 0;
	bool gimmick_No6 = 0;
	bool gimmick_No7 = 0;
	bool gimmick_No8 = 0;
	bool gimmick_No9 = 0;
	bool gimmick_No10 = 0;
	char have_knife_move = 0;
	bool go_end2 = 0;
	bool go_end2_1 = 0;
	bool go_end2_2 = 0;
	bool go_end2_3 = 0;
	bool go_end2_4 = 0;
	bool light_on_fire = 0;
};
struct ITEM {
	bool candle = 0;
	bool knife = 0;
	bool key = 0;
};
struct GAME {
	const enum {
		TITLE, STAGE, END1, END2, END3
	};
	char game_state = TITLE;
};
void initmap(struct STAGE* s_pointer) {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH - 1; x++) {
			s_pointer->map[y][x] = s_pointer->FLOOR;
			s_pointer->map[0][x] = s_pointer->WALL;
			s_pointer->map[y][0] = s_pointer->WALL;
			s_pointer->map[y][STAGE_WIDTH - 1] = s_pointer->WALL;
			s_pointer->map[STAGE_HEIGHT - 1][x] = s_pointer->WALL;
		}
	}
	//y,x.
	s_pointer->map[4][8] = s_pointer->GIMMICK;//燭.
	s_pointer->map[8][5] = s_pointer->GIMMICK;//鏡.
	s_pointer->map[5][1] = s_pointer->GIMMICK;//台.
	s_pointer->map[8][1] = s_pointer->GIMMICK;//箱.
	s_pointer->map[1][5] = s_pointer->GIMMICK;//花.
	s_pointer->map[4][5] = s_pointer->GIMMICK;//机.
	s_pointer->map[4][4] = s_pointer->GIMMICK;//机.
	s_pointer->map[8][8] = s_pointer->GIMMICK;//棚.
	s_pointer->map[7][8] = s_pointer->GIMMICK;//棚.
	s_pointer->map[0][1] = s_pointer->WINDOW;
	s_pointer->map[0][2] = s_pointer->WINDOW;
	s_pointer->map[0][4] = s_pointer->WINDOW;
	s_pointer->map[0][5] = s_pointer->WINDOW;
	s_pointer->map[0][7] = s_pointer->WINDOW;
	s_pointer->map[0][8] = s_pointer->WINDOW;
	s_pointer->map[9][6] = s_pointer->DOOR;
}
void INIT(struct PLAYER*p_pointer,struct GIMMICK* gi_pointer,struct ITEM* i_pointer) {
	p_pointer->player_x = 2;
	p_pointer->player_y = 2;
	p_pointer->direction = 0;
	p_pointer->Not_move = 0;
	gi_pointer->search_flower = 0;
	gi_pointer->broke_window = 0;
	gi_pointer->have_knife_move = 0;
	gi_pointer->light_on_fire = 0;
	i_pointer->candle = 0;
	i_pointer->key = 0;
	i_pointer->knife = 0;
}
void TITLE(struct GAME* g_pointer, struct OTHER* o_pointer, struct STAGE* s_pointer) {
	if (isTrigger(KEY_W)) { o_pointer->point = 0; }
	if (isTrigger(KEY_S)) { o_pointer->point = 1; }
	rectMode(CORNER);
	clear(0);
	fill(255);
	textSize(200);
	text("脱出ゲーム", 50, 200);
	rect(600, 400, 500, 200);
	if (o_pointer->point == 0) {
		text(">", 350, 600);
	}
	else {
		text(">", 350, 900);
	}
	rect(600, 700, 500, 200);
	fill(0);
	text("PLAY", 650, 600);
	text("EXIT", 650, 900);
	if (o_pointer->point == 0) {
		if (isTrigger(KEY_SPACE)) {
			initmap(s_pointer);
			g_pointer->game_state = g_pointer->STAGE;
		}
	}
}
void draw_player(struct STAGE* s_pointer, struct PLAYER* p_pointer) {
	rectMode(CENTER);
	fill(100);
	textSize(s_pointer->size);
	if (p_pointer->direction == 0) {
		text("↑", s_pointer->size * p_pointer->player_x, s_pointer->size * p_pointer->player_y);
	}
	if (p_pointer->direction == 1) {
		text("←", s_pointer->size * p_pointer->player_x, s_pointer->size * p_pointer->player_y);
	}
	if (p_pointer->direction == 2) {
		text("↓", s_pointer->size * p_pointer->player_x, s_pointer->size * p_pointer->player_y);
	}
	if (p_pointer->direction == 3) {
		text("→", s_pointer->size * p_pointer->player_x, s_pointer->size * p_pointer->player_y);
	}
}
void draw_map(struct STAGE* s_pointer, struct PLAYER* p_pointer) {
	rectMode(CENTER);
	textSize(s_pointer->size);
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			if (s_pointer->map[y][x] == s_pointer->WALL|| s_pointer->map[y][x] == s_pointer->WINDOW || s_pointer->map[y][x] == s_pointer->DOOR) {
				fill(200);
				rect((s_pointer->size * x) + 50, (s_pointer->size * y) + 50, s_pointer->size, s_pointer->size);
			}
			else if (s_pointer->map[y][x] == s_pointer->FLOOR) {
				fill(50);
				rect((s_pointer->size * x) + 50, (s_pointer->size * y) + 50, s_pointer->size / 10, s_pointer->size / 10);
			}
		}
	}
}
void draw_map_player(struct STAGE* s_pointer, struct PLAYER* p_pointer) {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			if (s_pointer->map[y][x] == s_pointer->map[p_pointer->player_y][p_pointer->player_x]) {
				draw_player(s_pointer, p_pointer);
			}
		}
	}
}
void use_item(struct STAGE* s_pointer, struct PLAYER* p_pointer) {
	if (isTrigger(KEY_F)) {
		if (p_pointer->direction == 0) {
			p_pointer->use_y = p_pointer->player_y-2;
			p_pointer->use_x = p_pointer->player_x;
		}
		else if (p_pointer->direction == 1) {
			p_pointer->use_y = p_pointer->player_y-1;
			p_pointer->use_x = p_pointer->player_x-1;
		}
		else if (p_pointer->direction == 2) {
			p_pointer->use_y = p_pointer->player_y;
			p_pointer->use_x = p_pointer->player_x;
		}
		else if (p_pointer->direction == 3) {
			p_pointer->use_y = p_pointer->player_y-1;
			p_pointer->use_x = p_pointer->player_x+1;
		}
		//debug.
		//fill(255);
		//rect((s_pointer->size * p_pointer->use_x) + 50, (s_pointer->size * p_pointer->use_y) + 50, s_pointer->size, s_pointer->size );
	}
}
void move_player(struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer) {
	if (gi_pointer->go_end2 == 0) {
		if (p_pointer->Not_move == 0) {
			if (isTrigger(KEY_W)) {
				if (i_pointer->knife == 1) {
					gi_pointer->have_knife_move++;
				}
				p_pointer->direction = 0;
				p_pointer->last_player_y = p_pointer->player_y;
				if (p_pointer->player_y - 1 != 1) { p_pointer->player_y--; }
			}
			if (isTrigger(KEY_A)) {
				if (i_pointer->knife == 1) {
					gi_pointer->have_knife_move++;
				}
				p_pointer->direction = 1;
				p_pointer->last_player_x = p_pointer->player_x;
				if (p_pointer->player_x - 1 != 0) { p_pointer->player_x--; }
			}
			if (isTrigger(KEY_S)) {
				if (i_pointer->knife == 1) {
					gi_pointer->have_knife_move++;
				}
				p_pointer->direction = 2;
				p_pointer->last_player_y = p_pointer->player_y;
				if (p_pointer->player_y + 1 != STAGE_HEIGHT) { p_pointer->player_y++; }
			}
			if (isTrigger(KEY_D)) {
				if (i_pointer->knife == 1) {
					gi_pointer->have_knife_move++;
				}
				p_pointer->direction = 3;
				p_pointer->last_player_x = p_pointer->player_x;
				if (p_pointer->player_x + 1 != STAGE_WIDTH - 1) { p_pointer->player_x++; }
			}
		}
	}
}
void judge_collision(struct STAGE* s_pointer, struct PLAYER* p_pointer) {
	if (p_pointer->direction == 0|| p_pointer->direction == 2) {
		if (s_pointer->map[p_pointer->player_y-1][p_pointer->player_x] == s_pointer->GIMMICK) {
			p_pointer->player_y = p_pointer->last_player_y;
		}
	}
	if (p_pointer->direction == 1|| p_pointer->direction == 3) {
		if (s_pointer->map[p_pointer->player_y-1][p_pointer->player_x] == s_pointer->GIMMICK) {
			p_pointer->player_x = p_pointer->last_player_x;
		}
	}
}
void gimmick(struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer) {
	if (gi_pointer->go_end2 == 0) {
		if (isTrigger(KEY_F)) {
			if (s_pointer->map[p_pointer->use_y][p_pointer->use_x] == s_pointer->GIMMICK) {
				if (p_pointer->use_y == 7 && p_pointer->use_x == 8) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No1 = 1;
				}
				if (p_pointer->use_y == 8 && p_pointer->use_x == 8) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No2 = 1;
				}
				if (p_pointer->use_y == 4 && p_pointer->use_x == 4) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No5 = 1;
				}
				if (p_pointer->use_y == 4 && p_pointer->use_x == 5) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No5 = 1;
				}
				if (p_pointer->use_y == 1 && p_pointer->use_x == 5) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No6 = 1;
				}
				if (p_pointer->use_y == 8 && p_pointer->use_x == 1) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No7 = 1;
				}
				if (p_pointer->use_y == 8 && p_pointer->use_x == 5) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No8 = 1;
				}
				if (p_pointer->use_y == 5 && p_pointer->use_x == 1) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No9 = 1;
				}
				if (p_pointer->use_y == 4 && p_pointer->use_x == 8) {
					if (i_pointer->knife == 1) {
						gi_pointer->have_knife_move++;
					}
					gi_pointer->gimmick_No10 = 1;
				}
			}
			else if (s_pointer->map[p_pointer->use_y][p_pointer->use_x] == s_pointer->WINDOW) {
				if (i_pointer->knife == 1) {
					gi_pointer->have_knife_move++;
				}
				gi_pointer->gimmick_No3 = 1;
			}
			else if (s_pointer->map[p_pointer->use_y][p_pointer->use_x] == s_pointer->DOOR) {
				if (i_pointer->knife == 1) {
					gi_pointer->have_knife_move++;
				}
				gi_pointer->gimmick_No4 = 1;
			}
		}
	}
}
void draw_gimmick(struct STAGE* s_pointer, struct PLAYER* p_pointer) {
	fill(255);
	text("燭", s_pointer->size * 8, s_pointer->size * 5);
	text("台", s_pointer->size * 1, s_pointer->size * 6);
	text("鏡", s_pointer->size * 5, s_pointer->size * 9);
	text("箱", s_pointer->size * 1, s_pointer->size * 9);
	text("棚", s_pointer->size * 8, s_pointer->size * 9);
	text("棚", s_pointer->size * 8, s_pointer->size * 8);
	text("机", s_pointer->size * 5, s_pointer->size * 5);
	text("机", s_pointer->size * 4, s_pointer->size * 5);
	text("花", s_pointer->size * 5, s_pointer->size * 2);
	fill(0);
	text("窓", s_pointer->size * 8, s_pointer->size * 1);
	text("窓", s_pointer->size * 7, s_pointer->size * 1);
	text("窓", s_pointer->size * 5, s_pointer->size * 1);
	text("窓", s_pointer->size * 4, s_pointer->size * 1);
	text("窓", s_pointer->size * 2, s_pointer->size * 1);
	text("窓", s_pointer->size * 1, s_pointer->size * 1);
	text("扉", s_pointer->size * 6, s_pointer->size * 10);
}
void Go_END2(struct GAME* g_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer, struct OTHER* o_pointer) {
	if (gi_pointer->have_knife_move >= 100) {
		gi_pointer->have_knife_move = 0;
		gi_pointer->go_end2 = 1;
	}
}
void Text(struct GAME* g_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer, struct OTHER* o_pointer) {
	textSize(50);
	fill(255);
	if (gi_pointer->gimmick_No1 == 1) {
		text("棚がある。", 1010, 100);
		text("中には何もない。", 1010, 150);
		text("Q：QUIT", 1010, 900);
		p_pointer->Not_move = 1;
		if (isTrigger(KEY_Q)) {
			gi_pointer->gimmick_No1 = 0;
			p_pointer->Not_move = 0;
		}
	}
	else if (gi_pointer->gimmick_No2 == 1) {
		if (i_pointer->knife == 0) {
			if (isTrigger(KEY_W)) { o_pointer->point = 0; }
			if (isTrigger(KEY_S)) { o_pointer->point = 1; }
			text("棚がある。", 1010, 100);
			text("ナイフがある。", 1010, 150);
			text("Q：QUIT/OK", 1010, 900);
			p_pointer->Not_move = 1;
			if (o_pointer->point == 0) {
				text(">手に取らない。", 1010, 400);
				text("手に取る。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					gi_pointer->gimmick_No2 = 0;
					p_pointer->Not_move = 0;
				}
			}
			else if (o_pointer->point == 1) {
				text("手に取らない。", 1010, 400);
				text(">手に取る。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					o_pointer->point = 0;
					i_pointer->knife = 1;
					gi_pointer->gimmick_No2 = 0;
					p_pointer->Not_move = 0;
				}
			}
		}
		if (i_pointer->knife == 1) {
			text("棚がある。", 1010, 100);
			text("中には何もない。", 1010, 150);
			text("Q：QUIT", 1010, 900);
			p_pointer->Not_move = 1;
			if (isTrigger(KEY_Q)) {
				gi_pointer->gimmick_No2 = 0;
				p_pointer->Not_move = 0;
			}
		}
	}
	else if (gi_pointer->gimmick_No3 == 1) {
		if (p_pointer->use_x != 4) {
			text("窓がある。", 1010, 100);
			text("暗くて外はよく見えない。", 1010, 150);
			text("Q：QUIT", 1010, 900);
			p_pointer->Not_move = 1;
			if (isTrigger(KEY_Q)) {
				gi_pointer->gimmick_No3 = 0;
				p_pointer->Not_move = 0;
			}
		}
		else if (p_pointer->use_x == 4) {
			if (gi_pointer->search_flower == 0) {
				text("窓がある。", 1010, 100);
				text("暗くて外はよく見えない。", 1010, 150);
				text("Q：QUIT", 1010, 900);
				p_pointer->Not_move = 1;
				if (isTrigger(KEY_Q)) {
					gi_pointer->gimmick_No3 = 0;
					p_pointer->Not_move = 0;
				}
			}
			else if (gi_pointer->search_flower == 1) {
				if (gi_pointer->broke_window == 0) {
					if (isTrigger(KEY_W)) { o_pointer->point = 0; }
					if (isTrigger(KEY_S)) { o_pointer->point = 1; }
					text("窓がある。", 1010, 100);
					text("花瓶で割れそうだ。", 1010, 150);
					text("Q：QUIT/OK", 1010, 900);
					p_pointer->Not_move = 1;
					if (o_pointer->point == 0) {
						text(">窓を割らない。", 1010, 400);
						text("窓を割る。", 1010, 450);
						if (isTrigger(KEY_Q)) {
							gi_pointer->gimmick_No3 = 0;
							p_pointer->Not_move = 0;
						}
					}
					else if (o_pointer->point == 1) {
						text("窓を割らない。", 1010, 400);
						text(">窓を割る。", 1010, 450);
						if (isTrigger(KEY_Q)) {
							o_pointer->point = 0;
							gi_pointer->broke_window = 1;
							gi_pointer->gimmick_No3 = 0;
							p_pointer->Not_move = 0;
						}
					}
				}
				else if (gi_pointer->broke_window == 1) {
					if (isTrigger(KEY_W)) { o_pointer->point = 0; }
					if (isTrigger(KEY_S)) { o_pointer->point = 1; }
					text("割れた窓がある。", 1010, 100);
					text("地面は見えない。", 1010, 150);
					text("ここから出られそうだ。", 1010, 200);
					text("Q：QUIT/OK", 1010, 900);
					p_pointer->Not_move = 1;
					if (o_pointer->point == 0) {
						text(">他を探索する。", 1010, 400);
						text("窓から脱出する。", 1010, 450);
						if (isTrigger(KEY_Q)) {
							gi_pointer->gimmick_No3 = 0;
							p_pointer->Not_move = 0;
						}
					}
					else if (o_pointer->point == 1) {
						text("他を探索する。", 1010, 400);
						text(">窓から脱出する。", 1010, 450);
						if (isTrigger(KEY_Q)) {
							o_pointer->point = 0;
							gi_pointer->gimmick_No3 = 0;
							p_pointer->Not_move = 0;
							g_pointer->game_state = g_pointer->END1;
						}
					}
				}
			}
		}
	}
	else if (gi_pointer->gimmick_No4 == 1) {
		if (i_pointer->key == 0) {
			text("扉がある。", 1010, 100);
			text("ここから出るのだろう。", 1010, 150);
			text("鍵が必要だ。", 1010, 200);
			text("Q：QUIT", 1010, 900);
			p_pointer->Not_move = 1;
			if (isTrigger(KEY_Q)) {
				gi_pointer->gimmick_No4 = 0;
				p_pointer->Not_move = 0;
			}
		}
		else if (i_pointer->key == 1) {
			if (isTrigger(KEY_W)) { o_pointer->point = 0; }
			if (isTrigger(KEY_S)) { o_pointer->point = 1; }
			text("扉がある。", 1010, 100);
			text("ここから出られそうだ。", 1010, 150);
			text("Q：QUIT/OK", 1010, 900);
			p_pointer->Not_move = 1;
			if (o_pointer->point == 0) {
				text(">他を探索する。", 1010, 400);
				text("脱出する。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					gi_pointer->gimmick_No4 = 0;
					p_pointer->Not_move = 0;
				}
			}
			else if (o_pointer->point == 1) {
				text("他を探索する。", 1010, 400);
				text(">脱出する。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					o_pointer->point = 0;
					i_pointer->key = 0;
					gi_pointer->gimmick_No4 = 0;
					p_pointer->Not_move = 0;
					g_pointer->game_state = g_pointer->END3;
				}
			}
		}
	}
	else if (gi_pointer->gimmick_No5 == 1) {
		if (gi_pointer->light_on_fire == 0) {
			text("机がある。", 1010, 100);
			text("少し埃を被っている。", 1010, 150);
			text("特に目ぼしいものはない。", 1010, 200);
			text("Q：QUIT", 1010, 900);
			p_pointer->Not_move = 1;
			if (isTrigger(KEY_Q)) {
				gi_pointer->gimmick_No5 = 0;
				p_pointer->Not_move = 0;
			}
		}
		else if (gi_pointer->light_on_fire == 1) {
			if (isTrigger(KEY_W)) { o_pointer->point = 0; }
			if (isTrigger(KEY_S)) { o_pointer->point = 1; }
			text("机がある。", 1010, 100);
			text("溝に鍵が挟まっている。", 1010, 150);
			text("Q：QUIT/OK", 1010, 900);
			p_pointer->Not_move = 1;
			if (o_pointer->point == 0) {
				text(">手に取らない。", 1010, 400);
				text("手に取る。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					gi_pointer->gimmick_No5 = 0;
					p_pointer->Not_move = 0;
				}
			}
			else if (o_pointer->point == 1) {
				text("手に取らない。", 1010, 400);
				text(">手に取る。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					o_pointer->point = 0;
					i_pointer->key = 1;
					gi_pointer->gimmick_No5 = 0;
					p_pointer->Not_move = 0;
				}
			}
		}
	}
	else if (gi_pointer->gimmick_No6 == 1) {
		text("花がある。", 1010, 100);
		text("もう少しで枯れそうだ。", 1010, 150);
		text("大きめの壺に入っている。", 1010, 200);
		text("Q：QUIT", 1010, 900);
		p_pointer->Not_move = 1;
		gi_pointer->search_flower = 1;
		if (isTrigger(KEY_Q)) {
			gi_pointer->gimmick_No6 = 0;
			p_pointer->Not_move = 0;
		}
	}
	else if (gi_pointer->gimmick_No7 == 1) {
		text("大きい箱がある。", 1010, 100);
		text("木製だが頑丈そうだ。", 1010, 150);
		text("Q：QUIT", 1010, 900);
		p_pointer->Not_move = 1;
		if (isTrigger(KEY_Q)) {
			gi_pointer->gimmick_No7 = 0;
			p_pointer->Not_move = 0;
		}
	}
	else if (gi_pointer->gimmick_No8 == 1) {
		text("鏡がある。", 1010, 100);
		text("汚れていて全く見えない。", 1010, 150);
		text("Q：QUIT", 1010, 900);
		p_pointer->Not_move = 1;
		if (isTrigger(KEY_Q)) {
			gi_pointer->gimmick_No8 = 0;
			p_pointer->Not_move = 0;
		}
	}
	else if (gi_pointer->gimmick_No9 == 1) {
		if (i_pointer->candle == 0 && gi_pointer->light_on_fire == 0) {
			if (isTrigger(KEY_W)) { o_pointer->point = 0; }
			if (isTrigger(KEY_S)) { o_pointer->point = 1; }
			text("小さめの台がある。", 1010, 100);
			text("上に蝋燭がある。", 1010, 150);
			text("Q：QUIT/OK", 1010, 900);
			p_pointer->Not_move = 1;
			if (o_pointer->point == 0) {
				text(">手に取らない。", 1010, 400);
				text("手に取る。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					gi_pointer->gimmick_No9 = 0;
					p_pointer->Not_move = 0;
				}
			}
			else if (o_pointer->point == 1) {
				text("手に取らない。", 1010, 400);
				text(">手に取る。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					o_pointer->point = 0;
					i_pointer->candle = 1;
					gi_pointer->gimmick_No9 = 0;
					p_pointer->Not_move = 0;
				}
			}
		}
		else if (i_pointer->candle == 1 || gi_pointer->light_on_fire == 1) {
			text("小さめの台がある。", 1010, 100);
			text("上には何もない。", 1010, 150);
			text("Q：QUIT", 1010, 900);
			p_pointer->Not_move = 1;
			if (isTrigger(KEY_Q)) {
				gi_pointer->gimmick_No9 = 0;
				p_pointer->Not_move = 0;
			}
		}
	}
	else if (gi_pointer->gimmick_No10 == 1) {
		if (i_pointer->candle == 0 && gi_pointer->light_on_fire == 0) {
			text("燭台がある。", 1010, 100);
			text("蝋燭がない。", 1010, 150);
			text("Q：QUIT", 1010, 900);
			p_pointer->Not_move = 1;
			if (isTrigger(KEY_Q)) {
				gi_pointer->gimmick_No10 = 0;
				p_pointer->Not_move = 0;
			}
		}
		else if (i_pointer->candle == 0 && gi_pointer->light_on_fire == 1) {
			text("燭台がある。", 1010, 100);
			text("火がついている。", 1010, 150);
			text("部屋が明るくなった。", 1010, 200);
			text("Q：QUIT", 1010, 900);
			p_pointer->Not_move = 1;
			if (isTrigger(KEY_Q)) {
				gi_pointer->gimmick_No10 = 0;
				p_pointer->Not_move = 0;
			}
		}
		else if (i_pointer->candle == 1 && gi_pointer->light_on_fire == 0) {
			if (isTrigger(KEY_W)) { o_pointer->point = 0; }
			if (isTrigger(KEY_S)) { o_pointer->point = 1; }
			text("燭台がある。", 1010, 100);
			text("火をつけようか。", 1010, 150);
			text("Q：QUIT/OK", 1010, 900);
			p_pointer->Not_move = 1;
			if (o_pointer->point == 0) {
				text(">火をつけない。", 1010, 400);
				text("火をつける。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					gi_pointer->gimmick_No10 = 0;
					p_pointer->Not_move = 0;
				}
			}
			else if (o_pointer->point == 1) {
				text("火をつけない。", 1010, 400);
				text(">火をつける。", 1010, 450);
				if (isTrigger(KEY_Q)) {
					o_pointer->point = 0;
					i_pointer->candle = 0;
					gi_pointer->light_on_fire = 1;
					gi_pointer->gimmick_No10 = 0;
					p_pointer->Not_move = 0;
				}
			}
		}
	}
	else {
		if (gi_pointer->go_end2 == 0) {
			text("目標:この部屋からの脱出", 1010, 100);
			text("移動:", 1010, 200);
			text("    W", 1010, 250);
			text("   ASD", 1010, 300);
			text("使用:", 1010, 400);
			text("    F", 1010, 450);
		}
		else if (gi_pointer->go_end2 == 1 && gi_pointer->go_end2_4 == 0) {
			if (p_pointer->Not_move == 0) {
				text("ここから出ることは", 1010, 100);
				text("出来ないのだろうか。", 1010, 150);
				text("Q：NEXT", 1010, 900);
				if (isTrigger(KEY_Q)) {
					gi_pointer->go_end2_1 = 1;
					gi_pointer->go_end2_4 = 1;
				}
			}
		}
		else if (gi_pointer->go_end2_1 == 1) {
			text("...", 1010, 100);
			text("Q：NEXT", 1010, 900);
			if (isTrigger(KEY_Q)) {
				gi_pointer->go_end2_1 = 0;
				gi_pointer->go_end2_2 = 1;
			}
		}
		else if (gi_pointer->go_end2_2 == 1) {
			text("出来ないのだろう。", 1010, 100);
			text("Q：NEXT", 1010, 900);
			if (isTrigger(KEY_Q)) {
				gi_pointer->go_end2_2 = 0;
				gi_pointer->go_end2_3 = 1;
			}
		}
		else if (gi_pointer->go_end2_3 == 1) {
			text("Q：NEXT", 1010, 900);
			if (isTrigger(KEY_Q)) {
				gi_pointer->go_end2_3 = 0;
				gi_pointer->go_end2_4 = 0;
				g_pointer->game_state = g_pointer->END2;
				i_pointer->knife = 0;
			}
		}
	}//gi_pointer->gimmick_No1
}
void Debug(struct STAGE* s_pointer) {
	fill(0);
	rect((s_pointer->size * 9) + 50, (s_pointer->size * 9) + 50, s_pointer->size / 10, s_pointer->size / 10);
}
void STAGE(struct GAME* g_pointer, struct OTHER* o_pointer,struct GIMMICK* gi_pointer,struct STAGE* s_pointer, struct PLAYER* p_pointer,struct ITEM* i_pointer) {
	move_player(s_pointer, p_pointer,gi_pointer,i_pointer);
	judge_collision(s_pointer, p_pointer);
	clear(0);
	Go_END2(g_pointer,p_pointer, gi_pointer, i_pointer, o_pointer);
	Text(g_pointer,p_pointer,gi_pointer,i_pointer,o_pointer);
	use_item(s_pointer, p_pointer);
	draw_map(s_pointer,p_pointer);
	draw_map_player(s_pointer, p_pointer);
	gimmick(s_pointer, p_pointer,gi_pointer,i_pointer);
	draw_gimmick(s_pointer, p_pointer);

	//Debug(s_pointer);
}
void END1(struct GAME* g_pointer,struct STAGE* s_pointer,struct PLAYER* p_pointer,struct GIMMICK* gi_pointer,struct ITEM* i_pointer) {
	clear(0);
	draw_map(s_pointer, p_pointer);
	textSize(100);
	fill(255);
	text("BAD_END", 100, height / 2);
	text("ENDING1", 100, height / 2+100);
	text("落ちる", 100, height / 2 + 200);
	textSize(50);
	text("Q：BACK:TITLE", 1010, 900);
	if (isTrigger(KEY_Q)) {
		INIT(p_pointer,gi_pointer,i_pointer);
		g_pointer->game_state = g_pointer->TITLE;
	}
}
void END2(struct GAME* g_pointer, struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer) {
	clear(0);
	draw_map(s_pointer, p_pointer);
	textSize(100);
	fill(255);
	text("BAD_END", 100, height / 2);
	text("ENDING2", 100, height / 2 + 100);
	text("諦める", 100, height / 2 + 200);
	textSize(50);
	text("Q：BACK:TITLE", 1010, 900);
	if (isTrigger(KEY_Q)) {
		INIT(p_pointer,gi_pointer,i_pointer);
		g_pointer->game_state = g_pointer->TITLE;
	}
}
void END3(struct GAME* g_pointer, struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer) {
	clear(0);
	draw_map(s_pointer, p_pointer);
	textSize(100);
	fill(255);
	text("TRUE_END", 100, height / 2);
	text("ENDING3", 100, height / 2 + 100);
	text("脱出した", 100, height / 2 + 200);
	textSize(50);
	text("Q：BACK:TITLE", 1010, 900);
	if (isTrigger(KEY_Q)) {
		INIT(p_pointer,gi_pointer,i_pointer);
		g_pointer->game_state = g_pointer->TITLE;
	}
}
void gmain() {
	struct PLAYER p;
	struct STAGE s;
	struct OTHER o;
	struct GIMMICK gi;
	struct ITEM i;
	struct GAME g;
	window(1600, 1000);

	while (notQuit)
	{
		if (g.game_state == g.TITLE) { TITLE(&g, &o, &s); }
		else if (g.game_state == g.STAGE) { STAGE(&g, &o, &gi, &s, &p, &i); }
		else if (g.game_state == g.END1) { END1(&g, &s, &p, &gi, &i); }
		else if (g.game_state == g.END2) { END2(&g, &s, &p, &gi, &i); }
		else if (g.game_state == g.END3) { END3(&g, &s, &p, &gi, &i); }
	}
}