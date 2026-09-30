/* Address: ram:00042e5e; name: FUN_ram_00042e5e; body bytes: 646 */

/* WARNING: Removing unreachable block (ram,0x00042eda) */
/* WARNING: Removing unreachable block (ram,0x00042f82) */

undefined4 FUN_ram_00042e5e(uint param_1,uint param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  gp = 0x20004000;
  if (DAT_ram_20001bc4 == 0) {
    if ((DAT_ram_20001b84 == 0) &&
       (DAT_ram_20001b84 = FUN_ram_20000040(DAT_ram_20001bca * DAT_ram_20001bc8,0x4e),
       DAT_ram_20001b84 == 0)) {
      return 10;
    }
    iVar5 = DAT_ram_20001b84;
    uVar4 = 4;
    while( true ) {
      uVar2 = uVar4;
      uVar6 = uVar2 >> 2;
      pcVar3 = (char *)(uVar6 * 4 + iVar5);
      if (*pcVar3 != 'Z') break;
      uVar4 = (uint)*(ushort *)(pcVar3 + 2);
      if ((byte)pcVar3[1] == param_1) {
        if ((int)param_2 <= (int)(uVar4 - uVar2)) goto LAB_ram_00042fde;
        pcVar3[1] = -1;
      }
    }
    if ((uint)DAT_ram_20001bca * (uint)DAT_ram_20001bc8 < uVar2 + param_2 + 4) {
      gp = 0x20004000;
      return 10;
    }
  }
  else {
    if (DAT_ram_20001bf4 == 0) {
      gp = 0x20004000;
      return 10;
    }
    if (DAT_ram_20001bf0 == (code *)0x0) {
      gp = 0x20004000;
      return 10;
    }
    if (param_1 < 0x20) {
      if ((DAT_ram_20001b84 == 0) &&
         (DAT_ram_20001b84 = FUN_ram_20000040(DAT_ram_20001bc8,0x4e), DAT_ram_20001b84 == 0)) {
        gp = 0x20004000;
        return 10;
      }
      if (DAT_ram_20001b88 != DAT_ram_20001bc4) {
        (*DAT_ram_20001bf0)(DAT_ram_20001bc4,DAT_ram_20001bc8 >> 2,DAT_ram_20001b84);
        DAT_ram_20001b88 = DAT_ram_20001bc4;
      }
      if (param_1 == 2) {
        if (param_2 != 0x10) {
          gp = 0x20004000;
          return 10;
        }
        uVar4 = (int)(DAT_ram_20001bc8 - 0x40) / 4 << 2;
      }
      else {
        if (param_1 == 3) {
          if (param_2 != 0x10) {
            gp = 0x20004000;
            return 10;
          }
          uVar4 = DAT_ram_20001bc8 - 0x2c;
        }
        else if (param_1 == 4) {
          if (param_2 != 4) {
            gp = 0x20004000;
            return 10;
          }
          uVar4 = DAT_ram_20001bc8 - 0x18;
        }
        else {
          if (param_1 != 0x10) {
            gp = 0x20004000;
            return 10;
          }
          if (8 < param_2) {
            gp = 0x20004000;
            return 10;
          }
          uVar4 = DAT_ram_20001bc8 - 0x10;
        }
        uVar4 = uVar4 & 0xfffffffc;
      }
      puVar1 = (undefined1 *)(DAT_ram_20001b84 + uVar4);
      *puVar1 = 0x5a;
      puVar1[1] = (char)param_1;
      puVar1 = puVar1 + 4;
      goto LAB_ram_00042efa;
    }
    if (param_1 < 0x70) {
      iVar5 = (int)(param_1 - 0x20) / 6;
    }
    else {
      if (0x7e < param_1) {
        gp = 0x20004000;
        return 10;
      }
      iVar5 = param_1 - 0x70;
    }
    iVar5 = DAT_ram_20001bc4 + iVar5 * (uint)DAT_ram_20001bc8;
    if ((DAT_ram_20001b84 == 0) &&
       (DAT_ram_20001b84 = FUN_ram_20000040(DAT_ram_20001bc8,0x4e), DAT_ram_20001b84 == 0)) {
      gp = 0x20004000;
      return 10;
    }
    if (DAT_ram_20001b88 != iVar5) {
      (*DAT_ram_20001bf0)(iVar5,DAT_ram_20001bc8 >> 2,DAT_ram_20001b84);
      DAT_ram_20001b88 = iVar5;
    }
    iVar5 = DAT_ram_20001b84;
    uVar4 = 4;
    while( true ) {
      uVar2 = uVar4;
      uVar6 = uVar2 >> 2;
      pcVar3 = (char *)(uVar6 * 4 + iVar5);
      if (*pcVar3 != 'Z') break;
      uVar4 = (uint)*(ushort *)(pcVar3 + 2);
      if ((byte)pcVar3[1] == param_1) {
        if ((int)param_2 <= (int)(uVar4 - uVar2)) goto LAB_ram_00042fde;
        pcVar3[1] = -1;
      }
    }
    if (DAT_ram_20001bc8 - 0x40 <= uVar2 + param_2 + 4) {
      gp = 0x20004000;
      return 10;
    }
  }
  *pcVar3 = 'Z';
  pcVar3[1] = (char)param_1;
  *(ushort *)(pcVar3 + 2) = (short)uVar2 + ((short)param_2 + 3U & 0xfc) + 4;
LAB_ram_00042fde:
  puVar1 = (undefined1 *)(iVar5 + (uVar6 + 1) * 4);
LAB_ram_00042efa:
  tmos_memcpy(puVar1,param_3,param_2);
  gp = 0x20004000;
  return 0;
}

