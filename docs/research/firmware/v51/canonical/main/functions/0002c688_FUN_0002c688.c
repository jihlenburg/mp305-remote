/* Address: 0002c688; name: FUN_0002c688; body bytes: 288 */

void FUN_0002c688(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  bool bVar7;
  undefined1 auStack_110 [112];
  undefined1 auStack_a0 [112];
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar1 = FUN_00046698();
  uVar2 = FUN_00046718(param_1);
  iVar3 = FUN_0004c5ca(iVar1,0);
  uVar4 = FUN_0003ac70(iVar1);
  bVar7 = (uint)*(byte *)(iVar1 + 0x4c) == (iVar3 == 1 & uVar4);
  iVar3 = thunk_FUN_0003e1fc(iVar1);
  if (uVar4 == 0) {
    uVar5 = FUN_0004ccf8(iVar1);
    if ((iVar3 == 0) || (-1 < *(int *)(iVar1 + 0x2c))) {
      if (bVar7) goto LAB_0002c746;
    }
    else if (!bVar7) {
LAB_0002c746:
      local_2c = *(undefined4 *)(iVar1 + 0x40);
      goto LAB_0002c708;
    }
    local_2c = *(undefined4 *)(iVar1 + 0x48);
    goto LAB_0002c708;
  }
  uVar5 = FUN_0004bbec();
  if ((iVar3 == 0) || (-1 < *(int *)(iVar1 + 0x2c))) {
    if (bVar7) goto LAB_0002c6f0;
  }
  else if (!bVar7) {
LAB_0002c6f0:
    local_30 = *(undefined4 *)(iVar1 + 0x44);
    goto LAB_0002c708;
  }
  local_30 = *(undefined4 *)(iVar1 + 0x3c);
LAB_0002c708:
  FUN_00042ec4(auStack_110);
  FUN_0004d0bc(iVar1,0x30000,auStack_110);
  FUN_000587b0(iVar1,&local_30,uVar5,uVar4);
  iVar6 = iVar1 + 0x84;
  FUN_0003d9ec(iVar6,&local_30);
  iVar3 = FUN_0005051c(iVar1);
  if (iVar3 == 2) {
    FUN_0004a404(auStack_a0,auStack_110,0x70);
    FUN_00042a98(uVar2,auStack_110,iVar6);
    if (uVar4 == 0) {
      if (bVar7) {
        local_2c = *(undefined4 *)(iVar1 + 0x48);
      }
      else {
        local_2c = *(undefined4 *)(iVar1 + 0x40);
      }
    }
    else if (bVar7) {
      local_30 = *(undefined4 *)(iVar1 + 0x3c);
    }
    else {
      local_30 = *(undefined4 *)(iVar1 + 0x44);
    }
    FUN_000587b0(iVar1,&local_30,uVar5,uVar4);
    iVar6 = iVar1 + 0x74;
    FUN_0003d9ec(iVar6,&local_30);
    FUN_0004a404(auStack_110,auStack_a0,0x70);
  }
  FUN_00042a98(uVar2,auStack_110,iVar6);
  return;
}

