#ifndef __MAP
#define __MAP

#include "gamesystem.h"

/* 新しい階を生成する */
void generate_map( struct context *con );

/* モンスターをマップに1体発生させる */
void generate_monster( struct context *con );

#endif
