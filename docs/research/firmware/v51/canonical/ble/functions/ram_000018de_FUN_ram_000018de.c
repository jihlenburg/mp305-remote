/* Address: ram:000018de; name: FUN_ram_000018de; body bytes: 874 */

uint FUN_ram_000018de(int param_1,uint param_2,int *param_3,uint param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  undefined4 uVar7;
  byte bVar8;
  int iVar9;
  byte *pbVar10;
  uint uVar11;
  
  uVar2 = DAT_ram_e000e004;
  uVar1 = DAT_ram_e000e000;
  gp = &DAT_ram_20002000;
  DAT_ram_e000e180 = 0xffffffff;
  DAT_ram_e000e184 = 0xffffffff;
  DAT_ram_40001040 = 0xa8;
  uVar11 = param_1 - 9U & 0xff;
  bVar8 = 0xe0;
  if (((1 < uVar11) && (param_1 != 1)) && (bVar8 = 0x20, param_1 == 2)) {
    bVar8 = 0xe0;
  }
  DAT_ram_40001044 = DAT_ram_40001044 | bVar8;
  DAT_ram_40001806 = '\x04';
  FUN_ram_00001822(0xff);
  uVar6 = FUN_ram_00001834();
  if (uVar11 < 3) {
    param_2 = param_2 + 0x70000;
    uVar6 = 0xfffffffe;
    uVar3 = uVar6;
    if ((0x77fff < param_2) || (0x78000 < param_2 + param_4)) goto LAB_ram_000019c6;
    param_2 = param_2 | 0x80000;
    if (param_1 != 10) {
      if (param_1 != 9) {
        uVar6 = FUN_ram_0000185e(0xb,param_2);
        piVar5 = (int *)(param_4 + (int)param_3);
        for (; param_3 != piVar5; param_3 = (int *)((int)param_3 + 1)) {
          uVar6 = FUN_ram_00001842();
          *(char *)param_3 = (char)uVar6;
        }
        goto LAB_ram_0000199e;
      }
      uVar11 = 0x1000;
      uVar3 = 0xff;
LAB_ram_00001a16:
      uVar4 = ~uVar3 & (param_2 & uVar3) + uVar3 + param_4;
      param_2 = ~uVar3 & param_2;
      do {
        if ((uVar11 - 1 & param_2) == 0) {
          for (; uVar11 <= uVar4; uVar4 = uVar4 - uVar11) {
            uVar7 = 0xd8;
            if ((uVar11 != 0x10000) && (uVar7 = 0x20, uVar11 != 0x1000)) {
              uVar7 = 0x81;
            }
            FUN_ram_0000185e(uVar7,param_2);
            uVar6 = FUN_ram_000018a6();
            if (uVar6 == 0) goto LAB_ram_000019c4;
            param_2 = param_2 + uVar11;
          }
        }
        uVar11 = uVar11 >> 4;
      } while (0x10 < uVar11);
      goto LAB_ram_0000199e;
    }
    do {
      if (param_4 == 0) goto LAB_ram_0000199e;
      FUN_ram_0000185e(2,param_2);
      piVar5 = param_3;
      do {
        param_3 = (int *)((int)piVar5 + 1);
        param_4 = param_4 - 1;
        param_2 = param_2 + 1;
        FUN_ram_00001850((char)*piVar5);
        if (param_4 == 0) break;
        piVar5 = param_3;
      } while ((param_2 & 0xff) != 0);
      uVar6 = FUN_ram_000018a6();
    } while (uVar6 != 0);
LAB_ram_000019c4:
    uVar3 = 0xffffffff;
    goto LAB_ram_000019c6;
  }
  if ((param_1 - 1U & 0xff) < 3) {
    if (((DAT_ram_40001041 == -0x7d) && (0x7ffff < param_2)) && (param_2 + param_4 < 0x100000)) {
      param_2 = param_2 ^ 0x80000;
    }
    else {
      uVar11 = 0x80000;
      if ((DAT_ram_40001045 & 0x20) == 0) {
        uVar11 = 0x78000;
      }
      uVar6 = 0xfffffffe;
      uVar3 = 0xfffffffe;
      if ((uVar11 <= param_2) || (uVar11 < param_2 + param_4)) goto LAB_ram_000019c6;
    }
    if (param_1 == 2) {
      param_4 = param_4 >> 2;
      do {
        if (param_4 == 0) goto LAB_ram_0000199e;
        FUN_ram_0000185e(2,param_2);
        piVar5 = param_3;
        do {
          param_3 = piVar5 + 1;
          DAT_ram_40001800 = *piVar5;
          iVar9 = 4;
          do {
            do {
            } while (DAT_ram_40001806 < '\0');
            DAT_ram_40001806 = '\x15';
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
          param_4 = param_4 - 1;
          param_2 = param_2 + 4;
        } while ((param_4 != 0) && (piVar5 = param_3, (param_2 & 0xff) != 0));
        uVar6 = FUN_ram_000018a6();
      } while (uVar6 != 0);
      goto LAB_ram_000019c4;
    }
    if (param_1 == 1) {
      uVar11 = 0x10000;
      uVar3 = 0xfff;
      goto LAB_ram_00001a16;
    }
    uVar6 = FUN_ram_0000185e(0xb,param_2);
    do {
      uVar3 = param_4;
      param_4 = uVar3 - 1;
      if (uVar3 == 0) goto LAB_ram_0000199e;
      uVar6 = FUN_ram_00001842();
    } while (((param_4 & 3) != 0) ||
            (iVar9 = *param_3, param_3 = param_3 + 1, DAT_ram_40001800 == iVar9));
  }
  else {
    if (param_1 == 0xd) {
      uVar6 = 0xb9;
LAB_ram_00001b60:
      uVar6 = FUN_ram_00001822(uVar6);
    }
    else {
      uVar6 = 0xab;
      if (param_1 == 0xc) goto LAB_ram_00001b60;
      if (param_1 == 6) {
        FUN_ram_0000185e(0xb,param_2 | 0x80000);
        iVar9 = 0;
        do {
          uVar6 = FUN_ram_00001842();
          if (iVar9 == 3) {
            *param_3 = DAT_ram_40001800;
          }
          iVar9 = iVar9 + 1;
        } while (iVar9 != 8);
        if ((int)(param_2 << 0x12) < 0) {
          *(short *)(param_3 + 1) = (short)DAT_ram_40001800;
        }
        else {
          param_3[1] = DAT_ram_40001800;
        }
      }
      else if (param_1 == 7) {
        FUN_ram_0000185e(0x4b,0);
        uVar11 = 0xf;
        *param_3 = 0;
        param_3[1] = 0;
        do {
          uVar6 = FUN_ram_00001842();
          pbVar10 = (byte *)((uVar11 & 7) + (int)param_3);
          uVar11 = uVar11 - 1;
          uVar6 = uVar6 ^ *pbVar10;
          *pbVar10 = (byte)uVar6;
        } while (uVar11 != 0xffffffff);
      }
      else if (param_1 == 8) {
        uVar6 = FUN_ram_000018a6(0xab);
        uVar11 = 0;
        if (((param_2 != 0) && (uVar11 = 0x3c, param_2 != 3)) && (uVar11 = 0x50, param_2 != 2)) {
          uVar11 = 0x44;
        }
        uVar6 = uVar6 & 0x7c;
        if (uVar6 != uVar11) {
          FUN_ram_00001822(6);
          FUN_ram_00001834();
          FUN_ram_00001822(1);
          FUN_ram_00001850(uVar11);
          FUN_ram_00001850(2);
          uVar6 = FUN_ram_000018a6();
          if (uVar6 == 0) goto LAB_ram_000019c4;
        }
      }
      else {
        if (param_1 == 4) {
          FUN_ram_00001822(0x66);
          FUN_ram_00001834();
          uVar6 = 0x99;
          goto LAB_ram_00001b60;
        }
        if (param_1 != 0) {
          uVar3 = 0xfffffffc;
          goto LAB_ram_000019a0;
        }
      }
    }
LAB_ram_0000199e:
    uVar3 = 0;
  }
LAB_ram_000019a0:
  FUN_ram_00001834(uVar6);
LAB_ram_000019c6:
  DAT_ram_40001040 = 0xa8;
  DAT_ram_40001044 = DAT_ram_40001044 & 0x10;
  DAT_ram_e000e100 = uVar1;
  DAT_ram_e000e104 = uVar2;
  return uVar3;
}

