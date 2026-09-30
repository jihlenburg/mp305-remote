/* Address: ram:00003178; name: FUN_ram_00003178; body bytes: 64 */

undefined4 FUN_ram_00003178(undefined4 param_1,int param_2,undefined4 param_3)

{
  gp = &DAT_ram_20002000;
  FUN_ram_200028d6(9,param_1,0,param_2 << 2);
  FUN_ram_200028d6(10,param_1,param_3,param_2 << 2);
  return 0;
}

