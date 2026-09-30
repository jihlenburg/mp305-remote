/* Address: ram:00051996; name: FUN_ram_00051996; body bytes: 96 */

void FUN_ram_00051996(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                     undefined2 param_5)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0xe);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e91;
    *(undefined1 *)(puVar1 + 1) = 6;
    puVar1[2] = param_1;
    puVar1[3] = param_2;
    puVar1[4] = param_3;
    puVar1[5] = param_4;
    puVar1[6] = param_5;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

