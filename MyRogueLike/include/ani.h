#ifndef __ANI
#define __ANI

#include "gamesystem.h"

/* GAMEOVERのアニメーションが発動
   完全にネタ機能
 */

/* AAの文字数 */
#define AA_NUM 10
/* AAの一文字当たりの幅 */
#define AA_WDT 17
/* AAの高さの長さ */
#define AA_HGT 9
/* [AAの文字数]*[AAの一文字当たりの幅] */
#define AA_LEN (AA_WDT*AA_NUM)

#define ANI_SHOW_Y (MAX_MAP_HEIGHT/4)


#define EMPTY_S "                 "

#define G0 "     o o o o o   "
#define G1 "   o          o  "
#define G2 "  o            o "
#define G3 "  o              "
#define G4 "  o      o o o o "
#define G5 "  o            o "
#define G6 "  o            o "
#define G7 "   o           o "
#define G8 "     o o o o o   "

#define A0 "        o        "
#define A1 "      o   o      "
#define A2 "     o     o     "
#define A3 "    o       o    "
#define A4 "   o         o   "
#define A5 "  o o o o o o o  "
#define A6 "  o           o  "
#define A7 "  o           o  "
#define A8 "  o           o  "

#define M0 "    o       o    "
#define M1 "   o o     o o   "
#define M2 "  o   o   o   o  "
#define M3 " o     o o     o "
#define M4 " o      o      o "
#define M5 " o             o "
#define M6 " o             o "
#define M7 " o             o "
#define M8 " o             o "

#define E0 "  o o o o o o o  "
#define E1 "  o              "
#define E2 "  o              "
#define E3 "  o              "
#define E4 "  o o o o o o o  "
#define E5 "  o              "
#define E6 "  o              "
#define E7 "  o              "
#define E8 "  o o o o o o o  "

#define O0 "     o o o o     "
#define O1 "   o         o   "
#define O2 "  o           o  "
#define O3 "  o           o  "
#define O4 "  o           o  "
#define O5 "  o           o  "
#define O6 "  o           o  "
#define O7 "   o         o   "
#define O8 "     o o o o     "

#define V0 "o               o"
#define V1 " o             o "
#define V2 "  o           o  "
#define V3 "   o         o   "
#define V4 "    o       o    "
#define V5 "     o     o     "
#define V6 "      o   o      "
#define V7 "       o o       "
#define V8 "        o        "

#define R0 " o o o o o o     "
#define R1 " o          o    "
#define R2 " o          o    "
#define R3 " o o o o o o     "
#define R4 " o        o      "
#define R5 " o         o     "
#define R6 " o          o    "
#define R7 " o           o   "
#define R8 " o            o  "


/* ゲームオーバの時のアニメーション */
void gameover_animation();

#endif
