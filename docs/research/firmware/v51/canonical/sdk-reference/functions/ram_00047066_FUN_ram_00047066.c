/* Address: ram:00047066; name: FUN_ram_00047066; body bytes: 380 */

int FUN_ram_00047066(undefined1 param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 uVar5;
  char cStack_29;
  undefined1 auStack_28 [12];
  
  gp = 0x20004000;
  if (DAT_ram_200019e4 != (undefined1 *)0x0) {
    gp = 0x20004000;
    return 0x11;
  }
  if ((DAT_ram_20001d50 & 5) == 0) {
    gp = 0x20004000;
    return 0x12;
  }
  DAT_ram_20001a0d = param_1;
  puVar2 = (undefined1 *)FUN_ram_20000040(0xc,0x4717);
  if (puVar2 == (undefined1 *)0x0) {
    gp = 0x20004000;
    DAT_ram_200019e4 = puVar2;
    return 0x13;
  }
  DAT_ram_200019e4 = puVar2;
  *puVar2 = param_1;
  puVar2[1] = 0;
  tmos_memcpy(puVar2 + 2,param_2,10);
  puVar2 = DAT_ram_200019e4;
  bVar1 = DAT_ram_200019e4[2];
  if (bVar1 < 5) {
    if (bVar1 == 0) {
      uVar5 = 0x13;
    }
    else if (bVar1 == 1) {
      uVar5 = 0x1d;
    }
    else if (bVar1 == 2) {
      uVar5 = 0x12;
    }
    else if (bVar1 == 3) {
      uVar5 = 0x10;
    }
    else {
      uVar5 = 0x15;
    }
    DAT_ram_200019e4[2] = uVar5;
    puVar2[2] = puVar2[2] | 0x10;
    goto LAB_ram_000470f0;
  }
  if (bVar1 != 5) {
    if (bVar1 == 6) {
      uVar5 = 2;
    }
    else {
      if (bVar1 == 7) {
        DAT_ram_200019e4[2] = 0;
        goto LAB_ram_00047192;
      }
      if (bVar1 == 8) {
        uVar5 = 1;
      }
      else {
        if (bVar1 == 9) {
          DAT_ram_200019e4[2] = 6;
          goto LAB_ram_00047192;
        }
        if (bVar1 != 10) {
          gp = 0x20004000;
          return 1;
        }
        uVar5 = 4;
      }
    }
    DAT_ram_200019e4[2] = uVar5;
  }
LAB_ram_00047192:
  iVar4 = GAP_GetParamValue(0x19);
  if (iVar4 != 0x7f) {
    DAT_ram_200019e4[2] = DAT_ram_200019e4[2] | 0x40;
  }
LAB_ram_000470f0:
  GAPBondMgr_GetParameter(0x41f,&cStack_29);
  if ((cStack_29 == '\0') && (DAT_ram_20001c06 == '\x03')) {
    uVar3 = FUN_ram_000443c2();
    FUN_ram_0004eef8(uVar3,auStack_28);
    FUN_ram_000449da(auStack_28);
    iVar4 = GAP_GetParamValue(0x11);
    if (iVar4 == 0) {
      gp = 0x20004000;
      return 0;
    }
    tmos_start_task(DAT_ram_20001d4c,4,iVar4 * 0x640);
    gp = 0x20004000;
    return 0;
  }
  iVar4 = FUN_ram_00046df2();
  if (iVar4 != 0) {
    FUN_ram_00046d4a();
  }
  return iVar4;
}

