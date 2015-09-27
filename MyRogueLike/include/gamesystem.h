#ifndef __GAMEDATA
#define __GAMEDATA

#include <stdbool.h>            /* for bool type */

#include "utils.h"


/* -----------------------------------
   |                                 |
   |             データ定義            |
   |                                 |
   ---------------------------------- */


/************************
 ***     マクロ定義     ***
 ************************/

/* ダンジョンの大きさ (0と最後の行と列は壁にするため+2の値)*/
#define MAX_MAP_WIDTH  52
#define MAX_MAP_HEIGHT 22

/* モンスターの最大出現数 */
#define MAX_MONSTER 25
/* モンスターの総数 */
#define MAX_MONSTER_TYPE 18


/* アイテムを持てる最大個数 */
#define MAX_ITEM_PORTABILITY 24

/* 表示する文字列の最大長 */
#define MAX_STRING_LEN 64


/* メニューのポインタ文字 */
#define MENU_POINTER '>'

/* メニューの表示開始位置 */
#define START_MENU_X (MAX_MAP_WIDTH / 10)
#define START_MENU_Y (MAX_MAP_HEIGHT / 10)

/* メッセージログ最大表示行数 */
#define MAX_LOG_LINES 25


/* 横側にメッセージを表示 */
#define HORIZONTAL_LOG

#ifdef HORIZONTAL_LOG

#define START_LOG_X (MAX_MAP_WIDTH + 2)
#define START_LOG_Y 1

#else

#define START_LOG_X 1
#define START_LOG_Y (MAX_MAP_HEIGHT + 1)

#endif

/* コマンド定義 */
#define KEY_YES    'y'
#define KEY_NO     'n'
#define KEY_MENU   'm'
#define KEY_QUIT   'q'

/************************
 ***      定数宣言     ***
 ************************/

//const char* MONSTER_DATA_FILENAME = "monsterdata";
//const char* ITEM_DATA_FILENAME    = "itemdata";


/************************
 ***     enum宣言      ***
 ************************/

enum ITEMTYPE {
  NONE,                         /* 持ってない */
  EQUIPMENT,                    /* 装備品 */
  POTION,                       /* 回復薬 */
  FOOD,                         /* 食料 */
  ARROW,                        /* 矢 */
  MAGICBOOK,                    /* 魔導書 */
};

enum MAPSYMBOL {
  WATCH,                        /* 番兵セル */
  FLOOR,                        /* 床 */
  WALL,                         /* 壁 */
  STEPS,                        /* 階段 */
  TRAP,                         /* 罠 */
  ITEM,                         /* アイテム */
  PLAYER,                       /* プレイヤー */
  MONSTER,                      /* モンスター */
};

enum MONSTER_PATTERN {
  NORMAL,                       /* 通常攻撃のみ */
  FIRE,                         /* 遠くから炎を吐く */
  POISONSHOT,                   /* 毒矢を打つ */
  CONFUSE,                      /* モンスターがデタラメに動く */
};

enum DRAW_MODE {
  MAIN,                         /* メイン */
  MENU,                         /* メニュー */
};


/************************
 ***     構造体宣言     ***
 ************************/

/* 座標 */
struct point {
  int x;
  int y;
};


/* アイテムの情報 */
struct item {
  char           name[MAX_STRING_LEN]; /* 名前 */
  enum  ITEMTYPE type;                 /* アイテムの種類 */
  union {
    /* this is a equipment */
    struct {
      int  atk;                 /* 攻撃値 */
      int  def;                 /* 防御値 */
      bool isweapon;            /* 武器かどうかのフラグ */
      bool equip;               /* 装備しているかのフラグ */
    } e;

    /* this is a potion */
    struct {
      int efficacy;            /* 効能 */
      int usable;              /* 使用回数 */
    } p;
  } cap;
};

/* プレイヤーの持ち物を入れるカバン */
struct itembag {
  struct item items[MAX_ITEM_PORTABILITY]; /* アイテム */
  int         eqp_weapon;       /* 装備している剣の持ち物番号 */
  int         eqp_shield;       /* 装備している盾の持ち物番号 */
};

/* 戦闘情報 */
struct status {
  int  maxhp;                   /* 最大ライフ */
  int  hp;                      /* 現在ライフ */
  int  atk;                     /* 攻撃力 */
  int  def;                     /* 防御力 */
  int  exp;                     /* 経験値 */
  int  move;                    /* 行動回数(1~3の値) */
  int  probability;             /* 命中率 */
};

/* プレイヤーとかモンスターを表わす */
struct charactor {
  bool          isplayer;        /* プレイヤーかどうかのフラグ */
  struct status st;              /* ステータス */
  struct point  location;        /* 現在地 */
  struct point  delta;           /* 移動する量 */

  union {
    /* im a player */
    struct {                    
      int lv;                  /* レベル(99Lvまで上がる) */
      int satiety;             /* 満腹度 */
    } p;

    /* im a monster */
    struct {
      char name[MAX_STRING_LEN];          /* 名前 */
      bool alive;               /* 生きているかのフラグ */
      int  no;                  /* シリアル番号 */
      void (*act)( struct context *con ); /* 特殊行動 */
    } m;
  } role;                       /* 役割に合うデータ構造 */
};

/* 要削除  */
/*
  MONSTER構造体に 
     void (*act)( context *con )
  という部分は
     戻り値 : void
     引数   : context
  の関数を代入できるということ.例として
    void hoge(context *con){...}   // 代入したい関数1
    void fuga(context *con){...}   // 代入したい関数2
    monster f;
    f.act = hoge;
    f.act(&con)     // call function (hoge)
    f.act = fuga;
    f.act(&con)     // call function (fuga)
  のようにできる
*/


/* マップの1マスの情報 */
struct mapcell {
  enum MAPSYMBOL symbol;    /* そのマスの状態(床，壁，罠など) */
  bool           checked;   /* 発見されているかのフラグ */
  bool           isroomfloor;   /* 部屋の床かのフラグ */
};


struct history {
  char msgs[MAX_LOG_LINES][MAX_STRING_LEN]; /* 履歴内容 */
  int point;                                /* 一番上に表示する場所 */
};


/* ゲームのコンテキスト，いろいろなことに使う */
struct context {
  struct charactor player;                /* プレイヤー */
  struct itembag   bag;                   /* 持ち物バッグ */
  struct charactor monsters[MAX_MONSTER]; /* モンスター */
  struct mapcell   map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH]; /* マップの盤面 */
  struct point     steps;                              /* 階段 */
  int              now;         /* 現在の階層 */

  struct history   hst;         /* 履歴 */
};


/************************
 ***   ロード用データ    ***
 ************************/
// 外部のファイルにて定義(初期化)する
//extern struct charactor* _MONSTER_CATALOG;
//extern struct item*      _ITEM_CATALOG;



/* -----------------------------------
   |                                 |
   |        関数プロトタイプ宣言        |
   |                                 |
   ---------------------------------- */

/* キャラを移動させる */
void move_charactor( struct charactor *c );

/* ダメージ計算 */
int calc_damage( const struct charactor* attacker, const struct charactor* defender );

#endif
