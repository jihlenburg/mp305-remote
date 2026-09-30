/* Address: 0004233c; name: FUN_0004233c; body bytes: 92 */

void FUN_0004233c(undefined4 param_1,undefined1 param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  iVar1 = FUN_0004f604();
  iVar2 = FUN_0004a360(0x4c);
  if (iVar2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(undefined4 *)(iVar2 + 0x3c) = param_1;
  uVar3 = param_3[1];
  uVar5 = param_3[2];
  uVar6 = param_3[3];
  *(undefined4 *)(iVar2 + 0x18) = *param_3;
  *(undefined4 *)(iVar2 + 0x1c) = uVar3;
  *(undefined4 *)(iVar2 + 0x20) = uVar5;
  *(undefined4 *)(iVar2 + 0x24) = uVar6;
  uVar3 = param_3[1];
  uVar5 = param_3[2];
  uVar6 = param_3[3];
  *(undefined4 *)(iVar2 + 4) = *param_3;
  *(undefined4 *)(iVar2 + 8) = uVar3;
  *(undefined4 *)(iVar2 + 0xc) = uVar5;
  *(undefined4 *)(iVar2 + 0x10) = uVar6;
  uVar3 = param_3[1];
  uVar5 = param_3[2];
  uVar6 = param_3[3];
  *(undefined4 *)(iVar2 + 0x28) = *param_3;
  *(undefined4 *)(iVar2 + 0x2c) = uVar3;
  *(undefined4 *)(iVar2 + 0x30) = uVar5;
  *(undefined4 *)(iVar2 + 0x34) = uVar6;
  *(undefined1 *)(iVar2 + 0x14) = param_2;
  iVar4 = *(int *)(iVar1 + 0x2a8);
  if (*(int *)(iVar1 + 0x2a8) == 0) {
    *(int *)(iVar1 + 0x2a8) = iVar2;
  }
  else {
    do {
      iVar1 = iVar4;
      iVar4 = *(int *)(iVar1 + 0x40);
    } while (iVar4 != 0);
    *(int *)(iVar1 + 0x40) = iVar2;
  }
  return;
}

