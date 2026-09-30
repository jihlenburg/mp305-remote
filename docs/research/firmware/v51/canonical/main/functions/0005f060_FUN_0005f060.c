/* Address: 0005f060; name: FUN_0005f060; body bytes: 242 */

void FUN_0005f060(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  byte bVar4;
  
  if ((DAT_1fffab17 == '\x01') && (iVar3 = FUN_0004cd1e(DAT_1ffe0770), iVar3 != 0)) {
    FUN_0004eb0e(DAT_1ffe0770,0);
    DAT_1fffab16 = 0;
  }
  else {
    iVar3 = FUN_0004cd1e(DAT_1ffe0770);
    if (iVar3 == 0) {
      uVar1 = FUN_0004037c(0x2626);
      uVar2 = FUN_0004b9de(DAT_1ffe0770,DAT_1fffab16);
      FUN_0004e874(uVar2,uVar1,0);
      DAT_1fffab16 = DAT_1fffab16 + 1;
      if (4 < DAT_1fffab16) {
        DAT_1fffab16 = 0;
      }
      uVar1 = FUN_0004037c(0xff81);
      uVar2 = FUN_0004b9de(DAT_1ffe0770,DAT_1fffab16);
      FUN_0004e874(uVar2,uVar1,0);
    }
  }
  if (((((DAT_1fffab17 != '\0') || (iVar3 = FUN_0004cd1e(DAT_1ffe0770), iVar3 != 0)) ||
       (DAT_1fffaaf2 != '\0')) || ((DAT_1fffaaee != '\0' || (DAT_1fffaaed != '\0')))) &&
     (DAT_1fffab17 != '\x02')) {
    return;
  }
  uVar1 = FUN_00037604();
  FUN_0004eb0e(DAT_1ffe0770,uVar1);
  bVar4 = 0;
  do {
    uVar1 = FUN_0004037c(0x2626);
    uVar2 = FUN_0004b9de(DAT_1ffe0770,bVar4);
    FUN_0004e874(uVar2,uVar1,0);
    bVar4 = bVar4 + 1;
  } while (bVar4 < 5);
  DAT_1fffab16 = 0;
  return;
}

