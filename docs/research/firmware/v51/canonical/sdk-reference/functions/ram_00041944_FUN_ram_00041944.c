/* Address: ram:00041944; name: FUN_ram_00041944; body bytes: 98 */

void FUN_ram_00041944(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  gp = 0x20004000;
  uVar3 = (uint)DAT_ram_20001ee1 + (uint)DAT_ram_20001ecf & 0x1f;
  DAT_ram_20001eb5 = (char)uVar3;
  DAT_ram_20001ee1 = (char)uVar3;
  if ((DAT_ram_20001ec8 >> uVar3 & 1) == 0) {
    uVar1 = 0;
    if (DAT_ram_20001ee5 != 0) {
      uVar3 = uVar3 % (uint)DAT_ram_20001ee5;
    }
    uVar2 = 0;
    do {
      if ((DAT_ram_20001ec8 >> (uVar2 & 0x1f) & 1) != 0) {
        if (uVar3 == uVar1) {
          DAT_ram_20001eb5 = (char)uVar2;
          return;
        }
        uVar1 = uVar1 + 1 & 0xff;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != 0x20);
  }
  return;
}

