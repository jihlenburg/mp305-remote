/* Address: ram:0000780e; name: FUN_ram_0000780e; body bytes: 58 */

void FUN_ram_0000780e(void)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  iVar1 = 0;
  while (iVar1 != 0) {
    iVar1 = iVar1 + -1;
    (*(code *)(&DAT_ram_00009318)[iVar1])();
  }
  return;
}

