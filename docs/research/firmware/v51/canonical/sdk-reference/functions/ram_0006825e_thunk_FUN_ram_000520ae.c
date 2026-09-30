/* Address: ram:0006825e; name: thunk_FUN_ram_000520ae; body bytes: 4 */

void thunk_FUN_ram_000520ae(undefined1 param_1,undefined2 param_2,undefined1 param_3)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(8);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x591;
    *(undefined1 *)(puVar1 + 1) = param_1;
    *(undefined1 *)(puVar1 + 3) = param_3;
    puVar1[2] = param_2;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

