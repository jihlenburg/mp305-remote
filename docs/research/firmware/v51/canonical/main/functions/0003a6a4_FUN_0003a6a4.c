/* Address: 0003a6a4; name: FUN_0003a6a4; body bytes: 22 */

/* Recovered from stored Thumb pointer at 0003a584; callback identification is inferred until
   reviewed. */

void FUN_0003a6a4(int *param_1)

{
  int iVar1;
  
  if ((param_1 != (int *)0x0) && (iVar1 = *param_1, iVar1 != 0)) {
    *(undefined4 *)(iVar1 + 0x58) = 0;
    *(undefined4 *)(iVar1 + 0x5c) = 0;
    *(undefined4 *)(iVar1 + 0xc0) = 0;
  }
  return;
}

