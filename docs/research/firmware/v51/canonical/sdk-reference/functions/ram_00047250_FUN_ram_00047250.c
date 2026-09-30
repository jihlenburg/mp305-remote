/* Address: ram:00047250; name: FUN_ram_00047250; body bytes: 298 */

void FUN_ram_00047250(int param_1,int param_2)

{
  char cVar1;
  undefined1 *puVar2;
  
  gp = 0x20004000;
  if (param_1 == 1) {
    if ((DAT_ram_20001a10 == 0) || (DAT_ram_20001c08 != '\0')) {
      if (DAT_ram_200019e4 != (char *)0x0) {
        FUN_ram_000471e2(*DAT_ram_200019e4);
        return;
      }
    }
    else if (DAT_ram_20001a10 < 0x3c) {
      tmos_stop_task(DAT_ram_20001d4c,2);
      tmos_start_task(DAT_ram_20001d4c,2,(uint)DAT_ram_20001a10 * 0x640);
      DAT_ram_20001a10 = 0;
    }
    else {
      DAT_ram_20001a10 = DAT_ram_20001a10 - 0x3c;
    }
  }
  else if ((DAT_ram_200019e4 != (char *)0x0) && ((DAT_ram_20001d50 & 4) != 0)) {
    if (param_1 != 2) {
      tmos_stop_task(DAT_ram_20001d4c,2);
      DAT_ram_20001a10 = 0;
      FUN_ram_00046d4a();
      return;
    }
    puVar2 = (undefined1 *)tmos_msg_allocate(0xb);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 0xd0;
      puVar2[1] = 0;
      puVar2[2] = 0x19;
      puVar2[3] = *(undefined1 *)(param_2 + 3);
      puVar2[4] = *(undefined1 *)(param_2 + 4);
      tmos_memcpy(puVar2 + 5,param_2 + 5,6);
      cVar1 = DAT_ram_20001d51;
      if (DAT_ram_20001d51 == -1) {
        cVar1 = *DAT_ram_200019e4;
      }
      tmos_msg_send(cVar1,puVar2);
      return;
    }
  }
  return;
}

