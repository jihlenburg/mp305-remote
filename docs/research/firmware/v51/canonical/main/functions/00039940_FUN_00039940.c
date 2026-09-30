/* Address: 00039940; name: FUN_00039940; body bytes: 848 */

void FUN_00039940(int param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  bVar2 = *(byte *)(param_1 + 10);
  if (*(char *)(param_2 + 0x12) == '\x01') {
    if ((int)((uint)bVar2 << 0x1c) < 0) {
      return;
    }
  }
  else if ((int)((uint)bVar2 << 0x1c) < 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(byte *)(param_1 + 10) = bVar2 & 0xf6;
    *(undefined1 *)(param_1 + 0x9c) = 0;
  }
  cVar1 = *(char *)(param_1 + 0x9c);
  *(undefined1 *)(param_1 + 0x9c) = *(undefined1 *)(param_2 + 0x12);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_2 + 8);
  iVar10 = *(int *)(param_1 + 0xa8);
  if (iVar10 == 0) {
    return;
  }
  DAT_2003a474 = FUN_000472e0();
  if (DAT_2003a474 == 0) {
    return;
  }
  if (*(char *)(param_2 + 0x12) != '\0') {
    *(undefined2 *)(param_2 + 0x10) = 0;
  }
  uVar4 = FUN_0004cd9c(DAT_2003a474,0x80);
  uVar4 = uVar4 ^ 1;
  if (*(char *)(param_2 + 0x12) != '\x01') {
    if ((*(char *)(param_2 + 0x12) != '\0') || (cVar1 != '\x01')) goto LAB_00039bdc;
    if (*(int *)(param_2 + 8) == 10) {
      iVar8 = FUN_0004d45a(DAT_2003a474);
      if ((iVar8 == 0) && (iVar8 = FUN_0004cd84(DAT_2003a474,0x10), iVar8 == 0)) {
        if ((uVar4 != 0) && (iVar8 = FUN_0005e710(8,DAT_2003a470), iVar8 == 0)) {
          return;
        }
        if (((uVar4 & ~(uint)*(byte *)(param_1 + 10)) != 0) &&
           (iVar8 = FUN_0005e710(4,DAT_2003a470), iVar8 == 0)) {
          return;
        }
        if ((uVar4 != 0) && (iVar8 = FUN_0005e710(7,DAT_2003a470), iVar8 == 0)) {
          return;
        }
      }
      else {
        iVar8 = FUN_000472d4(iVar10);
        iVar9 = (uint)*(byte *)(param_1 + 10) << 0x1f;
        if (iVar8 == 0) {
          if (iVar9 == 0) {
            FUN_0004743a(iVar10,1);
          }
        }
        else if ((iVar9 == 0) || (uVar7 = FUN_000472ee(iVar10), uVar7 < 2)) {
          if (uVar4 != 0) {
            iVar8 = FUN_0005e710(8,DAT_2003a470);
            if (iVar8 == 0) {
              return;
            }
            iVar8 = FUN_0005e710(4,DAT_2003a470);
            if (iVar8 == 0) {
              return;
            }
            iVar8 = FUN_0005e710(7,DAT_2003a470);
            if (iVar8 == 0) {
              return;
            }
          }
          FUN_00047414(iVar10,10);
          iVar8 = FUN_0003a5c8(param_1);
          if (iVar8 != 0) {
            return;
          }
        }
        else {
          FUN_0004e0e6(DAT_2003a474,0x20);
        }
      }
    }
    *(undefined4 *)(param_1 + 0xc) = 0;
    bVar2 = *(byte *)(param_1 + 10) & 0xfe;
LAB_00039bda:
    *(byte *)(param_1 + 10) = bVar2;
    goto LAB_00039bdc;
  }
  if (cVar1 == '\0') {
    uVar6 = FUN_00052708();
    *(undefined4 *)(param_1 + 0xc) = uVar6;
    iVar8 = *(int *)(param_2 + 8);
    if (iVar8 != 10) {
      if (iVar8 == 0x14) {
LAB_00039a0a:
        sVar3 = *(short *)(param_2 + 0x10) + -1;
      }
      else {
        if (iVar8 != 0x13) {
          if (iVar8 != 0x1b) {
LAB_00039aec:
            FUN_00047414(iVar10);
            iVar8 = FUN_0003a5c8(param_1);
            if (iVar8 != 0) {
              return;
            }
            goto LAB_00039bdc;
          }
          FUN_00047414(iVar10,0x1b);
          iVar8 = FUN_0003a5c8(param_1);
          if (iVar8 != 0) {
            return;
          }
          if (uVar4 == 0) goto LAB_00039bdc;
          uVar6 = 0x24;
          goto LAB_00039b04;
        }
LAB_00039a10:
        sVar3 = *(short *)(param_2 + 0x10) + 1;
      }
      *(short *)(param_2 + 0x10) = sVar3;
      goto LAB_00039bdc;
    }
    iVar8 = FUN_0004d45a(DAT_2003a474);
    if (iVar8 == 0) {
      iVar8 = FUN_0004cd84(DAT_2003a474,0x10);
      uVar7 = 0;
      if (iVar8 != 0) goto LAB_000399f0;
    }
    else {
LAB_000399f0:
      uVar7 = 1;
    }
    uVar5 = FUN_000472d4(iVar10);
    if (((uVar7 & ~uVar5) != 0) || (uVar4 == 0)) goto LAB_00039bdc;
    uVar6 = 1;
  }
  else {
    if (cVar1 != '\x01') goto LAB_00039bdc;
    if ((*(byte *)(param_1 + 10) & 1) == 0) {
      uVar7 = FUN_000526fc(*(undefined4 *)(param_1 + 0xc));
      if (*(ushort *)(param_1 + 0x28) < uVar7) {
        *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) | 1;
        uVar6 = FUN_00052708();
        *(undefined4 *)(param_1 + 0x10) = uVar6;
        if (*(int *)(param_2 + 8) == 10) {
          FUN_0004883e(DAT_2003a470,5,DAT_2003a474);
          iVar8 = FUN_0003a5c8(DAT_2003a470);
          if (iVar8 != 0) {
            return;
          }
          iVar8 = FUN_0004d45a(DAT_2003a474);
          if ((iVar8 == 0) && (iVar8 = FUN_0004cd84(DAT_2003a474,0x10), iVar8 == 0)) {
            if (uVar4 != 0) {
              FUN_0004e5a6(DAT_2003a474,5,DAT_2003a470);
              iVar8 = FUN_0003a5c8(DAT_2003a470);
              if (iVar8 != 0) {
                return;
              }
            }
          }
          else {
            uVar4 = FUN_000472ee(iVar10);
            if (1 < uVar4) {
              uVar4 = FUN_000472d4(iVar10);
              FUN_0004743a(iVar10,uVar4 ^ 1);
              FUN_0004e0e6(DAT_2003a474,0x20);
            }
          }
        }
        bVar2 = *(byte *)(param_1 + 10) | 1;
        goto LAB_00039bda;
      }
      if ((*(byte *)(param_1 + 10) & 1) == 0) goto LAB_00039bdc;
    }
    uVar7 = FUN_000526fc(*(undefined4 *)(param_1 + 0x10));
    if (uVar7 <= *(ushort *)(param_1 + 0x2a)) goto LAB_00039bdc;
    uVar6 = FUN_00052708();
    *(undefined4 *)(param_1 + 0x10) = uVar6;
    iVar8 = *(int *)(param_2 + 8);
    if (iVar8 != 10) {
      if (iVar8 != 0x14) {
        if (iVar8 != 0x13) goto LAB_00039aec;
        goto LAB_00039a10;
      }
      goto LAB_00039a0a;
    }
    if (uVar4 == 0) goto LAB_00039bdc;
    uVar6 = 6;
  }
