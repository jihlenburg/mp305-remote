/* Address: 0001429c; name: FUN_0001429c; body bytes: 24 */

void FUN_0001429c(int param_1,uint param_2,uint param_3)

{
  *(ushort *)(param_1 + 4) =
       *(ushort *)(param_1 + 4) & ~(ushort)(0x800 << (param_2 & 0xff)) |
       (ushort)((param_3 & 0x800) << (param_2 & 0xff));
  return;
}

