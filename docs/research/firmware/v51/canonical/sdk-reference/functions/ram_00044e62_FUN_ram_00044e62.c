/* Address: ram:00044e62; name: FUN_ram_00044e62; body bytes: 142 */

void FUN_ram_00044e62(undefined2 param_1,uint param_2)

{
  char *pcVar1;
  undefined2 *puVar2;
  char cVar3;
  
  gp = 0x20004000;
  pcVar1 = (char *)FUN_ram_0004df14();
  if ((pcVar1 != (char *)0x0) &&
     (puVar2 = (undefined2 *)tmos_msg_allocate(0xe), puVar2 != (undefined2 *)0x0)) {
    cVar3 = DAT_ram_20001c54;
    if (DAT_ram_20001c54 == '\0') {
      cVar3 = *pcVar1;
    }
    *puVar2 = 0xd0;
    *(undefined1 *)(puVar2 + 1) = 0xb;
    tmos_memcpy((int)puVar2 + 3,pcVar1 + 6,6);
    *(byte *)(puVar2 + 6) = (byte)param_2 & 1;
    *(byte *)((int)puVar2 + 0xd) = (byte)(param_2 >> 1) & 1;
    puVar2[5] = param_1;
    tmos_msg_send(cVar3,puVar2);
    return;
  }
  return;
}

