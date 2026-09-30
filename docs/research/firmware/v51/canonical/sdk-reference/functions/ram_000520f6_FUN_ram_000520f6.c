/* Address: ram:000520f6; name: FUN_ram_000520f6; body bytes: 80 */

void FUN_ram_000520f6(undefined1 param_1,undefined2 param_2,undefined1 param_3)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(8);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e92;
    *(undefined1 *)(puVar1 + 1) = 8;
    *(undefined1 *)(puVar1 + 3) = param_1;
    *(undefined1 *)((int)puVar1 + 7) = param_3;
    puVar1[2] = param_2;
    tmos_msg_send(DAT_ram_20001d4f,puVar1);
    return;
  }
  return;
}

