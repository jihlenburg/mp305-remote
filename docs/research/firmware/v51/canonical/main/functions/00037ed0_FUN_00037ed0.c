/* Address: 00037ed0; name: FUN_00037ed0; body bytes: 62 */

/* Recovered from stored Thumb pointer at 00061278; callback identification is inferred until
   reviewed. */

uint FUN_00037ed0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  
  if ((*(byte *)(DAT_2003a5d0 + 0x24) & 1) == 0) {
    uVar1 = FUN_0004f010(0x12,2,param_3,param_4,param_4);
  }
  else {
    uVar1 = FUN_0004efd0();
  }
  uVar2 = FUN_000403d2(uVar1,param_2,param_3);
  return uVar2 & 0xffffff;
}

