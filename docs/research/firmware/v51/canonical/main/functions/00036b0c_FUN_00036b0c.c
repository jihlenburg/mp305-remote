/* Address: 00036b0c; name: FUN_00036b0c; body bytes: 58 */

void FUN_00036b0c(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x48);
  if (piVar1 != (int *)0x0) {
    if (*piVar1 != 0) {
      FUN_00046c30();
      FUN_00046bec(*piVar1);
    }
    if (piVar1[7] != 0) {
      FUN_000413fe();
    }
    if (piVar1[8] != 0) {
      FUN_000413fe();
    }
    FUN_00046bec(piVar1[1]);
    FUN_00046bec(piVar1);
    *(undefined4 *)(param_1 + 0x48) = 0;
  }
  return;
}

