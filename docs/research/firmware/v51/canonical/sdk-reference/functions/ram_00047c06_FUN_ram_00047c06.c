/* Address: ram:00047c06; name: FUN_ram_00047c06; body bytes: 62 */

void FUN_ram_00047c06(undefined1 param_1)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(3);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 0xd0;
    puVar1[2] = 0x13;
    puVar1[1] = param_1;
    tmos_msg_send(DAT_ram_20001a0d,puVar1);
    return;
  }
  return;
}

