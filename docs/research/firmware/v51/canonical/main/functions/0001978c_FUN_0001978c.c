/* Address: 0001978c; name: FUN_0001978c; body bytes: 700 */

void FUN_0001978c(int param_1)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  
  bVar5 = 10;
  if (DAT_1fffaa27 < 'U') {
    if (DAT_1fffaa20 == '\0') {
      if (DAT_1fffaa27 < 'K') {
        DAT_1fffaa20 = '\n';
        DAT_1fffaa1e = DAT_1fffaa1e & 0xffef;
      }
    }
    else if (DAT_1fffaa27 < 'F') {
      DAT_1fffaa20 = 'd';
    }
    else {
      iVar2 = (short)(0x55 - DAT_1fffaa27) * 100;
      DAT_1fffaa20 = (char)(iVar2 + ((uint)(iVar2 >> 0x1f) >> 0x1c) >> 4);
    }
  }
  else {
    DAT_1fffaa20 = '\0';
    DAT_1fffaa1e = DAT_1fffaa1e | 0x10;
  }
  uVar4 = (uint)DAT_1fffa9d8;
  uVar3 = (uint)DAT_1fffa9d6;
  if ((((uVar4 < 0x3e9) && (uVar3 < 1000)) && (uVar3 + 3 <= uVar4)) && (DAT_1fffaa50 == '\0')) {
    DAT_1ffe01f8 = DAT_1ffe01f8 + param_1;
    if (29999 < DAT_1ffe01f8) {
      DAT_1fffaa25 = '\x01';
      goto LAB_0001982e;
    }
  }
  else {
    if (DAT_1fffaa25 != '\0') {
      if ((uVar3 < 1000) && (uVar3 <= uVar4)) goto LAB_00019830;
      DAT_1fffaa25 = '\0';
    }
LAB_0001982e:
    DAT_1ffe01f8 = 0;
  }
LAB_00019830:
  if ((((char)DAT_1fffaa26 < '-') && (-2 < (char)DAT_1fffaa26)) &&
     ((DAT_1fffaa20 != '\0' && (DAT_1fffaa25 == '\0')))) {
    if (DAT_1fffaa21 == 0) {
      if (DAT_1fffaa26 < 0x2a) goto LAB_00019890;
    }
    else {
      if ((char)DAT_1fffaa26 < '+') {
        DAT_1fffaa21 = 100;
      }
      else {
        DAT_1fffaa21 = (byte)(((short)(0x2d - (char)DAT_1fffaa26) * 100) / 3);
      }
      if ((DAT_1fffa9a4 < 9000) && (10 < DAT_1fffaa21)) {
        DAT_1fffaa21 = 10;
      }
      if (((char)DAT_1fffaa26 < '\x10') && (0x14 < DAT_1fffaa21)) {
        bVar5 = 0x14;
LAB_00019890:
        DAT_1fffaa21 = bVar5;
      }
    }
  }
  else {
    DAT_1fffaa21 = 0;
  }
  if (DAT_1fffa9c8 < 0x1f5) {
    if ((DAT_1fffaa1e & 1) != 0) {
      if (99 < DAT_1fffa9c8) goto LAB_00019912;
      uVar3 = (uint)DAT_1fffa9ca;
      DAT_1fffa9ca = (ushort)(uVar3 + param_1);
      if (1000 < (uVar3 + param_1 & 0xffff)) {
        DAT_1fffaa1e = DAT_1fffaa1e & 0xfffe;
      }
    }
  }
  else {
    DAT_1fffaa1e = DAT_1fffaa1e | 1;
LAB_00019912:
    DAT_1fffa9ca = 0;
  }
  sVar1 = (short)param_1;
  if (DAT_1fffaa40 == '\x01') {
    uVar3 = (uint)DAT_1fffa9c4;
    if (uVar3 < DAT_1fffa964) {
      uVar3 = DAT_1fffa964 - uVar3;
    }
    else {
      uVar3 = uVar3 - DAT_1fffa964;
    }
    if (uVar3 < 5000) goto LAB_0001994c;
    if (DAT_1fffa9c6 < 500) {
      DAT_1fffa9c6 = DAT_1fffa9c6 + sVar1;
    }
    else {
      DAT_1fffaa1e = DAT_1fffaa1e | 0x100;
    }
  }
  else {
LAB_0001994c:
    DAT_1fffa9c6 = 0;
  }
  if (DAT_1fffa964 < 0x80e9) {
    if (0 < DAT_1fffaa16) {
      sVar1 = -sVar1;
      goto LAB_00019984;
    }
    DAT_1fffaa1e = DAT_1fffaa1e & 0xffbf;
  }
  else if (DAT_1fffaa16 < 500) {
LAB_00019984:
    DAT_1fffaa16 = sVar1 + DAT_1fffaa16;
  }
  else {
    DAT_1fffaa1e = DAT_1fffaa1e | 0x40;
  }
  if (0x10cc < DAT_1fffa9e4) {
    if ((char)DAT_1fffaa26 < '-') {
      if ((char)DAT_1fffaa26 < -1) {
        DAT_1fffaa43 = '\x01';
      }
      if ((DAT_1fffaa42 == '\0') && (DAT_1fffaa43 == '\0')) goto LAB_000199c0;
    }
    else {
      DAT_1fffaa42 = '\x01';
    }
    if (DAT_1fffaa21 == 0) goto LAB_000199c0;
  }
  DAT_1fffaa42 = '\0';
  DAT_1fffaa43 = '\0';
LAB_000199c0:
  if ('9' < (char)DAT_1fffaa26) {
    DAT_1fffaa1e = DAT_1fffaa1e | 8;
  }
  if ((char)DAT_1fffaa26 < -0x13) {
    DAT_1fffaa1e = DAT_1fffaa1e | 4;
  }
  if ((DAT_1fffaa23 == '\0') && (-1 < DAT_1fffa998)) {
    DAT_1fffaa1e = DAT_1fffaa1e | 2;
  }
  if (DAT_1fffaa1e != 0) {
    if ((char)DAT_1fffaa26 < '6') {
      DAT_1fffaa1e = DAT_1fffaa1e & 0xfff7;
    }
    if (-0xf < (char)DAT_1fffaa26) {
      DAT_1fffaa1e = DAT_1fffaa1e & 0xfffb;
    }
    if ((9 < uVar4) || (DAT_1fffa998 < 0)) {
      DAT_1fffaa1e = DAT_1fffaa1e & 0xfffd;
    }
    if (DAT_1fffaa1e != 0) {
      DAT_1fffaa22 = 0;
      return;
    }
  }
  DAT_1fffaa22 = 100;
  return;
}

