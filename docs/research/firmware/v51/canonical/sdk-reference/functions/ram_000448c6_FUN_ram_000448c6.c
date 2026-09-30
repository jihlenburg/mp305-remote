/* Address: ram:000448c6; name: FUN_ram_000448c6; body bytes: 88 */

void FUN_ram_000448c6(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(8);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 0xd0;
    puVar1[2] = 0x11;
    puVar1[3] = *(undefined1 *)(param_2 + 3);
    *(undefined2 *)(puVar1 + 4) = *(undefined2 *)(param_2 + 4);
    puVar1[6] = *(undefined1 *)(param_2 + 6);
    puVar1[7] = *(undefined1 *)(param_2 + 7);
    tmos_msg_send(param_1,puVar1);
    return;
  }
  return;
}

