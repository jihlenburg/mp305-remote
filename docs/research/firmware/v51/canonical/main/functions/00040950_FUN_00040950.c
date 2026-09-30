/* Address: 00040950; name: FUN_00040950; body bytes: 12 */

undefined4 FUN_00040950(int param_1)

{
  if (param_1 == 0) {
    param_1 = DAT_2003a434;
  }
  return *(undefined4 *)(param_1 + 0x2f4);
}

