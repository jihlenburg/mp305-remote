/* Address: 000152e0; name: FUN_000152e0; body bytes: 106 */

undefined4 FUN_000152e0(int param_1,uint param_2,ushort *param_3)

{
  uint uVar1;
  
  if (param_3 != (ushort *)0x0) {
    uVar1 = 0;
    do {
      if ((param_2 & 1) != 0) {
        *(ushort *)(&DAT_40053c00 + param_1 * 0x40 + uVar1 * 4) =
             *(ushort *)(&DAT_40053c00 + param_1 * 0x40 + uVar1 * 4) & 0x2988 |
             (param_3[8] |
             param_3[9] |
             *param_3 | param_3[1] | param_3[2] | param_3[3] | param_3[5] | param_3[6] | param_3[7]
             | param_3[4]) & 0xd677;
      }
      param_2 = param_2 >> 1;
    } while ((param_2 != 0) && (uVar1 = uVar1 + 1 & 0xff, uVar1 < 0x10));
    return 0;
  }
  return 0xfffffffd;
}

