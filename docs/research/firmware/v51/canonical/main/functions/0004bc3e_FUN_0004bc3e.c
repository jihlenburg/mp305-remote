/* Address: 0004bc3e; name: FUN_0004bc3e; body bytes: 14 */

uint FUN_0004bc3e(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    uVar1 = (*(ushort *)(*(int *)(param_1 + 8) + 0x2a) & 0xfff) >> 10;
  }
  return uVar1;
}

