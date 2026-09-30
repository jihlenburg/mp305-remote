/* Address: ram:0004df46; name: FUN_ram_0004df46; body bytes: 92 */

undefined4 FUN_ram_0004df46(int param_1,uint param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004df14();
  if (iVar2 == 0) {
    uVar3 = 0;
    if (param_1 != 0xfffe) {
      uVar3 = 0x14;
    }
  }
  else {
    bVar1 = *(byte *)(iVar2 + 4);
    if (*(int *)(iVar2 + 0x2c) == 0) {
      uVar3 = 0;
      if ((bVar1 & 0x10) == 0) {
        uVar3 = 5;
      }
    }
    else if (((((bVar1 & 0x12) != 0x10) || (uVar3 = 5, param_3 == 0)) &&
             (uVar3 = 0xf, (bVar1 & 0x10) != 0)) &&
            (uVar3 = 0, *(byte *)(*(int *)(iVar2 + 0x2c) + 0x1a) < param_2)) {
      uVar3 = 0xc;
    }
  }
  return uVar3;
}

