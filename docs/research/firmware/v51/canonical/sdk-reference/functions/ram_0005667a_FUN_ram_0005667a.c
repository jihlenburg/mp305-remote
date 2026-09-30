/* Address: ram:0005667a; name: FUN_ram_0005667a; body bytes: 476 */

/* WARNING: Removing unreachable block (ram,0x000567fe) */
/* WARNING: Removing unreachable block (ram,0x0005678c) */

uint FUN_ram_0005667a(uint *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  
  cVar1 = DAT_ram_20001bd2;
  gp = 0x20004000;
  if (DAT_ram_20001b67 == '\0') {
    return 0xffffffff;
  }
  iVar4 = -1;
  if (param_1 == (uint *)0x0) {
    gp = 0x20004000;
    return 0xffffffff;
  }
  if (DAT_ram_20001df0 == (int *)0x0) {
    gp = 0x20004000;
    return 0xffffffff;
  }
  uVar9 = (uint)DAT_ram_20001b8c;
  uVar6 = (uint)DAT_ram_20001bd4;
  uVar8 = 0xffffffff;
  piVar7 = DAT_ram_20001df0;
  do {
    uVar2 = piVar7[0x24];
    if (*(char *)((int)piVar7 + 0xb) == '\x01') {
      if (((((uint)*(ushort *)((int)piVar7 + 0x7e) < (uint)*(ushort *)((int)piVar7 + 0x3a)) &&
           ((char)piVar7[4] == '\x01')) && (piVar7[0x46] == 0)) &&
         ((piVar7[0x29] == 0 && (*(char *)((int)piVar7 + 0xf) == '\a')))) {
        iVar10 = (uint)*(ushort *)((int)piVar7 + 0x3a) - (uint)*(ushort *)((int)piVar7 + 0x7e);
        uVar5 = (uint)*(ushort *)(piVar7 + 0xe) * iVar10 * 0x4e2;
        if (piVar7[0x25] == 0) {
          uVar3 = 0xffffffff;
        }
        else {
          uVar3 = uVar5 / (uint)piVar7[0x25];
        }
        *(short *)(piVar7 + 0x21) = (short)((uVar3 + uVar6) * 0x10000 >> 0x10);
        iVar4 = FUN_ram_0006bae2(uVar9 * uVar5,(int)((ulonglong)uVar9 * (ulonglong)uVar5 >> 0x20),
                                 1000000,0);
        uVar2 = uVar2 + iVar4;
        if ((-1 < cVar1) && (0xa8bfffff < uVar2)) {
          uVar2 = uVar2 + 0x57400000;
        }
        uVar5 = ((uVar3 + uVar6 & 0xffff) * uVar9 + 999999) / 1000000 + iVar10 * 2;
        if ((-1 < cVar1) && (uVar2 < uVar5)) {
          uVar2 = uVar2 + (-0x57400000 - uVar5);
          goto LAB_ram_000567a4;
        }
      }
      else {
        uVar5 = (*(ushort *)(piVar7 + 0x21) * uVar9 + 999999) / 1000000;
        if ((-1 < cVar1) && (uVar2 < uVar5)) {
          uVar2 = uVar2 + 0xa8c00000;
        }
      }
      uVar2 = uVar2 - uVar5;
    }
LAB_ram_000567a4:
    if (uVar2 < uVar8) {
      uVar8 = uVar2;
    }
    piVar7 = (int *)*piVar7;
  } while (piVar7 != (int *)0x0);
  uVar6 = (*DAT_ram_20001c00)(iVar4);
  if (uVar8 < uVar6) {
    if (-1 < (int)(uVar6 - uVar8)) {
      *param_1 = 0;
      goto LAB_ram_000567c8;
    }
    if (DAT_ram_20001bd2 < '\0') goto LAB_ram_000567c0;
    uVar9 = (uVar8 + 0xa8c00000) - uVar6;
  }
  else {
LAB_ram_000567c0:
    uVar9 = uVar8 - uVar6;
  }
  *param_1 = uVar9;
LAB_ram_000567c8:
  if (*param_1 < 0xb) {
    *param_1 = 0;
  }
  else {
    *param_1 = *param_1 - 10;
    if ((DAT_ram_20001bd2 < '\0') || (9 < uVar8)) {
      uVar6 = uVar8 - 10;
    }
    else {
      uVar6 = uVar8 + 0xa8bffff6;
    }
  }
  return uVar6;
}

