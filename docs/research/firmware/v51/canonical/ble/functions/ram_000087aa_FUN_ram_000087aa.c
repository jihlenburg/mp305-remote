/* Address: ram:000087aa; name: FUN_ram_000087aa; body bytes: 680 */

uint FUN_ram_000087aa(undefined4 param_1,uint *param_2,undefined4 param_3,code *param_4,int *param_5
                     )

{
  bool bVar1;
  byte bVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  char *pcVar13;
  uint uStack_24;
  
  gp = &DAT_ram_20002000;
  bVar2 = (byte)param_2[6];
  pcVar7 = (char *)((int)param_2 + 0x43);
  pcVar13 = pcVar7;
  if (bVar2 == 0x69) {
LAB_ram_0000880a:
    uVar9 = *param_2;
    puVar3 = (uint *)*param_5;
    if ((uVar9 & 0x80) == 0) {
      uVar10 = *puVar3;
      *param_5 = (int)(puVar3 + 1);
      if ((uVar9 & 0x40) != 0) {
        uVar10 = (uint)(short)uVar10;
      }
    }
    else {
      uVar10 = *puVar3;
      *param_5 = (int)(puVar3 + 1);
    }
    if ((int)uVar10 < 0) {
      uVar10 = -uVar10;
      *(undefined1 *)((int)param_2 + 0x43) = 0x2d;
    }
    pcVar8 = "0123456789ABCDEF";
    uVar9 = 10;
LAB_ram_000088f0:
    uVar6 = param_2[1];
    param_2[2] = uVar6;
    if (-1 < (int)uVar6) {
      *param_2 = *param_2 & 0xfffffffb;
    }
    if ((uVar10 != 0) || (uVar6 != 0)) {
      do {
        uVar6 = uVar10;
        if (uVar9 != 0) {
          uVar6 = uVar10 % uVar9;
        }
        pcVar13 = pcVar13 + -1;
        *pcVar13 = pcVar8[uVar6];
        if (uVar9 == 0) {
          uVar6 = 0xffffffff;
        }
        else {
          uVar6 = uVar10 / uVar9;
        }
        bVar1 = uVar9 <= uVar10;
        uVar10 = uVar6;
      } while (bVar1);
    }
    if (((uVar9 == 8) && ((*param_2 & 1) != 0)) && ((int)param_2[1] <= (int)param_2[4])) {
      pcVar13[-1] = '0';
      pcVar13 = pcVar13 + -1;
    }
    param_2[4] = (int)pcVar7 - (int)pcVar13;
    goto LAB_ram_00008942;
  }
  if (bVar2 < 0x6a) {
    if (bVar2 == 0x58) {
      *(undefined1 *)((int)param_2 + 0x45) = 0x58;
      pcVar8 = "0123456789ABCDEF";
LAB_ram_00008976:
      uVar9 = *param_2;
      uVar10 = *(uint *)*param_5;
      puVar3 = (uint *)*param_5 + 1;
      if ((uVar9 & 0x80) == 0) {
        *param_5 = (int)puVar3;
        if ((uVar9 & 0x40) != 0) {
          uVar10 = uVar10 & 0xffff;
        }
      }
      else {
        *param_5 = (int)puVar3;
      }
      if ((uVar9 & 1) != 0) {
        *param_2 = uVar9 | 0x20;
      }
      uVar9 = 0x10;
      if (uVar10 == 0) {
        *param_2 = *param_2 & 0xffffffdf;
        uVar9 = 0x10;
      }
LAB_ram_000088ec:
      *(undefined1 *)((int)param_2 + 0x43) = 0;
      goto LAB_ram_000088f0;
    }
    if (bVar2 < 0x59) {
      if (bVar2 == 0) {
LAB_ram_00008a04:
        param_2[4] = 0;
        goto LAB_ram_00008942;
      }
      if (bVar2 == 0x43) goto LAB_ram_000088a8;
LAB_ram_000087f0:
      *(byte *)((int)param_2 + 0x42) = bVar2;
    }
    else {
      if (bVar2 != 99) {
        if (bVar2 == 100) goto LAB_ram_0000880a;
        goto LAB_ram_000087f0;
      }
LAB_ram_000088a8:
      uVar11 = *(undefined4 *)*param_5;
      *param_5 = (int)((undefined4 *)*param_5 + 1);
      *(char *)((int)param_2 + 0x42) = (char)uVar11;
    }
    pcVar13 = (char *)((int)param_2 + 0x42);
    uVar10 = 1;
  }
  else {
    if (bVar2 == 0x70) {
      *param_2 = *param_2 | 0x20;
LAB_ram_000089aa:
      *(undefined1 *)((int)param_2 + 0x45) = 0x78;
      pcVar8 = "0123456789abcdef";
      goto LAB_ram_00008976;
    }
    if (bVar2 < 0x71) {
      if (bVar2 == 0x6e) {
        uVar9 = *param_2;
        puVar12 = (undefined4 *)*param_5;
        uVar10 = param_2[5];
        if ((uVar9 & 0x80) == 0) {
          *param_5 = (int)(puVar12 + 1);
          puVar3 = (uint *)*puVar12;
          if ((uVar9 & 0x40) != 0) {
            *(short *)puVar3 = (short)uVar10;
            goto LAB_ram_00008a04;
          }
        }
        else {
          *param_5 = (int)(puVar12 + 1);
          puVar3 = (uint *)*puVar12;
        }
        *puVar3 = uVar10;
        goto LAB_ram_00008a04;
      }
      if (bVar2 != 0x6f) goto LAB_ram_000087f0;
LAB_ram_00008854:
      uVar10 = *param_2;
      puVar3 = (uint *)*param_5;
      if ((uVar10 & 0x80) == 0) {
        *param_5 = (int)(puVar3 + 1);
        if ((uVar10 & 0x40) == 0) goto LAB_ram_00008866;
        uVar10 = (uint)(ushort)*puVar3;
      }
      else {
        *param_5 = (int)(puVar3 + 1);
LAB_ram_00008866:
        uVar10 = *puVar3;
      }
      if (bVar2 == 0x6f) {
        pcVar8 = "0123456789ABCDEF";
        uVar9 = 8;
      }
      else {
        pcVar8 = "0123456789ABCDEF";
        uVar9 = 10;
      }
      goto LAB_ram_000088ec;
    }
    if (bVar2 == 0x75) goto LAB_ram_00008854;
    if (bVar2 == 0x78) goto LAB_ram_000089aa;
    if (bVar2 != 0x73) goto LAB_ram_000087f0;
    puVar12 = (undefined4 *)*param_5;
    uVar10 = param_2[1];
    *param_5 = (int)(puVar12 + 1);
    pcVar13 = (char *)*puVar12;
    iVar4 = FUN_ram_00008cbc(pcVar13,0,uVar10);
    if (iVar4 != 0) {
      param_2[1] = iVar4 - (int)pcVar13;
    }
    uVar10 = param_2[1];
  }
  param_2[4] = uVar10;
  *(undefined1 *)((int)param_2 + 0x43) = 0;
LAB_ram_00008942:
  iVar4 = FUN_ram_0000869e(param_1,param_2,&uStack_24,param_3,param_4);
  if ((iVar4 == -1) || (iVar4 = (*param_4)(param_1,param_3,pcVar13,param_2[4]), iVar4 == -1)) {
LAB_ram_00008954:
    uVar10 = 0xffffffff;
  }
  else {
    if ((*param_2 & 2) != 0) {
      for (iVar4 = 0; iVar4 < (int)(param_2[3] - uStack_24); iVar4 = iVar4 + 1) {
        iVar5 = (*param_4)(param_1,param_3,(int)param_2 + 0x19,1);
        if (iVar5 == -1) goto LAB_ram_00008954;
      }
    }
    uVar10 = param_2[3];
    if ((int)param_2[3] < (int)uStack_24) {
      uVar10 = uStack_24;
    }
  }
  return uVar10;
}

