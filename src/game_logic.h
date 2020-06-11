#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// Game can be in one of 4 states:
// Busy: 	game is new or players are busy playing
// O Won:	O player won the game
// X Won: 	X player won the game
// Tie:		game was a tie
typedef enum {GM_BUSY, GM_O_WON, GM_X_WON, GM_TIE} game_state;

game_state get_game_state(const gchar *gm_board, gint *win_blocks);

#endif // GAME_LOGIC_H
