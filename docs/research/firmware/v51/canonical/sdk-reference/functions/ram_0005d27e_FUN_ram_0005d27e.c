/* Address: ram:0005d27e; name: FUN_ram_0005d27e; body bytes: 64 */

undefined4 FUN_ram_0005d27e(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    thunk_FUN_ram_00051996
              (*(undefined2 *)(iVar1 + 8),*(undefined2 *)(iVar1 + 0x72),
               *(undefined2 *)(iVar1 + 0x74),*(undefined2 *)(iVar1 + 0x58),
               *(undefined2 *)(iVar1 + 0x5a));
    uVar2 = 0;
    *(byte *)(iVar1 + 0x11) = *(byte *)(iVar1 + 0x11) | 4;
  }
  return uVar2;
}

