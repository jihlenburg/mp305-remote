/* Address: 000208e0; name: FUN_000208e0; body bytes: 672 */

void FUN_000208e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 uint param_5,uint param_6,uint param_7)

{
  bool bVar1;
  uint uVar2;
  undefined8 *puVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  char in_CY;
  char cVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  bool bVar13;
  undefined8 in_d0;
  undefined8 uVar14;
  undefined8 uVar15;
  char local_78 [32];
  
  uVar8 = (undefined4)in_d0;
  uVar6 = (uint)((ulonglong)in_d0 >> 0x20);
  uVar9 = 0;
  cVar10 = '\x01';
  FUN_00010ae8();
  if (cVar10 == '\0') {
    uVar9 = 3;
    pcVar5 = "nan";
  }
  else {
    FUN_00010ae8();
    if (in_CY == '\0') {
      uVar9 = 4;
      pcVar5 = "fni-";
    }
    else {
      FUN_00010b18();
      if (in_CY == '\0') {
        if ((int)(param_7 << 0x1d) < 0) {
          uVar9 = 4;
          pcVar5 = "fni+";
        }
        else {
          uVar9 = 3;
          pcVar5 = "fni";
        }
      }
      else {
        FUN_00010b18();
        if ((in_CY == '\0') || (FUN_00010ae8(), in_CY == '\0')) {
          FUN_00020368(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
          return;
        }
        FUN_00010ae8();
        bVar1 = in_CY != '\0';
        if (!bVar1) {
          uVar6 = uVar6 ^ 0x80000000;
        }
        if (-1 < (int)(param_7 << 0x15)) {
          param_5 = 6;
        }
        pcVar5 = local_78;
        do {
          cVar10 = 8 < param_5;
          if (param_5 < 10) break;
          pcVar5[uVar9] = '0';
          uVar9 = uVar9 + 1;
          param_5 = param_5 - 1;
          cVar10 = 0x1f < uVar9;
        } while (!(bool)cVar10);
        uVar2 = FUN_00010a52(uVar8,uVar6);
        uVar14 = FUN_000109fe();
        uVar14 = FUN_00010836((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar8,uVar6);
        puVar3 = (undefined8 *)(&UNK_00082c90 + param_5 * 8);
        uVar14 = FUN_0001083c((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),(int)*puVar3,
                              (int)((ulonglong)*puVar3 >> 0x20));
        uVar4 = FUN_00010a90();
        uVar15 = FUN_00010a20();
        uVar14 = FUN_00010836((int)uVar15,(int)((ulonglong)uVar15 >> 0x20),(int)uVar14,
                              (int)((ulonglong)uVar14 >> 0x20));
        uVar7 = (undefined4)((ulonglong)uVar14 >> 0x20);
        FUN_00010b18((int)uVar14,uVar7,0,0x3fe00000);
        if (cVar10 == '\0') {
          uVar12 = 0xfffffffe < uVar4;
          uVar4 = uVar4 + 1;
          uVar11 = uVar4 == 0;
          uVar14 = FUN_00010a20(uVar4);
          FUN_00010b18((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),(int)*puVar3,
                       (int)((ulonglong)*puVar3 >> 0x20));
          if (!(bool)uVar12 || (bool)uVar11) {
            uVar4 = 0;
            uVar2 = uVar2 + 1;
          }
        }
        else {
          FUN_00010ae8((int)uVar14,uVar7,0,0x3fe00000);
          if ((cVar10 != '\0') && (((uVar4 & 1) - 1 & uVar4) == 0)) {
            uVar4 = uVar4 + 1;
          }
        }
        cVar10 = 1;
        uVar11 = param_5 == 0;
        if ((bool)uVar11) {
          uVar14 = FUN_000109fe(uVar2);
          uVar14 = FUN_00010836((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar8,uVar6);
          uVar8 = (undefined4)((ulonglong)uVar14 >> 0x20);
          FUN_00010b18((int)uVar14,uVar8,0,0x3fe00000);
          if (((!(bool)cVar10 || (bool)uVar11) ||
              (FUN_00010b18((int)uVar14,uVar8,0,0x3fe00000), cVar10 == '\0')) && ((uVar2 & 1) != 0))
          {
            uVar2 = uVar2 + 1;
          }
LAB_00020b04:
          do {
            if (0x1f < uVar9) break;
            pcVar5[uVar9] = (char)uVar2 + (char)((int)uVar2 / 10) * -10 + '0';
            uVar2 = (int)uVar2 / 10;
            uVar9 = uVar9 + 1;
          } while (uVar2 != 0);
        }
        else {
          do {
            if (0x1f < uVar9) goto LAB_00020b20;
            uVar6 = uVar4 / 10;
            cVar10 = (char)uVar4;
            uVar4 = uVar4 / 10;
            pcVar5[uVar9] = cVar10 + (char)uVar6 * -10 + '0';
            param_5 = param_5 - 1;
            uVar9 = uVar9 + 1;
          } while (uVar4 != 0);
          for (; uVar9 < 0x20; uVar9 = uVar9 + 1) {
            bVar13 = param_5 == 0;
            param_5 = param_5 - 1;
            if (bVar13) {
              pcVar5[uVar9] = '.';
              uVar9 = uVar9 + 1;
              goto LAB_00020b04;
            }
            pcVar5[uVar9] = '0';
          }
        }
LAB_00020b20:
        if ((-1 < (int)(param_7 << 0x1e)) && ((param_7 & 1) != 0)) {
          if ((param_6 != 0) && ((param_7 & 0xc) != 0 || !bVar1)) {
            param_6 = param_6 - 1;
          }
          for (; uVar9 < param_6; uVar9 = uVar9 + 1) {
            if (0x1f < uVar9) goto LAB_00020b7a;
            pcVar5[uVar9] = '0';
          }
        }
        if (uVar9 < 0x20) {
          if (bVar1) {
            if ((int)(param_7 << 0x1d) < 0) {
              cVar10 = '+';
            }
            else {
              if (-1 < (int)(param_7 << 0x1c)) goto LAB_00020b7a;
              cVar10 = ' ';
            }
          }
          else {
            cVar10 = '-';
          }
          pcVar5[uVar9] = cVar10;
          uVar9 = uVar9 + 1;
        }
      }
    }
  }
LAB_00020b7a:
  FUN_00020dd6(param_1,param_2,param_3,param_4,pcVar5,uVar9,param_6,param_7);
  return;
}

