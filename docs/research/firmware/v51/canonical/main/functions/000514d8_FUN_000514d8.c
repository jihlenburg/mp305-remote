/* Address: 000514d8; name: FUN_000514d8; body bytes: 46 */

/* Recovered from stored Thumb pointer at 0007af20; callback identification is inferred until
   reviewed. */

void FUN_000514d8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0004b9b2(&DAT_0007af14);
  if (iVar1 == 1) {
    iVar1 = FUN_00046688(param_2);
    iVar2 = FUN_00046698(param_2);
    if (iVar1 == 0x2e) {
      FUN_0005152c(iVar2,*(undefined4 *)(iVar2 + 0x2c),0);
      return;
    }
  }
  return;
}

