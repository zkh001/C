#include <stdio.h>
#include <stdlib.h>

#include "monster_data.h"

//struct charactor* _MONSTER_CATALOG; /* EXTERN : From gamesystem.h */

/* データファイルの書式

   NO  NAME  HP  ATK  DEF  MOVE  EXP

   # NO の規則  百の位:進化順 下2桁:モンスター系統のシリアル番号
*/

/* モンスターのデータをロード(未完成) */
void load_monster_data()
{
  FILE *file;
  char buf[128];
  
  file = fopen( "monsterdata", "r" );
  if( file == NULL )
    return;                     //ERROR

  int n,h,a,d,m,e;
  char nm[64];
  
  while( fgets( buf, sizeof(buf), file ) != NULL ) {
    delete_space( buf );        /* 空白を削除する */
    sscanf(buf, "%d,%[^,],%d,%d,%d,%d,%d", &n,nm,&h,&a,&d,&m,&e );
    //    printf("%d %s %d %d %d %d %d\n",n,nm,h,a,d,m,e);
  }

  fclose( file );
}

/* シリアル番号からモンスターの行動を取得 */
int get_monster_pattern( int monster_no )
{
  return 0;
}

