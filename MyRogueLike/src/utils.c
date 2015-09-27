
#include "utils.h"


/* 階段の上にいるかの判定 */
bool is_on_steps( const struct context* con )
{
  return eql_point( &con->player.location, &con->steps );
}

/* point構造体を比較する*/
bool eql_point( const struct point* p1, const struct point* p2 )
{
  return ((p1->x == p2->x) && (p1->y == p2->y));
}

/* ランダム機能を使うための初期化 */
void init_rnd_seed()
{
  srand( (unsigned int)time(NULL) );
}

/* ランダムを返す関数(冗長性を持たせるため) */
int rnd()
{
  return rand();
}

/* (min, max) の範囲の乱数を返す */
int rnd_range(int min, int max)
{
  return rnd() % (max-min+1) + min;
}


/* 文字列にある空白を削除する */
void delete_space( char* str )
{
  char* p = str;
  int cnt = 0;
  
  for( int i = 0; *(p+i) != '\0'; ++i ) {
    if( isspace( *(p+i) ) ) continue;
    
    *(str+cnt) = *(p+i);
    cnt++;
  }

  /* 残りの部分をnullで埋める */
  while( *(str+cnt) != '\0' ) {
    *(str+cnt) = '\0';
    cnt++;
  }
}
