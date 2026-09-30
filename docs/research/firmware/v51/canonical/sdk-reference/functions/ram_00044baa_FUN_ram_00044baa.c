/* Address: ram:00044baa; name: FUN_ram_00044baa; body bytes: 170 */

undefined4 FUN_ram_00044baa(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  if ((byte)(DAT_ram_20001d50 - 1U) < 2) {
    uVar4 = 0x12;
  }
  else {
    uVar4 = 2;
    if (param_3 != 0) {
      iVar1 = FUN_ram_0004df14();
      uVar4 = 0x14;
      if (iVar1 != 0) {
        if (*(int *)(iVar1 + 0x2c) != 0) {
          FUN_ram_20000104();
        }
        iVar2 = FUN_ram_2000023a(param_3,0x1c);
        *(int *)(iVar1 + 0x2c) = iVar2;
        uVar4 = 0x13;
        if (iVar2 != 0) {
          uVar4 = 0;
          if ((*(char *)(iVar1 + 0xc) == '\b') && (param_4 != 0)) {
            uVar4 = FUN_ram_0004e898(param_1,iVar2,*(undefined2 *)(iVar2 + 0x10),iVar2 + 0x12,
                                     *(undefined1 *)(iVar2 + 0x1a));
          }
          if (param_2 == 0) {
            bVar3 = *(byte *)(iVar1 + 4) | 4;
          }
          else {
            bVar3 = *(byte *)(iVar1 + 4) | 6;
          }
          *(byte *)(iVar1 + 4) = bVar3;
        }
      }
      return uVar4;
    }
  }
  return uVar4;
}

