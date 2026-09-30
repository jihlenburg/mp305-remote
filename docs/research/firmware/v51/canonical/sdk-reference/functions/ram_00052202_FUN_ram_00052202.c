/* Address: ram:00052202; name: FUN_ram_00052202; body bytes: 72 */

void FUN_ram_00052202(undefined1 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(6);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0xf91;
    *(undefined1 *)((int)puVar1 + 3) = 1;
    *(undefined1 *)(puVar1 + 1) = param_1;
    puVar1[2] = param_2;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

