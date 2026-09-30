/* Address: ram:00041c48; name: tmos_msg_deallocate; body bytes: 44 */

undefined4 tmos_msg_deallocate(int param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (param_1 == 0) {
    uVar1 = 5;
  }
  else {
    uVar1 = 4;
    if (*(char *)(param_1 + -2) == -1) {
      FUN_ram_20000104();
      return 0;
    }
  }
  return uVar1;
}

