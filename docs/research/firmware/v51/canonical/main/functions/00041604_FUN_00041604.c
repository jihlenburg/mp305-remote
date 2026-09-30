/* Address: 00041604; name: FUN_00041604; body bytes: 310 */

undefined4 FUN_00041604(uint *param_1)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  
  if (param_1 == (uint *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar2 = *param_1 >> 0x10;
  if (((uVar2 & 1) == 0) && ((int)(uVar2 << 0x1a) < 0)) {
    uVar2 = (*param_1 & 0xffff) >> 8;
    if (uVar2 - 7 < 4) {
      if (uVar2 == 7) {
        iVar7 = 2;
      }
      else if (uVar2 == 8) {
        iVar7 = 4;
      }
      else if (uVar2 == 9) {
        iVar7 = 0x10;
      }
      else if (uVar2 == 10) {
        iVar7 = 0x100;
      }
      else {
        iVar7 = 0;
      }
      uVar2 = param_1[4];
      for (iVar5 = 0; iVar5 < iVar7; iVar5 = iVar5 + 1) {
        FUN_0004050c(uVar2 + iVar5 * 4);
      }
    }
    else if (uVar2 == 0x10) {
      uVar4 = param_1[1];
      uVar2 = param_1[2];
      uVar10 = param_1[4];
      for (uVar9 = 0; uVar9 < uVar4 >> 0x10; uVar9 = uVar9 + 1) {
        uVar6 = uVar10;
        for (uVar8 = 0; uVar8 < (uVar4 & 0xffff); uVar8 = uVar8 + 1) {
          FUN_0004050c(uVar6);
          uVar6 = uVar6 + 4;
        }
        uVar10 = uVar10 + (ushort)uVar2;
      }
    }
    else if (uVar2 == 0x14) {
      uVar2 = param_1[1];
      uVar10 = uVar2 >> 0x10;
      uVar1 = (ushort)param_1[2];
      uVar9 = param_1[4];
      iVar7 = uVar1 * uVar10 + uVar9;
      for (uVar4 = 0; uVar4 < uVar10; uVar4 = uVar4 + 1) {
        uVar6 = uVar9;
        for (uVar8 = 0; uVar8 < (uVar2 & 0xffff); uVar8 = uVar8 + 1) {
          FUN_0003feaa(uVar6,*(undefined1 *)(iVar7 + uVar8));
          uVar6 = uVar6 + 2;
        }
        uVar9 = uVar9 + uVar1;
        iVar7 = iVar7 + (uint)(uVar1 >> 1);
      }
    }
    else if (uVar2 == 0x13) {
      uVar4 = param_1[1];
      uVar2 = param_1[2];
      uVar10 = param_1[4];
      for (uVar9 = 0; uVar9 < uVar4 >> 0x10; uVar9 = uVar9 + 1) {
        uVar6 = uVar10;
        for (uVar8 = 0; uVar8 < (uVar4 & 0xffff); uVar8 = uVar8 + 1) {
          FUN_0003feaa(uVar6,*(undefined1 *)(uVar6 + 2));
          uVar6 = uVar6 + 3;
        }
        uVar10 = uVar10 + (ushort)uVar2;
      }
    }
    uVar3 = 1;
    *(ushort *)((int)param_1 + 2) = (ushort)(*param_1 >> 0x10) | 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

