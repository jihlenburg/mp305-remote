/* Address: 00014558; name: FUN_00014558; body bytes: 70 */

undefined4 FUN_00014558(int param_1,int param_2,uint *param_3)

{
  if (param_3 != (uint *)0x0) {
    param_1 = param_1 + param_2 * 0x40;
    *(uint *)(param_1 + 0x40) = param_3[1];
    *(uint *)(param_1 + 0x44) = param_3[2];
    *(uint *)(param_1 + 0x48) = (ushort)param_3[4] & 0x3ff | (uint)(ushort)param_3[5] << 0x10;
    *(uint *)(param_1 + 0x5c) =
         (*param_3 | param_3[3] | param_3[6] | param_3[7]) & 0x130f |
         *(uint *)(param_1 + 0x5c) & 0xffffecf0;
    return 0;
  }
  return 0xfffffffd;
}

