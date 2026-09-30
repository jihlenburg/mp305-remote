/* Address: ram:0005abba; name: FUN_ram_0005abba; body bytes: 50 */

undefined4 FUN_ram_0005abba(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 2;
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 2) = 2;
    *(undefined1 *)(iVar1 + 3) = *(undefined1 *)(param_1 + 0x52);
    *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 8;
    *(undefined1 *)(param_1 + 0x10) = 0x1c;
    return 0;
  }
  return 7;
}

