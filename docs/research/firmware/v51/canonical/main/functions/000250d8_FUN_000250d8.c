/* Address: 000250d8; name: FUN_000250d8; body bytes: 2902 */

void FUN_000250d8(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  float fVar7;
  char *pcVar8;
  int iVar9;
  byte bVar10;
  bool bVar11;
  undefined1 uVar12;
  char cVar13;
  undefined1 uVar14;
  char cVar15;
  char cVar16;
  undefined8 uVar17;
  undefined1 uStack_51;
  uint local_50 [3];
  
  local_50[0] = 0;
  local_50[1] = 0;
  uVar3 = FUN_0004675a();
  iVar4 = FUN_00050710(DAT_1ffe03d8);
  if ((DAT_1fffaad7 == '\0') || (DAT_1fffab04 == '\0')) {
    if ((DAT_1fffaad6 != '\0') && (DAT_1fffab03 != '\0')) {
      iVar1 = (iVar4 / 100) * 100;
      iVar9 = iVar4 / 100;
      pcVar8 = "%02d.%02d";
      goto LAB_00025136;
    }
    uVar6 = FUN_000491e8(DAT_1ffe03d4);
    FUN_0001050c(local_50,uVar6);
  }
  else {
    iVar1 = (iVar4 / 1000) * 1000;
    iVar9 = iVar4 / 1000;
    pcVar8 = "%01d.%03d";
LAB_00025136:
    FUN_00020034(local_50,pcVar8,iVar9,iVar4 - iVar1);
  }
  DAT_1ffe02b4 = 0;
  iVar4 = FUN_000104f0(uVar3,&DAT_00025504);
  bVar11 = iVar4 == 0;
  do {
    if (bVar11) {
      iVar4 = FUN_000104f0(uVar3,&DAT_00025504);
      if ((iVar4 == 0) && (iVar4 = FUN_000104e2(local_50), iVar4 != 0)) {
        iVar4 = FUN_000104e2(local_50);
        (&uStack_51)[iVar4] = 0;
        FUN_00049974(DAT_1ffe03d4);
        if (DAT_1fffaad7 != '\0') {
          bVar10 = 0;
          goto LAB_00025980;
        }
        cVar16 = true;
        if (DAT_1fffaad6 == '\0') goto LAB_00025c9c;
        bVar10 = 0;
        cVar13 = true;
        goto LAB_00025a6e;
      }
      iVar4 = FUN_000104f0(uVar3,&DAT_00025534);
      if ((iVar4 != 0) || (iVar4 = FUN_000104f0(local_50,&DAT_00025cac), iVar4 == 0))
      goto LAB_00025c9c;
      uVar17 = FUN_00020160(local_50);
      fVar7 = (float)FUN_00010b48((int)uVar17,(int)((ulonglong)uVar17 >> 0x20));
      local_50[0] = local_50[0] & 0xffffff00;
      if ((DAT_1fffab03 == '\0') && (DAT_1fffaad6 != '\0')) {
        FUN_00049974(DAT_1ffe03d4,local_50);
        uVar5 = VectorFloatToUnsigned(fVar7 * 1000.0 + 5.0,3);
        DAT_1fffab74 = (undefined2)(uVar5 / 10);
      }
      else {
        if ((DAT_1fffab04 != '\0') || (DAT_1fffaad7 == '\0')) {
          uVar2 = FUN_00050710(DAT_1ffe03d8);
          FUN_0005833c(uVar2);
          goto LAB_00025c9c;
        }
        FUN_00049974(DAT_1ffe03d4,local_50);
        uVar5 = VectorFloatToUnsigned(fVar7 * 10000.0 + 5.0,3);
        DAT_1fffab76 = (undefined2)(uVar5 / 10);
      }
      FUN_0005833c();
      FUN_000178a4();
      goto LAB_00025c9c;
    }
    iVar4 = FUN_000104f0(uVar3,&DAT_00025534);
    bVar11 = true;
  } while (iVar4 == 0);
  iVar4 = FUN_000104e2(local_50);
  if (iVar4 == 0) {
    iVar4 = FUN_000104f0(uVar3,&DAT_00025538);
    if (iVar4 == 0) {
      FUN_00020034(local_50,&DAT_0002553c);
      bVar10 = 0;
      do {
        uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
        FUN_0004e0e6(uVar3,0x80);
        uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
        uVar3 = FUN_0004b9de(uVar3,0);
        FUN_0004e0e6(uVar3,0x80);
        while( true ) {
          bVar10 = bVar10 + 1;
          if (10 < bVar10) goto LAB_00025932;
          if (bVar10 != 10) break;
          uVar3 = FUN_0004b9de(DAT_1ffe03e0,10);
          FUN_0004aaf6(uVar3,0x80);
          uVar3 = FUN_0004b9de(DAT_1ffe03e0,10);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004aaf6(uVar3,0x80);
        }
      } while( true );
    }
    uVar14 = 1;
    if (DAT_1fffaad7 == '\0') {
      cVar16 = '\x01';
      if (DAT_1fffaad6 != '\0') {
        FUN_000104b2(local_50,uVar3);
        bVar10 = 0;
        cVar13 = true;
        do {
          uVar17 = FUN_00020160(local_50);
          FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40080000);
          if ((cVar13 == '\0') || (bVar10 == 0)) {
LAB_000252bc:
            uVar17 = FUN_00020160(local_50);
            FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40080000);
            if ((cVar16 == '\0') && (cVar13 = bVar10 == 10, bVar10 < 10)) goto LAB_000252f4;
            uVar17 = FUN_00020160(local_50);
            FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0);
            if ((cVar13 != '\0') && (bVar10 < 10)) goto LAB_000252f4;
            uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            FUN_0004e0e6(uVar3,0x80);
            uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            uVar3 = FUN_0004b9de(uVar3,0);
            FUN_0004e0e6(uVar3,0x80);
          }
          else {
            cVar13 = bVar10 == 10;
            cVar16 = '\x01';
            if (9 < bVar10) goto LAB_000252bc;
LAB_000252f4:
            uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            FUN_0004aaf6(uVar3,0x80);
            uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            uVar3 = FUN_0004b9de(uVar3,0);
            FUN_0004aaf6(uVar3,0x80);
          }
          bVar10 = bVar10 + 1;
          cVar16 = 10 < bVar10;
          cVar13 = bVar10 == 0xb;
        } while (!(bool)cVar16);
      }
    }
    else {
      FUN_000104b2(local_50,uVar3);
      bVar10 = 0;
      uVar12 = true;
      do {
        uVar17 = FUN_00020160(local_50);
        FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40140000);
        if (((bool)uVar14 && !(bool)uVar12) || (9 < bVar10)) {
          uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
          FUN_0004e0e6(uVar3,0x80);
          uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004e0e6(uVar3,0x80);
        }
        else {
          uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
          FUN_0004aaf6(uVar3,0x80);
          uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004aaf6(uVar3,0x80);
        }
        bVar10 = bVar10 + 1;
        uVar14 = 10 < bVar10;
        uVar12 = bVar10 == 0xb;
      } while (!(bool)uVar14);
    }
  }
  else {
    iVar4 = FUN_000104e2(local_50);
    cVar16 = iVar4 != 0;
    if (iVar4 == 1) {
      if (DAT_1fffaad7 != '\0') {
        iVar4 = FUN_000104f0(uVar3,&DAT_00025538);
        if (iVar4 != 0) {
          FUN_000104b2(local_50,&DAT_00025538);
        }
        FUN_000104b2(local_50,uVar3);
        bVar10 = 0;
        cVar13 = '\x01';
        do {
          uVar17 = FUN_00020160(local_50);
          FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40140000);
          if (cVar16 != '\0') {
            uVar17 = FUN_00020160(local_50);
            FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40140000);
            if ((((cVar13 == '\0') || (iVar4 = FUN_000104f0(uVar3,&DAT_00025538), iVar4 != 0)) ||
                (bVar10 < 2)) || (9 < bVar10)) {
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              FUN_0004e0e6(uVar6,0x80);
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              uVar6 = FUN_0004b9de(uVar6,0);
              FUN_0004e0e6(uVar6,0x80);
              goto LAB_000253f6;
            }
          }
          do {
            uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            FUN_0004aaf6(uVar6,0x80);
            uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            uVar6 = FUN_0004b9de(uVar6,0);
            FUN_0004aaf6(uVar6,0x80);
LAB_000253f6:
            bVar10 = bVar10 + 1;
            if (10 < bVar10) goto LAB_00025932;
            cVar16 = 9 < bVar10;
            cVar13 = '\0';
          } while (bVar10 == 10);
        } while( true );
      }
      cVar16 = DAT_1fffaad6 == '\0';
      cVar13 = '\x01';
      if (!(bool)cVar16) {
        uVar17 = FUN_00020160(local_50);
        FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40080000);
        if (cVar13 == '\0') {
          iVar4 = FUN_000104f0(uVar3,&DAT_00025538);
          if (iVar4 != 0) {
            uVar17 = FUN_00020160(local_50);
            FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0);
            if (cVar16 != '\0') {
              FUN_000104b2(local_50,&DAT_00025538);
            }
          }
          FUN_000104b2(local_50,uVar3);
          bVar10 = 0;
          uVar14 = 1;
          do {
            uVar17 = FUN_00020160(local_50);
            FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x40240000);
            if (((bool)cVar13 && !(bool)uVar14) || (9 < bVar10)) {
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              FUN_0004e0e6(uVar6,0x80);
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              uVar6 = FUN_0004b9de(uVar6,0);
              FUN_0004e0e6(uVar6,0x80);
              goto LAB_000254d0;
            }
            do {
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              FUN_0004aaf6(uVar6,0x80);
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              uVar6 = FUN_0004b9de(uVar6,0);
              FUN_0004aaf6(uVar6,0x80);
LAB_000254d0:
              bVar10 = bVar10 + 1;
              if (10 < bVar10) goto LAB_00025932;
              cVar13 = 9 < bVar10;
              uVar14 = bVar10 == 10;
              if (!(bool)uVar14) break;
              uVar17 = FUN_00020160(local_50);
              FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x3ff00000);
            } while ((cVar13 == '\0') || (iVar4 = FUN_000104f0(uVar3,&DAT_00025538), iVar4 == 0));
          } while( true );
        }
        uVar17 = FUN_00020160(local_50);
        FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40080000);
        if (cVar16 != '\0') {
          iVar4 = FUN_000104f0(uVar3,&DAT_00025538);
          if ((iVar4 != 0) && (iVar4 = FUN_000104f0(uVar3,&DAT_00025964), iVar4 != 0)) {
            FUN_000104b2(local_50,&DAT_00025538);
          }
          FUN_000104b2(local_50,uVar3);
          bVar10 = 0;
          cVar16 = '\x01';
LAB_0002558e:
          uVar17 = FUN_00020160(local_50);
          FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x403e0000);
          if (cVar16 == '\0') goto LAB_000255de;
