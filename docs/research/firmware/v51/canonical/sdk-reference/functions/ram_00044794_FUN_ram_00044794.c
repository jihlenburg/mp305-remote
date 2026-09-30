/* Address: ram:00044794; name: FUN_ram_00044794; body bytes: 126 */

void FUN_ram_00044794(undefined1 param_1)

{
  char cVar1;
  undefined1 *puVar2;
  
  gp = 0x20004000;
  if ((DAT_ram_20001c07 != -1) &&
     (puVar2 = (undefined1 *)tmos_msg_allocate(0xe), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 0xd0;
    puVar2[1] = param_1;
    puVar2[2] = 0;
    tmos_memcpy(puVar2 + 3,&DAT_ram_20001c1c,6);
    cVar1 = DAT_ram_20001c07;
    *(undefined2 *)(puVar2 + 10) = DAT_ram_20001c0c;
    puVar2[0xc] = DAT_ram_20001c05;
    tmos_msg_send(cVar1,puVar2);
    return;
  }
  return;
}

