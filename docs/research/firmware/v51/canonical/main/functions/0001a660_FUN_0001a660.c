/* Address: 0001a660; name: FUN_0001a660; body bytes: 1186 */

uint FUN_0001a660(void)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  byte bVar5;
  undefined *puVar6;
  uint uVar7;
  uint uVar8;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  uint uVar9;
  uint *puVar10;
  undefined4 unaff_r6;
  int iVar11;
  uint *puVar12;
  undefined4 unaff_r7;
  int iVar13;
  undefined4 unaff_r8;
  uint uVar14;
  undefined4 unaff_lr;
  uint in_fpscr;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  
  uVar14 = 0;
  iVar13 = 0;
  iVar11 = 0;
  uVar9 = 0;
  iVar3 = FUN_00018ee0(0);
  if (iVar3 == 0) {
    DAT_1fffa9e4 = 0;
    DAT_1fffa9e6 = 0;
    DAT_1fffa9e8 = 0;
    DAT_1fffa9ea = 0;
LAB_0001a71e:
    DAT_1fffaa41 = '\0';
  }
  else {
    DAT_1fffa9e4 = FUN_00018db4(0);
    DAT_1fffa9e6 = FUN_00018d1a(0);
    DAT_1fffa9e8 = FUN_00018d72(0);
    DAT_1fffa9ea = FUN_00018cd6(0);
    if ((25000 < DAT_1fffa9e4) && (DAT_1fffa9e4 < DAT_1fff9b54)) {
      DAT_1fffa9e4 = DAT_1fff9b54;
    }
    iVar3 = FUN_0001bc68(0);
    if (iVar3 == 0) {
      iVar3 = FUN_0001bc80(0);
      if (iVar3 != 0) {
        uVar14 = (uint)DAT_1fffa9ea;
      }
      goto LAB_0001a71e;
    }
    iVar13 = (int)((uint)DAT_1fffa9e6 * (uint)DAT_1fffa9e4) / 1000;
    if (iVar13 == 0) {
      iVar13 = 1;
    }
    iVar11 = (int)((uint)DAT_1fffa9ea * (uint)DAT_1fffa9e8) / 1000;
    if (iVar11 == 0) {
      iVar11 = 1;
    }
    DAT_1fffaa41 = '\x01';
    uVar14 = -(uint)DAT_1fffa9ea;
    uVar9 = (uint)(ushort)(&DAT_1fff9b70)[DAT_1fff9b95];
    if (uVar9 == 0) {
      uVar9 = 500;
    }
  }
  uVar14 = DAT_1fffa9ee + uVar14;
  if ((((DAT_1fffaa41 != '\0') && (0 < (int)uVar14)) && (DAT_1fffa9d6 == 1000)) &&
     ((uint)DAT_1fffa9e6 < (uVar9 * 0x50) / 100)) {
    uVar14 = 0xffffffff;
  }
  if (DAT_1fffa9a4 < 0x1f41) {
    DAT_1fffa9a4 = (uint)DAT_1fffa9e8;
  }
  else {
    DAT_1fffa9a4 = DAT_1fffa9a4 * 7 + (uint)DAT_1fffa9e8 >> 3;
  }
  if ((DAT_1fffaa41 == '\0') && (0 < (int)uVar14)) {
    if ((int)uVar14 < 0x32) {
LAB_0001a794:
      if (DAT_1fffaa34 == 'd') {
        puVar6 = (undefined *)0xdbba0;
      }
      else {
        puVar6 = &UNK_0007a120;
      }
      uVar14 = (uint)puVar6 / DAT_1fffa9a4;
    }
  }
  else if ((uVar14 == 0) && (DAT_1fffa9ee == 0)) goto LAB_0001a794;
  iVar3 = DAT_1fffa998 * 7 + uVar14;
  DAT_1fffa998 = (int)(iVar3 + ((uint)(iVar3 >> 0x1f) >> 0x1d)) >> 3;
  uVar9 = DAT_1fffa998;
  do {
    if ((int)uVar9 < 1) {
      DAT_1fffa9a0 = 0;
      DAT_1ffe0208 = 0.0;
      DAT_1ffe0204 = 0.0;
      goto LAB_0001aaa8;
    }
    uVar9 = uVar14;
  } while ((int)uVar14 < 1);
  uVar14 = in_fpscr & 0xfffffff | (uint)(DAT_1ffe0208 == 0.0) << 0x1e;
  if ((((byte)(uVar14 >> 0x1e) != 0) ||
      (uVar14 = in_fpscr & 0xfffffff | (uint)(DAT_1ffe0204 == 0.0) << 0x1e,
      (byte)(uVar14 >> 0x1e) != 0)) || (DAT_1fffa9a0 == 0)) {
    DAT_1ffe0208 = (float)VectorUnsignedToFloat(DAT_1fffa9a4,(byte)(uVar14 >> 0x16) & 3);
    DAT_1ffe0204 = (float)VectorSignedToFloat(DAT_1fffa998,(byte)(uVar14 >> 0x16) & 3);
    DAT_1fffa9a0 = VectorFloatToUnsigned((DAT_1ffe0208 * DAT_1ffe0204 + 500.0) / 1000.0,3);
  }
  uVar9 = DAT_1fffa998;
  if (((DAT_1fffaa2e != '\0') && (DAT_1fffaa41 == '\0')) &&
     (uVar7 = (DAT_1fffa974 + 500U) / 900 + 900, DAT_1fffa9a0 < uVar7)) {
    fVar15 = (float)VectorUnsignedToFloat(uVar7 * 1000,(byte)(uVar14 >> 0x16) & 3);
    uVar9 = (uint)(fVar15 / DAT_1ffe0208);
    iVar3 = FUN_0001a14c(DAT_1fffa9a0);
    if (0xfa < iVar3) {
      DAT_1ffe0204 = (float)VectorSignedToFloat(uVar9,(byte)(uVar14 >> 0x16) & 3);
    }
  }
  fVar15 = DAT_1ffe0204;
  fVar16 = (float)VectorSignedToFloat(uVar9,(byte)(uVar14 >> 0x16) & 3);
  uVar7 = uVar14 & 0xfffffff | (uint)(fVar16 <= DAT_1ffe0204 + 20.0) << 0x1d;
  if ((byte)(uVar7 >> 0x1d) == 0) {
    DAT_1ffe01d8 = 0;
    DAT_1ffe01d7 = DAT_1ffe01d7 + 1;
    if (5 < DAT_1ffe01d7) {
      DAT_1ffe01d7 = 0;
      uVar18 = FUN_000109fe(uVar9);
      uVar19 = FUN_00010ac2(fVar15);
      uVar19 = FUN_0001083c((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),0,&DAT_401c0000);
      uVar18 = FUN_000106ee((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),(int)uVar18,
                            (int)((ulonglong)uVar18 >> 0x20));
      FUN_0001083c((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),0,0x3fc00000);
      DAT_1ffe0204 = (float)FUN_00010b48();
    }
  }
  else {
    DAT_1ffe01d7 = 0;
    fVar16 = (float)VectorSignedToFloat(uVar9 + 0x14,(byte)(uVar7 >> 0x16) & 3);
    uVar7 = uVar14 & 0xfffffff | (uint)(DAT_1ffe0204 <= fVar16) << 0x1d;
    if ((byte)(uVar7 >> 0x1d) == 0) {
      DAT_1ffe01d8 = DAT_1ffe01d8 + 1;
      if (5 < DAT_1ffe01d8) {
        DAT_1ffe01d8 = 0;
        uVar18 = FUN_000109fe(uVar9);
        uVar19 = FUN_00010ac2(fVar15);
        uVar19 = FUN_0001083c((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),0,&DAT_401c0000);
        uVar18 = FUN_000106ee((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),(int)uVar18,
                              (int)((ulonglong)uVar18 >> 0x20));
        FUN_0001083c((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),0,0x3fc00000);
        DAT_1ffe0204 = (float)FUN_00010b48();
      }
    }
    else {
      DAT_1ffe01d8 = 0;
    }
  }
  uVar8 = DAT_1fffa9a4;
  fVar15 = DAT_1ffe0208;
  fVar17 = DAT_1ffe0208 + 20.0;
  fVar16 = (float)VectorUnsignedToFloat(DAT_1fffa9a4,(byte)(uVar7 >> 0x16) & 3);
  uVar14 = uVar7 & 0xfffffff | (uint)(fVar16 < fVar17) << 0x1f | (uint)(fVar16 == fVar17) << 0x1e;
  bVar5 = (byte)(uVar14 >> 0x18);
  if ((bool)(bVar5 >> 6 & 1) || (bool)(bVar5 >> 7) != (NAN(fVar16) || NAN(fVar17))) {
    DAT_1ffe01d9 = 0;
    fVar16 = (float)VectorUnsignedToFloat(DAT_1fffa9a4 + 0x14,(byte)(uVar14 >> 0x16) & 3);
    if (DAT_1ffe0208 <= fVar16) {
      DAT_1ffe01da = 0;
      goto LAB_0001a9e8;
    }
    DAT_1ffe01da = DAT_1ffe01da + 1;
    bVar5 = DAT_1ffe01da;
  }
  else {
    DAT_1ffe01da = 0;
    DAT_1ffe01d9 = DAT_1ffe01d9 + 1;
    bVar5 = DAT_1ffe01d9;
  }
  if (5 < bVar5) {
    DAT_1ffe01da = 0;
    DAT_1ffe01d9 = 0;
    uVar18 = FUN_00010a20(DAT_1fffa9a4);
    uVar19 = FUN_00010ac2(fVar15);
    uVar19 = FUN_0001083c((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),0,&DAT_401c0000);
    uVar18 = FUN_000106ee((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),(int)uVar18,
                          (int)((ulonglong)uVar18 >> 0x20));
    FUN_0001083c((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),0,0x3fc00000);
    DAT_1ffe0208 = (float)FUN_00010b48();
  }
