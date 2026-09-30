/* Address: 00041498; name: FUN_00041498; body bytes: 46 */

void FUN_00041498(int param_1,ushort *param_2)

{
  FUN_00041554(param_1,*(uint *)(param_2 + 2) & 0xffff,*(uint *)(param_2 + 2) >> 0x10,*param_2 >> 8,
               param_2[4],*(undefined4 *)(param_2 + 8),*(undefined4 *)(param_2 + 6));
  *(short *)(param_1 + 2) = (short)((uint)*(undefined4 *)param_2 >> 0x10);
  return;
}

