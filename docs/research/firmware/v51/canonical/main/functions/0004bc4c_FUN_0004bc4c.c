/* Address: 0004bc4c; name: FUN_0004bc4c; body bytes: 62 */

undefined4 FUN_0004bc4c(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  while( true ) {
    if ((*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4 <= uVar2) {
      return 0;
    }
    uVar3 = *(uint *)(*(int *)(param_1 + 0xc) + uVar2 * 8 + 4);
    if (((int)(uVar3 << 7) < 0) && ((uVar3 & 0xffffff) == param_4)) break;
    uVar2 = uVar2 + 1;
  }
  uVar1 = FUN_00050a74(*(undefined4 *)(*(int *)(param_1 + 0xc) + uVar2 * 8));
  return uVar1;
}

