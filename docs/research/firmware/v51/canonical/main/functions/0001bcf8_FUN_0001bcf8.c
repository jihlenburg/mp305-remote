/* Address: 0001bcf8; name: FUN_0001bcf8; body bytes: 20 */

void FUN_0001bcf8(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 1) {
    uVar1 = *(uint *)(param_1 + 4) | 0x40;
  }
  else {
    uVar1 = *(uint *)(param_1 + 4) & 0xffffffbf;
  }
  *(uint *)(param_1 + 4) = uVar1;
  return;
}

