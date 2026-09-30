/* Address: 00055854; name: FUN_00055854; body bytes: 72 */

void FUN_00055854(uint param_1)

{
  if ((((DAT_1ffe026a != param_1) && (DAT_1ffe0330 != DAT_1ffe0468)) &&
      (DAT_1ffe0330 != DAT_1ffe06a0)) && ((DAT_1ffe0330 != DAT_1ffe06b4 && (DAT_1ffe0248 == '\0'))))
  {
    if (param_1 != 0) {
      if (DAT_1ffe0247 != '\0') {
        FUN_0001ba58();
        return;
      }
      FUN_0005f8e0();
    }
    DAT_1ffe026a = (byte)param_1;
  }
  return;
}

