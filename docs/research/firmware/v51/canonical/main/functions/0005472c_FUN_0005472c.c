/* Address: 0005472c; name: FUN_0005472c; body bytes: 212 */

void FUN_0005472c(uint param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar2 = DAT_1ffe02e4;
  uVar4 = (uint)(byte)(DAT_1ffe0268 + 1);
  if (7 < uVar4) {
    uVar4 = 0;
  }
  if (param_1 >> 9 == 0) {
    DAT_1ffe02e4 = 0;
    DAT_1ffe0268 = 8;
  }
  else if ((((DAT_1ffe0330 != DAT_1ffe0468) && (DAT_1ffe0248 == '\0')) &&
           (iVar1 = FUN_00040928(), iVar1 == DAT_1ffe0344)) && (DAT_1ffe0620 != 0)) {
    uVar2 = uVar2 >> uVar4;
    for (uVar6 = (param_1 >> 9) >> uVar4;
        (uVar5 = 8, uVar4 < 8 && (uVar5 = uVar4, (uVar6 & ~uVar2 & 1) == 0)); uVar6 = uVar6 >> 1) {
      if ((uVar2 & ~uVar6 & 1) != 0) {
        DAT_1ffe02e4 = DAT_1ffe02e4 & ~(1 << uVar4);
      }
      uVar2 = uVar2 >> 1;
      uVar4 = uVar4 + 1 & 0xff;
    }
    if (DAT_1ffe0268 == uVar5) {
      if (uVar5 < 8) {
        return;
      }
    }
    else if (uVar5 < 8) {
      if (DAT_1ffe0330 != 0) {
        FUN_0001ba58();
        return;
      }
      DAT_1ffe02e4 = 1 << uVar5 | DAT_1ffe02e4;
      DAT_1ffe0268 = (byte)uVar5;
      uVar3 = FUN_00016060(uVar5 + 9 & 0xff);
      FUN_0001d100(1,uVar3);
      return;
    }
    DAT_1ffe0268 = 8;
  }
  return;
}

