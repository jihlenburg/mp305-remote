/* Address: 000472d4; name: FUN_000472d4; body bytes: 12 */

uint FUN_000472d4(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = (*(byte *)(param_1 + 0x1c) & 3) >> 1;
  }
  return uVar1;
}

