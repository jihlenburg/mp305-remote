/* Address: 00051474; name: FUN_00051474; body bytes: 90 */

/* Recovered from stored Thumb pointer at 0007af18; callback identification is inferred until
   reviewed. */

void FUN_00051474(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_2 + 0x30) = 0;
  FUN_0004e84a(param_2,&DAT_20000064,&DAT_20000064);
  FUN_0004b384(param_2);
  uVar1 = FUN_0004b384(param_2);
  FUN_0004e624(uVar1,0);
  FUN_0004aa4c(uVar1,0x276c1,0);
  FUN_0004e822(uVar1,0);
  FUN_000515ec(param_2,4);
  FUN_0004aa6e(uVar1,0x80);
  FUN_0004e00e(uVar1,0x400);
  return;
}

