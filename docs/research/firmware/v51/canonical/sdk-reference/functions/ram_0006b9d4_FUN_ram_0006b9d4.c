/* Address: ram:0006b9d4; name: FUN_ram_0006b9d4; body bytes: 114 */

void FUN_ram_0006b9d4(void)

{
  gp = 0x20004000;
  DAT_ram_20000000 = FUN_ram_20000400;
  DAT_ram_20000004 = FUN_ram_20000fa4;
  DAT_ram_20000008 = FUN_ram_200014ae;
  FUN_ram_20000010(FUN_ram_000402b0,FUN_ram_20000040,&DAT_ram_200018b8);
  FUN_ram_20000010(&DAT_ram_0006c668,&DAT_ram_200018b8,&DAT_ram_200019d0);
  (*(code *)&LAB_ram_20000022)();
  return;
}

