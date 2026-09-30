/* Address: 00015a14; name: FUN_00015a14; body bytes: 56 */

int FUN_00015a14(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_1ffe0174;
  DAT_1ffe0174 = 0;
  iVar1 = FUN_00015a00();
  if (iVar1 == 0) {
    DAT_1ffe0180 = DAT_1ffe0180 + 1;
  }
  else {
    DAT_1ffe0180 = 0;
  }
  if (iVar2 + 100 != 100) {
    return iVar2 + 100;
  }
  iVar2 = FUN_00015a00();
  if ((iVar2 == 0) && (2 < DAT_1ffe0180)) {
    return 3;
  }
  return 0;
}

