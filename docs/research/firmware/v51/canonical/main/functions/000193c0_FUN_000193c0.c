/* Address: 000193c0; name: FUN_000193c0; body bytes: 846 */

void FUN_000193c0(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  iVar2 = FUN_00018ee0(0);
  if (iVar2 == 0) {
    return;
  }
  uVar6 = (uint)DAT_1fffa9d8;
  if (((uVar6 < 0x3e9) && (0 < DAT_1fffa998)) &&
     (DAT_1fffa12c = ((DAT_1fffa998 * DAT_1fffa9a4 + 500) / 1000) * param_1 + DAT_1fffa12c,
     3600000000 < DAT_1fffa12c)) {
    DAT_1fffa128 = DAT_1fffa12c / 3600000000 + DAT_1fffa128;
    DAT_1fffa12c = DAT_1fffa12c % 3600000000;
  }
  if (DAT_1ffe01ec + param_1 < 500) {
    DAT_1ffe01ec = DAT_1ffe01ec + param_1;
    return;
  }
  uVar7 = (uint)DAT_1fffa9dc;
  DAT_1ffe01ec = 0;
  DAT_1fffa9a8 = DAT_1fffa9a4 + ((int)(DAT_1fffa998 + ((uint)(DAT_1fffa998 >> 0x1f) >> 0x1d)) >> 3);
  uVar3 = FUN_0001a258((DAT_1fffa9a8 & 0x3ffff) >> 2);
  DAT_1fffa9da = (ushort)uVar3;
  uVar1 = DAT_1fffa9d8;
  if ((((0x32 < DAT_1fffa9d8) || (uVar3 < 500)) ||
      (DAT_1ffe01d5 = DAT_1ffe01d5 + 1, uVar1 = DAT_1fffa9da, 0x23 < DAT_1ffe01d5)) &&
     (DAT_1fffa9d8 = uVar1, DAT_1ffe01d5 = 0, 1000 < DAT_1fffa9d8)) {
    iVar2 = FUN_0001bc68(0);
    if (((iVar2 == 0) || (DAT_1fffa9ea < 0x191)) || (DAT_1fffaa50 != '\0')) {
      DAT_1ffe01d4 = 0;
      return;
    }
    if ((byte)(DAT_1ffe01d4 + 1) < 3) {
      DAT_1ffe01d4 = DAT_1ffe01d4 + 1;
      return;
    }
    DAT_1ffe01d4 = '\0';
    DAT_1fffa9d8 = DAT_1fffa9da;
    DAT_1fffa994 = 0;
  }
  if (DAT_1fffa9a8 < 0x2a30) {
    DAT_1ffe01f0 = DAT_1ffe01f0 + 500;
    if (2999 < DAT_1ffe01f0) {
      DAT_1ffe01f0 = 0;
      DAT_1fffa9d8 = 0;
    }
  }
  else {
    DAT_1ffe01f0 = 0;
  }
  iVar2 = FUN_0001bc68(0);
  if ((((iVar2 == 0) || (-1 < DAT_1fffa998)) || (DAT_1fffa998 < -799)) ||
     ((DAT_1fffa9da < 1000 || (999 < DAT_1fffa9d8)))) {
    iVar2 = FUN_0001bc68(0);
    if ((((iVar2 == 0) || ((-1 < DAT_1fffa998 || (DAT_1fffa998 < -499)))) || (999 < DAT_1fffa9da))
       || (((999 < DAT_1fffa9d8 || (DAT_1fffa9a4 < 0x4075)) || (DAT_1fffa9e4 < 0x1f41)))) {
      if (((DAT_1fffa998 < 0x33) || (DAT_1fffa9da != 0)) || (DAT_1fffa9d8 == 0)) {
        if ((DAT_1fffa998 - 1U < 100) && (DAT_1fffa9da + 0x32 < (uint)DAT_1fffa9d8)) {
          DAT_1fffa994 = DAT_1fffa994 + 0xfa;
        }
        else {
          DAT_1fffa994 = DAT_1fffa998 + DAT_1fffa994;
        }
      }
      else {
        DAT_1fffa994 = DAT_1fffa994 + 0x1d4c;
      }
    }
    else {
      DAT_1fffa994 = DAT_1fffa994 + -16000;
    }
    if (DAT_1fffa994 < -15999) goto LAB_00019586;
    if (DAT_1fffa994 < 15000) goto LAB_00019616;
    if (DAT_1fffa9d8 <= DAT_1fffa9da) {
      DAT_1fffa994 = 15000;
      goto LAB_00019616;
    }
    DAT_1fffa994 = DAT_1fffa994 + -15000;
    if (DAT_1fffa9d8 != 0) {
      DAT_1fffa9d8 = DAT_1fffa9d8 - 1;
      goto LAB_00019616;
    }
LAB_0001967c:
    if (DAT_1fffa994 < 1) goto LAB_0001962a;
  }
  else {
    DAT_1fffa994 = -16000;
LAB_00019586:
    if (((DAT_1fffa9d8 < DAT_1fffa9da) ||
        (((DAT_1fffa998 + 499U < 499 && (0x4074 < DAT_1fffa9a4)) && (8000 < DAT_1fffa9e4)))) &&
       (((-0x2bd < DAT_1fffa998 || (DAT_1fffa9d8 < 0x3e2)) && (iVar2 = FUN_0001bc68(0), iVar2 != 0))
       )) {
      if (DAT_1fffa9d8 < 0x3e2) {
        DAT_1fffa994 = DAT_1fffa994 + 16000;
        if (DAT_1fffa9d8 < 1000) {
          DAT_1fffa9d8 = DAT_1fffa9d8 + 1;
          goto LAB_00019616;
        }
        goto LAB_0001961c;
      }
      DAT_1fffa9d8 = 1000;
    }
    else {
      DAT_1fffa994 = -16000;
LAB_00019616:
      if (DAT_1fffa9d8 == 0) goto LAB_0001967c;
LAB_0001961c:
      if (DAT_1fffa9d8 != 1000) goto LAB_0001962a;
    }
    if (-1 < DAT_1fffa994) goto LAB_0001962a;
  }
  DAT_1fffa994 = 0;
LAB_0001962a:
  uVar3 = (uint)DAT_1fffa9d8;
  uVar4 = (uVar3 + 5) / 10;
  uVar5 = uVar4 & 0xff;
  DAT_1fffaa23 = (undefined1)uVar4;
  if (uVar6 < uVar3) {
    DAT_1fffa124 = DAT_1fffa124 + 1;
  }
  DAT_1fffa9dc = (ushort)(DAT_1fffa124 / 1000);
  if (uVar7 < (DAT_1fffa124 / 1000 & 0xffff)) {
    DAT_1fffa0d2 = DAT_1fffa0d2 + 1;
  }
  if ((uVar5 < 100) && (uVar3 < DAT_1fffa9d6)) {
    if (uVar5 < DAT_1fffa9d6 / 10) {
      DAT_1ffe01d6 = '\0';
    }
  }
  else if (DAT_1ffe01d6 == '\0') {
    DAT_1ffe01d6 = '\x01';
  }
  if ((DAT_1fffaa54 == '\x03') &&
     (((1000 < DAT_1fffa0d0 || (DAT_1fffa0d0 + 0x32 <= uVar3)) || (DAT_1ffe01d6 == '\x01')))) {
    FUN_00018a40(1);
    FUN_0001d958();
    FUN_00018a40(0);
    if (DAT_1ffe01d6 == '\x01') {
      DAT_1ffe01d6 = '\x02';
    }
  }
  if (((0 < DAT_1fffa998) && (DAT_1fffa9d8 < 0xc9)) &&
     ((int)(uint)DAT_1fffa9d8 <= (int)(DAT_1fffa0d0 - 0x32))) {
    FUN_0001d958();
  }
  if (DAT_1fffa9a0 == 0) {
    DAT_1fffa9b0 = 0xffffffff;
  }
  else {
    DAT_1fffa9b0 = ((uint)DAT_1fffa9d8 * 0x37ee2) / DAT_1fffa9a0;
  }
  return;
}

