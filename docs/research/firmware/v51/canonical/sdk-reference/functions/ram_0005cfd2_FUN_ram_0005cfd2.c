/* Address: ram:0005cfd2; name: FUN_ram_0005cfd2; body bytes: 34 */

undefined4 FUN_ram_0005cfd2(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    thunk_FUN_ram_00052066(*(undefined2 *)(iVar1 + 8),*(undefined1 *)(iVar1 + 0x140));
    uVar2 = 0;
  }
  return uVar2;
}

