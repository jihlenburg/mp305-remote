/* Address: ram:00052066; name: FUN_ram_00052066; body bytes: 72 */

void FUN_ram_00052066(undefined2 param_1,undefined1 param_2)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(8);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e91;
    *(undefined1 *)(puVar1 + 1) = 0x14;
    *(undefined1 *)(puVar1 + 3) = param_2;
    puVar1[2] = param_1;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

