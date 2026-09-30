/* Address: ram:00044ef0; name: FUN_ram_00044ef0; body bytes: 166 */

void FUN_ram_00044ef0(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  undefined2 *puVar3;
  
  gp = 0x20004000;
  pcVar2 = (char *)FUN_ram_0004df14();
  if ((pcVar2 != (char *)0x0) &&
     (puVar3 = (undefined2 *)tmos_msg_allocate(0x2c), puVar3 != (undefined2 *)0x0)) {
    cVar1 = DAT_ram_20001c54;
    if (DAT_ram_20001c54 == '\0') {
      cVar1 = *pcVar2;
    }
    *puVar3 = 0xd0;
    *(undefined1 *)(puVar3 + 1) = 0x1a;
    tmos_memcpy((int)puVar3 + 3,pcVar2 + 6,6);
    puVar3[5] = param_1;
    tmos_memcpy(puVar3 + 6,param_2,0x10);
    tmos_memcpy(puVar3 + 0xe,param_3,0x10);
    tmos_msg_send(cVar1,puVar3);
    return;
  }
  return;
}

