
#include "gamesystem.h"

/* キャラを移動させる
 * 動かない場合のみfalseを返す
 */
void move_charactor( struct charactor *c )
{
  c->location.x += c->delta.x;
  c->location.y += c->delta.y;

  c->delta.x = 0;
  c->delta.y = 0;
}

/* ダメージ計算 */
int calc_damage( const struct charactor* attacker, const struct charactor* defender )
{
  // 値の -10% ~ 10% が誤差
  int region = rnd_range( -10, 10 ) / 100;
  int base = attacker->st.atk - attacker->st.def;
  return (int)(base * region);
}
