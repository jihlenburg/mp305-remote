/* Address: 00040928; name: FUN_00040928; body bytes: 16 */

undefined4 FUN_00040928(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 != 0) || (uVar1 = 0, param_1 = DAT_2003a434, DAT_2003a434 != 0)) {
    uVar1 = *(undefined4 *)(param_1 + 0x2c0);
  }
  return uVar1;
}

