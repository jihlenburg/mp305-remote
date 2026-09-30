/* Address: 0003b010; name: FUN_0003b010; body bytes: 66 */

int FUN_0003b010(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00015a14();
  iVar2 = FUN_00015b54();
  if ((DAT_1ffe0128 == '\0') && (DAT_1fffaad4 == '\0')) {
    if (iVar1 == 0) {
      if (iVar2 == 0) {
        return 0;
      }
      if (DAT_1fffab1b == '\0') {
        return iVar2;
      }
    }
    else if (DAT_1fffab1b == '\0') {
      return iVar1;
    }
    DAT_1fffab88 = 0;
    DAT_1fffab8c = 0;
    DAT_1fffab90 = 0;
  }
  return 0;
}

