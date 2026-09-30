/* Address: ram:00045080; name: FUN_ram_00045080; body bytes: 106 */

undefined4 FUN_ram_00045080(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if ((byte)(DAT_ram_20001d50 - 1U) < 2) {
    uVar2 = 0x12;
  }
  else {
    uVar2 = 2;
    if (param_3 != 0) {
      iVar1 = FUN_ram_0004df14();
      uVar2 = 0x14;
      if (iVar1 != 0) {
        if (param_2 != 0) {
          *(byte *)(iVar1 + 4) = *(byte *)(iVar1 + 4) | 2;
        }
        tmos_memcpy(iVar1 + 0x18,param_3,0x10);
        *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(param_3 + 0x10);
        uVar2 = 0;
      }
      return uVar2;
    }
  }
  return uVar2;
}

