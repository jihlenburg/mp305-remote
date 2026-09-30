/* Address: 00052b48; name: FUN_00052b48; body bytes: 52 */

uint FUN_00052b48(uint param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((param_1 & 3) != 0) {
    return 0;
  }
  *(uint *)(param_1 + 8) = param_1;
  *(uint *)(param_1 + 0xc) = param_1;
  *(undefined4 *)(param_1 + 0x10) = 0;
  iVar2 = 0;
  do {
    *(undefined4 *)(param_1 + iVar2 * 4 + 0x14) = 0;
    iVar3 = 0;
    do {
      iVar1 = iVar3 * 4;
      iVar3 = iVar3 + 1;
      *(uint *)(param_1 + iVar2 * 0x80 + iVar1 + 0x44) = param_1;
    } while (iVar3 < 0x20);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xc);
  return param_1;
}

