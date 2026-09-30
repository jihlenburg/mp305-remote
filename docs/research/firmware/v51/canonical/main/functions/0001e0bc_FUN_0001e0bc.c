/* Address: 0001e0bc; name: FUN_0001e0bc; body bytes: 388 */

undefined4 FUN_0001e0bc(int param_1,uint *param_2)

{
  int iVar1;
  ulonglong uVar2;
  longlong lVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  float fVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  
  bVar4 = true;
  if ((param_1 == 0x4001dc00) || (param_1 == 0x40021c00)) {
    bVar4 = false;
  }
  uVar11 = *param_2;
  uVar12 = param_2[1];
  if (uVar11 == 0) {
    return 0xffffffff;
  }
  if (uVar12 == 0) {
    return 0xffffffff;
  }
  iVar5 = (*(int *)(param_1 + 0xc) << 0x10) >> 0x1f;
  uVar13 = uVar12 * (iVar5 + 2) * 8;
  uVar6 = uVar11 / uVar13;
  uVar7 = uVar6 - 1;
  if (bVar4) {
    if (0xff < uVar7) {
      return 0xffffffff;
    }
    param_2[2] = uVar7;
    if (uVar11 == uVar13 * (uVar11 / uVar13)) {
      fVar9 = 0.0;
      goto LAB_0001e1b8;
    }
    uVar10 = (iVar5 + 2U) * 8;
    uVar2 = (ulonglong)uVar10 * (ulonglong)uVar6;
    lVar3 = (uVar2 & 0xffffffff) * (ulonglong)uVar12;
    uVar8 = (uint)lVar3;
    uVar7 = ((uVar10 * (0xfffffffe < uVar7) +
             ((uint)(2 < (uint)-iVar5) * -8 | iVar5 + 2U >> 0x1d) * uVar6 + (int)(uVar2 >> 0x20)) *
             uVar12 + (int)((ulonglong)lVar3 >> 0x20)) * 0x100 | uVar8 >> 0x18;
    uVar8 = uVar8 * 0x100;
    uVar6 = (uVar11 >> 1) + uVar8;
    iVar1 = uVar7 + CARRY4(uVar11 >> 1,uVar8);
    if (iVar1 == 0) {
      uVar6 = uVar6 / uVar11;
    }
    else {
      uVar6 = FUN_00010388(uVar6,iVar1,uVar11,0);
    }
    uVar10 = uVar6 - 0x80;
    if (0x7f < uVar10) goto LAB_0001e1c4;
    param_2[3] = uVar10;
    uVar14 = FUN_00010a3a(uVar8,uVar7);
    uVar15 = FUN_00010a3a((int)((ulonglong)uVar6 * (ulonglong)uVar11),
                          (0xffffff7f < uVar10) * uVar11 +
                          (int)((ulonglong)uVar6 * (ulonglong)uVar11 >> 0x20));
  }
  else {
    if (bVar4) {
      return 0xffffffff;
    }
LAB_0001e1c4:
    uVar6 = ((uVar11 * 10) / uVar13 + 5) / 10;
    uVar7 = uVar6 - 1;
    if (0xff < uVar7) {
      return 0xffffffff;
    }
    param_2[2] = uVar7;
    uVar13 = (iVar5 + 2U) * 8;
    uVar2 = (ulonglong)uVar13 * (ulonglong)uVar6;
    lVar3 = (uVar2 & 0xffffffff) * (ulonglong)uVar12;
    uVar14 = FUN_00010a3a((int)lVar3,
                          (uVar13 * (0xfffffffe < uVar7) +
                          ((uint)(2 < (uint)-iVar5) * -8 | iVar5 + 2U >> 0x1d) * uVar6 +
                          (int)(uVar2 >> 0x20)) * uVar12 + (int)((ulonglong)lVar3 >> 0x20));
    uVar15 = FUN_00010a20(uVar11);
  }
  FUN_00010920((int)uVar15,(int)((ulonglong)uVar15 >> 0x20),(int)uVar14,
               (int)((ulonglong)uVar14 >> 0x20));
  fVar9 = (float)FUN_00010b48();
  fVar9 = fVar9 - 1.0;
LAB_0001e1b8:
  param_2[4] = (uint)fVar9;
  return 0;
}

