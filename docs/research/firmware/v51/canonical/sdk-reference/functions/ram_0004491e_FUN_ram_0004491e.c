/* Address: ram:0004491e; name: FUN_ram_0004491e; body bytes: 188 */

void FUN_ram_0004491e(undefined1 param_1,undefined4 param_2,undefined1 param_3,int param_4,
                     undefined2 param_5,undefined1 param_6,undefined2 param_7,undefined2 param_8,
                     undefined2 param_9,undefined1 param_10)

{
  undefined1 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined1 *)tmos_msg_allocate(0x16);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 0xd0;
    puVar1[3] = param_3;
    puVar1[1] = param_1;
    puVar1[2] = 5;
    if (param_4 == 0) {
      tmos_memset(puVar1 + 4,0,6);
    }
    else {
      tmos_memcpy(puVar1 + 4,param_4);
    }
    puVar1[0xc] = param_6;
    puVar1[0x14] = param_10;
    *(undefined2 *)(puVar1 + 10) = param_5;
    *(undefined2 *)(puVar1 + 0xe) = param_7;
    *(undefined2 *)(puVar1 + 0x10) = param_8;
    *(undefined2 *)(puVar1 + 0x12) = param_9;
    tmos_msg_send(param_2,puVar1);
    return;
  }
  return;
}

