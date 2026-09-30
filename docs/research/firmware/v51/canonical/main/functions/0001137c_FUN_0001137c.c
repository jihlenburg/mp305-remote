/* Address: 0001137c; name: FUN_0001137c; body bytes: 556 */

int FUN_0001137c(undefined4 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined1 *puVar12;
  int iVar13;
  char *pcVar14;
  char *pcVar15;
  undefined1 local_68;
  char local_67 [23];
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_48 [12];
  undefined1 *local_3c;
  undefined4 uStack_34;
  undefined4 local_30;
  int *local_2c;
  int *piStack_28;
  
  uVar7 = param_4[1];
  iVar10 = param_4[2];
  iVar13 = 0;
  local_3c = (undefined1 *)0x2e;
  iVar9 = -1;
  uStack_34 = param_1;
  local_30 = param_2;
  local_2c = param_3;
  piStack_28 = param_4;
  do {
    iVar3 = iVar9;
    iVar9 = iVar3 + 1;
    puVar1 = (undefined1 *)(*(code *)param_4[6])(local_30);
    iVar2 = (*(code *)param_4[8])();
  } while (iVar2 != 0);
  if (puVar1 == (undefined1 *)0xffffffff) {
    return -1;
  }
  uVar7 = uVar7 & 0xfffff97f;
  if (0 < iVar10) {
    if (puVar1 != (undefined1 *)0x2b) {
      if (puVar1 != (undefined1 *)0x2d) goto LAB_000113da;
      uVar7 = uVar7 | 0x400;
    }
    iVar9 = iVar3 + 2;
    puVar1 = (undefined1 *)(*(code *)param_4[6])(local_30);
    iVar10 = iVar10 + -1;
  }
LAB_000113da:
  if ((int)(uVar7 << 0x15) < 0) {
    local_68 = 0x2d;
  }
  else {
    local_68 = 0x2b;
  }
  pcVar15 = local_67;
  puVar12 = local_48;
  while ((0 < iVar10 && (puVar1 == &Reserved5))) {
    iVar9 = iVar9 + 1;
    puVar1 = (undefined1 *)(*(code *)param_4[6])(local_30);
    uVar7 = uVar7 | 0x200;
    iVar10 = iVar10 + -1;
    *local_2c = iVar9;
  }
  if (puVar1 == local_3c) {
    uVar7 = uVar7 | 0x80;
    iVar2 = iVar9;
    while( true ) {
      iVar9 = iVar2 + 1;
      iVar10 = iVar10 + -1;
      puVar1 = (undefined1 *)(*(code *)param_4[6])(local_30);
      if (puVar1 != &Reserved5) break;
      iVar13 = iVar13 + -1;
      uVar7 = uVar7 | 0x200;
      *local_2c = iVar2 + 2;
      iVar2 = iVar9;
    }
  }
  do {
    if (iVar10 < 1) {
LAB_00011544:
      (*(code *)param_4[7])(local_30);
      *pcVar15 = -1;
      *puVar12 = 0xff;
      local_50 = 0;
      local_4c = 0;
      FUN_00011254(&local_50,local_48,&local_68,iVar13);
      if (-1 < (int)(uVar7 << 0x16)) {
        return -2;
      }
      if ((uVar7 & 0x24) != 0) {
        if ((uVar7 & 1) != 0) {
          return iVar9;
        }
        piVar4 = (int *)*param_4;
        *param_4 = (int)(piVar4 + 1);
        puVar5 = (undefined4 *)*piVar4;
        *puVar5 = local_50;
        puVar5[1] = local_4c;
        return iVar9;
      }
      uVar6 = FUN_00010b48(local_50,local_4c);
      if ((uVar7 & 1) != 0) {
        return iVar9;
      }
      puVar5 = (undefined4 *)*param_4;
      *param_4 = (int)(puVar5 + 1);
      *(undefined4 *)*puVar5 = uVar6;
      return iVar9;
    }
    if ((puVar1 == local_3c) && (-1 < (int)(uVar7 << 0x18))) {
      uVar8 = uVar7 | 0x80;
    }
    else {
      iVar2 = FUN_00020bda(puVar1);
      if (iVar2 == 0) {
        if ((0 < iVar10) &&
           (((puVar1 == (undefined1 *)0x65 || (puVar1 == (undefined1 *)0x45)) &&
            ((int)(uVar7 << 0x16) < 0)))) {
          uVar7 = uVar7 & 0xfffffcff;
          iVar11 = iVar10 + -1;
          iVar3 = (*(code *)param_4[6])(local_30);
          iVar2 = iVar9 + 1;
          if (0 < iVar11) {
            if (iVar3 != 0x2b) {
              if (iVar3 != 0x2d) goto LAB_000114de;
              uVar7 = uVar7 | 0x100;
            }
            iVar3 = (*(code *)param_4[6])(local_30);
            iVar11 = iVar10 + -2;
            iVar2 = iVar9 + 2;
          }
LAB_000114de:
          iVar9 = iVar2;
          if ((int)(uVar7 << 0x17) < 0) {
            local_48[0] = 0x2d;
          }
          else {
            local_48[0] = 0x2b;
          }
          puVar12 = local_48 + 1;
          local_3c = puVar12;
          while ((0 < iVar11 && (iVar10 = FUN_00020bda(iVar3), iVar10 != 0))) {
            iVar11 = iVar11 + -1;
            if (puVar12 < local_48 + 9) {
              *puVar12 = (char)(iVar3 - 0x30U);
              if (((iVar3 - 0x30U & 0xff) != 0) || (local_3c < puVar12)) {
                puVar12 = puVar12 + 1;
              }
            }
            else if ((int)(uVar7 << 0x17) < 0) {
              iVar13 = -9999;
            }
            else {
              iVar13 = 9999;
            }
            iVar9 = iVar9 + 1;
            iVar3 = (*(code *)param_4[6])(local_30);
            *local_2c = iVar9;
            uVar7 = uVar7 | 0x200;
          }
        }
        goto LAB_00011544;
      }
      uVar8 = uVar7 | 0x200;
      if (pcVar15 < local_67 + 0x12) {
        pcVar14 = pcVar15 + 1;
        *pcVar15 = (char)puVar1 + -0x30;
        pcVar15 = pcVar14;
        if ((int)(uVar7 << 0x18) < 0) {
          iVar13 = iVar13 + -1;
        }
      }
      else if (-1 < (int)(uVar7 << 0x18)) {
        iVar13 = iVar13 + 1;
      }
    }
    iVar10 = iVar10 + -1;
    if ((int)(uVar8 << 0x16) < 0) {
      *local_2c = iVar9 + 1;
    }
    iVar9 = iVar9 + 1;
    puVar1 = (undefined1 *)(*(code *)param_4[6])(local_30);
    uVar7 = uVar8;
  } while( true );
}

