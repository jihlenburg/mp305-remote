/* Address: 0003f648; name: FUN_0003f648; body bytes: 298 */

void FUN_0003f648(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  byte bVar6;
  uint uVar7;
  int local_20;
  undefined4 uStack_1c;
  
  local_20 = param_3;
  uStack_1c = param_4;
  iVar1 = FUN_0004b9b2(&PTR_DAT_0007a68c);
  if (iVar1 == 1) {
    iVar1 = FUN_00046688(param_2);
    iVar2 = FUN_00046698(param_2);
    if (iVar1 == 1) {
      uVar3 = FUN_00047eec();
      FUN_00048288(uVar3,&local_20);
      local_20 = local_20 - *(int *)(iVar2 + 0x14);
      iVar4 = FUN_0004bd90(iVar2);
      iVar4 = iVar4 + local_20;
      uVar5 = FUN_0004bb1a(iVar2);
      iVar1 = FUN_0004c858(iVar2,0);
      iVar4 = iVar4 - iVar1;
      uVar7 = 0;
      if (-1 < iVar4) {
        if ((int)uVar5 < iVar4) {
          uVar7 = *(int *)(iVar2 + 0x70) - 1;
        }
        else {
          bVar6 = *(byte *)(iVar2 + 0x74) & 7;
          if (bVar6 == 1) {
            uVar7 = (uint)(iVar4 * (*(int *)(iVar2 + 0x70) + -1) + (int)uVar5 / 2) / uVar5;
          }
          else if (bVar6 == 2) {
            uVar7 = (uint)(iVar4 * *(int *)(iVar2 + 0x70)) / uVar5;
          }
        }
      }
      if (*(uint *)(iVar2 + 100) != uVar7) {
        FUN_0003ab20(iVar2,uVar7);
        FUN_0003ab20(iVar2,*(undefined4 *)(iVar2 + 100));
        *(uint *)(iVar2 + 100) = uVar7;
        FUN_0004e5a6(iVar2,0x20,0);
      }
    }
    else if (iVar1 == 8) {
      FUN_0003ab20(iVar2,*(undefined4 *)(iVar2 + 100));
      *(undefined4 *)(iVar2 + 100) = 0x7fffffff;
    }
    else if (iVar1 == 0x1a) {
      uVar3 = FUN_00046718(param_2);
      FUN_0002baf0(iVar2,uVar3);
      iVar1 = FUN_0004a23c(iVar2 + 0x2c);
      if (iVar1 == 0) {
        bVar6 = *(byte *)(iVar2 + 0x74) & 7;
        if (bVar6 == 1) {
          FUN_00031c68(iVar2,uVar3);
        }
        else if (bVar6 == 2) {
          FUN_00031a78(iVar2,uVar3);
        }
        else if (bVar6 == 3) {
          FUN_000320ac(iVar2,uVar3);
        }
      }
      FUN_0002b818(iVar2,uVar3,local_20,uStack_1c);
      return;
    }
  }
  return;
}

