/* Address: ram:0006827a; name: thunk_FUN_ram_00052288; body bytes: 4 */

void thunk_FUN_ram_00052288(undefined1 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(8);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e92;
    *(undefined1 *)(puVar1 + 1) = 0x30;
    *(undefined1 *)(puVar1 + 3) = param_1;
    puVar1[2] = param_2;
    tmos_msg_send(DAT_ram_20001d4f,puVar1);
    return;
  }
  return;
}