LAB_000255a2:
          uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
          FUN_0004aaf6(uVar3,0x80);
          uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004aaf6(uVar3,0x80);
          do {
            bVar10 = bVar10 + 1;
            if (10 < bVar10) goto LAB_00025932;
            cVar13 = 9 < bVar10;
            if (bVar10 == 10) {
              uVar17 = FUN_00020160(local_50);
              FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40100000);
              if (cVar13 == '\0') goto LAB_000255a2;
            }
            else {
              cVar16 = '\0';
              if (!(bool)cVar13) goto LAB_0002558e;
            }
LAB_000255de:
            uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            FUN_0004e0e6(uVar3,0x80);
            uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            uVar3 = FUN_0004b9de(uVar3,0);
            FUN_0004e0e6(uVar3,0x80);
          } while( true );
        }
        uVar17 = FUN_00020160(local_50);
        FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40080000);
        if (cVar13 == '\0') {
          iVar4 = FUN_000104f0(uVar3,&DAT_00025538);
          if (iVar4 != 0) {
            FUN_000104b2(local_50,&DAT_00025538);
          }
          FUN_000104b2(local_50,uVar3);
          bVar10 = 0;
          do {
            uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            FUN_0004e0e6(uVar3,0x80);
            uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            uVar3 = FUN_0004b9de(uVar3,0);
            FUN_0004e0e6(uVar3,0x80);
            while( true ) {
              bVar10 = bVar10 + 1;
              if (10 < bVar10) goto LAB_00025932;
              if (bVar10 != 10) break;
              uVar3 = FUN_0004b9de(DAT_1ffe03e0,10);
              FUN_0004aaf6(uVar3,0x80);
              uVar3 = FUN_0004b9de(DAT_1ffe03e0,10);
              uVar3 = FUN_0004b9de(uVar3,0);
              FUN_0004aaf6(uVar3,0x80);
            }
          } while( true );
        }
      }
    }
    else {
      uVar5 = FUN_000104e2(local_50);
      cVar16 = 1 < uVar5;
      if (uVar5 == 2) {
        if (DAT_1fffaad7 != '\0') {
          FUN_000104b2(local_50,uVar3);
          bVar10 = 0;
          do {
            iVar4 = FUN_000104f0(uVar3,&DAT_00025964);
            if (iVar4 != 0) {
              uVar17 = FUN_00020160(local_50);
              FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40140000);
              if (cVar16 == '\0') goto LAB_000256c6;
            }
            uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            FUN_0004e0e6(uVar6,0x80);
            uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            uVar6 = FUN_0004b9de(uVar6,0);
            FUN_0004e0e6(uVar6,0x80);
            while( true ) {
              bVar10 = bVar10 + 1;
              if (10 < bVar10) goto LAB_00025932;
              cVar16 = 9 < bVar10;
              if (bVar10 != 10) break;
LAB_000256c6:
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              FUN_0004aaf6(uVar6,0x80);
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              uVar6 = FUN_0004b9de(uVar6,0);
              FUN_0004aaf6(uVar6,0x80);
            }
          } while( true );
        }
        uVar14 = DAT_1fffaad6 == '\0';
        cVar16 = 1;
        if (!(bool)uVar14) {
          uVar17 = FUN_00020160(local_50);
          FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x40240000);
          if ((bool)cVar16 && !(bool)uVar14) {
            FUN_000104b2(local_50,uVar3);
            bVar10 = 0;
            do {
              uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              FUN_0004e0e6(uVar3,0x80);
              uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              uVar3 = FUN_0004b9de(uVar3,0);
              FUN_0004e0e6(uVar3,0x80);
              while( true ) {
                bVar10 = bVar10 + 1;
                if (10 < bVar10) goto LAB_00025932;
                if (bVar10 != 10) break;
                uVar3 = FUN_0004b9de(DAT_1ffe03e0,10);
                FUN_0004aaf6(uVar3,0x80);
                uVar3 = FUN_0004b9de(DAT_1ffe03e0,10);
                uVar3 = FUN_0004b9de(uVar3,0);
                FUN_0004aaf6(uVar3,0x80);
              }
            } while( true );
          }
          iVar4 = FUN_000104f0(uVar3,&DAT_00025538);
          if (iVar4 != 0) {
            FUN_000104b2(local_50,&DAT_00025538);
          }
          FUN_000104b2(local_50,uVar3);
          uVar5 = 0;
          do {
            uVar17 = FUN_00020160(local_50);
            FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x403e0000);
            if ((cVar16 != '\0') || (iVar4 = FUN_000104f0(uVar3,&DAT_00025970), iVar4 != 0)) {
              cVar16 = uVar5 - 6 == 4;
              if (3 < uVar5 - 6) {
LAB_000257be:
                uVar6 = FUN_0004b9de(DAT_1ffe03e0,uVar5);
                FUN_0004e0e6(uVar6,0x80);
                uVar6 = FUN_0004b9de(DAT_1ffe03e0,uVar5);
                uVar6 = FUN_0004b9de(uVar6,0);
                FUN_0004e0e6(uVar6,0x80);
                goto LAB_000257e0;
              }
              uVar17 = FUN_00020160(local_50);
              FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x403e0000);
              if (cVar16 == '\0') goto LAB_000257be;
            }
            do {
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,uVar5);
              FUN_0004aaf6(uVar6,0x80);
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,uVar5);
              uVar6 = FUN_0004b9de(uVar6,0);
              FUN_0004aaf6(uVar6,0x80);
