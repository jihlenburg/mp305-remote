/* Address: ram:00045fea; name: FUN_ram_00045fea; body bytes: 178 */

void FUN_ram_00045fea(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined2 *puVar3;
  
  gp = 0x20004000;
  if (((DAT_ram_20001d53 != -1) && (param_1 != 0)) &&
     (puVar3 = (undefined2 *)tmos_msg_allocate(0x14), puVar3 != (undefined2 *)0x0)) {
    *puVar3 = 0xd0;
    *(undefined1 *)(puVar3 + 1) = 0x15;
    *(undefined1 *)((int)puVar3 + 3) = *(undefined1 *)(param_1 + 3);
    puVar3[2] = *(undefined2 *)(param_1 + 4);
    *(undefined1 *)(puVar3 + 3) = *(undefined1 *)(param_1 + 6);
    uVar2 = FUN_ram_00044326(*(undefined1 *)(param_1 + 7),param_1 + 8);
    *(undefined1 *)((int)puVar3 + 7) = uVar2;
    tmos_memcpy(puVar3 + 4,param_1 + 8,6);
    cVar1 = DAT_ram_20001d53;
    *(undefined1 *)(puVar3 + 7) = *(undefined1 *)(param_1 + 0xe);
    puVar3[8] = *(undefined2 *)(param_1 + 0x10);
    *(undefined1 *)(puVar3 + 9) = *(undefined1 *)(param_1 + 0x12);
    tmos_msg_send(cVar1,puVar3);
    return;
  }
  return;
}

