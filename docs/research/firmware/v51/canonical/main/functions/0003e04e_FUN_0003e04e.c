/* Address: 0003e04e; name: FUN_0003e04e; body bytes: 42 */

/* Recovered from stored Thumb pointer at 0003e350; callback identification is inferred until
   reviewed. */

void FUN_0003e04e(int *param_1)

{
  int iVar1;
  
  param_1 = (int *)*param_1;
  iVar1 = *param_1;
  param_1[3] = -1;
  if (param_1 == (int *)(iVar1 + 0x50)) {
    *(int *)(iVar1 + 0x2c) = param_1[2];
  }
  else if (param_1 == (int *)(iVar1 + 0x60)) {
    *(int *)(iVar1 + 0x38) = param_1[2];
  }
  FUN_0004d3d8(*param_1);
  return;
}

