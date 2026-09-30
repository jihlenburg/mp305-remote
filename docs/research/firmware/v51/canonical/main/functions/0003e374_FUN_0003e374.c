/* Address: 0003e374; name: FUN_0003e374; body bytes: 528 */

/* Recovered from stored Thumb pointer at 0003e640; callback identification is inferred until
   reviewed. */

undefined4 FUN_0003e374(undefined4 param_1,int param_2,uint *param_3,uint *param_4)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  undefined4 *puVar13;
  int iVar14;
  
  uVar11 = (uint)(*(ushort *)(param_2 + 0x20) >> 8);
  uVar2 = uVar11 - 7;
  if (((((uVar2 < 4) || (uVar11 == 0x10)) || (uVar11 == 0x11)) ||
      ((uVar11 == 0xf || (uVar11 == 0x12)))) || ((uVar11 == 0x13 || (uVar11 == 0x14)))) {
    puVar13 = *(undefined4 **)(param_2 + 0x48);
    if (puVar13 == (undefined4 *)0x0) {
      return 0;
    }
    uVar3 = *puVar13;
    uVar4 = FUN_00040314(uVar11);
    uVar5 = FUN_0003db28(param_3);
    if (*(char *)(param_2 + 0x10) == '\x01') {
      iVar6 = 0xc;
    }
    else {
      iVar6 = 0;
    }
    if (param_4[1] == 0xe0000001) {
      uVar8 = uVar11;
      if (uVar2 < 4) {
        uVar8 = 0x10;
      }
      iVar7 = FUN_0004173e(puVar13[0x10],uVar8,uVar5,1,0);
      if (iVar7 == 0) {
        if (puVar13[0x10] != 0) {
          FUN_000413fe();
          puVar13[0x10] = 0;
        }
        iVar7 = FUN_0004137c(&DAT_2003a518,uVar5,1,uVar8,0);
        if (iVar7 == 0) {
          return 0;
        }
        puVar13[0x10] = iVar7;
      }
      uVar8 = param_3[1];
      uVar10 = param_3[2];
      *param_4 = *param_3;
      param_4[1] = uVar8;
      param_4[2] = uVar10;
      param_4[3] = uVar8;
    }
    else {
      param_4[1] = param_4[1] + 1;
      param_4[3] = param_4[3] + 1;
      iVar7 = puVar13[0x10];
    }
    uVar8 = param_4[1];
    iVar14 = *(int *)(iVar7 + 0x10);
    if ((int)uVar8 <= (int)param_3[3]) {
      if (uVar2 < 4) {
        uVar2 = *param_4;
        iVar9 = (uVar5 * uVar4 + 7 >> 3) + 1;
        iVar6 = uVar8 * *(ushort *)(param_2 + 0x28) + iVar6 + *(int *)(param_2 + 0x34) * 4 +
                (uVar2 * uVar4 >> 3);
        if (*(char *)(param_2 + 0x10) == '\x01') {
          iVar12 = FUN_0004a318(iVar9);
          if (iVar12 == 0) {
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
          iVar6 = FUN_00036b7c(uVar3,iVar6,iVar12,iVar9,0);
          if (iVar6 != 0) {
            FUN_00046bec(iVar12);
            return 0;
          }
        }
        else {
          iVar12 = *(int *)(*(int *)(param_2 + 0xc) + 0x10) + iVar6;
        }
        FUN_00027f94(uVar11,*(undefined4 *)(param_2 + 0x30),
                     uVar2 - (8 / uVar4) * (uVar2 / (8 / uVar4)),uVar5,iVar12,iVar14);
        if (*(char *)(param_2 + 0x10) == '\x01') {
          FUN_00046bec(iVar12);
        }
      }
      else {
        if (((uVar11 == 0x10) || (uVar11 == 0x11)) ||
           ((uVar11 == 0xf || ((uVar11 == 0x12 || (uVar11 == 0x13)))))) {
          uVar5 = uVar5 * uVar4 >> 3;
          iVar6 = uVar8 * *(ushort *)(param_2 + 0x28) + iVar6 + (*param_4 * uVar4 >> 3);
        }
        else {
          if (uVar11 != 0x14) {
            return 0;
          }
          uVar1 = *(ushort *)(iVar7 + 8);
          iVar6 = FUN_00036b7c(uVar3,uVar8 * *(ushort *)(param_2 + 0x28) + iVar6 +
                                     (*param_4 & 0xfffffff) * 2,iVar14,(uint)uVar1,0);
          if (iVar6 != 0) {
            return 0;
          }
          iVar14 = iVar14 + (uint)uVar1;
          iVar6 = *param_4 +
                  param_4[1] * (uint)(*(ushort *)(param_2 + 0x28) >> 1) +
                  (*(uint *)(param_2 + 0x24) >> 0x10) * (uint)*(ushort *)(param_2 + 0x28) + 0xc;
        }
        iVar6 = FUN_00036b7c(uVar3,iVar6,iVar14,uVar5,0);
        if (iVar6 != 0) {
          return 0;
        }
      }
      *(int *)(param_2 + 0x2c) = iVar7;
      return 1;
    }
  }
  return 0;
}

