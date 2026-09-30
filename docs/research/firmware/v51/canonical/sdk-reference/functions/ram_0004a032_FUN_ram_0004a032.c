/* Address: ram:0004a032; name: FUN_ram_0004a032; body bytes: 106 */

void FUN_ram_0004a032(undefined2 param_1,undefined2 param_2,undefined2 param_3)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_200019b5 != -1) &&
     (puVar1 = (undefined2 *)tmos_msg_allocate(10), puVar1 != (undefined2 *)0x0)) {
    *puVar1 = 0xb1;
    *(undefined1 *)(puVar1 + 2) = 0;
    puVar1[1] = param_1;
    puVar1[3] = param_2;
    puVar1[4] = param_3;
    tmos_msg_send(DAT_ram_200019b5,puVar1);
    return;
  }
  return;
}

