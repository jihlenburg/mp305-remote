/* Address: 0001a3b0; name: FUN_0001a3b0; body bytes: 766 */

void FUN_0001a3b0(int param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  
  cVar2 = DAT_1fff9b9a;
  FUN_0001978c(param_1);
  iVar3 = FUN_00018ccc(0);
  bVar1 = DAT_1fff9b95;
  if (iVar3 != 0) {
    if (cVar2 == '\0') {
      if (DAT_1fffaa4a != '\0') {
        return;
      }
    }
    else if (cVar2 == '\x01') {
      if ((DAT_1fffaa21 != 0) &&
         (((DAT_1fffaa4f == '\0' || (17999 < DAT_1fff9bb0)) && (DAT_1fffaa2a == DAT_1fff9b95)))) {
        uVar4 = ((uint)DAT_1fffa9e0 * (uint)DAT_1fffaa20) / 100;
        DAT_1fffa9de = (undefined2)uVar4;
        if ((uVar4 & 0xffff) < 300) {
          DAT_1fffa9de = 300;
        }
        FUN_00019046(0,DAT_1fffa9de);
        if (DAT_1ffe0200 + param_1 < 100) {
          DAT_1ffe0200 = DAT_1ffe0200 + param_1;
          return;
        }
        DAT_1ffe0200 = 0;
        uVar7 = 10000;
        uVar8 = (uint)DAT_1fffa9ee;
        uVar4 = (uint)((short)(ushort)DAT_1fffaa21 * 5000) / 100 + uVar8 & 0xffff;
        if (((DAT_1fffa0ba < 100) && (DAT_1fffa9d6 <= DAT_1fffa9d8)) &&
           ((DAT_1fffa9d8 < 0x3e9 && (DAT_1fffaa50 == '\0')))) {
          if (uVar8 < 500) {
            uVar8 = 500;
          }
          if (uVar8 < uVar4) {
            uVar4 = uVar8;
          }
        }
        if ((DAT_1fff9bb0 * 0x5a) / 100 < DAT_1fffa990) {
          uVar7 = (DAT_1fffa990 * 1000) / DAT_1fffa9a4 & 0xffff;
        }
        if (uVar7 < uVar4) {
          uVar4 = uVar7;
        }
        if (uVar4 < 300) {
          uVar4 = 300;
        }
        if ((uVar4 + 100 < (uint)DAT_1fffa9cc) || (DAT_1fffa9cc + 100 < uVar4)) {
          DAT_1fffa9cc = (ushort)uVar4;
        }
        if (DAT_1fffa9d4 == DAT_1fffa9cc) {
          return;
        }
        if (DAT_1fffa9d4 < DAT_1fffa9cc) {
          DAT_1fffa9d4 = DAT_1fffa9d4 + 100;
        }
        if (DAT_1fffa9cc < DAT_1fffa9d4) {
          DAT_1fffa9d4 = DAT_1fffa9cc;
        }
        FUN_00018ffc(0,DAT_1fffa9d4);
        return;
      }
    }
    else {
      if (cVar2 != '\x02') {
        return;
      }
      if (DAT_1fffaa22 != '\0') {
        uVar4 = FUN_00018df6(0);
        if (uVar4 != DAT_1fff9b58) {
          FUN_00019086(0);
        }
        uVar4 = FUN_00018d68(0);
        if (uVar4 != DAT_1fff9b5c) {
          FUN_00019046(0);
          return;
        }
        return;
      }
    }
    FUN_00018c52(0);
    if ((DAT_1fffaa54 == '\x03') && (DAT_1fffaa4f == '\0')) {
      FUN_00019156(0);
      FUN_00018a40(1);
      FUN_0001d958();
      FUN_00018a40(0);
    }
    DAT_1ffe01fc = 0;
    DAT_1ffe0200 = 0;
    DAT_1fffaa2a = 0;
    return;
  }
  uVar4 = (uint)DAT_1fff9b95;
  DAT_1ffe0200 = 0;
  DAT_1fffaa2a = 0;
  if (cVar2 != '\0') {
    iVar3 = FUN_00018ee0(0);
    if (iVar3 == 0) {
      FUN_00018e00(0);
    }
    if (cVar2 == '\x01') {
      if ((((DAT_1fffaa21 != 0) && (DAT_1fff9bb0 != 0)) && (DAT_1fff9bb4 == uVar4)) &&
         ((DAT_1fffaa4f == '\0' || (17999 < DAT_1fff9bb0)))) {
        uVar8 = (uint)DAT_1fffa9e4;
        uVar7 = (uint)(ushort)(&DAT_1fff9b70)[uVar4];
        if (uVar8 + 500 <= (uint)(ushort)(&DAT_1fff9b60)[uVar4]) {
          DAT_1ffe01fc = 0;
          return;
        }
        if (uVar8 < 0x1195) {
          DAT_1ffe01fc = 0;
          return;
        }
        DAT_1ffe01fc = DAT_1ffe01fc + param_1;
        if (999 < DAT_1ffe01fc) {
          uVar8 = uVar8 - 1000;
          if (uVar7 == 0) {
            uVar7 = 500;
          }
          if (uVar8 < 0x1194) {
            uVar8 = 0x1194;
          }
          uVar4 = (uVar7 * 0x5a) / 100;
          DAT_1fffa9d4 = 500;
          DAT_1fffa9e0 = (ushort)uVar4;
          DAT_1fffa9de = 500;
          if ((uVar4 & 0xffff) < 500) {
            DAT_1fffa9de = DAT_1fffa9e0;
          }
          FUN_00018e00(0);
          FUN_00018eea(0,uVar8 & 0xffff,DAT_1fffa9de,DAT_1fffa9d4);
          FUN_00018c74(0);
          DAT_1ffe01fc = 0;
          DAT_1fffaa2a = bVar1;
          return;
        }
        return;
      }
    }
    else if ((cVar2 == '\x02') && (DAT_1fffaa22 != '\0')) {
      if (0x157c < DAT_1fff9b58) {
        DAT_1fff9b58 = 5000;
      }
      if (5000 < DAT_1fff9b5c) {
        DAT_1fff9b5c = 0xce4;
      }
      FUN_00018e00(0);
      uVar9 = 1000;
      uVar6 = DAT_1fff9b5c;
      uVar5 = DAT_1fff9b58;
      goto LAB_0001a5d8;
    }
  }
  if (DAT_1fffaa4a == '\0') {
    DAT_1ffe01fc = 0;
    return;
  }
  FUN_00018e00(0);
  uVar9 = 2000;
  uVar6 = 1000;
  uVar5 = 5000;
LAB_0001a5d8:
  FUN_00018f48(0,uVar5,uVar6,uVar9);
  FUN_00018c74(0);
  DAT_1ffe01fc = 0;
  return;
}

