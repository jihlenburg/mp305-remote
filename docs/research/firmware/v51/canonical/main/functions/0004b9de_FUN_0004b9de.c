/* Address: 0004b9de; name: FUN_0004b9de; body bytes: 36 */

undefined4 FUN_0004b9de(int param_1,uint param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 8);
  if ((piVar1 != (int *)0x0) &&
     (((-1 < (int)param_2 || (param_2 = *(ushort *)(piVar1 + 10) + param_2, -1 < (int)param_2)) &&
      (param_2 < *(ushort *)(piVar1 + 10))))) {
    return *(undefined4 *)(*piVar1 + param_2 * 4);
  }
  return 0;
}

