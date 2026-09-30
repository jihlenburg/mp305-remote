/* Address: ram:000607a4; name: FUN_ram_000607a4; body bytes: 28 */

void FUN_ram_000607a4(int param_1)

{
  uint uVar1;
  
  gp = 0x20004000;
  uVar1 = (uint)*(ushort *)(param_1 + 0x7e);
  if (2 < uVar1) {
    uVar1 = 2;
  }
  *(short *)(param_1 + 0x84) = *(short *)(param_1 + 0x82) << (uVar1 & 0x1f);
  FUN_ram_00042954();
  return;
}

