/*
 * NOTE :
 *   1. I used C99 in C Language in this sources. You should compile(gcc) with [-std=c99].
 *   2. This program can exec on ONLY Linux so that it is used ncurses.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <sys/time.h>
#include <unistd.h>

#include "gamesystem.h"
#include "keyboard.h"
#include "draw.h"
#include "utils.h"
#include "map.h"
#include "menu.h"
#include "monster_data.h"

#include "ani.h"

/* ゲームの初期設定 */
void initialize( struct context* con );
/* ゲームの終了処理 */
void finalize( struct context* con );
/* 入力キーの読取 */
int readkey();
/* 入力によるコマンドの処理 */
bool command( struct context* con, int key );
/* プレイヤーの行動の処理 */
void turn_player( struct context* con, int input );
/* モンスターの行動の処理 */
void turn_monster( struct context* con );

/* 履歴に追加する */
void add_history( struct context* con, char* str );

int main(void)
{
  int input;                    /* ユーザー入力のキー */

  /* ゲームに必要なデータの宣言 */
  struct context con;           /* ゲームのコンテキスト */

  bool player_turn = true;

  initialize( &con );                 /* ゲームの初期化 */

  generate_map( &con );         /* マップ生成 */

  /* メインループ */
  while(1) {
    draw( &con, MAIN, NULL );               /* 描画 */

    while( (input = readkey()) < 0 );          /* 入力の読取 */

    if( player_turn ) {
      turn_player( &con, input ); /* プレイヤーの処理 */
    }
    else {
      turn_monster( &con );       /* モンスターの処理 */
    }

    usleep( 500 );              /* ナノ秒待つ */
  }

  finalize( &con );

  return 0;
}

/* ゲームの初期設定 */
void initialize( struct context* con )
{
  // 一番始めにinitscr()を実行しなければならないことに注意
  initscr();                    /* cursesの初期化 */

  init_keyboard( stdscr );

  wtimeout( stdscr, 100 );      /* キー入力の待ち時間(100ms) */

  curs_set( 0 );                /* カーソルを表示しない */

  init_rnd_seed();

  /* プレイヤー設定 */
  con->player.isplayer       = true;
  con->player.role.p.lv      = 1;
  con->player.role.p.satiety = 100;
  con->player.st.maxhp       = 15;
  con->player.st.hp          = 15;
  con->player.st.atk         = 5;
  con->player.st.def         = 0;
  con->player.st.exp         = 0;
  con->player.st.move        = 1;
  con->player.st.probability = 90; /* 90% */

  /* 1階から */
  con->now = 1;

  /* 履歴の初期化 */
  con->hst.point = 0;
  for( int i=0; i < MAX_LOG_LINES; ++i ) {
    strcpy( con->hst.msgs[i], "" );
  }


  for( int i = 0; i < MAX_MONSTER; ++i ) {
    con->monsters[i].role.m.alive = false;
  }

  // DEBUG
  for( int i=0; i < MAX_ITEM_PORTABILITY; ++i ){
    con->bag.items[i].type = POTION;

    //strcpy( con->bag.items[i].name, "item" );
    char buf[ MAX_STRING_LEN ];
    sprintf( buf ,"item%d", i);
    strcpy( con->bag.items[i].name, buf );
  }

  con->bag.items[2].type = EQUIPMENT;
  con->bag.items[2].cap.e.atk = 10;
  con->bag.items[2].cap.e.def = 0;
  con->bag.items[2].cap.e.equip = true;

}

/* ゲームの終了処理 */
void finalize( struct context* con )
{
  curs_set(1);
  endwin();                     /* cursesの終了 */
}

/* 入力によるコマンドの処理
 * もしコマンドでターンが進む場合は true を返す
 */
bool command( struct context* con, int key )
{
  bool gain_turn = false;

  switch( key ) {
  case KEY_DOWN:  // ↓キー
    con->player.delta.x = 0;
    con->player.delta.y = 1;
    gain_turn = true;

    add_history( con, "move [DOWN]");

    break;
  case KEY_UP:    // ↑キー
    con->player.delta.x = 0;
    con->player.delta.y = -1;
    gain_turn = true;

    add_history( con, "move [UP]");

    break;
  case KEY_RIGHT: // →キー
    con->player.delta.x = 1;
    con->player.delta.y = 0;
    gain_turn = true;

    add_history( con, "move [RIGHT]");

    break;
  case KEY_LEFT:  // ←キー
    con->player.delta.x = -1;
    con->player.delta.y = 0;
    gain_turn = true;

    add_history( con, "move [LEFT]");

    break;
  case KEY_MENU:
    start_menu( con );
    break;

  case 'g' :                    /* 完全なネタ(もちろんこの機能はいらない) */
    gameover_animation();
    break;
  default:
    /* 何もしない */
    break;
  }

  return gain_turn;
}

/* プレイヤーの行動の処理 */
void turn_player( struct context* con, int input )
{
  command( con, input );

  /* キャラを動かす(動かない場合でも実行する) */
  move_charactor( &con->player );

}

/* モンスターの行動の処理 */
void turn_monster( struct context* con )
{

}

/* 履歴に追加する */
void add_history( struct context* con, char* str )
{
  strcpy( con->hst.msgs[ con->hst.point ], str);
  con->hst.point = (con->hst.point+1) % MAX_LOG_LINES;
}
