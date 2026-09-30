/* Address: 0004bf04; name: FUN_0004bf04; body bytes: 16 */

uint FUN_0004bf04(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    uVar1 = (*(byte *)(*(int *)(param_1 + 8) + 0x2a) & 0x3f) >> 4;
  }
  return uVar1;
}

