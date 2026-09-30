/* Address: CODE:9781; name: FUN_CODE_9781; body bytes: 25 */

void FUN_CODE_9781(void)

{
  bool bVar1;
  char cVar2;
  
  FUN_CODE_866f();
  FUN_CODE_a6cd();
  cVar2 = BANK0_R7;
  FUN_CODE_a74b();
  bVar1 = BANK0_R7 == cVar2;
  BANK0_R7 = cVar2;
  if (bVar1) {
    FUN_CODE_a32a(10);
  }
  return;
}

