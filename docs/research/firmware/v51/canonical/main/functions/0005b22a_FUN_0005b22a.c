/* Address: 0005b22a; name: FUN_0005b22a; body bytes: 86 */

void FUN_0005b22a(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  do {
    if ((*(ushort *)(param_2 + 0x2a) & 0x3ff) >> 4 <= uVar1) {
LAB_0005b25c:
      uVar1 = FUN_0004ba5c(param_2);
      for (uVar2 = 0; uVar2 < uVar1; uVar2 = uVar2 + 1) {
        FUN_0005b22a(param_1,*(undefined4 *)(**(int **)(param_2 + 8) + uVar2 * 4));
      }
      return;
    }
    if ((param_1 == 0) || (*(int *)(*(int *)(param_2 + 0xc) + uVar1 * 8) == param_1)) {
      FUN_0004dedc(param_2,0xf0000,0xff);
      goto LAB_0005b25c;
    }
    uVar1 = uVar1 + 1;
  } while( true );
}

