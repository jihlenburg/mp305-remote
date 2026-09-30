/* Address: ram:00044696; name: FUN_ram_00044696; body bytes: 150 */

void FUN_ram_00044696(undefined1 param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4,
                     undefined1 param_5,undefined1 param_6,undefined4 param_7)

{
  char cVar1;
  char *pcVar2;
  undefined1 *puVar3;
  
  gp = 0x20004000;
  pcVar2 = (char *)FUN_ram_0004df14(param_2);
  if ((pcVar2 != (char *)0x0) &&
     (puVar3 = (undefined1 *)tmos_msg_allocate(0x10), puVar3 != (undefined1 *)0x0)) {
    tmos_memset(puVar3,0,0x10);
    cVar1 = DAT_ram_20001c54;
    if (DAT_ram_20001c54 == '\0') {
      cVar1 = *pcVar2;
    }
    *puVar3 = 0xd0;
    puVar3[2] = 0xf;
    puVar3[1] = param_1;
    *(short *)(puVar3 + 4) = (short)param_2;
    puVar3[8] = param_3;
    puVar3[9] = param_4;
    puVar3[10] = param_5;
    puVar3[0xb] = param_6;
    *(undefined4 *)(puVar3 + 0xc) = param_7;
    tmos_msg_send(cVar1,puVar3);
  }
  return;
}

