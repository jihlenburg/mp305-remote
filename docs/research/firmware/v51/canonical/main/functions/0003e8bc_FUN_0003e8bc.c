/* Address: 0003e8bc; name: FUN_0003e8bc; body bytes: 1202 */

void FUN_0003e8bc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  
  uStack_30 = param_2;
  uStack_2c = param_3;
  local_28 = param_4;
  iVar3 = FUN_0004b9b2(&PTR_DAT_0007a5fc);
  if (iVar3 != 1) {
    return;
  }
  iVar3 = FUN_00046688(param_2);
  iVar4 = FUN_00046698(param_2);
  if (iVar3 == 0x18) {
    if (*(int *)(iVar4 + 0x3c) == 0) {
      return;
    }
    iVar7 = 0;
    iVar8 = *(int *)(iVar4 + 0x2c);
    while( true ) {
      iVar9 = *(int *)(iVar8 + iVar7 * 4);
      if (iVar9 == 0) {
        return;
      }
      iVar9 = thunk_FUN_00050a1a(iVar9,&LAB_0003ecc0);
      if (iVar9 == 0) {
        return;
      }
      if (**(char **)(iVar8 + iVar7 * 4) == '\0') {
        return;
      }
      if ((int)((uint)*(ushort *)(*(int *)(iVar4 + 0x34) + iVar7 * 2) << 0x15) < 0) break;
      iVar7 = iVar7 + 1;
    }
    if (*(int *)(iVar4 + 0x3c) == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = FUN_0004baf8(iVar4);
      uVar6 = uVar6 / *(uint *)(iVar4 + 0x3c);
    }
    FUN_00046862(param_2,uVar6);
  }
  else if (iVar3 == 0x2f) goto LAB_0003e978;
  if (iVar3 == 0x2e) {
LAB_0003e978:
    FUN_0003ee60(iVar4,*(undefined4 *)(iVar4 + 0x2c));
    return;
  }
  if (iVar3 == 1) {
    uVar5 = FUN_000466ae(param_2);
    FUN_0003aa70(iVar4,*(undefined4 *)(iVar4 + 0x40));
    FUN_00047eec();
    iVar3 = FUN_000482e0();
    if ((iVar3 == 1) || (iVar3 == 3)) {
      FUN_00048288(uVar5,&uStack_30);
      iVar3 = FUN_00036f38(iVar4,&uStack_30);
      *(undefined4 *)(iVar4 + 0x40) = 0xffff;
      if (iVar3 == 0xffff) {
        return;
      }
      uVar6 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + iVar3 * 2);
      if ((int)(uVar6 << 0x19) < 0) {
        return;
      }
      if ((int)(uVar6 << 0x1b) < 0) {
        return;
      }
      *(int *)(iVar4 + 0x40) = iVar3;
      FUN_0003aa70(iVar4,iVar3);
    }
    if (*(int *)(iVar4 + 0x40) == 0xffff) {
      return;
    }
    uVar6 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + *(int *)(iVar4 + 0x40) * 2);
    if ((int)(uVar6 << 0x16) < 0) {
      return;
    }
    iVar3 = uVar6 << 0x15;
