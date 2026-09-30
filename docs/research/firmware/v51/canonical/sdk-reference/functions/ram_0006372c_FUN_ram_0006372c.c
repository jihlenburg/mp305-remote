/* Address: ram:0006372c; name: FUN_ram_0006372c; body bytes: 248 */

uint FUN_ram_0006372c(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  gp = 0x20004000;
  if ((param_2 & 1) == 0) {
    if ((param_2 & 2) == 0) {
      if ((param_2 & 4) == 0) {
        if ((param_2 & 8) == 0) {
          uVar1 = 0;
          if ((param_2 & 0x10) != 0) {
            FUN_ram_00042954(0);
            if (DAT_ram_20001e9b == '\b') {
              tmos_start_task(DAT_ram_20001ee4,0x10,0x640);
            }
            uVar1 = param_2 ^ 0x10;
          }
        }
        else {
          if ((DAT_ram_20001ee0 & 4) != 0) {
            RF_FrequencyHoppingShut();
          }
          uVar1 = param_2 ^ 8;
        }
      }
      else {
        FUN_ram_000635fe();
        uVar1 = param_2 ^ 4;
      }
    }
    else {
      if ((DAT_ram_20001ee0 & 4) != 0) {
        iVar2 = 0xa0;
        if ((char)DAT_ram_20001ee0 < '\0') {
          iVar2 = (uint)DAT_ram_20001ecd * 0xa0 + 0x28;
        }
        tmos_start_task(DAT_ram_20001ee4,8,iVar2);
      }
      uVar1 = param_2 ^ 2;
    }
  }
  else {
    if ((DAT_ram_20001ee0 & 2) != 0) {
      iVar2 = 0x50;
      if ((char)DAT_ram_20001ee0 < '\0') {
        iVar2 = (uint)DAT_ram_20001ecd * 0xa0;
      }
      tmos_start_task(DAT_ram_20001ee4,4,iVar2);
    }
    uVar1 = param_2 ^ 1;
  }
  return uVar1;
}

