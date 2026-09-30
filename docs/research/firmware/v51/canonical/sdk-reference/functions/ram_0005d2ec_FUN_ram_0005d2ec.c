/* Address: ram:0005d2ec; name: FUN_ram_0005d2ec; body bytes: 48 */

undefined4 FUN_ram_0005d2ec(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    thunk_FUN_ram_000518cc(*(undefined1 *)(iVar1 + 0x2a),*(undefined2 *)(iVar1 + 8),iVar1 + 0x100);
    uVar2 = 0;
    *(undefined1 *)(iVar1 + 0x2a) = 0;
  }
  return uVar2;
}

