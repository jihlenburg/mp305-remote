/* Address: ram:0004472c; name: FUN_ram_0004472c; body bytes: 104 */

void FUN_ram_0004472c(undefined1 param_1,undefined2 param_2,undefined4 param_3,undefined1 param_4)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0xe);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0xd0;
    puVar1[2] = param_2;
    *(undefined1 *)(puVar1 + 1) = 0xc;
    tmos_memcpy(puVar1 + 3,param_3,6);
    *(undefined1 *)(puVar1 + 6) = param_4;
    tmos_msg_send(param_1,puVar1);
    return;
  }
  return;
}