LAB_000257e0:
              uVar5 = uVar5 + 1 & 0xff;
              if (10 < uVar5) goto LAB_00025932;
              cVar16 = 9 < uVar5;
            } while (uVar5 == 10);
          } while( true );
        }
      }
      else {
        uVar5 = FUN_000104e2(local_50);
        cVar16 = 2 < uVar5;
        if ((uVar5 == 3) && (DAT_1fffaad6 != '\0')) {
          FUN_000104b2(local_50,uVar3);
          bVar10 = 0;
          do {
            uVar17 = FUN_00020160(local_50);
            FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x40240000);
            if (cVar16 == '\0') goto LAB_000258be;
            uVar17 = FUN_00020160(local_50);
            FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x403e0000);
            if ((cVar16 == '\0') && (iVar4 = FUN_000104f0(uVar3,&DAT_00025970), iVar4 == 0))
            goto LAB_000258be;
            uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            FUN_0004e0e6(uVar6,0x80);
            uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
            uVar6 = FUN_0004b9de(uVar6,0);
            FUN_0004e0e6(uVar6,0x80);
            while( true ) {
              bVar10 = bVar10 + 1;
              if (10 < bVar10) goto LAB_00025932;
              cVar16 = 9 < bVar10;
              if (bVar10 != 10) break;
LAB_000258be:
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              FUN_0004aaf6(uVar6,0x80);
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              uVar6 = FUN_0004b9de(uVar6,0);
              FUN_0004aaf6(uVar6,0x80);
            }
          } while( true );
        }
        uVar5 = FUN_000104e2(local_50);
        if (uVar5 < 5) {
          iVar4 = FUN_000104e2(local_50);
          if (iVar4 == 4) {
            bVar10 = 0;
            do {
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              FUN_0004aaf6(uVar6,0x80);
              uVar6 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
              uVar6 = FUN_0004b9de(uVar6,0);
              FUN_0004aaf6(uVar6,0x80);
              bVar10 = bVar10 + 1;
            } while (bVar10 < 0xb);
          }
          uVar3 = FUN_000104b2(local_50,uVar3);
          FUN_0001050c(local_50,uVar3);
        }
      }
    }
  }
