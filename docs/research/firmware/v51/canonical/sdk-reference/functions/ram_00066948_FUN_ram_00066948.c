/* Address: ram:00066948; name: FUN_ram_00066948; body bytes: 76 */

undefined4 FUN_ram_00066948(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    uVar2 = 2;
    if ((*(char *)(iVar1 + 0xb) == '\x01') && (*(char *)(iVar1 + 0x10) == '$')) {
      *(undefined **)(iVar1 + 0x2a) = &mcounteren;
      *(undefined1 *)(iVar1 + 0x10) = 0x25;
      uVar2 = 0;
      *(byte *)(iVar1 + 0x29) = *(byte *)(iVar1 + 0x29) | 1;
    }
  }
  return uVar2;
}

