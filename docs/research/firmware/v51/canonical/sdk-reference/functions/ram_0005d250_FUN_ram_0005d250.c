/* Address: ram:0005d250; name: FUN_ram_0005d250; body bytes: 46 */

undefined4 FUN_ram_0005d250(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    thunk_FUN_ram_00051a38
              (*(undefined2 *)(iVar1 + 8),*(undefined2 *)(iVar1 + 0x1c8),
               *(undefined2 *)(iVar1 + 0x1ca),*(undefined2 *)(iVar1 + 0x1c4),
               *(undefined2 *)(iVar1 + 0x1c6));
    uVar2 = 0;
  }
  return uVar2;
}