LAB_0001a9e8:
  uVar18 = FUN_00010a20(uVar8);
  uVar19 = FUN_00010ac2(DAT_1ffe0208);
  uVar19 = FUN_0001083c((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),0,0x408ff800);
  uVar18 = FUN_000106ee((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),(int)uVar18,
                        (int)((ulonglong)uVar18 >> 0x20));
  FUN_0001083c((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),0,0x3f500000);
  fVar15 = (float)FUN_00010b48();
  DAT_1ffe0208 = fVar15;
  uVar18 = FUN_000109fe(uVar9);
  uVar19 = FUN_00010ac2(DAT_1ffe0204);
  uVar19 = FUN_0001083c((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),0,0x408ff800);
  uVar18 = FUN_000106ee((int)uVar19,(int)((ulonglong)uVar19 >> 0x20),(int)uVar18,
                        (int)((ulonglong)uVar18 >> 0x20));
  FUN_0001083c((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),0,0x3f500000);
  DAT_1ffe0204 = (float)FUN_00010b48();
  uVar14 = VectorFloatToUnsigned(fVar15 * DAT_1ffe0204 + 500.0,3);
  DAT_1fffa9a0 = uVar14 / 1000 + DAT_1fffa9a0 * 3 >> 2;
  if (DAT_1fffaa34 == 'd') {
    uVar14 = 900;
  }
  else {
    uVar14 = 500;
  }
  if (DAT_1fffa9a0 < uVar14) {
    DAT_1fffa9a0 = uVar14;
  }
