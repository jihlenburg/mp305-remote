/* Address: ram:0005170a; name: FUN_ram_0005170a; body bytes: 202 */

void FUN_ram_0005170a(int param_1,undefined2 param_2,undefined1 param_3,undefined1 param_4,
                     undefined4 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8,
                     undefined1 param_9)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0x16);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e91;
    *(undefined1 *)(puVar1 + 1) = 1;
    if (param_1 == 0) {
      *(undefined1 *)((int)puVar1 + 3) = 0;
      tmos_memcpy(puVar1 + 4,param_5,6);
    }
    else {
      *(undefined1 *)((int)puVar1 + 3) = 0x31;
      tmos_memset(puVar1 + 4,0,6);
    }
    *(undefined1 *)(puVar1 + 3) = param_3;
    *(undefined1 *)((int)puVar1 + 7) = param_4;
    *(undefined1 *)(puVar1 + 10) = param_9;
    puVar1[2] = param_2;
    puVar1[7] = param_6;
    puVar1[8] = param_7;
    puVar1[9] = param_8;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

