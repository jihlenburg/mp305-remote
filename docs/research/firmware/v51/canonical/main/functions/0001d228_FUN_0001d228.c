/* Address: 0001d228; name: FUN_0001d228; body bytes: 334 */

undefined4 FUN_0001d228(int param_1,uint *param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ushort local_48 [8];
  uint local_38;
  
  local_48[0] = 0x20;
  local_48[1] = 0x40;
  local_48[2] = 0x5d;
  local_48[3] = 0x80;
  local_48[4] = 0xba;
  local_48[5] = 0x100;
  local_48[6] = 0x174;
  local_48[7] = 0x200;
  uVar8 = *param_2;
  uVar9 = param_2[1];
  if (uVar8 == 0) {
    return 0xffffffff;
  }
  if (uVar9 == 0) {
    return 0xffffffff;
  }
  uVar10 = (uint)local_48[*(uint *)(param_1 + 0x14) >> 0x15 & 7];
  uVar11 = uVar9 * uVar10 * 2;
  uVar3 = uVar8 / uVar11;
  uVar4 = uVar3 - 1;
  if (uVar4 < 0x100) {
    param_2[2] = uVar4;
    if (uVar8 == uVar11 * (uVar8 / uVar11)) {
      fVar6 = 0.0;
      goto LAB_0001d2fc;
    }
    uVar1 = (ulonglong)(uVar10 * 2) * (ulonglong)uVar3;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)uVar9;
    uVar5 = (uint)lVar2;
    uVar7 = uVar5 * 0x100;
    local_38 = ((uVar10 * 2 * (uint)(0xfffffffe < uVar4) +
                CARRY4(uVar10,uVar10) * uVar3 + (int)(uVar1 >> 0x20)) * uVar9 +
               (int)((ulonglong)lVar2 >> 0x20)) * 0x100 | uVar5 >> 0x18;
    uVar3 = FUN_00010388(uVar7 + (uVar8 >> 1),local_38 + CARRY4(uVar7,uVar8 >> 1),uVar8,0);
    uVar4 = uVar3 - 0x80;
    if (0x7f < uVar4) goto LAB_0001d306;
    param_2[3] = uVar4;
    uVar12 = FUN_00010a3a(uVar7,local_38);
    uVar13 = FUN_00010a3a((int)((ulonglong)uVar3 * (ulonglong)uVar8),
                          (0xffffff7f < uVar4) * uVar8 +
                          (int)((ulonglong)uVar3 * (ulonglong)uVar8 >> 0x20));
  }
  else {
LAB_0001d306:
    uVar3 = ((uVar8 * 10) / uVar11 + 5) / 10;
    uVar4 = uVar3 - 1;
    if (0xff < uVar4) {
      return 0xffffffff;
    }
    param_2[2] = uVar4;
    uVar1 = (ulonglong)(uVar10 * 2) * (ulonglong)uVar3;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)uVar9;
    uVar12 = FUN_00010a3a((int)lVar2,
                          (uVar10 * 2 * (uint)(0xfffffffe < uVar4) +
                          CARRY4(uVar10,uVar10) * uVar3 + (int)(uVar1 >> 0x20)) * uVar9 +
                          (int)((ulonglong)lVar2 >> 0x20));
    uVar13 = FUN_00010a20(uVar8);
  }
  FUN_00010920((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),(int)uVar12,
               (int)((ulonglong)uVar12 >> 0x20));
  fVar6 = (float)FUN_00010b48();
  fVar6 = fVar6 - 1.0;
LAB_0001d2fc:
  param_2[4] = (uint)fVar6;
  return 0;
}

