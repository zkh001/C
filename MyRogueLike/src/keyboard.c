#include <ncurses.h>

#include "keyboard.h"


/* キー入力に関する初期化 */
void init_keyboard( WINDOW* win )
{
  noecho();                   /* 入力のとき画面表示しない */
  cbreak();                   /* リアルタイムのキー入力を可能にする */
  keypad( win, true );     /* キー入力を有効化 */
}

/* キー入力を読み取る */
int readkey()
{
  return getch();
}
