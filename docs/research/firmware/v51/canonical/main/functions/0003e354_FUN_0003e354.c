/* Address: 0003e354; name: FUN_0003e354; body bytes: 30 */

void FUN_0003e354(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0x48);
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x40) != 0)) {
    FUN_000413fe();
    *(undefined4 *)(iVar1 + 0x40) = 0;
  }
  FUN_00036b0c(param_2);
  return;
}

