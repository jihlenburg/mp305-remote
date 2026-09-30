/* Address: ram:000442de; name: FUN_ram_000442de; body bytes: 72 */

undefined4 FUN_ram_000442de(int param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  uVar2 = 0;
  if ((param_2 != 0) && (param_1 != 0)) {
    if (param_1 == 1) {
      bVar1 = *(byte *)(param_2 + 5) | 0xc0;
    }
    else {
      if (param_1 != 2) {
        if (param_1 != 3) {
          gp = 0x20004000;
          return 1;
        }
        *(byte *)(param_2 + 5) = *(byte *)(param_2 + 5) & 0x3f | 0x40;
        gp = 0x20004000;
        return 1;
      }
      bVar1 = *(byte *)(param_2 + 5) & 0x3f;
    }
    *(byte *)(param_2 + 5) = bVar1;
    uVar2 = 1;
  }
  return uVar2;
}

