/* Address: ram:00051598; name: FUN_ram_00051598; body bytes: 370 */

int FUN_ram_00051598(undefined4 param_1,int param_2,uint param_3,undefined4 param_4,
                    undefined4 param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 *puVar8;
  uint uVar9;
  undefined1 auStack_40 [16];
  
  gp = 0x20004000;
  puVar8 = auStack_40;
  iVar4 = FUN_ram_20000040(0x10,0x53);
  iVar5 = FUN_ram_20000040(0x10,0x53);
  iVar3 = 0x13;
  if (iVar4 == 0) goto LAB_ram_0005167a;
  if ((iVar5 != 0) && (iVar3 = FUN_ram_00051236(param_1,iVar4,iVar5), iVar3 == 0)) {
    iVar6 = FUN_ram_20000040(0x10,0x53);
    iVar7 = FUN_ram_20000040(0x10,0x53);
    if (iVar6 == 0) {
      iVar3 = 0x13;
    }
    else {
      if (iVar7 == 0) {
        iVar3 = 0x13;
      }
      else {
        iVar1 = (int)(param_3 + 0xf) >> 4;
        if (iVar1 == 0) {
          uVar2 = 0;
LAB_ram_000516a8:
          FUN_ram_000511fe(uVar2 * 0x10 + param_2,auStack_40);
          iVar1 = iVar5;
        }
        else {
          uVar2 = iVar1 - 1U & 0xffff;
          if ((param_3 & 0xf) != 0) goto LAB_ram_000516a8;
          puVar8 = (undefined1 *)(uVar2 * 0x10 + param_2);
          iVar1 = iVar4;
        }
        FUN_ram_000511a8(puVar8,iVar1,iVar7);
        tmos_memset(iVar6,0,0x10);
        for (uVar9 = 0; (uVar9 & 0xffff) < uVar2; uVar9 = uVar9 + 1) {
          if (iVar3 != 0) goto LAB_ram_00051658;
          FUN_ram_000511a8(iVar6,uVar9 * 0x10 + param_2,auStack_40);
          iVar3 = LL_Encrypt(param_1,auStack_40,iVar6);
        }
        if (iVar3 == 0) {
          FUN_ram_000511a8(iVar6,iVar7,auStack_40);
          iVar3 = LL_Encrypt(param_1,auStack_40,iVar6);
          tmos_memcpy(param_4,iVar6,param_5);
        }
      }
LAB_ram_00051658:
      FUN_ram_20000104(iVar6);
    }
    if (iVar7 != 0) {
      FUN_ram_20000104(iVar7);
    }
  }
  FUN_ram_20000104(iVar4);
LAB_ram_0005167a:
  if (iVar5 != 0) {
    FUN_ram_20000104(iVar5);
  }
  return iVar3;
}

