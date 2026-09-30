/* Address: ram:00068276; name: thunk_FUN_ram_0005224a; body bytes: 4 */

void thunk_FUN_ram_0005224a(undefined1 param_1)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(3);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 0x91;
    puVar1[1] = 0x1a;
    puVar1[2] = param_1;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

