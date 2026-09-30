/* Address: 0005e778; name: FUN_0005e778; body bytes: 32 */

void FUN_0005e778(int param_1,int param_2)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)(param_1 + ((int)(param_2 + ((uint)(param_2 >> 0x1f) >> 0x1d)) >> 3));
  *pbVar1 = *pbVar1 | (byte)(1 << (7U - param_2 % 8 & 0xff));
  return;
}

