#include "draw.h"

/* 描画を行う */
void draw( const struct context* con, enum DRAW_MODE mode, void* any )
{
  erase();                      /* 画面をクリア */

  
  switch( mode ) {
  case MAIN :
    draw_main( con );
    draw_history( con );
    break;
  case MENU :
    draw_menu( con, *((int*)any) );
    break;
  }
  
  /* 一番上にインフォメーションバーを表示 */
  draw_bar( &con->player );

  move( 0, 0 );           /* カーソルを(邪魔なので)原点に配置しとく */
  refresh();              /* 描画を反映させる */
}

/* インフォメーションバーを描画(HPやATKなどの情報) */
void draw_bar( const struct charactor* player )
{
  char str[MAX_STRING_LEN];
  sprintf( str, "  LV %d | HP %d/%d | ATK %d | DEF %d | SATIETY %d ", player->role.p.lv, player->st.hp, player->st.maxhp, player->st.atk, player->st.def, player->role.p.satiety);
  move(0,0);
  mvaddstr( 0, 0, str );
}

/* main画面の描画 */
void draw_main( const struct context* con )
{
  
  draw_map( con->map );

  draw_player( &con->player );
  // draw_monsters( con->monsters );

  // Debug
  if( is_on_steps( con ) )
    mvaddstr(MAX_MAP_HEIGHT, 0 , "reach steps!");
  // Debug
  char buf[50];
  sprintf(buf, "player(x,y) = (%d, %d)", con->player.location.x, con->player.location.y);
  mvaddstr( MAX_MAP_HEIGHT+1, 0, buf );
  
}

/* 1文字の描画 */
void draw_ch( int x, int y, char ch )
{
  mvaddch( y, x, ch );
}

/* マップの描画 */
void draw_map( const struct mapcell map[][MAX_MAP_WIDTH] )
{
  for( int y = 0; y < MAX_MAP_HEIGHT; ++y ) {
    for( int x = 0;  x < MAX_MAP_WIDTH; ++x ) {
      draw_ch( x, y, get_map_symbol(map[y][x].symbol) );
    }
  }
}

/* プレイヤーの描画 */
void draw_player( const struct charactor* player )
{
  draw_ch( player->location.x, player->location.y, get_map_symbol(PLAYER) );
}

/* モンスターの描画 */
void draw_monsters( const struct charactor* monsters )
{
  for( int i = 0; i < MAX_MONSTER; ++i ) {
    if( !monsters[i].role.m.alive ) continue;
    draw_ch( monsters[i].location.x, monsters[i].location.x, get_map_symbol(MONSTER) );
  }
}

/* マップのみクリア */
void clear_map( struct mapcell map[][MAX_MAP_WIDTH] )
{
  for( int y = 0; y < MAX_MAP_HEIGHT; ++y ) {
    for( int x = 0; x < MAX_MAP_WIDTH; ++x ) {
      draw_ch( x, y, ' ' );
    }
  }
}

/* マップに表示されるシンボル(プレイヤーやアイテムなど)の文字を取得 */
char get_map_symbol( enum MAPSYMBOL symbol )
{
  switch( symbol ) {
  case WATCH  : return ' ';
  case FLOOR  : return ' ';
  case WALL   : return '#';
  case STEPS  : return 'H';
  case TRAP   : return 'X';
  case ITEM   : return '!';
  case PLAYER : return '@';
  case MONSTER: return '&';
  }
  return 'E';                    /* これがあるとバグあり */
  /* return '#'; // スタブ */
}



/* -----------  メニュー関係  ------------ */

/* メニューの描画 */
void draw_menu( const struct context* con, int pointer_idx )
{
  show_items( con, pointer_idx );
}

/* メニューのアイテム欄の出力 */
void show_items( const struct context* con, int pointer_idx )
{

  for( int idx = 0; idx < MAX_ITEM_PORTABILITY; ++idx ) {
    struct item *it = &con->bag.items[idx];

    char buf[ MAX_STRING_LEN ];  /* 表示文字列 */
    char info[ MAX_STRING_LEN ] = " "; /* アイテムの説明とか */
    char eqp_ch = ' ';         /* 装備状態を表わす文字 */
    char pointer = ' ';

    /* 装備していたら E と表示 */
    if( it->type == EQUIPMENT && it->cap.e.equip )
      eqp_ch = 'E';

    if( idx == pointer_idx )
      pointer = MENU_POINTER;

    set_item_text( info, it );
    
    sprintf( buf, "%c [%c] %s (%s)", pointer, eqp_ch, it->name, info );
    mvaddstr( START_MENU_Y + idx, START_MENU_X, buf );
  }
}

/* アイテムの説明文を生成 */
void set_item_text( char* buf, const struct item* it )
{
  char str[ MAX_STRING_LEN ];
  switch( it->type ) {
  case EQUIPMENT:
    sprintf( str, "atk=%d, def=%d", it->cap.e.atk, it->cap.e.def );
    break;
  case POTION :
    sprintf( str,"heal hp %d point", it->cap.p.efficacy );
    break;
  case FOOD :
    sprintf( str,"satisfy appetite %d point", it->cap.p.efficacy );
    break;
  case ARROW :
    break;
  case MAGICBOOK :
    break;
  case NONE :
    break;
  }

  strcpy( buf, str );
}

/* -----------  履歴の描画  ------------ */

/* 履歴の描画 */
void draw_history( const struct context* con )
{
  int p = con->hst.point;
  for( int i=0; i<MAX_LOG_LINES; ++i) {
    mvaddstr( START_LOG_Y + i, START_LOG_X, con->hst.msgs[p] );
    p = (p + 1)%MAX_LOG_LINES;
  }
}
