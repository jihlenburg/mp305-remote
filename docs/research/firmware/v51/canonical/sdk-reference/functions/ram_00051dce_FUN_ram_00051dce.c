/* Address: ram:00051dce; name: FUN_ram_00051dce; body bytes: 156 */

void FUN_ram_00051dce(int param_1)

{
  undefined2 *puVar1;
  
  gp = 0x20004000;
  puVar1 = (undefined2 *)tmos_msg_allocate(0x14);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0x3e91;
    *(undefined1 *)(puVar1 + 1) = 0xe;
    *(undefined1 *)((int)puVar1 + 3) = *(undefined1 *)(param_1 + 1);
    puVar1[2] = *(undefined2 *)(param_1 + 2);
    *(undefined1 *)(puVar1 + 3) = *(undefined1 *)(param_1 + 4);
    *(undefined1 *)((int)puVar1 + 7) = *(undefined1 *)(param_1 + 5);
    tmos_memcpy(puVar1 + 4,param_1 + 6,6);
    *(undefined1 *)(puVar1 + 7) = *(undefined1 *)(param_1 + 0xc);
    puVar1[8] = *(undefined2 *)(param_1 + 0xd);
    *(undefined1 *)(puVar1 + 9) = *(undefined1 *)(param_1 + 0xf);
    tmos_msg_send(DAT_ram_20001d4c,puVar1);
    return;
  }
  return;
}

