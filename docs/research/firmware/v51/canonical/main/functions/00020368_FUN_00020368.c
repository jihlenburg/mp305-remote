/* Address: 00020368; name: FUN_00020368; body bytes: 862 */

int FUN_00020368(code *param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
                uint param_6,uint param_7)

{
  ulonglong uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  char in_ZR;
  char in_CY;
  char cVar10;
  bool bVar11;
  undefined8 in_d0;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  
  uVar5 = (undefined4)in_d0;
  uVar6 = (uint)((ulonglong)in_d0 >> 0x20);
  FUN_00010ae8();
  if (((in_ZR == '\0') || (FUN_00010b18(), in_CY == '\0')) || (FUN_00010ae8(), in_CY == '\0')) {
    iVar2 = FUN_000208e0(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  else {
    FUN_00010ae8();
    if (in_CY == '\0') {
      uVar6 = uVar6 ^ 0x80000000;
    }
    cVar10 = (param_7 & 0x800) != 0;
    if (-1 < (int)(param_7 << 0x15)) {
      param_5 = 6;
    }
    uVar1 = CONCAT44(uVar6,uVar5) & 0xfffffffffffff;
    uVar12 = FUN_00010830((int)uVar1,(uint)(uVar1 >> 0x20) | 0x3ff00000,0,0x3ff80000);
    uVar12 = FUN_0001083c((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),0x636f4361,0x3fd287a7);
    uVar13 = FUN_000109fe(((uVar6 & 0x7fffffff) >> 0x14) - 0x3ff);
    uVar13 = FUN_0001083c((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),0x509f79fb,0x3fd34413);
    uVar13 = FUN_000106ee((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),0x8b60c8b3,0x3fc68a28);
    FUN_000106ee((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),(int)uVar12,
                 (int)((ulonglong)uVar12 >> 0x20));
    uVar3 = FUN_00010a52();
    uVar12 = FUN_000109fe();
    uVar14 = (undefined4)((ulonglong)uVar12 >> 0x20);
    uVar13 = FUN_0001083c((int)uVar12,uVar14,0x979a371,&DAT_400a934f);
    FUN_000106ee((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),0,0x3fe00000);
    iVar2 = FUN_00010a52();
    uVar13 = FUN_000109fe();
    uVar13 = FUN_0001083c((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),0xfefa39ef,0x3fe62e42);
    uVar12 = FUN_0001083c((int)uVar12,uVar14,0xbbb55516,&DAT_40026bb1);
    uVar12 = FUN_00010830((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)uVar13,
                          (int)((ulonglong)uVar13 >> 0x20));
    uVar7 = (undefined4)((ulonglong)uVar12 >> 0x20);
    uVar14 = (undefined4)uVar12;
    uVar12 = FUN_0001083c(uVar14,uVar7,uVar14,uVar7);
    uVar8 = (undefined4)((ulonglong)uVar12 >> 0x20);
    uVar4 = (undefined4)uVar12;
    iVar2 = iVar2 * 0x100000 + 0x3ff00000;
    uVar15 = 0;
    uVar12 = FUN_00010920(uVar4,uVar8,0,0x402c0000);
    uVar12 = FUN_000106ee((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),0,0x40240000);
    uVar12 = FUN_00010920(uVar4,uVar8,(int)uVar12,(int)((ulonglong)uVar12 >> 0x20));
    uVar12 = FUN_000106ee((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),0,&DAT_40180000);
    uVar12 = FUN_00010920(uVar4,uVar8,(int)uVar12,(int)((ulonglong)uVar12 >> 0x20));
    uVar13 = FUN_00010830(0,0x40000000,uVar14,uVar7);
    uVar12 = FUN_000106ee((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),(int)uVar12,
                          (int)((ulonglong)uVar12 >> 0x20));
    uVar13 = FUN_0001083c(uVar14,uVar7,0,0x40000000);
    uVar12 = FUN_00010920((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),(int)uVar12,
                          (int)((ulonglong)uVar12 >> 0x20));
    uVar12 = FUN_000106ee((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),0,0x3ff00000);
    uVar12 = FUN_0001083c((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar15,iVar2);
    uVar4 = (undefined4)((ulonglong)uVar12 >> 0x20);
    uVar14 = (undefined4)uVar12;
    FUN_00010ae8(uVar5,uVar6,uVar14,uVar4);
    if (cVar10 == '\0') {
      uVar3 = uVar3 - 1;
      uVar12 = FUN_00010920(uVar14,uVar4,0,0x40240000);
    }
    if (uVar3 + 99 < 199) {
      uVar9 = 4;
    }
    else {
      uVar9 = 5;
    }
    cVar10 = (param_7 & 0x1000) != 0;
    bVar11 = param_7 << 0x14 == 0;
    if ((int)(param_7 << 0x14) < 0) {
      FUN_00010b18(uVar5,uVar6,0xeb1c432d,0x3f1a36e2);
      if (((bool)cVar10 && !bVar11) || (FUN_00010ae8(uVar5,uVar6,0,0x412e8480), cVar10 != '\0')) {
        if ((param_5 != 0) && ((int)(param_7 << 0x15) < 0)) {
          param_5 = param_5 + -1;
        }
      }
      else {
        if ((int)uVar3 < param_5) {
          param_5 = (param_5 - uVar3) + -1;
        }
        else {
          param_5 = 0;
        }
        uVar9 = 0;
        param_7 = param_7 | 0x400;
        uVar3 = 0;
      }
    }
    if (uVar9 < param_6) {
      iVar2 = param_6 - uVar9;
    }
    else {
      iVar2 = 0;
    }
    if (((int)(param_7 << 0x1e) < 0) && (uVar9 != 0)) {
      iVar2 = 0;
    }
    if (uVar3 != 0) {
      uVar5 = FUN_00010920(uVar5,uVar6,(int)uVar12,(int)((ulonglong)uVar12 >> 0x20));
    }
    iVar2 = FUN_000208e0(uVar5,param_1,param_2,param_3,param_4,param_5,iVar2,param_7 & 0xfffff7ff);
    if (uVar9 != 0) {
      if ((int)(param_7 << 0x1a) < 0) {
        uVar5 = 0x45;
      }
      else {
        uVar5 = 0x65;
      }
      (*param_1)(uVar5,param_2,iVar2,param_4);
      uVar6 = uVar3 >> 0x1f;
      if ((int)uVar3 < 0) {
        uVar3 = -uVar3;
      }
      iVar2 = FUN_00020ccc(param_1,param_2,iVar2 + 1,param_4,uVar3,uVar6,10,0,uVar9 - 1,5);
      if ((int)(param_7 << 0x1e) < 0) {
        for (; (uint)(iVar2 - param_3) < param_6; iVar2 = iVar2 + 1) {
          (*param_1)(0x20,param_2,iVar2,param_4);
        }
      }
    }
  }
  return iVar2;
}

