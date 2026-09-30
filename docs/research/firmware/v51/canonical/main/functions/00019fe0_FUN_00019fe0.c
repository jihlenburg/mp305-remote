/* Address: 00019fe0; name: FUN_00019fe0; body bytes: 270 */

void FUN_00019fe0(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  DAT_1ffe01f4 = DAT_1ffe01f4 + param_1;
  if (DAT_1fffaa04 < 1) {
    if (DAT_1ffe01f4 < 1000) goto LAB_0001a0d4;
    uVar1 = 0;
    DAT_1ffe01f4 = 0;
    uVar4 = 0;
    uVar5 = 0;
    uVar3 = 0;
    if ('&' < DAT_1fffaa26) {
      uVar1 = ((short)(DAT_1fffaa26 + -0x27) * 100) / 7 & 0xffff;
    }
    if ('%' < DAT_1fffaa26) {
      uVar4 = ((short)(DAT_1fffaa26 + -0x26) * 100) / 7 & 0xffff;
    }
    if (';' < DAT_1fffaa27) {
      uVar5 = ((short)(DAT_1fffaa27 + -0x3c) * 100) / 0x14 & 0xffff;
    }
    if ('8' < DAT_1fffaa27) {
      uVar3 = ((short)(DAT_1fffaa27 + -0x39) * 100) / 0x14 & 0xffff;
    }
    if (uVar1 <= uVar5) {
      uVar1 = uVar5;
    }
    if (uVar3 < uVar4) {
      uVar3 = uVar4;
    }
    if (100 < uVar1) {
      uVar1 = 100;
    }
    if (100 < uVar3) {
      uVar3 = 100;
    }
    DAT_1fffaa2b = (byte)uVar1;
    DAT_1fffaa2c = (byte)uVar3;
    if ((uint)DAT_1fffaa2d < (uVar1 & 0xff)) {
      DAT_1fffaa2d = DAT_1fffaa2b;
    }
    if ((uVar3 & 0xff) < (uint)DAT_1fffaa2d) {
      DAT_1fffaa2d = DAT_1fffaa2c;
    }
    if ((((DAT_1fffaa06 != 0) || (9999999 < DAT_1fffa974)) || (DAT_1fffaa41 != '\0')) ||
       ('*' < DAT_1fffaa26)) goto LAB_0001a0d4;
  }
  else {
    DAT_1fffaa04 = DAT_1fffaa04 - (short)param_1;
    DAT_1ffe01f4 = 0;
    if (0 < DAT_1fffaa04) {
      DAT_1fffaa2d = 0x14;
      goto LAB_0001a0d4;
    }
  }
  DAT_1ffe01f4 = 0;
  DAT_1fffaa2d = 0;
LAB_0001a0d4:
  uVar2 = FUN_0001a158(DAT_1fffaa2d);
  DAT_1fffaa06 = (short)uVar2;
  FUN_0001ceb8(&DAT_40026000,0,uVar2);
  return;
}

