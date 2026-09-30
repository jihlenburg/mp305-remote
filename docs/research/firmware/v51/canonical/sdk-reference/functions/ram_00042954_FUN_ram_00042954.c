/* Address: ram:00042954; name: FUN_ram_00042954; body bytes: 110 */

void FUN_ram_00042954(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  gp = 0x20004000;
  if (DAT_ram_20001be4 != (code *)0x0) {
    uVar1 = (*DAT_ram_20001be4)();
    uVar2 = (uint)DAT_ram_20001b6c;
    if (uVar2 != 0) {
      uVar3 = uVar2;
      if (uVar2 < uVar1) {
        uVar3 = uVar1;
      }
      if (uVar1 < uVar2) {
        uVar2 = uVar1;
      }
      if (0x14 < (int)((uVar3 & 0xffff) - (uVar2 & 0xffff))) {
        if (DAT_ram_20001be8 != (code *)0x0) {
          (*DAT_ram_20001be8)();
        }
        BLE_RegInit();
        DAT_ram_20001b6c = (ushort)uVar1;
      }
    }
    return;
  }
  return;
}

