/* Address: 00010c18; name: FUN_00010c18; body bytes: 12 */

/* Recovered from stored Thumb pointer at 00010c38; callback identification is inferred until
   reviewed. */

undefined1 FUN_00010c18(undefined4 *param_1,int param_2)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)*param_1;
  *param_1 = (undefined1 *)*param_1 + param_2;
  return uVar1;
}

