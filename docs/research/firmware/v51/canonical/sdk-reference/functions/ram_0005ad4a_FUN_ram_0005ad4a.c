/* Address: ram:0005ad4a; name: FUN_ram_0005ad4a; body bytes: 42 */

undefined4 FUN_ram_0005ad4a(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 3;
  iVar1 = *(int *)(param_1 + 0x110);
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 2) = 0x11;
    *(undefined1 *)(iVar1 + 3) = *(undefined1 *)(param_1 + 0x2b);
    *(undefined1 *)(iVar1 + 4) = *(undefined1 *)(param_1 + 0x2a);
    return 0;
  }
  return 1;
}

