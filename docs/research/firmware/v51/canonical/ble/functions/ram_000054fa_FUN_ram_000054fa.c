/* Address: ram:000054fa; name: FUN_ram_000054fa; body bytes: 198 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000054fa(void)

{
  int iVar1;
  char cVar2;
  undefined4 in_a3;
  undefined4 in_a4;
  undefined1 *puVar3;
  char cVar4;
  uint uVar5;
  undefined1 auStack_20 [24];
  
  gp = &DAT_ram_20002000;
  (*_DAT_ram_00040048)(auStack_20,0xff,0xe,in_a3,in_a4,_DAT_ram_00040048);
  FUN_ram_200028d6(0xb,0x6e00,&DAT_ram_200042b0,0x16);
  iVar1 = (*_DAT_ram_0004003c)(auStack_20,&DAT_ram_200042be,8);
  if (iVar1 == 0) {
    puVar3 = &DAT_ram_200042b0;
    cVar4 = '\0';
    do {
      cVar2 = cVar4 + '\x01';
      if ((puVar3[0xe] & 0xdf) == 0) break;
      puVar3 = puVar3 + 1;
      cVar4 = cVar2;
    } while (cVar2 != '\b');
    DAT_ram_20002e44 = (cVar4 + '\x01') * '\x02';
    DAT_ram_20002e45 = 3;
    for (uVar5 = 2; uVar5 < DAT_ram_20002e44; uVar5 = uVar5 + 2 & 0xff) {
      (&DAT_ram_20002e44)[uVar5] = *(undefined1 *)((uVar5 >> 1) + 0x200042bd);
      (&DAT_ram_20002e45)[uVar5] = 0;
    }
  }
  return;
}

