/* Address: ram:0005d638; name: FUN_ram_0005d638; body bytes: 142 */

undefined4 FUN_ram_0005d638(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    gp = 0x20004000;
    return 2;
  }
  iVar2 = *(int *)(iVar1 + 0x120);
  *(undefined1 *)(iVar1 + 0x1a) = 0;
  if (iVar2 == 0) {
LAB_ram_0005d6ae:
    *(undefined2 *)(iVar1 + 0x40) = 0;
  }
  else {
    if ((*(byte *)(iVar1 + 0xf) & 1) != 0) {
      iVar2 = thunk_FUN_ram_00052316
                        (*(undefined2 *)(iVar1 + 8),*(undefined1 *)(iVar2 + 8),
                         *(undefined1 *)(iVar2 + 0xc),*(int *)(iVar2 + 4) + 2);
      if (iVar2 == 0) {
        puVar3 = *(undefined4 **)(iVar1 + 0x120);
        *(undefined1 *)((int)puVar3 + 9) = 0;
        *(ushort *)((int)puVar3 + 10) = *(ushort *)((int)puVar3 + 10) | 0xff00;
        *(undefined4 *)(iVar1 + 0x120) = *puVar3;
        if (*(short *)(iVar1 + 0x40) != 0) {
          *(short *)(iVar1 + 0x40) = *(short *)(iVar1 + 0x40) + -1;
        }
      }
      if (*(int *)(iVar1 + 0x120) == 0) goto LAB_ram_0005d6ae;
    }
    iVar2 = FUN_ram_0005d5f6(*(undefined2 *)(iVar1 + 8),0x80,0);
    if (iVar2 == 0) {
      *(undefined1 *)(iVar1 + 0x1a) = 1;
      gp = 0x20004000;
      return 0;
    }
  }
  return 0;
}

