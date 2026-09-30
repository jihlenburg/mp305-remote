/* Address: ram:0000685a; name: FUN_ram_0000685a; body bytes: 276 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_0000685a(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  
  gp = &DAT_ram_20002000;
  iVar3 = param_1 * 0x4e;
  if ((undefined *)(&DAT_ram_20004c5c)[param_1 * 0x27] == &pmpaddr18) {
    cVar1 = (&DAT_ram_20004c7e)[iVar3];
    puVar6 = &DAT_ram_20004be5;
    iVar2 = 0;
    do {
      iVar4 = (*_DAT_ram_0004003c)(&DAT_ram_20004c52 + iVar3,puVar6,6);
      if (iVar4 != 0) {
        if ((&DAT_ram_20004c03)[iVar2] != '\0') {
          gp = &DAT_ram_20002000;
          return;
        }
        if (cVar1 == '\0') {
          gp = &DAT_ram_20002000;
          return;
        }
        (&DAT_ram_20004c03)[iVar2] = cVar1;
        FUN_ram_000078b2(&DAT_ram_20004b4a + iVar2 * 0x1f,iVar3 + 0x20004c5f,cVar1);
        return;
      }
      iVar2 = iVar2 + 1;
      puVar6 = puVar6 + 6;
    } while (iVar2 != 5);
    (&DAT_ram_20004b4a)[(uint)DAT_ram_20004c08 * 0x1f] = 0;
    FUN_ram_000078b2(&DAT_ram_20004b4a + (uint)DAT_ram_20004c08 * 0x1f,iVar3 + 0x20004c5f,cVar1);
    uVar5 = (uint)DAT_ram_20004c08;
    (&DAT_ram_20004c03)[uVar5] = cVar1;
    FUN_ram_000078b2(&DAT_ram_20004be5 + uVar5 * 6,&DAT_ram_20004c52 + iVar3,6);
    if (4 < DAT_ram_20004c08) {
      DAT_ram_20004c08 = 0;
      FUN_ram_0000696e();
      return;
    }
    DAT_ram_20004c08 = DAT_ram_20004c08 + 1;
  }
  return;
}

