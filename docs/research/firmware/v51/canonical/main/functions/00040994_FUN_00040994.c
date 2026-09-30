/* Address: 00040994; name: FUN_00040994; body bytes: 26 */

undefined4 FUN_00040994(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 != 0) || (uVar1 = 0, param_1 = DAT_2003a434, DAT_2003a434 != 0)) {
    if (*(int *)(param_1 + 0x260) < 1) {
      return 0;
    }
    uVar1 = 1;
  }
  return uVar1;
}

