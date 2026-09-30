/* Address: ram:000682ee; name: thunk_FUN_ram_00051f28; body bytes: 4 */

void thunk_FUN_ram_00051f28(undefined2 param_1)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(6);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e91;
    *(undefined1 *)(puVar1 + 1) = 0x10;
    puVar1[2] = param_1;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

