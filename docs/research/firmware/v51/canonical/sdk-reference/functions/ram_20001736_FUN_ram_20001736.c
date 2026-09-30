/* Address: ram:20001736; name: FUN_ram_20001736; body bytes: 1 */

uint FUN_ram_20001736(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  gp = 0x20004000;
  uVar2 = (*DAT_ram_20001c00)();
  uVar4 = 0;
  if (DAT_ram_20001edc != uVar2) {
    if ((DAT_ram_20001bd2 < '\0') || (DAT_ram_20001edc <= uVar2)) {
      iVar1 = -DAT_ram_20001edc;
    }
    else {
      iVar1 = -0x57400000 - DAT_ram_20001edc;
    }
    uVar4 = uVar2 + iVar1 >> 5;
    if (DAT_ram_20001ece <= uVar4) {
      do {
        FUN_ram_200016d4();
        uVar3 = (uint)DAT_ram_20001ece;
        DAT_ram_20001edc = uVar3 * 0x20 + DAT_ram_20001edc;
        uVar4 = uVar4 - uVar3;
        if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < DAT_ram_20001edc)) {
          DAT_ram_20001edc = DAT_ram_20001edc + 0x57400000;
        }
      } while (uVar3 <= uVar4);
    }
    uVar4 = uVar4 << 5 | uVar2 + iVar1 & 0x1f;
  }
  return uVar4;
}

