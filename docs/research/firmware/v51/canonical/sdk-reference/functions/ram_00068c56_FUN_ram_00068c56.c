/* Address: ram:00068c56; name: FUN_ram_00068c56; body bytes: 50 */

void FUN_ram_00068c56(void)

{
  byte bVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = 0;
  bVar1 = 0;
  while ((bVar1 < DAT_ram_20001a8d && (iVar2 == 0))) {
    iVar2 = FUN_ram_00068b10(bVar1);
    bVar1 = bVar1 + 1;
  }
  return;
}

