/* Address: ram:0005af82; name: FUN_ram_0005af82; body bytes: 72 */

undefined4 FUN_ram_0005af82(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 3;
  *(undefined1 *)(iVar1 + 2) = 0x19;
  *(byte *)(iVar1 + 3) =
       (byte)(1 << (*(byte *)(param_1 + 0x147) & 0x1f)) |
       (byte)(1 << (*(byte *)(param_1 + 0x146) & 0x1f));
  *(undefined1 *)(iVar1 + 4) = *(undefined1 *)(param_1 + 0x141);
  *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
  *(undefined1 *)(param_1 + 0x10) = 0x60;
  return 0;
}

