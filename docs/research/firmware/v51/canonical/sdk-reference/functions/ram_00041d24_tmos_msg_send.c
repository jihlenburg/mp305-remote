/* Address: ram:00041d24; name: tmos_msg_send; body bytes: 96 */

undefined4 tmos_msg_send(uint param_1,int param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (param_2 == 0) {
    return 5;
  }
  if ((param_1 < DAT_ram_20001b65) && (2 < param_1)) {
    if (*(int *)(param_2 + -8) == 0) {
      if (*(char *)(param_2 + -2) == -1) {
        *(char *)(param_2 + -2) = (char)param_1;
        FUN_ram_00041c2a(&DAT_ram_20001b60);
        uVar1 = tmos_set_event(param_1,0x8000);
        return uVar1;
      }
    }
    tmos_msg_deallocate(param_2);
    uVar1 = 5;
  }
  else {
    tmos_msg_deallocate(param_2);
    uVar1 = 3;
  }
  return uVar1;
}

