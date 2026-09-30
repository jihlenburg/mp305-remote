/* Address: 0004bef4; name: FUN_0004bef4; body bytes: 16 */

uint FUN_0004bef4(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    uVar1 = (*(byte *)(*(int *)(param_1 + 8) + 0x2a) & 0xf) >> 2;
  }
  return uVar1;
}