LAB_0003eac2:
    if (iVar3 < 0) {
      return;
    }
    if ((int)(uVar6 << 0x19) < 0) {
      return;
    }
    if ((int)(uVar6 << 0x1b) < 0) {
      return;
    }
    local_28 = *(undefined4 *)(iVar4 + 0x40);
    FUN_0004e5a6(iVar4,0x20,&local_28);
    return;
  }
  if (iVar3 == 2) {
    if (*(int *)(iVar4 + 0x40) == 0xffff) {
      return;
    }
    uVar5 = FUN_000466ae(param_2);
    FUN_00048288(uVar5,&uStack_30);
    iVar3 = FUN_00036f38(iVar4,&uStack_30);
    iVar7 = *(int *)(iVar4 + 0x40);
    if (iVar7 == iVar3) {
      return;
    }
LAB_0003eadc:
    FUN_0003aa70(iVar4,iVar7);
LAB_0003eb72:
    *(undefined4 *)(iVar4 + 0x40) = 0xffff;
    return;
  }
  if (iVar3 == 8) {
    iVar3 = *(int *)(iVar4 + 0x40);
    if (iVar3 != 0xffff) {
      uVar2 = *(ushort *)(*(int *)(iVar4 + 0x34) + iVar3 * 2);
      uVar6 = (uint)uVar2;
      if (((int)(uVar6 << 0x18) < 0) && (-1 < (int)(uVar6 << 0x19))) {
        if (((int)(uVar6 << 0x17) < 0) && ((*(byte *)(iVar4 + 0x44) & 1) == 0)) {
          uVar2 = uVar2 & 0xfeff;
        }
        else {
          uVar2 = uVar2 | 0x100;
        }
        *(ushort *)(*(int *)(iVar4 + 0x34) + iVar3 * 2) = uVar2;
        if ((*(byte *)(iVar4 + 0x44) & 1) != 0) {
          FUN_00053534(iVar4,*(undefined4 *)(iVar4 + 0x40));
        }
      }
      uVar6 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + *(int *)(iVar4 + 0x40) * 2);
      if (((((int)(uVar6 << 0x16) < 0) || ((int)(uVar6 << 0x15) < 0)) && (-1 < (int)(uVar6 << 0x19))
          ) && (-1 < (int)(uVar6 << 0x1b))) {
        local_28 = *(undefined4 *)(iVar4 + 0x40);
        iVar3 = FUN_0004e5a6(iVar4,0x20,&local_28);
        if (iVar3 != 1) {
          return;
        }
      }
    }
    goto LAB_0003eaa8;
  }
  if (iVar3 == 6) {
    if (*(int *)(iVar4 + 0x40) == 0xffff) {
      return;
    }
    uVar6 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + *(int *)(iVar4 + 0x40) * 2);
    iVar3 = uVar6 << 0x1a;
    goto LAB_0003eac2;
  }
  if (iVar3 == 3) {
    iVar7 = *(int *)(iVar4 + 0x40);
    goto LAB_0003eadc;
  }
  if (iVar3 == 0x10) {
    if (*(int *)(iVar4 + 0x38) == 0) {
      return;
    }
    iVar3 = FUN_000466ae(param_2);
    iVar7 = FUN_000482e0();
    if (iVar3 == 0) {
      FUN_00048270(0);
      iVar7 = FUN_000482e0();
    }
    FUN_0004bbe2(iVar4);
    iVar3 = FUN_000472d4();
    if (*(int *)(iVar4 + 0x40) != 0xffff) {
      return;
    }
    if ((iVar7 == 2) || ((iVar7 == 4 && (iVar3 != 0)))) {
      uVar6 = 0;
      if ((*(byte *)(iVar4 + 0x44) & 1) == 0) {
        while ((uVar6 < *(uint *)(iVar4 + 0x38) &&
               ((uVar11 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + uVar6 * 2),
                (int)(uVar11 << 0x1b) < 0 || ((int)(uVar11 << 0x19) < 0))))) {
          uVar6 = uVar6 + 1;
        }
      }
      else {
        while ((uVar6 < *(uint *)(iVar4 + 0x38) &&
               (((uVar11 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + uVar6 * 2),
                 (int)(uVar11 << 0x1b) < 0 || ((int)(uVar11 << 0x19) < 0)) ||
                (-1 < (int)(uVar11 << 0x17)))))) {
          uVar6 = uVar6 + 1;
        }
      }
      *(uint *)(iVar4 + 0x40) = uVar6;
      return;
    }
    goto LAB_0003eb72;
  }
  if (iVar3 == 0x11) {
    return;
  }
  if (iVar3 == 0x12) {
    return;
  }
  if (iVar3 != 0xe) {
    if (iVar3 != 0x1a) {
      return;
    }
    FUN_0002d378(param_2);
    return;
  }
  FUN_0003aa70(iVar4,*(undefined4 *)(iVar4 + 0x40));
  iVar3 = FUN_00046700(param_2);
  if (iVar3 == 0x13) {
    if (*(int *)(iVar4 + 0x40) == 0xffff) {
      uVar6 = 0;
      *(undefined4 *)(iVar4 + 0x40) = 0;
    }
    else {
      uVar6 = *(int *)(iVar4 + 0x40) + 1;
      *(uint *)(iVar4 + 0x40) = uVar6;
    }
    if (*(uint *)(iVar4 + 0x38) <= uVar6) {
      *(undefined4 *)(iVar4 + 0x40) = 0;
    }
    iVar3 = *(int *)(iVar4 + 0x40);
    do {
      uVar6 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + *(int *)(iVar4 + 0x40) * 2);
      if ((-1 < (int)(uVar6 << 0x1b)) && (-1 < (int)(uVar6 << 0x19))) goto LAB_0003eaa8;
      uVar6 = *(int *)(iVar4 + 0x40) + 1;
      *(uint *)(iVar4 + 0x40) = uVar6;
      if (*(uint *)(iVar4 + 0x38) <= uVar6) {
        *(undefined4 *)(iVar4 + 0x40) = 0;
      }
    } while (*(int *)(iVar4 + 0x40) != iVar3);
  }
  else if (iVar3 == 0x14) {
    iVar3 = *(int *)(iVar4 + 0x40);
    if (iVar3 == 0xffff) {
      *(undefined4 *)(iVar4 + 0x40) = 0;
LAB_0003ec04:
      iVar3 = *(int *)(iVar4 + 0x38);
    }
    else if (iVar3 == 0) goto LAB_0003ec04;
    *(int *)(iVar4 + 0x40) = iVar3 + -1;
    do {
      iVar7 = *(int *)(iVar4 + 0x40);
      uVar6 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + iVar7 * 2);
      if ((-1 < (int)(uVar6 << 0x1b)) && (-1 < (int)(uVar6 << 0x19))) goto LAB_0003eaa8;
      if (iVar7 == 0) {
        iVar7 = *(int *)(iVar4 + 0x38) + -1;
        *(int *)(iVar4 + 0x40) = iVar7;
      }
      else {
        iVar7 = iVar7 + -1;
        *(int *)(iVar4 + 0x40) = iVar7;
      }
    } while (iVar7 != iVar3 + -1);
  }
  else if (iVar3 == 0x12) {
    iVar3 = FUN_0004c822(iVar4,0);
    if (*(int *)(iVar4 + 0x40) != 0xffff) {
      iVar7 = FUN_0003db28(*(int *)(iVar4 + 0x30) + *(int *)(iVar4 + 0x40) * 0x10);
      uVar11 = *(uint *)(iVar4 + 0x40);
      iVar8 = *(int *)(iVar4 + 0x30);
      iVar7 = *(int *)(iVar8 + uVar11 * 0x10) + (iVar7 >> 1);
      uVar6 = uVar11;
      while ((uVar6 < *(uint *)(iVar4 + 0x38) &&
             ((((*(int *)(iVar8 + uVar6 * 0x10 + 4) <= *(int *)(iVar8 + uVar11 * 0x10 + 4) ||
                (iVar7 < *(int *)(iVar8 + uVar6 * 0x10))) ||
               (*(int *)(iVar8 + uVar6 * 0x10 + 8) + iVar3 < iVar7)) ||
              ((uVar10 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + uVar6 * 2),
               (int)(uVar10 << 0x19) < 0 || ((int)(uVar10 << 0x1b) < 0))))))) {
        uVar6 = uVar6 + 1;
      }
      if (uVar6 < *(uint *)(iVar4 + 0x38)) {
LAB_0003ed74:
        *(uint *)(iVar4 + 0x40) = uVar6;
      }
      goto LAB_0003eaa8;
    }
    *(undefined4 *)(iVar4 + 0x40) = 0;
    do {
      uVar6 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + *(int *)(iVar4 + 0x40) * 2);
      if ((-1 < (int)(uVar6 << 0x1b)) && (-1 < (int)(uVar6 << 0x19))) goto LAB_0003eaa8;
      uVar6 = *(int *)(iVar4 + 0x40) + 1;
      *(uint *)(iVar4 + 0x40) = uVar6;
    } while (uVar6 < *(uint *)(iVar4 + 0x38));
  }
  else {
    if (iVar3 != 0x11) goto LAB_0003eaa8;
    iVar3 = FUN_0004c822(iVar4,0);
    if (*(int *)(iVar4 + 0x40) != 0xffff) {
      iVar7 = FUN_0003db28(*(int *)(iVar4 + 0x30) + *(int *)(iVar4 + 0x40) * 0x10);
      iVar9 = *(int *)(iVar4 + 0x40);
      iVar8 = *(int *)(iVar4 + 0x30);
      iVar7 = *(int *)(iVar8 + iVar9 * 0x10) + (iVar7 >> 1);
      for (sVar1 = (short)iVar9; uVar6 = (uint)sVar1, -1 < (int)uVar6; sVar1 = sVar1 + -1) {
        if ((((*(int *)(iVar8 + uVar6 * 0x10 + 4) < *(int *)(iVar8 + iVar9 * 0x10 + 4)) &&
             (*(int *)(iVar8 + uVar6 * 0x10) - iVar3 <= iVar7)) &&
            (iVar7 <= *(int *)(iVar8 + uVar6 * 0x10 + 8))) &&
           ((uVar11 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + uVar6 * 2),
            -1 < (int)(uVar11 << 0x19) && (-1 < (int)(uVar11 << 0x1b))))) {
          if (-1 < (int)uVar6) goto LAB_0003ed74;
          break;
        }
      }
      goto LAB_0003eaa8;
    }
    *(undefined4 *)(iVar4 + 0x40) = 0;
    do {
      uVar6 = (uint)*(ushort *)(*(int *)(iVar4 + 0x34) + *(int *)(iVar4 + 0x40) * 2);
      if ((-1 < (int)(uVar6 << 0x1b)) && (-1 < (int)(uVar6 << 0x19))) goto LAB_0003eaa8;
      uVar6 = *(int *)(iVar4 + 0x40) + 1;
      *(uint *)(iVar4 + 0x40) = uVar6;
    } while (uVar6 < *(uint *)(iVar4 + 0x38));
  }
  *(undefined4 *)(iVar4 + 0x40) = 0xffff;
LAB_0003eaa8:
  FUN_0003aa70(iVar4,*(undefined4 *)(iVar4 + 0x40));
  return;
}

