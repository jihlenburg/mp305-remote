/* Address: 000237b0; name: FUN_000237b0; body bytes: 118 */

void FUN_000237b0(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  bVar1 = *(byte *)(param_1 + 0x54);
  iVar4 = *(int *)(param_1 + 0x3c);
  iVar3 = *(int *)(param_1 + 0x44);
  if ((bVar1 & 1) == 0) {
    if (iVar3 != 0) {
      if (iVar3 == -1) goto LAB_000237f8;
      iVar3 = iVar3 + -1;
      *(int *)(param_1 + 0x44) = iVar3;
      goto LAB_000237ca;
    }
  }
  else {
LAB_000237ca:
    if (iVar3 != 0) goto LAB_000237f8;
  }
  if ((iVar4 == 0) || ((bVar1 & 1) != 0)) {
    FUN_0004a2ac(&DAT_2003a4cc,param_1);
    FUN_0002382c();
    if (*(code **)(param_1 + 0x10) != (code *)0x0) {
      (**(code **)(param_1 + 0x10))(param_1);
    }
    if (*(code **)(param_1 + 0x14) != (code *)0x0) {
      (**(code **)(param_1 + 0x14))(param_1);
    }
    FUN_00046bec(param_1);
    return;
  }
LAB_000237f8:
  *(int *)(param_1 + 0x34) = -*(int *)(param_1 + 0x40);
  if (iVar4 != 0) {
    if ((bVar1 & 1) == 0) {
      *(int *)(param_1 + 0x34) = -*(int *)(param_1 + 0x38);
    }
    *(byte *)(param_1 + 0x54) = bVar1 & 0xfe | bVar1 + 1 & 1;
    uVar2 = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(param_1 + 0x2c) = uVar2;
    uVar2 = *(undefined4 *)(param_1 + 0x30);
    *(int *)(param_1 + 0x30) = iVar4;
    *(undefined4 *)(param_1 + 0x3c) = uVar2;
  }
  return;
}

