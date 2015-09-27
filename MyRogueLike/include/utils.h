#ifndef __UTILS
#define __UTILS

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "gamesystem.h"

/* 階段の上にいるかの判定 */
bool is_on_steps( const struct context *con ); 

/* point構造体を比較する*/
bool eql_point( const struct point *p1, const struct point *p2 );

/* ランダム機能を使うための初期化 */
void init_rnd_seed();
/* ランダムを返す関数(冗長性を持たせるため) */
int rnd();
/* (min, max) の範囲の乱数を返す */
int rnd_range(int min, int max);

/* 文字列にある空白を削除する */
void delete_space( char* str );


#endif
