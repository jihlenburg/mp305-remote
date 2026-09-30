/* Address: ram:0005d5f6; name: FUN_ram_0005d5f6; body bytes: 66 */

undefined4 FUN_ram_0005d5f6(undefined2 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(4);
  if (puVar1 != (undefined1 *)0x0) {
    *(undefined2 *)(puVar1 + 2) = param_1;
    *puVar1 = param_2;
    puVar1[1] = param_3;
    uVar2 = tmos_msg_send(DAT_ram_20001b67,puVar1);
    return uVar2;
  }
  return 4;
}

