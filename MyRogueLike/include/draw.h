#ifndef __DRAW
#define __DRAW

#include "gamesystem.h"
#include "menu.h"

/*
 *  ここでは描画関係の定義をします
 */

/* 描画を一手に引き受ける */
void draw( const struct context* con, enum DRAW_MODE mode, void* any );

/* インフォメーションバーを描画(HPやATKなどの情報) */
void draw_bar( const struct charactor* player );

/* 画面の描画 */
void draw_main( const struct context* con );     

/* 1文字の描画 */
void draw_ch( int x, int y, char ch ); 

/* マップの描画 */
void draw_map( const struct mapcell map[][MAX_MAP_WIDTH] );

/* プレイヤーの描画 */
void draw_player( const struct charactor* player );

/* モンスターの描画 */
void draw_monsters( const struct charactor* monsters );

/* マップのみクリア */
void clear_map( struct mapcell map[][MAX_MAP_WIDTH] );

/* マップに表示されるシンボル(プレイヤーやアイテムなど)の文字を取得 */
char get_map_symbol( enum MAPSYMBOL symbol );

/* -----------  メニューの描画  ------------ */

/* メニューの描画 */
void draw_menu( const struct context* con, int pointer_idx );

/* メニューのアイテム欄の出力 */
void show_items( const struct context* con, int pointer_idx );

/* アイテムの説明文を生成 */
void set_item_text( char* buf, const struct item* it );

/* -----------  履歴の描画  ------------ */

/* 履歴の描画 */
void draw_history( const struct context* con );

#endif