LAB_00025932:
  FUN_00049974(DAT_1ffe03d4,local_50);
  goto LAB_00025c9c;
LAB_00025980:
  do {
    iVar4 = FUN_000104e2(local_50);
    if (((iVar4 == 0) && (5 < bVar10)) && (bVar10 < 10)) {
LAB_00025a14:
      uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
      FUN_0004aaf6(uVar3,0x80);
      uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004aaf6(uVar3,0x80);
    }
    else {
      uVar5 = FUN_000104e2(local_50);
      cVar13 = uVar5 == 2;
      cVar16 = false;
      if (1 < uVar5) {
        cVar16 = 9 < bVar10;
        cVar13 = false;
        if (bVar10 == 10) goto LAB_00025a14;
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40140000);
      cVar15 = false;
      if (cVar13 != '\0') {
        iVar4 = FUN_000104e2(local_50);
        cVar16 = iVar4 != 0;
        cVar15 = false;
        if (iVar4 == 1) {
          cVar16 = 9 < bVar10;
          cVar15 = bVar10 == 10;
          if (!(bool)cVar16) goto LAB_00025a14;
        }
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40140000);
      if (cVar15 != '\0') {
        uVar5 = FUN_000104e2(local_50);
        cVar16 = 1 < uVar5;
        if (((uVar5 == 2) && (cVar16 = bVar10 != 0, 1 < bVar10)) &&
           (cVar16 = 9 < bVar10, !(bool)cVar16)) goto LAB_00025a14;
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40140000);
      if (((cVar16 == '\0') && (iVar4 = FUN_000104e2(local_50), iVar4 == 1)) && (bVar10 < 10))
      goto LAB_00025a14;
      uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
      FUN_0004e0e6(uVar3,0x80);
      uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004e0e6(uVar3,0x80);
    }
    bVar10 = bVar10 + 1;
  } while (bVar10 < 0xb);
  goto LAB_00025c9c;
