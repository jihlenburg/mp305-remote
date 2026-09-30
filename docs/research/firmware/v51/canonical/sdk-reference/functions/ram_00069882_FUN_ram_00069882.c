/* Address: ram:00069882; name: FUN_ram_00069882; body bytes: 192 */

void FUN_ram_00069882(void)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  undefined1 *puVar5;
  
  gp = 0x20004000;
  iVar4 = thunk_FUN_ram_0004e07e();
  if (iVar4 == 0) {
    if (DAT_ram_20001a8c == '\x01') {
      FUN_ram_00068c56();
      bVar1 = DAT_ram_20001a8d;
      DAT_ram_20001a8c = '\0';
      puVar5 = (undefined1 *)(DAT_ram_20001a88 + 0xe);
      for (bVar2 = 0; bVar2 != bVar1; bVar2 = bVar2 + 1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 0x10;
      }
    }
    else {
      for (uVar3 = 0; uVar3 < DAT_ram_20001a8d; uVar3 = uVar3 + 1 & 0xff) {
        if (*(char *)(DAT_ram_20001a88 + uVar3 * 0x10 + 0xe) == '\x01') {
          FUN_ram_00068b10(uVar3);
          *(undefined1 *)(DAT_ram_20001a88 + uVar3 * 0x10 + 0xe) = 0;
        }
      }
    }
    FUN_ram_000430e4();
    FUN_ram_00068dbc();
    return;
  }
  return;
}

