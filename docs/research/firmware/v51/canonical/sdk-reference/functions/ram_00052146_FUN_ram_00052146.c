/* Address: ram:00052146; name: FUN_ram_00052146; body bytes: 90 */

void FUN_ram_00052146(undefined1 param_1,undefined2 param_2,undefined1 param_3,undefined2 param_4,
                     undefined2 param_5)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0xc);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = &hpmcounter17h;
    *(undefined1 *)(puVar1 + 1) = param_1;
    *(undefined1 *)(puVar1 + 3) = param_3;
    puVar1[2] = param_2;
    puVar1[4] = param_4;
    puVar1[5] = param_5;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

