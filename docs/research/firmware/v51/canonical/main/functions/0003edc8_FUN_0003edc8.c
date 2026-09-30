/* Address: 0003edc8; name: FUN_0003edc8; body bytes: 24 */

undefined4 FUN_0003edc8(int param_1,uint param_2,uint param_3)

{
  if ((param_2 < *(uint *)(param_1 + 0x38)) &&
     ((param_3 & ~(uint)*(ushort *)(*(int *)(param_1 + 0x34) + param_2 * 2)) == 0)) {
    return 1;
  }
  return 0;
}

