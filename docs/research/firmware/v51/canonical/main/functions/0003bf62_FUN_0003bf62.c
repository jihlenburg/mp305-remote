/* Address: 0003bf62; name: FUN_0003bf62; body bytes: 90 */

void FUN_0003bf62(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_0004ba5c();
  for (uVar2 = 0; uVar2 < uVar1; uVar2 = uVar2 + 1) {
    FUN_0003bf62(*(undefined4 *)(**(int **)(param_1 + 8) + uVar2 * 4));
  }
  if ((*(ushort *)(param_1 + 0x2a) & 1) != 0) {
    *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) & 0xfffe;
    FUN_0004dbe0(param_1);
    FUN_0004da38(param_1);
    if (uVar1 != 0) {
      FUN_00049a7c(param_1);
    }
  }
  if ((int)((uint)*(ushort *)(param_1 + 0x2a) << 0x1e) < 0) {
    *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) & 0xfffd;
    FUN_0004d706(param_1,0);
    return;
  }
  return;
}

