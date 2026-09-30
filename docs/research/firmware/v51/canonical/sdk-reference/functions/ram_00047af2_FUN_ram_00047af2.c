/* Address: ram:00047af2; name: FUN_ram_00047af2; body bytes: 276 */

undefined1 FUN_ram_00047af2(undefined4 param_1)

{
  undefined1 *puVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  undefined1 auStack_22 [6];
  
  gp = 0x20004000;
  if (DAT_ram_200019e4 == (undefined1 *)0x0) {
    gp = 0x20004000;
    return 0;
  }
  if (DAT_ram_200019e4[1] != '\x01') {
    if (DAT_ram_20001c08 != '\0') {
      gp = 0x20004000;
      return 1;
    }
    puVar1 = (undefined1 *)tmos_msg_allocate(3);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 0xd0;
      puVar1[1] = (char)param_1;
      puVar1[2] = 4;
      tmos_msg_send(*DAT_ram_200019e4,puVar1);
    }
    FUN_ram_00046d4a();
    gp = 0x20004000;
    return 1;
  }
  if (((DAT_ram_20001a18 == (undefined4 *)0x0) ||
      (pbVar3 = (byte *)FUN_ram_00044162(1,auStack_22,*(undefined2 *)(DAT_ram_20001a18 + 1),
                                         *DAT_ram_20001a18), pbVar3 == (byte *)0x0)) ||
     ((*pbVar3 & 1) == 0)) {
    iVar2 = GAP_GetParamValue(0);
  }
  else {
    uVar4 = GAP_GetParamValue(1);
    if (0x3b < uVar4) {
      tmos_start_reload_task(DAT_ram_20001d4c,2,96000);
      DAT_ram_20001a10 = (short)uVar4 + -0x3c;
      goto LAB_ram_00047be4;
    }
    iVar2 = uVar4 * 0x640;
  }
  if (iVar2 != 0) {
    tmos_start_task(DAT_ram_20001d4c,2);
  }
LAB_ram_00047be4:
  DAT_ram_200019e4[1] = 2;
  if (DAT_ram_20001c08 == '\0') {
    FUN_ram_00047a9e(param_1);
  }
  else {
    DAT_ram_20001c08 = '\0';
  }
  return 1;
}

