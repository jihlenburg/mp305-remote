/* Address: ram:000678ae; name: FUN_ram_000678ae; body bytes: 1226 */

undefined4
FUN_ram_000678ae(undefined1 param_1,uint param_2,undefined1 param_3,undefined4 param_4,uint param_5,
                ushort *param_6,ushort *param_7,ushort *param_8,ushort *param_9,ushort *param_10,
                ushort *param_11,undefined2 *param_12,undefined2 *param_13)

{
  ushort uVar1;
  ushort uVar2;
  undefined2 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined1 auStack_46 [18];
  
  gp = 0x20004000;
  tmos_memcpy(auStack_46,param_4,6);
  if ((((DAT_ram_20001dd8 != 0) && (*(int *)(DAT_ram_20001dd8 + 0x1c) << 0x11 < 0)) ||
      (DAT_ram_20001dec == (code *)0x0)) ||
     (uVar4 = FUN_ram_00055ebc(), uVar4 == DAT_ram_20001bd3 >> 2)) {
    return 0xc;
  }
  if ((param_5 & 0xfffffff8) != 0) {
    gp = 0x20004000;
    return 0x11;
  }
  if ((param_5 & 5) != 0) {
    if (DAT_ram_20001dd8 != 0) {
      if (*(int *)(DAT_ram_20001dd8 + 0x1c) << 0x11 < 0) {
        gp = 0x20004000;
        return 0xc;
      }
      if (*(char *)(DAT_ram_20001dd8 + 0xb) != '\0') {
        gp = 0x20004000;
        return 0xc;
      }
    }
    if (DAT_ram_20001de8 == 0) {
      iVar5 = (*DAT_ram_20001dec)(0x11);
      if (iVar5 == 0) {
        gp = 0x20004000;
        return 0xc;
      }
    }
    else {
      iVar5 = DAT_ram_20001de8;
      if (*(char *)(DAT_ram_20001de8 + 7) == '\x01') {
        gp = 0x20004000;
        return 0xc;
      }
    }
    if (param_2 < 4) {
      *(undefined1 *)(iVar5 + 0xd) = param_1;
      *(char *)(iVar5 + 0x65) = (char)param_2;
      iVar6 = tmos_isbufset(param_4,0,6);
      if (iVar6 == 0) {
        *(undefined1 *)(iVar5 + 0x6c) = 1;
        *(undefined1 *)(iVar5 + 0x6d) = param_3;
        tmos_memcpy(iVar5 + 0x6e,param_4,6);
      }
      else {
        *(undefined1 *)(iVar5 + 0x6c) = 0;
      }
      *(undefined1 *)(iVar5 + 0x38) = 0;
      iVar6 = 0;
      if ((param_5 & 1) != 0) {
        uVar4 = (uint)*param_6;
        if (uVar4 < 4) {
          uVar4 = 4;
        }
        *(short *)(iVar5 + 0x34) = (short)uVar4;
        uVar10 = (uint)*param_7;
        if (uVar4 < *param_7) {
          uVar10 = uVar4;
        }
        if (uVar10 < 4) {
          uVar10 = 4;
        }
        *(short *)(iVar5 + 0x36) = (short)uVar10;
        *(short *)(iVar5 + 0x32) = (short)(uVar10 * 0x55 >> 8);
        *(undefined1 *)(iVar5 + 0x38) = 1;
        uVar1 = *param_8;
        *(ushort *)(iVar5 + 0xe) = uVar1;
        uVar2 = *param_9;
        *(short *)(iVar5 + 0x50) = (short)((int)((uint)uVar1 + (uint)uVar2) >> 1);
        *(ushort *)(iVar5 + 0x14) = uVar2;
        FUN_ram_00052694((uint)uVar2,iVar5 + 0x50);
        puVar8 = *(undefined **)(iVar5 + 0x50);
        if (&cycleh < *(undefined **)(iVar5 + 0x50)) {
          puVar8 = &cycleh;
        }
        if (puVar8 < 6) {
          puVar8 = (undefined *)0x6;
        }
        *(undefined **)(iVar5 + 0x50) = puVar8;
        uVar10 = (uint)*param_10;
        uVar4 = ZEXT24(puVar8);
        if (499 < uVar10) {
          uVar10 = 499;
        }
        *(short *)(iVar5 + 0x1a) = (short)uVar10;
        uVar11 = (int)((uVar10 + 1) * uVar4) >> 2;
        if ((int)uVar11 < (int)(uint)*param_11) {
          uVar11 = (uint)*param_11;
        }
        *(short *)(iVar5 + 0x20) = (short)uVar11;
        *(undefined2 *)(iVar5 + 0x26) = *param_12;
        *(undefined2 *)(iVar5 + 0x2c) = *param_13;
        uVar9 = uVar11 & 0xffff;
        if (0xc80 < (uVar11 & 0xffff)) {
          uVar9 = 0xc80;
        }
        if (uVar9 < 10) {
          uVar9 = 10;
        }
        if (uVar4 == 0) {
          uVar4 = 0xffffffff;
        }
        else {
          uVar4 = (uVar9 << 2) / uVar4;
        }
        *(short *)(iVar5 + 0x20) = (short)uVar9;
        uVar11 = uVar4 - 1;
        if ((int)uVar10 < (int)(uVar4 - 1)) {
          uVar11 = uVar10;
        }
        *(short *)(iVar5 + 0x1a) = (short)uVar11;
        iVar6 = 1;
      }
      if ((param_5 & 2) != 0) {
        uVar1 = param_8[iVar6];
        *(ushort *)(iVar5 + 0x10) = uVar1;
        uVar2 = param_9[iVar6];
        *(short *)(iVar5 + 0x52) = (short)((int)((uint)uVar1 + (uint)uVar2) >> 1);
        *(ushort *)(iVar5 + 0x16) = uVar2;
        FUN_ram_00052694((uint)uVar2,iVar5 + 0x52);
        puVar8 = *(undefined **)(iVar5 + 0x52);
        if (&cycleh < *(undefined **)(iVar5 + 0x52)) {
          puVar8 = &cycleh;
        }
        if (puVar8 < 6) {
          puVar8 = (undefined *)0x6;
        }
        *(undefined **)(iVar5 + 0x52) = puVar8;
        uVar10 = (uint)param_10[iVar6];
        uVar4 = ZEXT24(puVar8);
        if (499 < uVar10) {
          uVar10 = 499;
        }
        *(short *)(iVar5 + 0x1c) = (short)uVar10;
        uVar11 = (int)((uVar10 + 1) * uVar4) >> 2;
        if ((int)uVar11 < (int)(uint)param_11[iVar6]) {
          uVar11 = (uint)param_11[iVar6];
        }
        *(short *)(iVar5 + 0x22) = (short)uVar11;
        *(undefined2 *)(iVar5 + 0x28) = param_12[iVar6];
        *(undefined2 *)(iVar5 + 0x2e) = param_13[iVar6];
        uVar9 = uVar11 & 0xffff;
        if (0xc80 < (uVar11 & 0xffff)) {
          uVar9 = 0xc80;
        }
        if (uVar9 < 10) {
          uVar9 = 10;
        }
        if (uVar4 == 0) {
          uVar4 = 0xffffffff;
        }
        else {
          uVar4 = (uVar9 << 2) / uVar4;
        }
        *(short *)(iVar5 + 0x22) = (short)uVar9;
        uVar11 = uVar4 - 1;
        if ((int)uVar10 < (int)(uVar4 - 1)) {
          uVar11 = uVar10;
        }
        iVar6 = iVar6 + 1;
        *(short *)(iVar5 + 0x1c) = (short)uVar11;
      }
      if ((param_5 & 4) == 0) {
        *(undefined2 *)(iVar5 + 0x54) = *(undefined2 *)(iVar5 + 0x50);
        *(undefined2 *)(iVar5 + 0x1e) = *(undefined2 *)(iVar5 + 0x1a);
        *(undefined2 *)(iVar5 + 0x24) = *(undefined2 *)(iVar5 + 0x20);
      }
      else {
        uVar4 = (uint)param_6[iVar6];
        if (uVar4 < 4) {
          uVar4 = 4;
        }
        *(short *)(iVar5 + 0x46) = (short)uVar4;
        uVar10 = (uint)param_7[iVar6];
        if (uVar4 < param_7[iVar6]) {
          uVar10 = uVar4;
        }
        if (uVar10 < 4) {
          uVar10 = 4;
        }
        *(short *)(iVar5 + 0x48) = (short)uVar10;
        *(short *)(iVar5 + 0x4a) = (short)(uVar10 * 0x55 >> 8);
        *(byte *)(iVar5 + 0x38) = *(byte *)(iVar5 + 0x38) | 2;
        uVar1 = param_8[iVar6];
        *(ushort *)(iVar5 + 0x12) = uVar1;
        uVar2 = param_9[iVar6];
        *(short *)(iVar5 + 0x54) = (short)((int)((uint)uVar1 + (uint)uVar2) >> 1);
        *(ushort *)(iVar5 + 0x18) = uVar2;
        FUN_ram_00052694((uint)uVar2,iVar5 + 0x54);
        puVar8 = *(undefined **)(iVar5 + 0x54);
        if (&cycleh < *(undefined **)(iVar5 + 0x54)) {
          puVar8 = &cycleh;
        }
        if (puVar8 < 6) {
          puVar8 = (undefined *)0x6;
        }
        *(undefined **)(iVar5 + 0x54) = puVar8;
        uVar10 = (uint)param_10[iVar6];
        uVar4 = ZEXT24(puVar8);
        if (499 < uVar10) {
          uVar10 = 499;
        }
        *(short *)(iVar5 + 0x1e) = (short)uVar10;
        uVar11 = (int)((uVar10 + 1) * uVar4) >> 2;
        if ((int)uVar11 < (int)(uint)param_11[iVar6]) {
          uVar11 = (uint)param_11[iVar6];
        }
        *(short *)(iVar5 + 0x24) = (short)uVar11;
        *(undefined2 *)(iVar5 + 0x2a) = param_12[iVar6];
        *(undefined2 *)(iVar5 + 0x30) = param_13[iVar6];
        uVar9 = uVar11 & 0xffff;
        if (0xc80 < (uVar11 & 0xffff)) {
          uVar9 = 0xc80;
        }
        if (uVar9 < 10) {
          uVar9 = 10;
        }
        if (uVar4 == 0) {
          uVar4 = 0xffffffff;
        }
        else {
          uVar4 = (uVar9 << 2) / uVar4;
        }
        *(short *)(iVar5 + 0x24) = (short)uVar9;
        uVar11 = uVar4 - 1;
        if ((int)uVar10 < (int)(uVar4 - 1)) {
          uVar11 = uVar10;
        }
        *(short *)(iVar5 + 0x1e) = (short)uVar11;
      }
      if ((param_5 & 2) == 0) {
        if ((param_5 & 1) == 0) {
          *(undefined2 *)(iVar5 + 0x52) = *(undefined2 *)(iVar5 + 0x54);
          *(undefined2 *)(iVar5 + 0x1c) = *(undefined2 *)(iVar5 + 0x1e);
          uVar3 = *(undefined2 *)(iVar5 + 0x24);
        }
        else {
          *(undefined2 *)(iVar5 + 0x52) = *(undefined2 *)(iVar5 + 0x50);
          *(undefined2 *)(iVar5 + 0x1c) = *(undefined2 *)(iVar5 + 0x1a);
          uVar3 = *(undefined2 *)(iVar5 + 0x20);
        }
        *(undefined2 *)(iVar5 + 0x22) = uVar3;
      }
      uVar7 = (**(code **)(iVar5 + 0x88))();
      gp = 0x20004000;
      return uVar7;
    }
  }
  gp = 0x20004000;
  return 0x12;
}

