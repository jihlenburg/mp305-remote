/* Address: 000152a8; name: FUN_000152a8; body bytes: 50 */

void FUN_000152a8(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  ushort uVar2;
  
  uVar1 = 0;
  do {
    if ((param_2 & 1) != 0) {
      uVar2 = *(ushort *)(&DAT_40053c00 + param_1 * 0x40 + uVar1 * 4);
      if (param_3 == 1) {
        uVar2 = uVar2 | 0x8000;
      }
      else {
        uVar2 = (ushort)(((uint)uVar2 << 0x11) >> 0x11);
      }
      *(ushort *)(&DAT_40053c00 + param_1 * 0x40 + uVar1 * 4) = uVar2;
    }
    param_2 = param_2 >> 1;
  } while ((param_2 != 0) && (uVar1 = uVar1 + 1 & 0xff, uVar1 < 0x10));
  return;
}

