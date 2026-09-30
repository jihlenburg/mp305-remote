/* Address: ram:000624fc; name: BLE_AccessAddressGenerate; body bytes: 216 */

uint BLE_AccessAddressGenerate(void)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  gp = 0x20004000;
  cVar2 = '\x01';
  do {
    if (cVar2 == '\0') {
      iVar3 = FUN_ram_000428ec(0x10,0xf0);
      return iVar3 << 0x10 | 0x6a00ace6;
    }
    iVar3 = FUN_ram_00042910(0,0xffff);
    uVar7 = iVar3 << 8;
    uVar1 = 0x6a0000e6;
    if ((uVar7 & 0x100) != 0) {
      uVar1 = 0xac0000ce;
    }
    uVar4 = uVar7 | uVar1;
    uVar8 = 0;
    bVar5 = 0;
    do {
      uVar6 = uVar8 & 0x1f;
      uVar8 = uVar8 + 1;
      if (((uVar4 >> (uVar8 & 0x1f) & 1) != (uVar4 >> uVar6 & 1)) &&
         (bVar5 = bVar5 + 1, 0x18 < bVar5)) goto LAB_ram_000625cc;
    } while (uVar8 != 0x20);
    uVar8 = 0;
    do {
      uVar6 = uVar4 >> (uVar8 & 0x1f) & 0x3f;
      if ((uVar6 == 0) || (uVar6 == 0x3f)) goto LAB_ram_000625cc;
      uVar8 = uVar8 + 1;
    } while (uVar8 != 0x1b);
    uVar1 = uVar1 & 0xff;
    if (uVar1 != (uVar7 & 0xff00) >> 8) {
      gp = 0x20004000;
      return uVar4;
    }
    if (uVar1 != (uVar7 & 0xff0000) >> 0x10) {
      gp = 0x20004000;
      return uVar4;
    }
    if (uVar1 != uVar4 >> 0x18) {
      gp = 0x20004000;
      return uVar4;
    }
LAB_ram_000625cc:
    cVar2 = cVar2 + '\x01';
  } while( true );
}

