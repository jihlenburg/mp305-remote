/* Address: ram:000682c4; name: thunk_FUN_ram_00051c7a; body bytes: 4 */

void thunk_FUN_ram_00051c7a
               (undefined1 param_1,undefined2 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(8);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e91;
    *(undefined1 *)(puVar1 + 1) = 0xc;
    *(undefined1 *)((int)puVar1 + 3) = param_1;
    *(undefined1 *)(puVar1 + 3) = param_3;
    *(undefined1 *)((int)puVar1 + 7) = param_4;
    puVar1[2] = param_2;
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

