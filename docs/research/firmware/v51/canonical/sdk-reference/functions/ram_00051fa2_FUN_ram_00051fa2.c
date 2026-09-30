/* Address: ram:00051fa2; name: FUN_ram_00051fa2; body bytes: 88 */

void FUN_ram_00051fa2(undefined1 param_1,undefined1 param_2,undefined2 param_3,undefined1 param_4)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(10);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e91;
    *(undefined1 *)(puVar1 + 1) = 0x12;
    *(undefined1 *)(puVar1 + 2) = param_2;
    *(undefined1 *)((int)puVar1 + 3) = param_1;
    *(undefined1 *)(puVar1 + 4) = param_4;
    puVar1[3] = param_3;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

