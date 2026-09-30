/* Address: 000202e8; name: FUN_000202e8; body bytes: 46 */

int FUN_000202e8(undefined4 *param_1)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  while (iVar2 = FUN_00020bcc(*(undefined1 *)*param_1), iVar2 != 0) {
    pbVar1 = (byte *)*param_1;
    *param_1 = pbVar1 + 1;
    iVar3 = (uint)*pbVar1 + iVar3 * 10 + -0x30;
  }
  return iVar3;
}

