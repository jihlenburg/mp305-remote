/* Address: 000571b0; name: FUN_000571b0; body bytes: 62 */

void FUN_000571b0(uint param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0259 = 0xff;
  }
  else if (DAT_1ffe0259 != param_1) {
    DAT_1ffe0259 = (byte)param_1;
    uVar1 = FUN_0004b9de(DAT_1ffe03ac,2);
    if (param_1 == 1) {
      puVar2 = &DAT_0007fb50;
    }
    else if (param_1 == 2) {
      puVar2 = &DAT_0007f500;
    }
    else {
      puVar2 = (undefined *)0x0;
    }
    FUN_00047d8e(uVar1,puVar2);
    return;
  }
  return;
}

