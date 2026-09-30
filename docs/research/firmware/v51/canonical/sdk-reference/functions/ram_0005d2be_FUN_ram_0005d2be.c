/* Address: ram:0005d2be; name: FUN_ram_0005d2be; body bytes: 46 */

undefined4 FUN_ram_0005d2be(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    thunk_FUN_ram_00051932(*(undefined2 *)(iVar1 + 8),iVar1 + 399,*(undefined2 *)(iVar1 + 0x197));
    uVar2 = 0;
  }
  return uVar2;
}

