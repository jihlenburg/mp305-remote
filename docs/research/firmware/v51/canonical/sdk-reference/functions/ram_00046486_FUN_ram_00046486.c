/* Address: ram:00046486; name: FUN_ram_00046486; body bytes: 266 */

void FUN_ram_00046486(int param_1)

{
  undefined1 *puVar1;
  char cVar2;
  undefined1 *puVar3;
  byte bVar4;
  
  gp = 0x20004000;
  if (param_1 == 0) {
    if (DAT_ram_20001a04 != (undefined1 *)0x0) {
      FUN_ram_000461a2();
      FUN_ram_0004588a(0);
      return;
    }
  }
  else if ((*(char *)(param_1 + 3) != '\0') &&
          (puVar1 = *(undefined1 **)(param_1 + 4), puVar1 != (undefined1 *)0x0)) {
    cVar2 = GAP_GetParamValue(0x16);
    for (bVar4 = 0; bVar4 < *(byte *)(param_1 + 3); bVar4 = bVar4 + 1) {
      if (((cVar2 <= (char)puVar1[0xf]) && (DAT_ram_20001a04 != (undefined1 *)0x0)) &&
         (puVar3 = (undefined1 *)tmos_msg_allocate(0x14), puVar3 != (undefined1 *)0x0)) {
        *puVar3 = 0xd0;
        puVar3[1] = 0;
        puVar3[2] = 0x10;
        puVar3[3] = *puVar1;
        puVar3[0x12] = puVar1[0xf];
        puVar3[4] = puVar1[1];
        tmos_memcpy(puVar3 + 5,puVar1 + 2,6);
        puVar3[0xb] = puVar1[8];
        tmos_memcpy(puVar3 + 0xc,puVar1 + 9,6);
        tmos_msg_send(*DAT_ram_20001a04,puVar3);
      }
      puVar1 = puVar1 + 0x10;
    }
  }
  return;
}

