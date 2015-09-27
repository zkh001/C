#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "menu.h"
#include "gamesystem.h"
#include "draw.h"

/* メニュー機能を実行する */
void start_menu( struct context* con )
{
  int now_pointer = 0;          /* 現在のカーソルポインタ */

  int input;

  /* メインループ */
  while(1) {
    draw( con, MENU, &now_pointer );
    while( (input = readkey()) < 0 );

    if( input == KEY_QUIT ) break; /* メニューを閉じる */

    direct_pointer( &now_pointer, input );
  }
}

/* ポインターを進める */
void direct_pointer( int* np, int input )
{
  int mv = 0;
  
  switch( input ) {
    case KEY_UP :
      mv = -1;
      break;
    case KEY_DOWN :
      mv = 1;
      break;
  }
  *np = (MAX_ITEM_PORTABILITY + *np + mv) % MAX_ITEM_PORTABILITY;
}
