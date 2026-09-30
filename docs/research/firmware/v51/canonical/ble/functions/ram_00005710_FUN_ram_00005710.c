/* Address: ram:00005710; name: FUN_ram_00005710; body bytes: 52 */

void FUN_ram_00005710(void)

{
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  gp = &DAT_ram_20002000;
  uStack_18 = 0;
  uStack_14 = 0;
  FUN_ram_200028d6(0xb,&LAB_ram_000069fe_2,&uStack_18,8);
  FUN_ram_000078b2(&DAT_ram_20002f30,(int)&uStack_18 + 1,6);
  return;
}

