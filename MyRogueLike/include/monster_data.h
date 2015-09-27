#ifndef __MONSTER_DATA
#define __MONSTER_DATA

#include "gamesystem.h"
#include "utils.h"

/* モンスターのデータをロード */
void load_monster_data();
/* シリアル番号からモンスターの行動を取得 */
int get_monster_pattern( int monster_no );

#endif
