/* Address: ram:0005cede; name: FUN_ram_0005cede; body bytes: 138 */

undefined4 FUN_ram_0005cede(undefined2 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uStack_1c;
  undefined1 uStack_1b;
  undefined2 uStack_1a;
  char cStack_18;
  undefined1 uStack_17;
  char cStack_16;
  undefined1 uStack_15;
  undefined1 uStack_14;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    uStack_1b = *(undefined1 *)(iVar1 + 0x2a);
    uStack_17 = *(undefined1 *)(iVar1 + 0x15a);
    cStack_18 = *(char *)(iVar1 + 0x159);
    if (cStack_18 == '\0') {
      uStack_14 = *(undefined1 *)(iVar1 + 0x15d);
      cStack_16 = *(char *)(iVar1 + 0x143);
      if (*(char *)(iVar1 + 0x15f) == cStack_16) {
        uStack_15 = 2;
      }
      else if (*(char *)(iVar1 + 0x15e) == cStack_16) {
        uStack_15 = 1;
      }
      else {
        uStack_15 = 0;
      }
    }
    else {
      cStack_16 = *(char *)(iVar1 + 0x160);
      uStack_15 = *(undefined1 *)(iVar1 + 0x15b);
      uStack_14 = *(undefined1 *)(iVar1 + 0x165);
    }
    uStack_1a = param_1;
    FUN_ram_00068304(&uStack_1c);
    uVar2 = 0;
  }
  return uVar2;
}

