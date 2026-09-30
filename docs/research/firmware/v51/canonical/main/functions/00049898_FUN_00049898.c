/* Address: 00049898; name: FUN_00049898; body bytes: 96 */

void FUN_00049898(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if (((*(byte *)(param_1 + 0x5c) & 7) == 1) && (*(int *)(param_1 + 0x34) != -1)) {
    iVar1 = FUN_00051c28(*(undefined4 *)(param_1 + 0x2c),*(int *)(param_1 + 0x34) + -3);
    uVar2 = 0;
    if ((int)((uint)*(byte *)(param_1 + 0x5c) << 0x1a) < 0) {
      iVar3 = *(int *)(param_1 + 0x30);
    }
    else {
      iVar3 = param_1 + 0x30;
    }
    while( true ) {
      iVar4 = *(int *)(param_1 + 0x2c);
      if (*(char *)(iVar4 + iVar1 + uVar2) == '\0') break;
      *(undefined1 *)(iVar4 + iVar1 + uVar2) = *(undefined1 *)(iVar3 + uVar2);
      uVar2 = uVar2 + 1 & 0xff;
    }
    *(undefined1 *)(iVar4 + uVar2 + iVar1) = *(undefined1 *)(iVar3 + uVar2);
    FUN_00048dbe(param_1);
    *(undefined4 *)(param_1 + 0x34) = 0xffffffff;
  }
  return;
}

