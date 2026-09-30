/* Address: 000452b4; name: FUN_000452b4; body bytes: 70 */

undefined4
FUN_000452b4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  
  bVar1 = false;
  iVar5 = 0;
  while( true ) {
    puVar3 = *(undefined4 **)(param_1 + iVar5 * 4);
    if (puVar3 == (undefined4 *)0x0) {
      if (bVar1) {
        uVar4 = 2;
      }
      else {
        uVar4 = 1;
      }
      return uVar4;
    }
    iVar2 = (*(code *)*puVar3)(param_2,param_3,param_4,param_5,puVar3);
    if (iVar2 == 0) break;
    if (iVar2 == 2) {
      bVar1 = true;
    }
    iVar5 = iVar5 + 1;
  }
  return 0;
}

