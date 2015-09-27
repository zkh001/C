#include "ani.h"

/* ゲームオーバの時のアニメーション */
void gameover_animation()
{
  /* AA */
  char AA[ AA_NUM ][ AA_HGT ][ AA_WDT ] = {
    { G0, G1, G2, G3, G4, G5, G6, G7, G8, }, /* G */
    { A0, A1, A2, A3, A4, A5, A6, A7, A8, }, /* A */
    { M0, M1, M2, M3, M4, M5, M6, M7, M8, }, /* M */
    { E0, E1, E2, E3, E4, E5, E6, E7, E8, }, /* E */
    { EMPTY_S, EMPTY_S, EMPTY_S, EMPTY_S,    /* 空白 */
      EMPTY_S, EMPTY_S, EMPTY_S, EMPTY_S, EMPTY_S},
    { O0, O1, O2, O3, O4, O5, O6, O7, O8, }, /* O */
    { V0, V1, V2, V3, V4, V5, V6, V7, V8, }, /* V */
    { E0, E1, E2, E3, E4, E5, E6, E7, E8, }, /* E */
    { R0, R1, R2, R3, R4, R5, R6, R7, R8, }, /* R */
    { EMPTY_S, EMPTY_S, EMPTY_S, EMPTY_S,    /* 空白 */
      EMPTY_S, EMPTY_S, EMPTY_S, EMPTY_S, EMPTY_S},
  };

  /* AAを連結した配列 */
  char aa_str[ AA_HGT ][ AA_LEN ];

  // AAの連結
  for( int c=0, num=0; c<AA_NUM; ++c ) {
    for( int w=0; w<AA_WDT; ++w ) {
      for( int h=0; h<AA_HGT; ++h ) {
        aa_str[h][ num ] = AA[ c ][ h ][ w ];
      }
      num++;
    }
  }

  /* アニメーション開始 */
  for( int i = 0;; i = (i+1) % AA_LEN ) {    // i : AAの中の位置
    /* 描画 */
    erase();
    for( int x = 0; x < MAX_STRING_LEN; ++x ) {
      for( int h=0; h < AA_HGT; ++h ) {
        mvaddch( ANI_SHOW_Y + h, x, aa_str[h][ (i+x)%AA_LEN ] );
      }
    }
    refresh();
    usleep( 100000 );  /* アニメーションのフレーム制御のためのsleep */
  }
  
}
