/* Address: ram:000517d4; name: FUN_ram_000517d4; body bytes: 152 */

void FUN_ram_000517d4(undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined1 param_6)

{
  undefined4 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined4 *)tmos_msg_allocate(0x31);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[1] = puVar1 + 2;
    *puVar1 = 0x1023e91;
    *(undefined1 *)(puVar1 + 2) = param_1;
    *(undefined1 *)((int)puVar1 + 9) = param_2;
    tmos_memcpy((int)puVar1 + 10,param_3,6);
    *(char *)(puVar1 + 4) = (char)param_4;
    tmos_memcpy((int)puVar1 + 0x11,param_5,param_4);
    *(undefined1 *)(puVar1 + 0xc) = param_6;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

