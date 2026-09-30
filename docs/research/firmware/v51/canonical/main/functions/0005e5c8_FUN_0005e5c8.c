/* Address: 0005e5c8; name: FUN_0005e5c8; body bytes: 280 */

undefined1 FUN_0005e5c8(undefined4 param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 local_18;
  undefined1 uStack_16;
  
  FUN_00042ec4(param_2);
  uVar3 = FUN_0004c620(param_1,0x10000);
  *(char *)(param_2 + 0x20) = (char)uVar3;
  if (2 < uVar3) {
    uVar4 = FUN_0004c924(param_1,0x10000,0x1c);
    local_18 = (undefined2)uVar4;
    *(undefined2 *)(param_2 + 0x21) = local_18;
    uStack_16 = (undefined1)((uint)uVar4 >> 0x10);
    *(undefined1 *)(param_2 + 0x23) = uStack_16;
  }
  bVar1 = FUN_0004c924(param_1,0x10000,0x32);
  *(byte *)(param_2 + 0x48) = bVar1;
  if (2 < bVar1) {
    iVar5 = FUN_0004c924(param_1,0x10000,0x30);
    *(int *)(param_2 + 0x44) = iVar5;
    if (iVar5 < 1) {
      *(undefined1 *)(param_2 + 0x48) = 0;
    }
    else {
      uVar4 = FUN_0004c924(param_1,0x10000,0x31);
      local_18 = (undefined2)uVar4;
      *(undefined2 *)(param_2 + 0x3e) = local_18;
      uStack_16 = (undefined1)((uint)uVar4 >> 0x10);
      *(undefined1 *)(param_2 + 0x40) = uStack_16;
    }
  }
  bVar1 = FUN_0004c924(param_1,0x10000,0x3e);
  *(byte *)(param_2 + 0x6c) = bVar1;
  if (2 < bVar1) {
    iVar5 = FUN_0004c924(param_1,0x10000,0x3c);
    *(int *)(param_2 + 0x5c) = iVar5;
    if (iVar5 < 1) {
      *(undefined1 *)(param_2 + 0x6c) = 0;
    }
    else {
      uVar4 = FUN_0004c924(param_1,0x10000,0x42);
      *(undefined4 *)(param_2 + 0x68) = uVar4;
      uVar4 = FUN_0004c924(param_1,0x10000,0x3d);
      local_18 = (undefined2)uVar4;
      *(undefined2 *)(param_2 + 0x59) = local_18;
      uStack_16 = (undefined1)((uint)uVar4 >> 0x10);
      *(undefined1 *)(param_2 + 0x5b) = uStack_16;
    }
  }
  uVar3 = FUN_0004c774(param_1,0x10000);
  if (uVar3 < 0xfd) {
    uVar2 = (undefined1)
            ((uint)((int)(short)(ushort)*(byte *)(param_2 + 0x20) * (int)(short)uVar3) >> 8);
    *(undefined1 *)(param_2 + 0x20) = uVar2;
    *(undefined1 *)(param_2 + 0x48) = uVar2;
    *(undefined1 *)(param_2 + 0x6c) = uVar2;
  }
  if (((*(char *)(param_2 + 0x20) != '\0') || (*(char *)(param_2 + 0x48) != '\0')) ||
     (uVar2 = 0, *(char *)(param_2 + 0x6c) != '\0')) {
    uVar4 = FUN_0004c94e(param_1,0x10000);
    *(undefined4 *)(param_2 + 0x1c) = uVar4;
    uVar2 = 1;
  }
  return uVar2;
}

