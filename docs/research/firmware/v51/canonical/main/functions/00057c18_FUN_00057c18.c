/* Address: 00057c18; name: FUN_00057c18; body bytes: 280 */

void FUN_00057c18(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 1;
  if (DAT_1ffe05b8 == 0) {
    DAT_1ffe0262 = 0xff;
  }
  else if (DAT_1ffe0262 != param_1) {
    if (DAT_1ffe0263 < 9) {
      uVar1 = FUN_0004037c(0xffff);
      uVar2 = FUN_0004b9de(DAT_1ffe05d4,DAT_1ffe0263);
      uVar2 = FUN_0004b9de(uVar2,1);
      FUN_0004ea90(uVar2,uVar1,1);
      if (DAT_1ffe0263 == 0) {
        uVar1 = 0xffff;
      }
      else {
        uVar1 = 0x999999;
      }
      uVar1 = FUN_0004037c(uVar1);
      uVar2 = FUN_0004b9de(DAT_1ffe05d4,DAT_1ffe0263);
      uVar2 = FUN_0004b9de(uVar2,1);
      FUN_0004ea90(uVar2,uVar1,0);
    }
    for (uVar3 = 0; uVar3 < DAT_1ffe0190; uVar3 = uVar3 + 1 & 0xff) {
      if (DAT_1fffaad1 != '\0') {
        if (uVar3 == 7) {
          uVar4 = 8;
        }
        if ((*(byte *)(&DAT_1fff9bc0 + uVar3) & 7) != 0) {
          if (uVar4 == param_1) {
            uVar1 = FUN_0004037c(0xffa600);
            uVar2 = FUN_0004b9de(DAT_1ffe05d4,uVar3);
            uVar2 = FUN_0004b9de(uVar2,1);
            FUN_0004ea90(uVar2,uVar1,1);
            uVar1 = FUN_0004037c(0xffa600);
            uVar2 = FUN_0004b9de(DAT_1ffe05d4,uVar3);
            uVar2 = FUN_0004b9de(uVar2,1);
            FUN_0004ea90(uVar2,uVar1,0);
            uVar1 = FUN_0004b9de(DAT_1ffe05d4,uVar3);
            FUN_0004e4b2(uVar1,0);
            DAT_1ffe0263 = (byte)uVar3;
            break;
          }
          uVar4 = uVar4 + 1 & 0xff;
        }
      }
    }
    DAT_1ffe0262 = (byte)param_1;
  }
  if (param_1 == 0xff) {
    DAT_1ffe0263 = 0xff;
  }
  return;
}

