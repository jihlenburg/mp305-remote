/* Address: 00010f10; name: FUN_00010f10; body bytes: 18 */

byte FUN_00010f10(int param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00010f08();
  return *(byte *)(*piVar1 + param_1) & 1;
}

