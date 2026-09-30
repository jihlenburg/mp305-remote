/* Address: 00013f40; name: FUN_00013f40; body bytes: 308 */

undefined4 FUN_00013f40(int param_1,uint *param_2)

{
  longlong lVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  bVar2 = true;
  if ((param_1 == 0x4001dc00) || (param_1 == 0x40021c00)) {
    bVar2 = false;
  }
  uVar8 = *param_2;
  uVar9 = param_2[1];
  if (uVar8 == 0) {
    return 0xffffffff;
  }
  if (uVar9 == 0) {
    return 0xffffffff;
  }
  uVar10 = uVar9 * 4;
  uVar3 = uVar8 / uVar10;
  uVar4 = uVar3 - 1;
  if (bVar2) {
    if (0xff < uVar4) {
      return 0xffffffff;
    }
    param_2[2] = uVar4;
    if (uVar8 == uVar10 * (uVar8 / uVar10)) {
      fVar6 = 0.0;
      goto LAB_00014008;
    }
    lVar1 = (ulonglong)(uVar3 * 4) * (ulonglong)uVar9;
    uVar7 = (uint)lVar1;
    uVar5 = uVar7 * 0x100;
    uVar7 = (((uint)(0xfffffffe < uVar4) << 2 | uVar3 >> 0x1e) * uVar9 +
            (int)((ulonglong)lVar1 >> 0x20)) * 0x100 | uVar7 >> 0x18;
    uVar3 = FUN_00010388(uVar5 + (uVar8 >> 1),uVar7 + CARRY4(uVar5,uVar8 >> 1),uVar8,0);
    uVar4 = uVar3 - 0x80;
    if (0x7f < uVar4) goto LAB_00014012;
    param_2[3] = uVar4;
    uVar11 = FUN_00010a3a(uVar5,uVar7);
    uVar12 = FUN_00010a3a((int)((ulonglong)uVar3 * (ulonglong)uVar8),
                          (0xffffff7f < uVar4) * uVar8 +
                          (int)((ulonglong)uVar3 * (ulonglong)uVar8 >> 0x20));
  }
  else {
    if (bVar2) {
      return 0xffffffff;
    }
LAB_00014012:
    uVar3 = ((uVar8 * 10) / uVar10 + 5) / 10;
    uVar4 = uVar3 - 1;
    if (0xff < uVar4) {
      return 0xffffffff;
    }
    param_2[2] = uVar4;
    lVar1 = (ulonglong)(uVar3 * 4) * (ulonglong)uVar9;
    uVar11 = FUN_00010a3a((int)lVar1,
                          (uint)(0xfffffffe < uVar4) * 4 * uVar9 + (int)((ulonglong)lVar1 >> 0x20));
    uVar12 = FUN_00010a20(uVar8);
  }
  FUN_00010920((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)uVar11,
               (int)((ulonglong)uVar11 >> 0x20));
  fVar6 = (float)FUN_00010b48();
  fVar6 = fVar6 - 1.0;
LAB_00014008:
  param_2[4] = (uint)fVar6;
  return 0;
}

