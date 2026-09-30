/* Address: ram:00067800; name: FUN_ram_00067800; body bytes: 174 */

undefined4 FUN_ram_00067800(int param_1,undefined1 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  if (((DAT_ram_20001dd8 == 0) || (-1 < *(int *)(DAT_ram_20001dd8 + 0x1c) << 0x11)) &&
     (DAT_ram_20001ddc != (code *)0x0)) {
    if (param_1 == 0) {
      if (DAT_ram_20001dd8 != 0) {
        FUN_ram_000603de();
        gp = 0x20004000;
        return 0;
      }
    }
    else if (param_1 == 1) {
      if (DAT_ram_20001dd8 == 0) {
        iVar2 = (*DAT_ram_20001ddc)();
        if (iVar2 == 0) {
          gp = 0x20004000;
          return 3;
        }
        *(undefined1 *)(iVar2 + 0x4d) = 0;
        *(undefined2 *)(iVar2 + 0x16) = 4;
        *(undefined2 *)(iVar2 + 0x18) = 4;
      }
      else {
        iVar2 = DAT_ram_20001dd8;
        if (*(int *)(DAT_ram_20001dd8 + 0x1c) << 0x11 < 0) goto LAB_ram_000678a0;
      }
      if (*(char *)(iVar2 + 0xb) != '\x01') {
        if (param_3 == 0) {
          *(undefined4 *)(iVar2 + 0x38) = 0;
LAB_ram_00067882:
          *(undefined1 *)(iVar2 + 0x12) = param_2;
                    /* WARNING: Could not recover jumptable at 0x00067894. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          uVar1 = (**(code **)(iVar2 + 0x68))();
          return uVar1;
        }
        *(short *)(iVar2 + 0x38) = (short)param_3;
        *(short *)(iVar2 + 0x3a) = (short)param_4;
        if ((param_4 == 0) || (param_3 < param_4 << 7)) goto LAB_ram_00067882;
      }
    }
    uVar1 = 0x12;
  }
  else {
LAB_ram_000678a0:
    uVar1 = 0xc;
  }
  return uVar1;
}

