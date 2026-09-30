/* Address: 00014954; name: FUN_00014954; body bytes: 34 */

void FUN_00014954(uint param_1,uint param_2)

{
  *(uint *)(&DAT_40010590 + (param_1 >> 5) * 4) =
       *(uint *)(&DAT_40010590 + (param_1 >> 5) * 4) & ~(1 << (param_1 & 0x1f)) |
       (param_2 & 1) << (param_1 & 0x1f);
  return;
}

