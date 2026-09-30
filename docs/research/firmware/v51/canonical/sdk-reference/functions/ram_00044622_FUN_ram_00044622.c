/* Address: ram:00044622; name: FUN_ram_00044622; body bytes: 116 */

void FUN_ram_00044622(undefined1 param_1,undefined4 param_2)

{
  char cVar1;
  char *pcVar2;
  undefined1 *puVar3;
  
  gp = 0x20004000;
  pcVar2 = (char *)FUN_ram_0004df14(param_2);
  if (pcVar2 != (char *)0x0) {
    cVar1 = DAT_ram_20001c54;
    if (DAT_ram_20001c54 == '\0') {
      cVar1 = *pcVar2;
    }
    puVar3 = (undefined1 *)tmos_msg_allocate(6);
    if (puVar3 != (undefined1 *)0x0) {
      tmos_memset(puVar3,0,6);
      *puVar3 = 0xd0;
      puVar3[1] = param_1;
      puVar3[2] = 0xe;
      *(short *)(puVar3 + 4) = (short)param_2;
      tmos_msg_send(cVar1,puVar3);
      return;
    }
  }
  return;
}