LAB_00025a6e:
  do {
    uVar17 = FUN_00020160(local_50);
    FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x40240000);
    if (cVar16 == '\0') {
      uVar5 = FUN_000104e2(local_50);
      cVar16 = 1 < uVar5;
      cVar13 = uVar5 == 2;
      if (!(bool)cVar16) goto LAB_00025a98;
      cVar16 = 9 < bVar10;
      cVar13 = bVar10 == 10;
      if (!(bool)cVar13) goto LAB_00025a98;
LAB_00025ba2:
      uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
      FUN_0004aaf6(uVar3,0x80);
      uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004aaf6(uVar3,0x80);
    }
    else {
LAB_00025a98:
      uVar17 = FUN_00020160(local_50);
      FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x40240000);
      if (!(bool)cVar16 || (bool)cVar13) {
        uVar5 = FUN_000104e2(local_50);
        cVar13 = uVar5 == 3;
        cVar16 = '\0';
        if (2 < uVar5) {
          cVar16 = 9 < bVar10;
          cVar13 = '\0';
          if (bVar10 == 10) goto LAB_00025ba2;
        }
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40080000);
      cVar15 = false;
      if (cVar13 != '\0') {
        iVar4 = FUN_000104e2(local_50);
        cVar16 = iVar4 != 0;
        cVar15 = iVar4 == 1;
        if (((bool)cVar15) && (bVar10 != 0)) {
          cVar16 = 9 < bVar10;
          cVar15 = bVar10 == 10;
          if (!(bool)cVar16) goto LAB_00025ba2;
        }
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,&DAT_40080000);
      if (cVar16 == '\0') {
        iVar4 = FUN_000104e2(local_50);
        cVar16 = iVar4 != 0;
        cVar15 = '\0';
        if (iVar4 == 1) {
          cVar16 = 9 < bVar10;
          cVar15 = bVar10 == 10;
          if (!(bool)cVar16) goto LAB_00025ba2;
        }
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x403e0000);
      cVar13 = false;
      if (cVar15 != '\0') {
        uVar5 = FUN_000104e2(local_50);
        cVar16 = 1 < uVar5;
        cVar13 = false;
        if (uVar5 == 2) {
          cVar16 = 9 < bVar10;
          cVar13 = bVar10 == 10;
          if (!(bool)cVar16) goto LAB_00025ba2;
        }
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x403e0000);
      cVar15 = false;
      if (cVar13 != '\0') {
        uVar5 = FUN_000104e2(local_50);
        cVar16 = 2 < uVar5;
        cVar15 = false;
        if (uVar5 == 3) {
          cVar16 = 4 < bVar10;
          cVar15 = bVar10 == 5;
          if (5 < bVar10) {
            cVar16 = 9 < bVar10;
            cVar15 = bVar10 == 10;
            if (!(bool)cVar16) goto LAB_00025ba2;
          }
        }
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010ae8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0);
      uVar14 = false;
      if (cVar15 != '\0') {
        iVar4 = FUN_000104e2(local_50);
        cVar16 = iVar4 != 0;
        uVar14 = false;
        if (iVar4 == 1) {
          cVar16 = 9 < bVar10;
          uVar14 = bVar10 == 10;
          if (!(bool)cVar16) goto LAB_00025ba2;
        }
      }
      uVar17 = FUN_00020160(local_50);
      FUN_00010b18((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,0x40240000);
      if (((!(bool)cVar16 || (bool)uVar14) && (iVar4 = FUN_000104e2(local_50), iVar4 == 2)) &&
         (bVar10 < 10)) goto LAB_00025ba2;
      uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
      FUN_0004e0e6(uVar3,0x80);
      uVar3 = FUN_0004b9de(DAT_1ffe03e0,bVar10);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004e0e6(uVar3,0x80);
    }
    bVar10 = bVar10 + 1;
    cVar16 = 10 < bVar10;
    cVar13 = bVar10 == 0xb;
  } while (!(bool)cVar16);
LAB_00025c9c:
  FUN_0001cb8c(0xf);
  return;
}

