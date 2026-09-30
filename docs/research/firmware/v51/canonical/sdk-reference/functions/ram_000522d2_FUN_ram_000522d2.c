/* Address: ram:000522d2; name: FUN_ram_000522d2; body bytes: 68 */

void FUN_ram_000522d2(undefined4 param_1,undefined2 param_2,undefined2 param_3)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(8);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x1390;
    *(undefined1 *)(puVar1 + 1) = 1;
    puVar1[2] = param_2;
    puVar1[3] = param_3;
    tmos_msg_send(DAT_ram_20001cc8,puVar1);
    return;
  }
  return;
}

