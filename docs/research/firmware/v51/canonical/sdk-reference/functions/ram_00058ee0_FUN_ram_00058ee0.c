/* Address: ram:00058ee0; name: FUN_ram_00058ee0; body bytes: 404 */

uint FUN_ram_00058ee0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  if (*(char *)(param_1 + 0x7c) != '\0') {
    iVar1 = *(int *)(param_1 + 0x84);
    if ((iVar1 != 0) && (*(char *)(iVar1 + 10) != '\0')) {
      if ((*(char *)(param_1 + 0x7d) == '\0') || ((*(byte *)(param_1 + 0x83) & 0xc0) != 0x40)) {
        if (*(char *)(iVar1 + 1) == '\0') {
          gp = 0x20004000;
          return 0;
        }
      }
      else {
        iVar1 = FUN_ram_0005d6c6(iVar1 + 0x1a,param_1 + 0x7e);
        if (iVar1 == 1) {
          *(undefined1 *)(param_1 + 0x7c) = 2;
          tmos_memcpy(*(int *)(param_1 + 0x84) + 0xc,param_1 + 0x7e,6);
        }
        else {
          if (*(char *)(*(int *)(param_1 + 0x84) + 1) == '\0') {
            gp = 0x20004000;
            return 0;
          }
          if (DAT_ram_20001d61 != '\0') {
            gp = 0x20004000;
            return 0;
          }
        }
      }
    }
    if ((*(char *)(param_1 + 0x7c) != '\x02') &&
       (iVar1 = tmos_memcmp(param_1 + 0x66,param_1 + 0x7e,6), iVar1 == 0)) {
      gp = 0x20004000;
      return 0;
    }
  }
  iVar1 = *(int *)(param_1 + 0x84);
  if ((iVar1 != 0) && (*(char *)(iVar1 + 0x12) != '\0')) {
    if ((*(char *)(param_1 + 0x75) == '\0') || ((*(byte *)(param_1 + 0x7b) & 0xc0) != 0x40)) {
      if (*(char *)(iVar1 + 1) == '\0') {
        gp = 0x20004000;
        return 0;
      }
    }
    else {
      iVar1 = FUN_ram_0005d6c6(iVar1 + 0x2a,param_1 + 0x76);
      if (iVar1 == 1) {
        tmos_memcpy(*(int *)(param_1 + 0x84) + 0x14,param_1 + 0x76,6);
        if (DAT_ram_20001d61 != '\0') {
          *(undefined1 *)(param_1 + 0x74) = 2;
          if (*(char *)(param_1 + 0xd) != '\x01') {
            gp = 0x20004000;
            return 1;
          }
          uVar2 = *(undefined4 *)(*(int *)(param_1 + 0x84) + 2);
          uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x84) + 6);
          goto LAB_ram_0005901e;
        }
      }
      else {
        if (*(char *)(*(int *)(param_1 + 0x84) + 1) == '\0') {
          gp = 0x20004000;
          return 0;
        }
        if (DAT_ram_20001d61 != '\0') {
          gp = 0x20004000;
          return 0;
        }
      }
    }
  }
  if (*(char *)(param_1 + 0xd) != '\x01') {
    if (*(char *)(param_1 + 0x6d) != *(char *)(param_1 + 0x75)) {
      return 0;
    }
    iVar1 = tmos_memcmp(param_1 + 0x6e,param_1 + 0x76,6);
    gp = 0x20004000;
    return (uint)(iVar1 != 0);
  }
  uVar2 = *(undefined4 *)(param_1 + 0x74);
  uVar4 = *(undefined4 *)(param_1 + 0x78);
LAB_ram_0005901e:
  uVar3 = FUN_ram_20000d70(uVar2,uVar4);
  return uVar3;
}

