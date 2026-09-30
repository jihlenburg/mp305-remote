/* Address: ram:000621c8; name: FUN_ram_000621c8; body bytes: 154 */

void FUN_ram_000621c8(void)

{
  int iVar1;
  undefined1 uVar2;
  
  gp = 0x20004000;
  if (DAT_ram_20001e9c == '\b') {
    if (((DAT_ram_20001eb4 & 1) == 0) || (DAT_ram_20001ed8 == 0)) {
      uVar2 = 0;
      iVar1 = 0;
    }
    else {
      uVar2 = *(undefined1 *)(DAT_ram_20001ed8 + 1);
      iVar1 = DAT_ram_20001ed8 + 2;
    }
    iVar1 = RF_Rx(iVar1,uVar2,DAT_ram_20001ed4._3_1_,DAT_ram_20001ed4._2_1_);
    if (iVar1 != 0) {
      DAT_ram_20001e9d = 1;
    }
  }
  if (DAT_ram_20001e9c == '\x06') {
    if (*(char *)(DAT_ram_20001dd8 + 0xb) == '\0') {
      gp = 0x20004000;
      return;
    }
    FUN_ram_0005fea2();
  }
  if ((DAT_ram_20001e9c == '\a') && (*(char *)(DAT_ram_20001de8 + 7) != '\0')) {
    FUN_ram_000585c6();
    return;
  }
  return;
}

