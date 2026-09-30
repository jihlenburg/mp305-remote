/* Address: 0001b058; name: FUN_0001b058; body bytes: 936 */

void FUN_0001b058(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  bool bVar8;
  
  uVar5 = 0;
  uVar1 = (uint)DAT_1ffe01db;
  iVar6 = 500;
  switch(DAT_1fffaa55) {
  case '\0':
    DAT_1ffe020c = 0;
    DAT_1ffe0210 = 0;
    DAT_1ffe01db = 0;
    FUN_00019dd4(0,0);
    FUN_00016c56(0);
    FUN_000144a8(0);
    FUN_00014494(0);
    FUN_0001f23c(0);
    if (DAT_1fffa0cf != '\0') {
      DAT_1fffa9f4 = 0;
      DAT_1fffaa55 = 2;
      DAT_1fffaa58 = 0;
      return;
    }
    DAT_1fffa9f4 = 0;
    DAT_1fffaa55 = 1;
    DAT_1fffaa58 = 0;
    return;
  case '\x01':
    if (DAT_1fffaa52 != '\0') {
      DAT_1ffe01db = 0;
      DAT_1fffa9f4 = 0;
      DAT_1fffaa55 = 2;
      return;
    }
    return;
  case '\x02':
    if ((DAT_1fffa9f4 < 100) || (uVar1 != 0)) {
      if ((199 < DAT_1fffa9f4) && (uVar1 == 1)) {
        DAT_1ffe01db = 2;
        uVar5 = FUN_00015fe0();
        uVar2 = FUN_00016004();
        FUN_0001a14c(DAT_1ffe020c,uVar5);
        FUN_0001a14c(DAT_1ffe0210,uVar2);
        if (uVar5 < 0x1f5) {
          DAT_1ffe020c = 5000;
          DAT_1ffe0210 = 100;
          FUN_00019dd4();
          break;
        }
        DAT_1fffaa58 = DAT_1fffaa58 | 4;
        goto LAB_0001b374;
      }
      if ((DAT_1fffa9f4 < 1000) || (uVar1 != 2)) {
        if (DAT_1fffa9f4 < 0x5dc) {
          return;
        }
        if (uVar1 != 3) {
          return;
        }
        DAT_1ffe01db = 0;
        uVar2 = FUN_00015fe0();
        iVar6 = FUN_00016004();
        FUN_0001a14c(DAT_1ffe020c,uVar2);
        FUN_0001a14c(DAT_1ffe0210,iVar6);
        if (iVar6 < 0xb) {
          DAT_1fffa9f4 = 0;
          DAT_1fffaa55 = 3;
          return;
        }
        DAT_1fffaa58 = DAT_1fffaa58 | 8;
        goto LAB_0001b374;
      }
      DAT_1ffe01db = 3;
      uVar2 = FUN_00015fe0();
      uVar5 = FUN_00016004();
      uVar1 = FUN_0001a14c(DAT_1ffe020c,uVar2);
      FUN_0001a14c(DAT_1ffe0210,uVar5);
      if (10 < (int)uVar5) {
        DAT_1fffaa58 = DAT_1fffaa58 | 1;
        DAT_1fffaa55 = '\a';
      }
      if (500 < uVar1) {
        DAT_1fffaa58 = DAT_1fffaa58 | 2;
        goto LAB_0001b374;
      }
      uVar2 = 0;
LAB_0001b24a:
      FUN_00016c56(uVar2);
      FUN_000144a8(1);
      FUN_00014494(1);
      uVar2 = 0;
      goto LAB_0001b2d8;
    }
    DAT_1ffe01db = 1;
    if (0x32 < DAT_1fffaa26) {
      DAT_1fffaa58 = DAT_1fffaa58 | 0x800;
      goto LAB_0001b374;
    }
    if (0x32 < DAT_1fffaa28) {
      DAT_1fffaa58 = DAT_1fffaa58 | 0x1000;
      goto LAB_0001b374;
    }
    bVar8 = 0x32 < DAT_1fffaa29;
    uVar1 = DAT_1fffaa58;
    goto LAB_0001b16a;
  case '\x03':
    bVar7 = 99 < DAT_1fffa9f4;
LAB_0001b200:
    bVar8 = false;
    if (bVar7) {
      if (uVar1 == 0) {
        DAT_1ffe01db = 1;
        uVar2 = 1;
        goto LAB_0001b24a;
      }
      bVar8 = false;
      if (199 < DAT_1fffa9f4) goto LAB_0001b20a;
    }
LAB_0001b16a:
    if (!bVar8) {
      return;
    }
    DAT_1fffaa58 = uVar1 | 0x2000;
LAB_0001b374:
    while( true ) {
      DAT_1fffaa55 = '\a';
LAB_0001b3ec:
      do {
        FUN_00019b10();
        if (DAT_1fffaa55 == '\b') {
          FUN_0001cb8c();
        }
        bVar8 = false;
        if (DAT_1fffaa55 == '\a') {
          FUN_0001cb8c();
          return;
        }
LAB_0001b3ea:
        bVar7 = false;
      } while (bVar8);
LAB_0001b30c:
      if (!bVar7) {
        return;
      }
      DAT_1ffe01db = (byte)uVar5;
      uVar2 = FUN_00015fe0();
      uVar3 = FUN_00016004();
      FUN_0001a14c(DAT_1ffe020c,uVar2);
      FUN_0001a14c(DAT_1ffe0210,uVar3);
      DAT_1fffaa4a = (byte)uVar5;
      iVar4 = FUN_0001a14c(5000,DAT_1fff9b54);
      if (iVar4 < iVar6) break;
      DAT_1fffaa58 = DAT_1fffaa58 | 0x80;
    }
    DAT_1fffaa55 = 6;
    DAT_1fffa9f4 = (short)uVar5;
    return;
  case '\x04':
    if ((DAT_1fffa9f4 < 100) || (uVar1 != 0)) {
      bVar7 = 1999 < DAT_1fffa9f4;
      if (!bVar7) goto LAB_0001b200;
      if (uVar1 == 1) {
        DAT_1ffe01db = 0;
        uVar2 = FUN_00015fe0();
        uVar3 = FUN_00016004();
        FUN_0001a14c(DAT_1ffe020c,uVar2);
        FUN_0001a14c(DAT_1ffe0210,uVar3);
        iVar4 = FUN_0001a14c(DAT_1ffe020c,DAT_1fff9b56);
        if (iVar4 < 500) {
          if (DAT_1fff9b9a == '\0') {
            DAT_1fffa9f4 = 0;
            DAT_1fffaa55 = 5;
            return;
          }
          goto LAB_0001b2ea;
        }
        DAT_1fffaa58 = DAT_1fffaa58 | 0x40;
        goto LAB_0001b374;
      }
LAB_0001b20a:
      if (uVar1 != 1) {
        return;
      }
      DAT_1ffe01db = 0;
      iVar6 = FUN_00015fe0();
      iVar4 = FUN_00016004();
      FUN_0001a14c(DAT_1ffe020c,iVar6);
      FUN_0001a14c(DAT_1ffe0210,iVar4);
      if (iVar4 < 0xb) {
        DAT_1fffaa58 = DAT_1fffaa58 | 0x10;
      }
      else {
        if (DAT_1fff9b56 < 1000) {
          DAT_1fffa9f4 = 0;
          DAT_1fffaa55 = 4;
          return;
        }
        DAT_1fffaa58 = DAT_1fffaa58 | 0x20;
      }
      goto LAB_0001b374;
    }
    DAT_1ffe01db = 1;
    FUN_00016c56(0);
    FUN_000144a8(0);
    FUN_00014494(0);
    uVar2 = 1;
LAB_0001b2d8:
    FUN_0001f23c(uVar2);
    break;
  case '\x05':
    if (DAT_1fffa9f4 < 100) {
      return;
    }
    if (uVar1 != 0) {
      if (1999 < DAT_1fffa9f4) {
        bVar7 = uVar1 == 1;
        goto LAB_0001b30c;
      }
      return;
    }
    uVar5 = 1;
    DAT_1ffe01db = 1;
    FUN_00016c56(0);
    FUN_000144a8(0);
    FUN_00014494(0);
    FUN_0001f23c(0);
    DAT_1fffaa4a = 1;
    break;
  case '\x06':
    if ((99 < DAT_1fffa9f4) && (uVar1 == 0)) {
      DAT_1ffe01db = 1;
      FUN_00016c56(0);
      FUN_000144a8(0);
      FUN_00014494(0);
      FUN_0001f23c(0);
      DAT_1fffaa04 = 0;
    }
    if (499 < DAT_1fffa9f4) {
      if (DAT_1ffe01db == 1) {
        DAT_1ffe01db = 2;
        DAT_1ffe01de = FUN_00018d1a(1);
        DAT_1fffaa04 = 2000;
      }
      else if ((1999 < DAT_1fffa9f4) && (DAT_1ffe01db == 2)) {
        DAT_1ffe01db = 0;
        DAT_1ffe01e0 = FUN_00018d1a(1);
        DAT_1fffaa04 = 0;
LAB_0001b2ea:
        DAT_1fffa9f4 = 0;
        DAT_1fffaa55 = '\b';
        goto LAB_0001b3ec;
      }
    }
    break;
  case '\a':
  case '\b':
    DAT_1ffe01db = 0;
  }
  if (DAT_1fffaa55 == '\b') goto LAB_0001b3ec;
  bVar8 = DAT_1fffaa55 == '\a';
  goto LAB_0001b3ea;
}

