/* Address: 00016004; name: FUN_00016004; body bytes: 30 */

int FUN_00016004(void)

{
  int iVar1;
  
  iVar1 = FUN_00016024();
  if (iVar1 < 1) {
    iVar1 = iVar1 + -500;
  }
  else {
    iVar1 = iVar1 + 500;
  }
  return iVar1 / 1000;
}

