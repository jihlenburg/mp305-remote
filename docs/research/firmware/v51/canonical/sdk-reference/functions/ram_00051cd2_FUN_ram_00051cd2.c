/* Address: ram:00051cd2; name: FUN_ram_00051cd2; body bytes: 252 */

void FUN_ram_00051cd2(undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined1 param_4,
                     undefined1 param_5,undefined1 param_6,undefined1 param_7,undefined1 param_8,
                     undefined2 param_9,undefined1 param_10,undefined4 param_11,byte param_12,
                     undefined4 param_13)

{
  undefined4 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined4 *)tmos_msg_allocate(param_12 + 0x24);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[1] = puVar1 + 2;
    *(undefined1 *)(puVar1 + 2) = param_1;
    *puVar1 = 0x10d3e91;
    *(undefined1 *)((int)puVar1 + 9) = param_2;
    tmos_memcpy((int)puVar1 + 10,param_3,6);
    *(undefined1 *)(puVar1 + 4) = param_4;
    *(undefined1 *)((int)puVar1 + 0x11) = param_5;
    *(undefined1 *)((int)puVar1 + 0x12) = param_6;
    *(undefined1 *)((int)puVar1 + 0x13) = param_7;
    *(undefined1 *)(puVar1 + 5) = param_8;
    *(undefined2 *)((int)puVar1 + 0x16) = param_9;
    *(undefined1 *)(puVar1 + 6) = param_10;
    tmos_memcpy((int)puVar1 + 0x19,param_11,6);
    *(byte *)((int)puVar1 + 0x1f) = param_12;
    puVar1[8] = puVar1 + 9;
    tmos_memcpy(puVar1 + 9,param_13,(uint)param_12);
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

