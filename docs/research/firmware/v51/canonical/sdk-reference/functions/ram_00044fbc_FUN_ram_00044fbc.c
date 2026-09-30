/* Address: ram:00044fbc; name: FUN_ram_00044fbc; body bytes: 122 */

void FUN_ram_00044fbc(undefined4 param_1,undefined4 param_2)

{
  char *pcVar1;
  undefined2 *puVar2;
  char cVar3;
  
  gp = 0x20004000;
  pcVar1 = (char *)FUN_ram_0004df14();
  cVar3 = DAT_ram_20001c54;
  if (pcVar1 != (char *)0x0) {
    *(undefined4 *)(pcVar1 + 0x28) = param_2;
    if (cVar3 == '\0') {
      cVar3 = *pcVar1;
    }
    puVar2 = (undefined2 *)tmos_msg_allocate(0x10);
    if (puVar2 != (undefined2 *)0x0) {
      *puVar2 = 0xd0;
      *(undefined1 *)(puVar2 + 1) = 9;
      *(char *)((int)puVar2 + 3) = pcVar1[5];
      tmos_memcpy(puVar2 + 2,pcVar1 + 6,6);
      *(undefined4 *)(puVar2 + 6) = *(undefined4 *)(pcVar1 + 0x28);
      tmos_msg_send(cVar3,puVar2);
      return;
    }
  }
  return;
}

