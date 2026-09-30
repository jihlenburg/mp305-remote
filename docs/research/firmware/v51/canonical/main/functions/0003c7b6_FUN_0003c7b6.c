/* Address: 0003c7b6; name: FUN_0003c7b6; body bytes: 116 */

void FUN_0003c7b6(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uStack_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  iVar4 = *(int *)(param_1 + 0x2c);
  uStack_20 = param_2;
  local_1c = param_3;
  local_18 = param_4;
  uVar1 = FUN_00047eec();
  iVar2 = FUN_000482e0();
  if (iVar2 == 4) {
    *(undefined4 *)(iVar4 + 0x44) = *(undefined4 *)(iVar4 + 0x40);
    uVar3 = FUN_0004bbe2(iVar4);
    iVar2 = FUN_000472d4();
    if (iVar2 != 0) {
      FUN_0004743a(uVar3,0);
    }
  }
  iVar2 = FUN_000482e0(uVar1);
  if ((iVar2 == 1) || (iVar2 = FUN_000482e0(uVar1), iVar2 == 3)) {
    FUN_00048288(uVar1,&uStack_20);
    uVar1 = FUN_000373ec(iVar4,local_1c);
    *(undefined4 *)(iVar4 + 0x40) = uVar1;
    *(undefined4 *)(iVar4 + 0x44) = uVar1;
  }
  FUN_00045fa8(iVar4);
  if (*(int *)(iVar4 + 0x30) == 0) {
    FUN_0004d3d8(iVar4);
  }
  local_18 = *(undefined4 *)(iVar4 + 0x40);
  FUN_0004e5a6(iVar4,0x20,&local_18);
  return;
}

