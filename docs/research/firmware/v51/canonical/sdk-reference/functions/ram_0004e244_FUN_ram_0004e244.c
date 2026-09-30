/* Address: ram:0004e244; name: FUN_ram_0004e244; body bytes: 94 */

uint FUN_ram_0004e244(void)

{
  uint uVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  
  gp = 0x20004000;
  uVar4 = 0;
  pcVar2 = (char *)(DAT_ram_20001d00 + 4);
  for (uVar3 = 0; DAT_ram_20001d54 != uVar3; uVar3 = uVar3 + 1 & 0xff) {
    if (*pcVar2 != '\0') {
      uVar4 = uVar4 | *(ushort *)(pcVar2 + 0x2c);
    }
    pcVar2 = pcVar2 + 0x3c;
  }
  uVar1 = 1;
  for (uVar4 = ~(uVar4 >> 1) & 0xffff; (uVar1 < uVar3 && ((uVar4 & 1) == 0)); uVar4 = uVar4 >> 1) {
    uVar1 = uVar1 + 1 & 0xff;
  }
  return 1 << (uVar1 & 0x1f) & 0xffff;
}

