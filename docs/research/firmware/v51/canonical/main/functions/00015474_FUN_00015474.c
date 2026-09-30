/* Address: 00015474; name: FUN_00015474; body bytes: 14 */

undefined2 FUN_00015474(uint param_1)

{
  if (5 < param_1) {
    param_1 = 1;
  }
  return *(undefined2 *)(&DAT_0007b16e + param_1 * 2);
}

