/* Address: ram:00051a98; name: FUN_ram_00051a98; body bytes: 296 */

void FUN_ram_00051a98(int param_1,undefined2 param_2,undefined1 param_3,undefined1 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined2 param_8,
                     undefined2 param_9,undefined2 param_10,undefined1 param_11)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0x22);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e91;
    *(undefined1 *)(puVar1 + 1) = 10;
    if (param_1 == 0) {
      *(undefined1 *)((int)puVar1 + 3) = 0;
      tmos_memcpy(puVar1 + 4,param_5,6);
      tmos_memcpy(puVar1 + 7,param_6,6);
      tmos_memcpy(puVar1 + 10,param_7,6);
    }
    else {
      *(undefined1 *)((int)puVar1 + 3) = 0x31;
      tmos_memset(puVar1 + 4,0,6);
      tmos_memset(puVar1 + 7,0,6);
      tmos_memset(puVar1 + 10,0,6);
    }
    *(undefined1 *)(puVar1 + 3) = param_3;
    *(undefined1 *)((int)puVar1 + 7) = param_4;
    *(undefined1 *)(puVar1 + 0x10) = param_11;
    puVar1[2] = param_2;
    puVar1[0xd] = param_8;
    puVar1[0xe] = param_9;
    puVar1[0xf] = param_10;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

