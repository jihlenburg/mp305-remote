/* Address: ram:000661ca; name: FUN_ram_000661ca; body bytes: 64 */

undefined4 FUN_ram_000661ca(undefined4 param_1,undefined1 param_2)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x2a) = param_2;
    if ((*(byte *)(iVar1 + 0x11) & 4) != 0) {
      *(byte *)(iVar1 + 0x11) = *(byte *)(iVar1 + 0x11) & 0xfb;
      *(undefined1 *)(iVar1 + 0x2b) = 0xf;
      *(uint *)(iVar1 + 0xa8) = *(uint *)(iVar1 + 0xa8) | 2;
      gp = 0x20004000;
      return 0;
    }
  }
  return 0x12;
}

