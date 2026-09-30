/* Address: ram:000682ea; name: thunk_FUN_ram_00051e6a; body bytes: 4 */

void thunk_FUN_ram_00051e6a
               (undefined2 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
               undefined1 param_5,int param_6,undefined4 param_7)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  if ((DAT_ram_20001d53 != -1) &&
     (puVar1 = (undefined2 *)tmos_msg_allocate(param_6 + 0x10), puVar1 != (undefined2 *)0x0)) {
    *puVar1 = 0xd0;
    *(undefined1 *)(puVar1 + 1) = 0x16;
    puVar1[2] = param_1;
    *(undefined1 *)(puVar1 + 3) = param_2;
    *(undefined1 *)((int)puVar1 + 7) = param_3;
    *(undefined1 *)(puVar1 + 4) = param_4;
    *(undefined1 *)((int)puVar1 + 9) = param_5;
    *(char *)(puVar1 + 5) = (char)param_6;
    if (param_6 == 0) {
      *(undefined4 *)(puVar1 + 6) = 0;
    }
    else {
      *(undefined2 **)(puVar1 + 6) = puVar1 + 8;
      tmos_memcpy(puVar1 + 8,param_7,param_6);
    }
    tmos_msg_send(DAT_ram_20001d53,puVar1);
    return;
  }
  return;
}

