/* Address: 00056e3c; name: FUN_00056e3c; body bytes: 212 */

void FUN_00056e3c(void)

{
  int iVar1;
  
  if (DAT_1fffaaed != '\0') {
    DAT_1fffaaed = '\0';
    DAT_1fffab48 = 0;
    DAT_1fffa408 = DAT_1fffaaf0;
    if (DAT_1ffe04f4 != 0) {
      if ((&DAT_1fffa3f4)[DAT_1fffaaf0] == '\0') {
        FUN_0004aa6e(DAT_1ffe04fc,1);
        FUN_0004e00e(DAT_1ffe0500,1);
        DAT_1fffab84 = 0;
      }
      else {
        FUN_0004aa6e(DAT_1ffe0500,1);
        FUN_0004e00e(DAT_1ffe04fc,1);
        FUN_0002f0f4(DAT_1ffe04fc);
      }
      if (DAT_1ffe0241 == '\0') {
        if (DAT_1ffe04f4 != 0) {
          iVar1 = FUN_0004cd1e();
          if (((iVar1 == 0) && (iVar1 = FUN_0004cd1e(DAT_1ffe0540), iVar1 != 0)) &&
             (DAT_1ffe0330 == 0)) {
            FUN_00017cf8();
          }
          else if (((DAT_1ffe04f4 != 0) && (iVar1 = FUN_0004cd1e(DAT_1ffe0540), iVar1 == 0)) &&
                  (DAT_1ffe0330 == 0)) {
            FUN_00017d34();
          }
        }
      }
      else {
        DAT_1ffe0241 = '\0';
        FUN_0004e5a6(DAT_1ffe0544,7,0);
      }
      if (DAT_1fffaacf != '\0') {
        DAT_1ffe0187 = 0;
        DAT_1fff9550 = DAT_1fff9550 | 0x200;
      }
    }
  }
  return;
}

