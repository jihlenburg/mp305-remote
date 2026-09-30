/* Address: 0005dfdc; name: FUN_0005dfdc; body bytes: 190 */

void FUN_0005dfdc(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  
  for (iVar1 = FUN_0004a14a(); iVar1 != 0; iVar1 = FUN_0004a144(param_1 + 0x2c,iVar1)) {
    if ((*(int *)(iVar1 + 0xc) <= param_5) && (param_5 <= *(int *)(iVar1 + 0x10))) {
      if (param_2 == 0) {
        uVar4 = *(undefined4 *)(iVar1 + 8);
        puVar5 = &LAB_00050000;
        iVar3 = param_4;
      }
      else {
        puVar5 = (undefined1 *)0x20000;
        uVar4 = *(undefined4 *)(iVar1 + 4);
        iVar3 = param_3;
      }
      FUN_0005df30(param_1,iVar3,uVar4,puVar5);
    }
    if (*(int *)(iVar1 + 0x14) == param_6) {
      if (*(int *)(iVar1 + 0x1c) == 0) {
        uVar2 = *(uint *)(param_4 + 0x30);
      }
      else {
        uVar2 = *(uint *)(param_3 + 0x30);
      }
      *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(param_7 + 4);
      if ((uVar2 & 1) != 0) {
        if ((*(char *)(param_1 + 0x3c) == '\x02') || (*(char *)(param_1 + 0x3c) == '\x04')) {
          uVar2 = uVar2 + 1;
        }
        else {
          uVar2 = uVar2 - 1;
        }
      }
      *(uint *)(iVar1 + 0x24) = uVar2;
    }
    else if (*(int *)(iVar1 + 0x18) == param_6) {
      if (*(int *)(iVar1 + 0x20) == 0) {
        uVar2 = *(uint *)(param_4 + 0x30);
      }
      else {
        uVar2 = *(uint *)(param_3 + 0x30);
      }
      *(undefined4 *)(iVar1 + 0x38) = *(undefined4 *)(param_7 + 4);
      if ((uVar2 & 1) != 0) {
        if ((*(char *)(param_1 + 0x3c) == '\x02') || (*(char *)(param_1 + 0x3c) == '\x04')) {
          uVar2 = uVar2 - 1;
        }
        else {
          uVar2 = uVar2 + 1;
        }
      }
      *(uint *)(iVar1 + 0x28) = uVar2;
    }
  }
  return;
}

