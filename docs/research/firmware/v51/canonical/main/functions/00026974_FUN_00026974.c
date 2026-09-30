/* Address: 00026974; name: FUN_00026974; body bytes: 70 */

/* Recovered from stored Thumb pointer at 000223d8; callback identification is inferred until
   reviewed. */

void FUN_00026974(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_0004675a();
  uVar2 = FUN_0004b9de(uVar1,0);
  FUN_0004aa6e(uVar2,1);
  uVar2 = FUN_0004b9de(uVar1,1);
  FUN_0004aa6e(uVar2,1);
  FUN_0003f960(uVar1,DAT_1ffe0340,0,0x7fffffff);
  DAT_1fffabc0 = 0xffffffff;
  FUN_0001cb8c(0xf);
  return;
}

