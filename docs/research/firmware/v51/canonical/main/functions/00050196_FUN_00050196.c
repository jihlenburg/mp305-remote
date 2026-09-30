/* Address: 00050196; name: FUN_00050196; body bytes: 98 */

void FUN_00050196(undefined4 param_1,int param_2)

{
  int iVar1;
  
  *(undefined4 *)(param_2 + 0x9c) = 0;
  *(byte *)(param_2 + 0xa0) = *(byte *)(param_2 + 0xa0) & 0xfc;
  FUN_0004e00e(param_2,0x100);
  FUN_0004e00e(param_2,0x10);
  FUN_0004aa6e(param_2,0x400);
  iVar1 = FUN_0004089c(0);
  if (iVar1 * 8 + 0x50 < 0x140) {
    iVar1 = 1;
  }
  else {
    iVar1 = FUN_0004089c(0);
    iVar1 = (iVar1 * 8 + 0x50) / 0xa0;
  }
  FUN_0004e5e4(param_2,iVar1);
  return;
}

