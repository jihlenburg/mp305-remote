/* Address: 0001a258; name: FUN_0001a258; body bytes: 110 */

uint FUN_0001a258(uint param_1)

{
  uint uVar1;
  
  if (param_1 < 0xabf) {
    return 0;
  }
  if (param_1 < 0x1054) {
    uVar1 = 1;
    do {
      if (param_1 < *(ushort *)(&UNK_0007b120 + uVar1 * 2)) break;
      uVar1 = uVar1 + 1 & 0xff;
    } while (uVar1 < 0xb);
    uVar1 = ((((param_1 - *(ushort *)(&UNK_0007b11e + uVar1 * 2) & 0xffff) * 10) /
              ((uint)*(ushort *)(&UNK_0007b120 + uVar1 * 2) -
               (uint)*(ushort *)(&UNK_0007b11e + uVar1 * 2) & 0xffff) + uVar1 * 10) - 10 & 0xffff) *
            10 & 0xffff;
    if (uVar1 < 0x3e9) {
      return uVar1;
    }
  }
  return 1000;
}

