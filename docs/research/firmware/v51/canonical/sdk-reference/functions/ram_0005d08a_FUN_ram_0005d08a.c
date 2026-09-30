/* Address: ram:0005d08a; name: FUN_ram_0005d08a; body bytes: 64 */

undefined4 FUN_ram_0005d08a(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    thunk_FUN_ram_00051c7a
              (*(undefined1 *)(iVar1 + 0x2a),*(undefined2 *)(iVar1 + 8),
               *(char *)(iVar1 + 0x146) + '\x01',*(char *)(iVar1 + 0x147) + '\x01');
    uVar2 = 0;
    *(undefined1 *)(iVar1 + 0x2a) = 0;
  }
  return uVar2;
}

