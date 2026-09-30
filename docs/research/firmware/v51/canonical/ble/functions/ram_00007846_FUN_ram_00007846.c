/* Address: ram:00007846; name: FUN_ram_00007846; body bytes: 108 */

void FUN_ram_00007846(void)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + 1) {
    (*(code *)(&PTR_FUN_ram_00007d1e_ram_00009310)[iVar1])();
  }
  FUN_ram_00007800();
  for (iVar1 = 0; iVar1 != 2; iVar1 = iVar1 + 1) {
    (*(code *)(&PTR_FUN_ram_00007d1e_ram_00009310)[iVar1])();
  }
  return;
}

