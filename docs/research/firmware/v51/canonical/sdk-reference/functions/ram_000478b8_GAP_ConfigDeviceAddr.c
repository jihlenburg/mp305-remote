/* Address: ram:000478b8; name: GAP_ConfigDeviceAddr; body bytes: 292 */

int GAP_ConfigDeviceAddr(uint param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  char cStack_29;
  undefined1 auStack_28 [16];
  
  uVar1 = DAT_ram_20001c06;
  gp = 0x20004000;
  if (3 < param_1) {
    gp = 0x20004000;
    return 2;
  }
  if (DAT_ram_20001c04 != '\x03') {
    gp = 0x20004000;
    return 0x10;
  }
  if ((param_1 - 1 & 0xff) < 2) {
    if (param_2 != 0) {
      tmos_memset(auStack_28,0,6);
      iVar2 = tmos_memcmp(param_2,auStack_28,6);
      if (iVar2 == 0) {
        tmos_memset(auStack_28,0xff,6);
        iVar2 = tmos_memcmp(param_2,auStack_28,6);
        if (iVar2 == 0) {
          tmos_memcpy(auStack_28,param_2,6);
          goto LAB_ram_00047916;
        }
      }
      gp = 0x20004000;
      return 2;
    }
    FUN_ram_000440ba(auStack_28,6);
  }
  else if ((param_1 == 3) && (iVar2 = FUN_ram_0004eef8(DAT_ram_20001c10,auStack_28), iVar2 != 0)) {
    gp = 0x20004000;
    DAT_ram_20001c06 = uVar1;
    return iVar2;
  }
LAB_ram_00047916:
  DAT_ram_20001c06 = (undefined1)param_1;
  tmos_stop_task(DAT_ram_20001d4c,4);
  if (param_1 != 0) {
    iVar2 = FUN_ram_000449da(auStack_28);
    if (iVar2 != 0) {
      gp = 0x20004000;
      DAT_ram_20001c06 = uVar1;
      return iVar2;
    }
    GAPBondMgr_GetParameter(0x41f,&cStack_29);
    if (((cStack_29 == '\0') && (param_1 == 3)) && (iVar2 = GAP_GetParamValue(0x11), iVar2 != 0)) {
      tmos_start_reload_task(DAT_ram_20001d4c,4,iVar2 * 1600000);
      gp = 0x20004000;
      return 0;
    }
  }
  return 0;
}

