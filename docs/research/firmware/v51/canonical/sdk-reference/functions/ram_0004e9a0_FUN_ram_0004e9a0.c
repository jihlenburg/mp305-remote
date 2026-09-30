/* Address: ram:0004e9a0; name: FUN_ram_0004e9a0; body bytes: 32 */

byte FUN_ram_0004e9a0(int param_1)

{
  byte bVar1;
  
  gp = 0x20004000;
  bVar1 = 0x10;
  if (param_1 != 0) {
    bVar1 = 0x10;
    if (((*(int *)(param_1 + 0x28) != 0) && (*(int *)(param_1 + 0x6c) != 0)) &&
       (bVar1 = *(byte *)(*(int *)(param_1 + 0x28) + 3), 0xf < bVar1)) {
      bVar1 = *(byte *)(*(int *)(param_1 + 0x6c) + 0x18);
    }
  }
  return bVar1;
}

