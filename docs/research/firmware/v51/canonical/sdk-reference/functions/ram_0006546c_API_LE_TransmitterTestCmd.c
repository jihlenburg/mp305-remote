/* Address: ram:0006546c; name: API_LE_TransmitterTestCmd; body bytes: 432 */

/* WARNING: Removing unreachable block (ram,0x000654f0) */

char API_LE_TransmitterTestCmd(undefined1 *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  char cStack_11;
  
  gp = 0x20004000;
  if (DAT_ram_20001b67 == '\0') {
    gp = 0x20004000;
    return '\f';
  }
  if (param_2 == 0x201e) {
    DAT_ram_20001d64 = *param_1;
    DAT_ram_20001d65 = param_1[1];
    DAT_ram_20001d66 = param_1[2];
    DAT_ram_20001d67 = '\x01';
  }
  else if (param_2 == 0x2034) {
    DAT_ram_20001d64 = *param_1;
    DAT_ram_20001d65 = param_1[1];
    DAT_ram_20001d66 = param_1[2];
    DAT_ram_20001d67 = param_1[3];
  }
  else {
    if (param_2 == 0x2050) {
      DAT_ram_20001d64 = *param_1;
      DAT_ram_20001d65 = param_1[1];
      DAT_ram_20001d66 = param_1[2];
      DAT_ram_20001d67 = param_1[3];
      cStack_11 = FUN_ram_00067fb8();
      goto LAB_ram_00065582;
    }
    if (param_2 != 0x207b) {
      cStack_11 = '\f';
      goto LAB_ram_00065582;
    }
    DAT_ram_20001d64 = *param_1;
    DAT_ram_20001d65 = param_1[1];
    DAT_ram_20001d66 = param_1[2];
    DAT_ram_20001d67 = param_1[3];
    FUN_ram_00061dd4((int)(char)param_1[(byte)param_1[6] + 7]);
    LL_SetTxPowerLevel();
  }
  cStack_11 = FUN_ram_00065aec(DAT_ram_20001d64,DAT_ram_20001d65,DAT_ram_20001d66,DAT_ram_20001d67);
  if (cStack_11 == '\0') {
    if ((DAT_ram_20001d67 == '\x01') || (DAT_ram_20001d67 == '\x02')) {
      uVar1 = (uint)DAT_ram_20001d65 * 8 + 0x3b9;
    }
    else {
      iVar2 = DAT_ram_20001d65 + 2;
      if (DAT_ram_20001d67 == '\x03') {
        uVar1 = iVar2 * 0x40 + 0x5b9;
      }
      else {
        uVar1 = iVar2 * 0x10 + 0x517;
      }
    }
    DAT_ram_20001d68 = 0;
    tmos_start_reload_task(DAT_ram_20001b67,0x2000,uVar1 / 0x271);
  }
LAB_ram_00065582:
  thunk_FUN_ram_000521a0(param_2,1,&cStack_11);
  return cStack_11;
}

