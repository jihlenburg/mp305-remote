/* Address: ram:00068296; name: thunk_FUN_ram_000518cc; body bytes: 4 */

void thunk_FUN_ram_000518cc(undefined1 param_1,undefined2 param_2,undefined4 param_3)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0xe);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e92;
    *(undefined1 *)(puVar1 + 1) = 4;
    *(undefined1 *)((int)puVar1 + 3) = param_1;
    puVar1[2] = param_2;
    tmos_memcpy(puVar1 + 3,param_3,8);
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

