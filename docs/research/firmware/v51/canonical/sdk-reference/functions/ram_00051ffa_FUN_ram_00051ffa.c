/* Address: ram:00051ffa; name: FUN_ram_00051ffa; body bytes: 108 */

void FUN_ram_00051ffa(undefined1 param_1,undefined1 param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(0xb);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 0x91;
    puVar1[1] = 0x3e;
    puVar1[2] = 0x13;
    puVar1[3] = param_1;
    puVar1[4] = param_2;
    tmos_memcpy(puVar1 + 5,param_3,6);
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

