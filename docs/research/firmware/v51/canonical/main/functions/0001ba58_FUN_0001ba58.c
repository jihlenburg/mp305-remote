/* Address: 0001ba58; name: FUN_0001ba58; body bytes: 94 */

void FUN_0001ba58(void)

{
  int *piVar1;
  int iVar2;
  
  if (DAT_1ffe0247 == '\0') {
    return;
  }
  if (DAT_1ffe0330 == DAT_1ffe0468) {
    piVar1 = &DAT_1ffe0474;
  }
  else if (DAT_1ffe0330 == DAT_1ffe068c) {
    piVar1 = &DAT_1ffe0698;
  }
  else if (DAT_1ffe0330 == DAT_1ffe06a0) {
    DAT_1fffab0f = 1;
    piVar1 = &DAT_1ffe06b0;
  }
  else {
    iVar2 = DAT_1ffe0330;
    if (DAT_1ffe0330 != DAT_1ffe06b4) goto LAB_0001ba84;
    piVar1 = &DAT_1ffe06c4;
  }
  iVar2 = *piVar1;
LAB_0001ba84:
  FUN_0004e5a6(iVar2,7,0);
  return;
}

