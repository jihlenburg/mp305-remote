/* Address: 00034868; name: FUN_00034868; body bytes: 232 */

void FUN_00034868(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined2 local_20;
  undefined1 uStack_1e;
  
  uVar1 = FUN_00046698();
  iVar2 = FUN_0004673a(param_1);
  if (*(undefined1 **)(*(int *)(iVar2 + 0x4c) + 4) == &LAB_00050000) {
    iVar3 = FUN_00045f8c(iVar2);
    iVar4 = FUN_00045f7e(iVar2);
    if (iVar3 != 0 || iVar4 != 0) {
      iVar2 = *(int *)(*(int *)(iVar2 + 0x4c) + 8);
      if ((iVar2 < 7) || (iVar5 = FUN_0003edc8(uVar1,iVar2,0x40), iVar5 != 0)) {
        if (iVar3 != 0) {
          *(undefined1 *)(iVar3 + 0x20) = 0;
        }
        if (iVar4 != 0) {
          *(undefined1 *)(iVar4 + 0x28) = 0;
        }
      }
      iVar5 = FUN_0003edc8(uVar1,iVar2,0x8000);
      if (iVar5 != 0) {
        if (iVar4 != 0) {
          uVar6 = FUN_000526c4(uVar1);
          local_20 = (undefined2)uVar6;
          *(undefined2 *)(iVar4 + 0x20) = local_20;
          uStack_1e = (undefined1)((uint)uVar6 >> 0x10);
          *(undefined1 *)(iVar4 + 0x22) = uStack_1e;
        }
        if (iVar3 != 0) {
          *(undefined1 *)(iVar3 + 0x20) = 0x66;
          uVar6 = FUN_000526c4(uVar1);
          local_20 = (undefined2)uVar6;
          *(undefined2 *)(iVar3 + 0x21) = local_20;
          uStack_1e = (undefined1)((uint)uVar6 >> 0x10);
          *(undefined1 *)(iVar3 + 0x23) = uStack_1e;
        }
        iVar5 = FUN_0003edc4(uVar1);
        if ((iVar5 == iVar2) && (iVar3 != 0)) {
          *(undefined1 *)(iVar3 + 0x20) = 0xb2;
        }
      }
      iVar2 = FUN_0003edc8(uVar1,iVar2,0x4000);
      if ((iVar2 != 0) && (iVar4 != 0)) {
        *(undefined1 *)(iVar4 + 0x28) = 0xff;
        uVar1 = FUN_000526c4(uVar1);
        local_20 = (undefined2)uVar1;
        *(undefined2 *)(iVar4 + 0x20) = local_20;
        uStack_1e = (undefined1)((uint)uVar1 >> 0x10);
        *(undefined1 *)(iVar4 + 0x22) = uStack_1e;
        *(int *)(iVar4 + 0x24) = *(int *)(iVar4 + 0x24) + 1;
      }
    }
  }
  return;
}

