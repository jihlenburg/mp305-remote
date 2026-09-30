/* Address: ram:00051932; name: FUN_ram_00051932; body bytes: 100 */

void FUN_ram_00051932(undefined2 param_1,undefined4 param_2,undefined2 param_3)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0x10);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e92;
    *(undefined1 *)(puVar1 + 1) = 5;
    puVar1[2] = param_1;
    tmos_memcpy(puVar1 + 3,param_2,8);
    puVar1[7] = param_3;
    tmos_msg_send(DAT_ram_20001d4f,puVar1);
    return;
  }
  return;
}

