/* Address: 000153b4; name: FUN_000153b4; body bytes: 40 */

void FUN_000153b4(int param_1,uint param_2,ushort param_3)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if ((param_2 & 1) != 0) {
      *(ushort *)(&DAT_40053c02 + param_1 * 0x40 + uVar1 * 4) =
           *(ushort *)(&DAT_40053c02 + param_1 * 0x40 + uVar1 * 4) & 0xffc0 | param_3 & 0x3f;
    }
    param_2 = param_2 >> 1;
  } while ((param_2 != 0) && (uVar1 = uVar1 + 1 & 0xff, uVar1 < 0x10));
  return;
}

