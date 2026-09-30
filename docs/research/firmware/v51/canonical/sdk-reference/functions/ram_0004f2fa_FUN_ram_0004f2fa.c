/* Address: ram:0004f2fa; name: FUN_ram_0004f2fa; body bytes: 336 */

int FUN_ram_0004f2fa(undefined4 param_1,int param_2,int param_3,int param_4,byte *param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined1 auStack_40 [8];
  undefined1 auStack_38 [12];
  
  gp = 0x20004000;
  if (param_3 == 0) {
    gp = 0x20004000;
    return 2;
  }
  if (param_5 == (byte *)0x0) {
    gp = 0x20004000;
    return 2;
  }
  iVar3 = FUN_ram_0004df14();
  if (iVar3 == 0) {
    gp = 0x20004000;
    return 0x14;
  }
  iVar4 = FUN_ram_20000040(0x10,0x53);
  if (iVar4 != 0) {
    uVar2 = (uint)param_5[1] * 0x100 + (uint)param_5[2] * 0x10000 + (uint)*param_5 +
            (uint)param_5[3] * 0x1000000;
    if (((*(uint *)(iVar3 + 0x28) < uVar2) || (iVar1 = 2, *(uint *)(iVar3 + 0x28) == 0xffffffff)) &&
       ((param_2 == 0 || (iVar1 = 1, (*(byte *)(iVar3 + 4) & 2) != 0)))) {
      tmos_memset(auStack_40,0,8);
      uVar6 = param_4 + 4U & 0xffff;
      iVar5 = FUN_ram_20000040(uVar6,0x53);
      iVar1 = 0x13;
      if (iVar5 != 0) {
        FUN_ram_20000298(iVar5 + 4,param_3,param_4);
        FUN_ram_20000298(iVar5,param_5,4);
        FUN_ram_20000298(iVar4,iVar3 + 0x18,0x10);
        iVar1 = FUN_ram_00051598(iVar4,iVar5,uVar6,auStack_40,8);
        if (iVar1 == 0) {
          FUN_ram_20000298(auStack_38,auStack_40,8);
          iVar3 = tmos_memcmp(auStack_38,param_5 + 4,8);
          if (iVar3 == 1) {
            FUN_ram_00044fbc(param_1,uVar2);
          }
          else {
            iVar1 = 1;
          }
        }
        FUN_ram_20000104(iVar5);
      }
    }
    FUN_ram_20000104(iVar4);
    return iVar1;
  }
  gp = 0x20004000;
  return 0x13;
}

