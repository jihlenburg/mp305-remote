/* Address: ram:000682f2; name: thunk_FUN_ram_00051f68; body bytes: 4 */

void thunk_FUN_ram_00051f68(void)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(3);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 0x91;
    puVar1[1] = 0x3e;
    puVar1[2] = 0x11;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

