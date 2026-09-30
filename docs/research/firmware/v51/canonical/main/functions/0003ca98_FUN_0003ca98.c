/* Address: 0003ca98; name: FUN_0003ca98; body bytes: 36 */

int FUN_0003ca98(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0004a388(*(undefined4 *)(param_1 + 0x34),0,*(undefined4 *)(param_1 + 0x30),0,0x400);
  return *(int *)(param_1 + 0x24) +
         (iVar1 * (*(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x24)) >> 10);
}

