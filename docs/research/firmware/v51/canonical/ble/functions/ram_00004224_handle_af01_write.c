/* Address: ram:00004224; name: handle_af01_write; body bytes: 128 */

/* Handles C0/10 local settings; forwards other application commands. */

void handle_af01_write(char *param_1,undefined4 param_2,code *param_3)

{
  undefined2 local_110;
  undefined1 uStack_10e;
  
  gp = &DAT_ram_20002000;
  FUN_ram_00001d1a(&local_110,0,0x100);
  if (DAT_ram_20002f89 != '\x02') {
    if ((*param_1 == '\x10') || (*param_1 == -0x40)) {
      FUN_ram_00007568(param_1 + 1,0xe);
      local_110 = 0xc131;
      uStack_10e = 0;
      (*param_3)(&local_110,3);
    }
    else {
      queue_gatt_to_main(param_1,param_2,0);
    }
  }
  return;
}

