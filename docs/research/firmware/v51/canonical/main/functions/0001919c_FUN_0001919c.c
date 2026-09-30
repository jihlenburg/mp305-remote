/* Address: 0001919c; name: FUN_0001919c; body bytes: 104 */

uint FUN_0001919c(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_0001b624();
  if (iVar1 == 0) {
    if (DAT_1ffe0178 - 0x14 < 0x17c) {
      uVar2 = 0xff;
    }
    if ((DAT_1fffab1b != '\0') && (0x13 < DAT_1ffe0178)) {
      DAT_1fffab88 = 0;
      DAT_1fffab8c = 0;
      DAT_1fffab90 = 0;
    }
    DAT_1ffe016d = '\0';
  }
  else {
    if (DAT_1ffe016d != '\0') goto LAB_000191f8;
    DAT_1ffe0178 = DAT_1ffe0178 + param_1;
    uVar2 = (DAT_1ffe0178 * 100) / param_2 & 0xff;
    if (DAT_1ffe0178 < param_2) goto LAB_000191f8;
    DAT_1ffe016d = '\x01';
  }
  DAT_1ffe0178 = 0;
LAB_000191f8:
  if (DAT_1fffaaea != '\0') {
    DAT_1fffaaea = '\0';
    uVar2 = 0xff;
  }
  return uVar2;
}

