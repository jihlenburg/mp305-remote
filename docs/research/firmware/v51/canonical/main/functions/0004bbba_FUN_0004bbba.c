/* Address: 0004bbba; name: FUN_0004bbba; body bytes: 40 */

undefined4 FUN_0004bbba(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + 8);
  if (piVar2 != (int *)0x0) {
    for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(piVar2 + 10); iVar1 = iVar1 + 1) {
      if (-1 < (int)((uint)*(ushort *)(*(int *)(*piVar2 + iVar1 * 4) + 0x2a) << 0x13)) {
        return *(undefined4 *)(*piVar2 + iVar1 * 4);
      }
    }
  }
  return 0;
}

