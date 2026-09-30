/* Address: 00019f18; name: FUN_00019f18; body bytes: 590 */

void FUN_00019f18(void)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  
  if (DAT_1fffaa54 < 6) {
    return;
  }
  FUN_00019f4c();
  uVar2 = DAT_1fffa964;
  if ((DAT_1fffaa1e != 0) || (DAT_1fffaa30 == '\0')) {
    DAT_1fffaa30 = 0;
    DAT_1fffa950 = 0;
    DAT_1fffa954 = 0;
    DAT_1fffaa40 = 0;
    DAT_1fffaa3c = 0;
    if (DAT_1fffaa2f != '\0') {
      FUN_00019e0c();
      FUN_00016c56(1);
      FUN_000658d4(400);
      FUN_00016c56(0);
    }
    bVar7 = DAT_1fffaa37 == '\x02';
    if (bVar7) {
      FUN_000144a8(0);
    }
    else {
      FUN_000144a8(0);
    }
    FUN_00014494(!bVar7);
    FUN_0001f23c(0);
    if ((DAT_1fffa950 * 10 < 0x14) && ((int)DAT_1fffa964 < 0x32)) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
    FUN_00016c56(uVar3);
    return;
  }
  iVar4 = DAT_1fffa950 * 10;
  iVar1 = DAT_1fffa968 + 500;
  if (DAT_1fffaa2f == '\0') {
    DAT_1fffa958 = DAT_1fffa960;
    DAT_1fffaa2f = '\x01';
    FUN_00018c74();
    FUN_00019e44();
  }
  if (iVar4 + 100 < (int)uVar2) {
    iVar4 = FUN_000154a0();
    if ((iVar4 != 0) && (iVar1 / 1000 < 100)) {
      DAT_1fffaa38 = DAT_1fffaa38 + 1;
      if (DAT_1fffaa38 == 10) {
        FUN_00016c56(1);
        DAT_1fffa984 = uVar2;
      }
      else if (10 < DAT_1fffaa38) {
        FUN_00016c56(0);
        if (uVar2 < DAT_1fffa984) {
          uVar2 = DAT_1fffa984 - uVar2;
        }
        else {
          uVar2 = uVar2 - DAT_1fffa984;
        }
        if (uVar2 < 0x65) {
          DAT_1fffaa40 = '\x03';
        }
        else {
          DAT_1fffaa38 = 9;
        }
      }
    }
  }
  else {
    DAT_1fffaa38 = 0;
    if (DAT_1fffaa37 == '\x02') {
      FUN_000144a8(0);
      FUN_0001f23c(DAT_1fff9b9b != '\0');
    }
    else {
      FUN_000144a8(1);
    }
    if (DAT_1fffaa40 == '\x03') {
      DAT_1fffaa40 = '\0';
    }
    if ((iVar4 < 0x14) && ((int)uVar2 < 0x32)) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
    FUN_00016c56(uVar3);
  }
  uVar2 = DAT_1fffa964;
  iVar5 = (DAT_1fffa968 + 500) / 1000;
  iVar6 = DAT_1fffa950 * 100;
  iVar4 = DAT_1fffa954 * 100;
  iVar1 = FUN_000154a0();
  if (iVar1 == 0) {
    if ((DAT_1fffaa40 != '\x03') &&
       (bVar7 = 10 < DAT_1fffaa3c, DAT_1fffaa3c = DAT_1fffaa3c + 1, bVar7)) {
      DAT_1fffaa40 = '\x02';
      DAT_1fffaa3c = 10;
    }
  }
  else if ((DAT_1fffaa40 != '\x03') &&
          (bVar7 = DAT_1fffaa3c < 0xfffffff6, DAT_1fffaa3c = DAT_1fffaa3c - 1, bVar7)) {
    DAT_1fffaa40 = '\x01';
    DAT_1fffaa3c = 0xfffffff6;
  }
  FUN_00014080();
  FUN_0001f284();
  if ((int)uVar2 < 0x5dc) {
    if (2000 < iVar5) {
      if (DAT_1fffa93c < 0x3e9) {
        DAT_1ffe0218 = iVar6;
        DAT_1ffe021c = iVar4;
        return;
      }
      DAT_1fffa93c = DAT_1fffa93c - 2;
      goto LAB_00019cd2;
    }
    if (0x79d < iVar5) {
      DAT_1ffe0218 = iVar6;
      DAT_1ffe021c = iVar4;
      return;
    }
  }
  else if ((int)uVar2 < 0x641) {
    DAT_1ffe0218 = iVar6;
    DAT_1ffe021c = iVar4;
    return;
  }
  if (0x5db < DAT_1fffa93c) {
    DAT_1ffe0218 = iVar6;
    DAT_1ffe021c = iVar4;
    return;
  }
  DAT_1fffa93c = DAT_1fffa93c + 2;
LAB_00019cd2:
  FUN_00019116(1);
  DAT_1ffe0218 = iVar6;
  DAT_1ffe021c = iVar4;
  return;
}

