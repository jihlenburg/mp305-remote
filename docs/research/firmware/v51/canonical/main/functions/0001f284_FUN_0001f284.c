/* Address: 0001f284; name: FUN_0001f284; body bytes: 102 */

void FUN_0001f284(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = DAT_1fffa950 * 100;
  iVar1 = iVar3 - DAT_1fffa960;
  iVar2 = iVar1;
  if (iVar1 < 1) {
    iVar2 = -iVar1;
  }
  if (iVar2 < 0x1f) {
    return;
  }
  iVar2 = DAT_1fffa958 + ((int)(iVar1 + ((uint)(iVar1 >> 0x1f) >> 0x1d)) >> 3);
  iVar1 = (DAT_1fffa950 * 200) / 100;
  if (iVar1 < 1000) {
    iVar1 = 1000;
  }
  if (DAT_1fffa960 < iVar3) {
    iVar4 = iVar3 + iVar1;
    if (DAT_1fffa960 < iVar3 - iVar1) {
      iVar4 = iVar3;
    }
    if (iVar4 < iVar2) {
      iVar2 = iVar4;
    }
  }
  else {
    iVar4 = iVar3 - iVar1;
    if (iVar3 + iVar1 < DAT_1fffa960) {
      iVar4 = iVar3;
    }
    if (iVar2 < iVar4) {
      iVar2 = iVar4;
    }
  }
  FUN_0001f548(iVar2);
  return;
}

