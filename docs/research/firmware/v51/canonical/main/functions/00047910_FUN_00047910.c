/* Address: 00047910; name: FUN_00047910; body bytes: 40 */

void FUN_00047910(undefined4 param_1,int param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_2 + 0x58) & 3;
  if ((bVar1 == 1) || (bVar1 == 2)) {
    FUN_00046bec(*(undefined4 *)(param_2 + 0x2c));
    *(undefined4 *)(param_2 + 0x2c) = 0;
    *(uint *)(param_2 + 0x58) = *(uint *)(param_2 + 0x58) | 3;
  }
  return;
}

