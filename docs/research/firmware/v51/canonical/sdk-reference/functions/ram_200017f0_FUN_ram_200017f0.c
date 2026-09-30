/* Address: ram:200017f0; name: FUN_ram_200017f0; body bytes: 154 */

void FUN_ram_200017f0(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  gp = 0x20004000;
  uVar2 = (*DAT_ram_20001c00)();
  if (DAT_ram_20001edc != uVar2) {
    if ((DAT_ram_20001bd2 < '\0') || (DAT_ram_20001edc <= uVar2)) {
      iVar1 = -DAT_ram_20001edc;
    }
    else {
      iVar1 = -0x57400000 - DAT_ram_20001edc;
    }
    uVar2 = uVar2 + iVar1 >> 5;
    if (DAT_ram_20001ece <= uVar2) {
      do {
        FUN_ram_200016d4();
        uVar3 = (uint)DAT_ram_20001ece;
        DAT_ram_20001edc = DAT_ram_20001edc + uVar3 * 0x20;
        uVar2 = uVar2 - uVar3;
      } while (uVar3 <= uVar2);
      FUN_ram_00062784(DAT_ram_20001eb5,0);
      return;
    }
  }
  return;
}

