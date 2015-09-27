#ifndef __MENU
#define __MENU

#include <ncurses.h>
#include <string.h>

#include "draw.h"
#include "gamesystem.h"
#include "utils.h"

/* メニュー機能を実行する */
void start_menu( struct context* con );

/* ポインターを進める */
void direct_pointer( int* np, int input );

#endif
