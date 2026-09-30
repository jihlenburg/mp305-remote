/* Address: ram:0004609c; name: FUN_ram_0004609c; body bytes: 90 */

void FUN_ram_0004609c(int param_1)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  if (((DAT_ram_20001d53 != -1) && (param_1 != 0)) &&
     (puVar1 = (undefined2 *)tmos_msg_allocate(6), puVar1 != (undefined2 *)0x0)) {
    *puVar1 = 0xd0;
    *(undefined1 *)(puVar1 + 1) = 0x17;
    puVar1[2] = *(undefined2 *)(param_1 + 4);
    tmos_msg_send(DAT_ram_20001d53,puVar1);
    return;
  }
  return;
}

