/* Address: 00015b54; name: FUN_00015b54; body bytes: 66 */

int FUN_00015b54(void)

{
  int iVar1;
  
  iVar1 = DAT_1ffe01b0;
  DAT_1ffe01b0 = 0;
  if (DAT_1ffe0191 == '\x01') {
    DAT_1ffe01b8 = DAT_1ffe01b8 + 1;
  }
  else {
    if ((DAT_1ffe01b8 < 200) && (DAT_1ffe0191 == '\0')) {
      if (0x4b < DAT_1ffe01b8) {
        DAT_1ffe01b8 = 0;
        return 4;
      }
      if (DAT_1ffe01b8 != 0) {
        DAT_1ffe01b0 = 0;
        DAT_1ffe01b8 = 0;
        return 3;
      }
    }
    DAT_1ffe01b8 = 0;
  }
  if (iVar1 + 100 != 100) {
    return iVar1 + 100;
  }
  return 0;
}

