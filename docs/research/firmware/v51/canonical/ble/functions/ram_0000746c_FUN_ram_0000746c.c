/* Address: ram:0000746c; name: FUN_ram_0000746c; body bytes: 80 */

void FUN_ram_0000746c(undefined1 param_1)

{
  gp = &DAT_ram_20002000;
  FUN_ram_200028d6(0xb,0x7000,&DAT_ram_20005150,4);
  FUN_ram_200028d6(9,0x7000,0,0x100);
  DAT_ram_20005150 = param_1;
  FUN_ram_200028d6(10,0x7000,&DAT_ram_20005150,4);
  return;
}

