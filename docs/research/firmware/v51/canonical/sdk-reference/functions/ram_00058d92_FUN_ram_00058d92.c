/* Address: ram:00058d92; name: FUN_ram_00058d92; body bytes: 334 */

void FUN_ram_00058d92(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  gp = 0x20004000;
  FUN_ram_0005a804();
  iVar3 = FUN_ram_00057ba2();
  if (iVar3 != 0) {
    iVar5 = *(int *)(param_1 + 0x94);
    *(undefined4 *)(iVar3 + 0x88) = *(undefined4 *)(param_1 + 0x60);
    *(undefined4 *)(iVar3 + 0x98) = *(undefined4 *)(param_1 + 0x58);
    *(undefined4 *)(iVar3 + 0x9c) = *(undefined4 *)(param_1 + 0x5c);
    *(undefined1 *)(iVar3 + 0x35) = *(undefined1 *)(iVar5 + 0x15);
    *(undefined2 *)(iVar3 + 0x36) = *(undefined2 *)(iVar5 + 0x16);
    *(undefined2 *)(iVar3 + 0x38) = *(undefined2 *)(iVar5 + 0x18);
    *(undefined2 *)(iVar3 + 0x3a) = *(undefined2 *)(iVar5 + 0x1a);
    *(undefined2 *)(iVar3 + 0x3c) = *(undefined2 *)(iVar5 + 0x1c);
    uVar1 = *(undefined1 *)(param_1 + 0xc);
    *(undefined4 *)(iVar3 + 0x13c) = 0;
    *(undefined1 *)(iVar3 + 0x33) = uVar1;
    *(undefined4 *)(iVar3 + 0x138) = 0;
    tmos_memcpy((undefined4 *)(iVar3 + 0x138),&DAT_ram_20001e56,5);
    if (*(char *)(param_1 + 6) == -0x4a) {
      *(undefined1 *)(iVar3 + 0x140) = 1;
      cVar2 = *(char *)(param_1 + 0x3c);
      if (cVar2 == '\x03') {
        *(undefined2 *)(iVar3 + 0x146) = 0x202;
        *(undefined2 *)(iVar3 + 0x148) = 1;
      }
      else {
        *(char *)(iVar3 + 0x146) = cVar2;
        *(char *)(iVar3 + 0x147) = cVar2;
      }
    }
    else if (DAT_ram_20001e28 << 0x11 < 0) {
      *(byte *)(iVar3 + 0x140) =
           (**(byte **)(param_1 + 0x98) & **(byte **)(param_1 + 0x94)) >> 5 & 1;
    }
    FUN_ram_0005a6ea(iVar3);
    uVar4 = 10;
    if ((DAT_ram_20001e30 & 0x200) == 0) {
      uVar4 = 1;
    }
    FUN_ram_0005d5f6(*(undefined2 *)(iVar3 + 8),0x80,uVar4);
    if (DAT_ram_20001e28 << 0x11 < 0) {
      FUN_ram_0005d5f6(*(undefined2 *)(iVar3 + 8),0x80,0x14);
    }
  }
  FUN_ram_00058d50(param_1);
  return;
}

