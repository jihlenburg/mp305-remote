/* Address: ram:00046fcc; name: FUN_ram_00046fcc; body bytes: 154 */

void FUN_ram_00046fcc(undefined1 param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  if (DAT_ram_20001a0c == -2) {
    puVar1 = (undefined1 *)tmos_msg_allocate(4);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 0xd0;
      puVar1[2] = 2;
      puVar1[1] = param_2;
      puVar1[3] = param_1;
      tmos_msg_send(DAT_ram_20001a0d,puVar1);
      return;
    }
  }
  else {
    if ((DAT_ram_20001a0c != -1) &&
       (puVar1 = (undefined1 *)tmos_msg_allocate(4), puVar1 != (undefined1 *)0x0)) {
      *puVar1 = 0xd0;
      puVar1[1] = param_2;
      puVar1[2] = 2;
      puVar1[3] = param_1;
      tmos_msg_send(DAT_ram_20001a0c,puVar1);
    }
    DAT_ram_20001a0c = -2;
  }
  return;
}

