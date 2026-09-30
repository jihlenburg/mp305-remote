/* Address: ram:000526d0; name: FUN_ram_000526d0; body bytes: 264 */

uint FUN_ram_000526d0(undefined4 param_1,uint param_2)

{
  byte *pbVar1;
  uint uVar2;
  
  gp = 0x20004000;
  if ((short)param_2 < 0) {
    pbVar1 = (byte *)tmos_msg_receive();
    if (pbVar1 != (byte *)0x0) {
      if ((*pbVar1 ^ 0x80) < 2) {
        FUN_ram_0005d458();
      }
      tmos_msg_deallocate(pbVar1);
    }
    uVar2 = 0x8000;
  }
  else {
    if ((param_2 & 1) != 0) {
      if (DAT_ram_20001dcc != (code *)0x0) {
        (*DAT_ram_20001dcc)();
      }
      gp = 0x20004000;
      return param_2 ^ 1;
    }
    if ((param_2 & 2) != 0) {
      if (DAT_ram_20001dd0 != (code *)0x0) {
        (*DAT_ram_20001dd0)();
      }
      gp = 0x20004000;
      return param_2 ^ 2;
    }
    if ((param_2 & 8) != 0) {
      if (*(code **)(DAT_ram_20001dd8 + 0x70) != (code *)0x0) {
        (**(code **)(DAT_ram_20001dd8 + 0x70))();
      }
      gp = 0x20004000;
      return param_2 ^ 8;
    }
    if ((param_2 & 4) != 0) {
      if (*(code **)(DAT_ram_20001dd8 + 0x6c) != (code *)0x0) {
        (**(code **)(DAT_ram_20001dd8 + 0x6c))();
      }
      gp = 0x20004000;
      return param_2 ^ 4;
    }
    if ((param_2 & 0x20) != 0) {
      if (*(code **)(DAT_ram_20001de8 + 0x90) != (code *)0x0) {
        (**(code **)(DAT_ram_20001de8 + 0x90))();
      }
      gp = 0x20004000;
      return param_2 ^ 0x20;
    }
    if ((param_2 & 0x10) != 0) {
      if (*(code **)(DAT_ram_20001de8 + 0x8c) != (code *)0x0) {
        (**(code **)(DAT_ram_20001de8 + 0x8c))();
      }
      gp = 0x20004000;
      return param_2 ^ 0x10;
    }
    if (-1 < (int)(param_2 << 0x12)) {
      gp = 0x20004000;
      return 0;
    }
    FUN_ram_00065aec(DAT_ram_20001d64,DAT_ram_20001d65,DAT_ram_20001d66,DAT_ram_20001d67);
    uVar2 = 0x2000;
  }
  return uVar2 ^ param_2;
}

