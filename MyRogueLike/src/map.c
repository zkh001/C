
#include "map.h"
#include "gamesystem.h"

/* 新しい階を生成する */
void generate_map( struct context *con )
{
  /* テスト用のマップ(マップ生成アルゴリズムは独自で．．．) */
  for( int y=0; y<MAX_MAP_HEIGHT; ++y ) {

    
    for( int x=2; x<MAX_MAP_WIDTH-1; ++x ) {
      con->map[y][x].symbol = FLOOR;
      if( y == 0 || y == MAX_MAP_HEIGHT )
        con->map[y][x].symbol = WATCH;
      else if( y == 1 || y == MAX_MAP_HEIGHT - 1 )
        con->map[y][x].symbol = WALL;
    }

    con->map[y][0].symbol = WATCH;
    con->map[y][MAX_MAP_WIDTH].symbol = WATCH;

    if( y != 0 ) {
      con->map[y][1].symbol = WALL;
      con->map[y][MAX_MAP_WIDTH-1].symbol = WALL;
    }


  }

  con->map[MAX_MAP_HEIGHT/2][MAX_MAP_WIDTH/2].symbol = STEPS;
  
  con->player.location.x = 2;
  con->player.location.y = 2;

  con->steps.x = MAX_MAP_WIDTH/2;
  con->steps.y = MAX_MAP_HEIGHT/2;
  /* ここまで */
}

/* モンスターをマップに1体発生させる */
void generate_monster( struct context *con )
{
  
}
