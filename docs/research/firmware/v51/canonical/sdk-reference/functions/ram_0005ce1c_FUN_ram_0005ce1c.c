/* Address: ram:0005ce1c; name: FUN_ram_0005ce1c; body bytes: 46 */

undefined4 FUN_ram_0005ce1c(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    thunk_FUN_ram_000519f6
              (*(undefined2 *)(iVar1 + 8),*(undefined2 *)(iVar1 + 0x72),
               *(undefined2 *)(iVar1 + 0x74),*(undefined2 *)(iVar1 + 0x58),
               *(undefined2 *)(iVar1 + 0x5a));
    uVar2 = 0;
  }
  return uVar2;
}

