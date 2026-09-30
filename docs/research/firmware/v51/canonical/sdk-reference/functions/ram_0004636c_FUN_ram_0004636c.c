/* Address: ram:0004636c; name: FUN_ram_0004636c; body bytes: 282 */

void FUN_ram_0004636c(int param_1)

{
  char cVar1;
  undefined1 *puVar2;
  char cVar3;
  int iVar4;
  undefined2 *puVar5;
  byte bVar6;
  
  gp = 0x20004000;
  if (param_1 == 0) {
    if (DAT_ram_20001a04 != (undefined1 *)0x0) {
      FUN_ram_000461a2();
      FUN_ram_0004588a(0);
      return;
    }
  }
  else if ((*(char *)(param_1 + 3) != '\0') &&
          (puVar2 = *(undefined1 **)(param_1 + 4), puVar2 != (undefined1 *)0x0)) {
    cVar3 = GAP_GetParamValue(0x16);
    for (bVar6 = 0; bVar6 < *(byte *)(param_1 + 3); bVar6 = bVar6 + 1) {
      if ((((cVar3 <= (char)puVar2[0x28]) && (DAT_ram_20001a04 != (undefined1 *)0x0)) &&
          (iVar4 = FUN_ram_00045b14(puVar2), iVar4 != 0)) &&
         (puVar5 = (undefined2 *)tmos_msg_allocate((byte)puVar2[8] + 0x14),
         puVar5 != (undefined2 *)0x0)) {
        *puVar5 = 0xd0;
        *(undefined1 *)(puVar5 + 1) = 0xd;
        *(undefined1 *)((int)puVar5 + 3) = *puVar2;
        *(undefined1 *)((int)puVar5 + 0xb) = puVar2[0x28];
        *(undefined1 *)(puVar5 + 2) = puVar2[1];
        tmos_memcpy((int)puVar5 + 5,puVar2 + 2,6);
        cVar1 = puVar2[8];
        *(char *)(puVar5 + 6) = cVar1;
        if (cVar1 == '\0') {
          *(undefined4 *)(puVar5 + 8) = 0;
        }
        else {
          *(undefined2 **)(puVar5 + 8) = puVar5 + 10;
          tmos_memcpy(puVar5 + 10,puVar2 + 9);
        }
        tmos_msg_send(*DAT_ram_20001a04,puVar5);
      }
      puVar2 = puVar2 + 0x29;
    }
  }
  return;
}

