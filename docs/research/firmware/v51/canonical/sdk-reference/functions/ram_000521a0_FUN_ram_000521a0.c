/* Address: ram:000521a0; name: FUN_ram_000521a0; body bytes: 98 */

void FUN_ram_000521a0(undefined2 param_1,int param_2,undefined4 param_3)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(param_2 + 0xc);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0xe91;
    *(char *)(puVar1 + 1) = (char)param_2;
    puVar1[2] = param_1;
    *(undefined2 **)(puVar1 + 4) = puVar1 + 6;
    tmos_memcpy(puVar1 + 6,param_3,param_2);
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

