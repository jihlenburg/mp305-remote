/* Address: 00040900; name: FUN_00040900; body bytes: 16 */

undefined4 FUN_00040900(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 != 0) || (uVar1 = 0, param_1 = DAT_2003a434, DAT_2003a434 != 0)) {
    uVar1 = *(undefined4 *)(param_1 + 700);
  }
  return uVar1;
}

