/* Address: 00046258; name: FUN_00046258; body bytes: 166 */

void FUN_00046258(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 uVar6;
  undefined4 uStack_20;
  undefined4 local_1c;
  
  uStack_20 = param_3;
  local_1c = param_4;
  iVar1 = FUN_00046688(param_2);
  if ((iVar1 == 0x1d) || (iVar2 = FUN_0004b9b2(&PTR_DAT_0007a6f8,param_2), iVar2 == 1)) {
    uVar6 = FUN_00046698(param_2);
    iVar2 = (int)uVar6;
    iVar5 = *(int *)(iVar2 + 0x2c);
    if (iVar1 == 8) {
      FUN_00047eec();
      uVar6 = FUN_000482c2();
      if ((int)uVar6 == 0) {
        FUN_0003c7b6(iVar2,(int)((ulonglong)uVar6 >> 0x20),uStack_20,local_1c);
        return;
      }
    }
    else if (iVar1 == 1) {
      iVar1 = FUN_00047eec();
      if ((iVar1 != 0) &&
         ((iVar3 = FUN_000482e0(), iVar3 == 1 || (iVar3 = FUN_000482e0(iVar1), iVar3 == 3)))) {
        FUN_00048288(iVar1,&uStack_20);
        uVar4 = FUN_000373ec(iVar5,local_1c);
        *(undefined4 *)(iVar5 + 0x48) = uVar4;
        FUN_0004d3d8(iVar2);
      }
    }
    else {
      if (iVar1 == 9) {
        *(undefined4 *)(iVar5 + 0x48) = 0xffff;
        FUN_0004d3d8(iVar2,(int)((ulonglong)uVar6 >> 0x20),uStack_20,local_1c);
        return;
      }
      if (iVar1 == 0x1d) {
        FUN_0002d2ce(param_2);
        FUN_0004b9b2(&PTR_DAT_0007a6f8,param_2,uStack_20,local_1c);
        return;
      }
    }
  }
  return;
}

