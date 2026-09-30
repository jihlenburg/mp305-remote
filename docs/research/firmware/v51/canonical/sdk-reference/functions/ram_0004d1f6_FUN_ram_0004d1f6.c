/* Address: ram:0004d1f6; name: FUN_ram_0004d1f6; body bytes: 122 */

void FUN_ram_0004d1f6(undefined4 param_1,undefined2 param_2,undefined1 param_3,undefined1 param_4,
                     undefined1 param_5,int param_6)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(0x20);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 0xa2;
    puVar1[1] = param_3;
    *(undefined2 *)(puVar1 + 2) = param_2;
    puVar1[4] = param_5;
    puVar1[5] = param_4;
    if (param_6 == 0) {
      tmos_memset(puVar1 + 8,0,0x18);
    }
    else {
      tmos_memcpy(puVar1 + 8,param_6);
    }
    tmos_msg_send(param_1,puVar1);
    return;
  }
  return;
}

