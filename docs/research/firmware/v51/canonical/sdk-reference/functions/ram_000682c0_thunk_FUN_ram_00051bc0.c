/* Address: ram:000682c0; name: thunk_FUN_ram_00051bc0; body bytes: 4 */

void thunk_FUN_ram_00051bc0
               (undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined1 param_4,
               undefined4 param_5,undefined1 param_6)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  byte bVar3;
  
  gp = 0x20004000;
  puVar2 = (undefined4 *)tmos_msg_allocate(0x18);
  if (puVar2 != (undefined4 *)0x0) {
    puVar1 = puVar2 + 2;
    *puVar2 = 0x10b3e91;
    puVar2[1] = puVar1;
    bVar3 = 0;
    do {
      *(undefined1 *)puVar1 = param_1;
      *(undefined1 *)((int)puVar1 + 1) = param_2;
      tmos_memcpy((int)puVar1 + 2,param_3,6);
      *(undefined1 *)(puVar1 + 2) = param_4;
      tmos_memcpy((int)puVar1 + 9,param_5,6);
      *(undefined1 *)((int)puVar1 + 0xf) = param_6;
      bVar3 = bVar3 + 1;
      puVar1 = puVar1 + 4;
    } while (bVar3 < *(byte *)((int)puVar2 + 3));
    tmos_msg_send(DAT_ram_20001d4c,puVar2);
    return;
  }
  return;
}