LAB_0001aaa8:
  puVar2 = DAT_1ffe0224;
  if (DAT_1fffa9e4 < 0x10cd) {
    DAT_1fffa990 = 0;
    DAT_1fffa98c = 0;
    DAT_1fffaa08 = 0;
  }
  else {
    DAT_1fffa990 = DAT_1fffa990 * 7 + iVar11 >> 3;
    DAT_1fffa98c = DAT_1fffa98c * 7 + iVar13 >> 3;
    DAT_1fffaa08 = (ushort)((uint)DAT_1fffa9e4 + (uint)DAT_1fffaa08 * 7 >> 3);
  }
  if (DAT_1ffe0224 == (uint *)0x0) {
    return 0;
  }
  uVar14 = 0;
  puVar12 = DAT_1ffe0224 + 3;
  FUN_00065c04();
  *puVar2 = *puVar2 | 2;
  puVar10 = (uint *)puVar2[4];
LAB_00066540:
  do {
    puVar4 = puVar10;
    if (puVar4 == puVar12) {
      *puVar2 = *puVar2 & ~uVar14;
      FUN_00066f6c();
      return *puVar2;
    }
    puVar10 = (uint *)puVar4[1];
    uVar8 = *puVar4 & 0xff000000;
    uVar9 = *puVar2;
    uVar7 = *puVar4 & 0xffffff;
    if ((int)(uVar8 << 5) < 0) goto LAB_00066528;
  } while ((uVar9 & uVar7) == 0);
  goto LAB_0006652e;
LAB_00066528:
  uVar1 = ~uVar9;
  uVar9 = 0;
  if ((uVar7 & uVar1) == 0) {
LAB_0006652e:
    iVar3 = uVar8 << 7;
    if (iVar3 < 0) {
      uVar14 = uVar14 | uVar7;
    }
    FUN_00065b08(puVar4,*puVar2 | 0x2000000,iVar3,uVar9,unaff_r4,unaff_r5,unaff_r6,unaff_r7,unaff_r8
                 ,unaff_lr);
  }
  goto LAB_00066540;
}

