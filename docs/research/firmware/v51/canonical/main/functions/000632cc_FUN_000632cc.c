/* Address: 000632cc; name: FUN_000632cc; body bytes: 14 */

int FUN_000632cc(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != 0) {
    iVar1 = 0x20 - LZCOUNT(param_1);
  }
  return iVar1 + -1;
}

