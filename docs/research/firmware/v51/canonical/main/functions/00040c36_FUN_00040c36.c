/* Address: 00040c36; name: FUN_00040c36; body bytes: 62 */

void FUN_00040c36(int param_1,undefined4 *param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  iVar1 = FUN_0004a360(0x54);
  uVar3 = param_2[1];
  uVar5 = param_2[2];
  uVar6 = param_2[3];
  *(undefined4 *)(iVar1 + 8) = *param_2;
  *(undefined4 *)(iVar1 + 0xc) = uVar3;
  *(undefined4 *)(iVar1 + 0x10) = uVar5;
  *(undefined4 *)(iVar1 + 0x14) = uVar6;
  uVar3 = param_2[1];
  uVar5 = param_2[2];
  uVar6 = param_2[3];
  *(undefined4 *)(iVar1 + 0x18) = *param_2;
  *(undefined4 *)(iVar1 + 0x1c) = uVar3;
  *(undefined4 *)(iVar1 + 0x20) = uVar5;
  *(undefined4 *)(iVar1 + 0x24) = uVar6;
  uVar3 = *(undefined4 *)(param_1 + 0x1c);
  uVar5 = *(undefined4 *)(param_1 + 0x20);
  uVar6 = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(iVar1 + 0x38) = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(iVar1 + 0x3c) = uVar3;
  *(undefined4 *)(iVar1 + 0x40) = uVar5;
  *(undefined4 *)(iVar1 + 0x44) = uVar6;
  *(undefined4 *)(iVar1 + 0x48) = 1;
  piVar4 = *(int **)(param_1 + 0x38);
  if (*(int **)(param_1 + 0x38) != (int *)0x0) {
    do {
      piVar2 = piVar4;
      piVar4 = (int *)*piVar2;
    } while (piVar4 != (int *)0x0);
    *piVar2 = iVar1;
    return;
  }
  *(int *)(param_1 + 0x38) = iVar1;
  return;
}