LAB_00039b04:
  iVar8 = FUN_0005e710(uVar6,DAT_2003a470);
  if (iVar8 == 0) {
    return;
  }
LAB_00039bdc:
  DAT_2003a474 = 0;
  if (*(short *)(param_2 + 0x10) != 0) {
    iVar8 = FUN_000472d4(iVar10);
    sVar3 = *(short *)(param_2 + 0x10);
    if (iVar8 == 0) {
      if (sVar3 < 0) {
        for (iVar8 = 0;
            -iVar8 != (int)*(short *)(param_2 + 0x10) && iVar8 <= -(int)*(short *)(param_2 + 0x10);
            iVar8 = iVar8 + 1) {
          FUN_00047298(iVar10);
          iVar9 = FUN_0003a5c8(param_1);
          if (iVar9 != 0) {
            return;
          }
        }
      }
      else if (0 < sVar3) {
        for (iVar8 = 0; iVar8 < *(short *)(param_2 + 0x10); iVar8 = iVar8 + 1) {
          FUN_000471d8(iVar10);
          iVar9 = FUN_0003a5c8(param_1);
          if (iVar9 != 0) {
            return;
          }
        }
      }
    }
    else if (sVar3 < 0) {
      for (iVar8 = 0;
          -iVar8 != (int)*(short *)(param_2 + 0x10) && iVar8 <= -(int)*(short *)(param_2 + 0x10);
          iVar8 = iVar8 + 1) {
        FUN_00047414(iVar10,0x14);
        iVar9 = FUN_0003a5c8(param_1);
        if (iVar9 != 0) {
          return;
        }
      }
    }
    else if (0 < sVar3) {
      for (iVar8 = 0; iVar8 < *(short *)(param_2 + 0x10); iVar8 = iVar8 + 1) {
        FUN_00047414(iVar10,0x13);
        iVar9 = FUN_0003a5c8(param_1);
        if (iVar9 != 0) {
          return;
        }
      }
    }
  }
  return;
}

