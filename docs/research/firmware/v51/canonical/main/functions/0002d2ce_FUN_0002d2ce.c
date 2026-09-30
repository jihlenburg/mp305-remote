/* Address: 0002d2ce; name: FUN_0002d2ce; body bytes: 168 */

undefined8 FUN_0002d2ce(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  local_30 = param_1;
  uStack_2c = param_2;
  uStack_28 = param_3;
  uStack_24 = param_4;
  iVar2 = FUN_00046698();
  iVar7 = *(int *)(iVar2 + 0x2c);
  iVar2 = FUN_00046718(param_1);
  iVar3 = FUN_0003db4c(&local_30,iVar2 + 0x18,*(int *)(iVar7 + 0x2c) + 0x14);
  if (iVar3 != 0) {
    uVar10 = *(undefined4 *)(iVar2 + 0x20);
    uVar4 = *(undefined4 *)(iVar2 + 0x24);
    puVar1 = (undefined4 *)(iVar2 + 0x18);
    uVar8 = *puVar1;
    uVar9 = *(undefined4 *)(iVar2 + 0x1c);
    *puVar1 = local_30;
    *(undefined4 *)(iVar2 + 0x1c) = uStack_2c;
    *(undefined4 *)(iVar2 + 0x20) = uStack_28;
    *(undefined4 *)(iVar2 + 0x24) = uStack_24;
    if ((int)((uint)*(byte *)(iVar7 + 0x4c) << 0x1a) < 0) {
      iVar3 = *(int *)(iVar7 + 0x48);
      if (iVar3 == *(int *)(iVar7 + 0x40)) {
        FUN_00029570(iVar7,iVar2,iVar3,0x21);
        uVar6 = 0x21;
        uVar5 = *(undefined4 *)(iVar7 + 0x48);
      }
      else {
        FUN_00029570(iVar7,iVar2,iVar3,0x20);
        FUN_00029610(iVar7,iVar2,*(undefined4 *)(iVar7 + 0x48),0x20);
        FUN_00029570(iVar7,iVar2,*(undefined4 *)(iVar7 + 0x40),1);
        uVar5 = *(undefined4 *)(iVar7 + 0x40);
        uVar6 = 1;
      }
    }
    else {
      FUN_00029570(iVar7,iVar2,*(undefined4 *)(iVar7 + 0x48),0x20);
      uVar6 = 0x20;
      uVar5 = *(undefined4 *)(iVar7 + 0x48);
    }
    FUN_00029610(iVar7,iVar2,uVar5,uVar6);
    *puVar1 = uVar8;
    *(undefined4 *)(iVar2 + 0x1c) = uVar9;
    *(undefined4 *)(iVar2 + 0x20) = uVar10;
    *(undefined4 *)(iVar2 + 0x24) = uVar4;
  }
  return CONCAT44(uStack_2c,local_30);
}

