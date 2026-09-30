/* Address: 00047304; name: FUN_00047304; body bytes: 42 */

void FUN_00047304(int param_1)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 0x1c);
  *(byte *)(param_1 + 0x1c) = bVar1 | 8;
  if ((int)((uint)bVar1 << 0x1d) < 0) {
    FUN_00047298(param_1);
  }
  else {
    FUN_000471d8();
  }
  *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) & 0xf7 | bVar1 & 8;
  return;
}

