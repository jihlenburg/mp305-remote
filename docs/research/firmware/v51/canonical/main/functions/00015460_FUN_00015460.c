/* Address: 00015460; name: FUN_00015460; body bytes: 14 */

undefined2 FUN_00015460(uint param_1)

{
  if (5 < param_1) {
    param_1 = 1;
  }
  return *(undefined2 *)(&DAT_0007b162 + param_1 * 2);
}

