/* Address: ram:00042bb4; name: tmos_snv_read; body bytes: 604 */

/* WARNING: Removing unreachable block (ram,0x00042c48) */
/* WARNING: Removing unreachable block (ram,0x00042d18) */

undefined4 tmos_snv_read(uint param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  
  gp = 0x20004000;
  if (DAT_ram_20001bc4 == 0) {
    if (DAT_ram_20001b84 != 0) {
      uVar2 = 4;
      while( true ) {
        pcVar3 = (char *)((uVar2 >> 2) * 4 + DAT_ram_20001b84);
        if (*pcVar3 != 'Z') break;
        if ((byte)pcVar3[1] == param_1) {
          tmos_memcpy(param_3,DAT_ram_20001b84 + ((uVar2 >> 2) + 1) * 4,param_2);
          gp = 0x20004000;
          return 0;
        }
        uVar2 = (uint)*(ushort *)(pcVar3 + 2);
      }
    }
  }
  else if (DAT_ram_20001bf0 != (code *)0x0) {
    iVar1 = DAT_ram_20001b84;
    if (param_1 < 0x20) {
      if (DAT_ram_20001b84 == 0) {
        DAT_ram_20001b84 = FUN_ram_20000040(DAT_ram_20001bc8,0x4e01);
        if (DAT_ram_20001b84 == 0) {
          gp = 0x20004000;
          return 10;
        }
        (*DAT_ram_20001bf0)(DAT_ram_20001bc4,DAT_ram_20001bc8 >> 2,DAT_ram_20001b84);
        DAT_ram_20001b88 = DAT_ram_20001bc4;
        iVar1 = DAT_ram_20001b84;
      }
      else if (DAT_ram_20001bc4 != DAT_ram_20001b88) {
        iVar1 = FUN_ram_20000040(DAT_ram_20001bc8,0x4e02);
        if (iVar1 == 0) {
          gp = 0x20004000;
          return 10;
        }
        (*DAT_ram_20001bf0)(DAT_ram_20001bc4,DAT_ram_20001bc8 >> 2,iVar1);
      }
      if (param_1 == 2) {
        if (param_2 != 0x10) {
          gp = 0x20004000;
          return 10;
        }
        uVar2 = (int)(DAT_ram_20001bc8 - 0x40) / 4 << 2;
      }
      else {
        if (param_1 == 3) {
          if (param_2 != 0x10) {
            gp = 0x20004000;
            return 10;
          }
          uVar2 = DAT_ram_20001bc8 - 0x2c;
        }
        else if (param_1 == 4) {
          if (param_2 != 4) {
            gp = 0x20004000;
            return 10;
          }
          uVar2 = DAT_ram_20001bc8 - 0x18;
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
          uVar2 = DAT_ram_20001bc8 - 0x10;
        }
        uVar2 = uVar2 & 0xfffffffc;
      }
      pcVar3 = (char *)(uVar2 + iVar1);
      if ((*pcVar3 == 'Z') && ((byte)pcVar3[1] == param_1)) {
        tmos_memcpy(param_3,pcVar3 + 4,param_2);
        if (DAT_ram_20001b84 != iVar1) {
LAB_ram_00042d9c:
          FUN_ram_20000104(iVar1);
        }
        gp = 0x20004000;
        return 0;
      }
      if (DAT_ram_20001b84 == iVar1) {
        gp = 0x20004000;
        return 10;
      }
    }
    else {
      if (param_1 < 0x70) {
        iVar4 = (int)(param_1 - 0x20) / 6;
      }
      else {
        if (0x7e < param_1) {
          gp = 0x20004000;
          return 10;
        }
        iVar4 = param_1 - 0x70;
      }
      iVar4 = iVar4 * (uint)DAT_ram_20001bc8 + DAT_ram_20001bc4;
      if ((DAT_ram_20001b88 != iVar4) || (DAT_ram_20001b84 == 0)) {
        iVar1 = FUN_ram_20000040(DAT_ram_20001bc8,0x4e);
        if (iVar1 == 0) {
          gp = 0x20004000;
          return 10;
        }
        (*DAT_ram_20001bf0)(iVar4,DAT_ram_20001bc8 >> 2,iVar1);
      }
      uVar2 = 4;
      while( true ) {
        pcVar3 = (char *)((uVar2 >> 2) * 4 + iVar1);
        if (*pcVar3 != 'Z') break;
        if ((byte)pcVar3[1] == param_1) {
          tmos_memcpy(param_3,((uVar2 >> 2) + 1) * 4 + iVar1,param_2);
          if (DAT_ram_20001b84 == iVar1) {
            gp = 0x20004000;
            return 0;
          }
          goto LAB_ram_00042d9c;
        }
        uVar2 = (uint)*(ushort *)(pcVar3 + 2);
      }
      if (DAT_ram_20001b84 == iVar1) {
        gp = 0x20004000;
        return 10;
      }
    }
    FUN_ram_20000104(iVar1);
  }
  return 10;
}

