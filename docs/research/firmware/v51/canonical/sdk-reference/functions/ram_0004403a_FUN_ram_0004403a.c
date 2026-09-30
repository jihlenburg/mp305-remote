/* Address: ram:0004403a; name: FUN_ram_0004403a; body bytes: 88 */

void FUN_ram_0004403a(undefined1 param_1,undefined4 param_2,undefined2 param_3,undefined1 param_4,
                     undefined1 param_5)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(8);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 0xd0;
    puVar1[1] = param_1;
    puVar1[2] = 6;
    puVar1[6] = param_4;
    puVar1[7] = param_5;
    *(undefined2 *)(puVar1 + 4) = param_3;
    tmos_msg_send(param_2,puVar1);
    return;
  }
  return;
}

