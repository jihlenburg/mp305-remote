/* Address: 0005553c; name: FUN_0005553c; body bytes: 198 */

void FUN_0005553c(uint param_1)

{
  byte bVar1;
  int iVar2;
  
  if (((((DAT_1ffe0269 == param_1) || (DAT_1ffe0330 == DAT_1ffe0468)) ||
       (DAT_1ffe0330 == DAT_1ffe068c)) || ((DAT_1ffe0330 == DAT_1ffe06b4 || (DAT_1ffe0248 != '\0')))
      ) || (iVar2 = FUN_00040928(0), iVar2 != DAT_1ffe0344)) {
    iVar2 = FUN_00040928(0);
    bVar1 = DAT_1ffe0269;
    if ((iVar2 != DAT_1ffe0344) && (param_1 == 2)) {
      DAT_1fff9550 = DAT_1fff9550 | 4;
      remote_granted = 0;
      remote_request = 0;
      return;
    }
  }
  else {
    bVar1 = (byte)param_1;
    if (param_1 == 2) {
      if (DAT_1ffe0247 == '\0') {
        FUN_0005f434();
        DAT_1ffe0269 = bVar1;
        return;
      }
      FUN_0001ba58();
      return;
    }
    if (param_1 == 1) {
      if (DAT_1ffe0330 == DAT_1ffe06a0) {
        DAT_1ffe0269 = bVar1;
        return;
      }
      FUN_0004e00e(DAT_1ffe03c4,1);
      DAT_1ffe0269 = bVar1;
      return;
    }
  }
  DAT_1ffe0269 = bVar1;
  if ((param_1 == 0) && (DAT_1ffe0330 == DAT_1ffe06a0)) {
    FUN_0004e5a6(DAT_1ffe06b0,7,0);
    return;
  }
  return;
}

