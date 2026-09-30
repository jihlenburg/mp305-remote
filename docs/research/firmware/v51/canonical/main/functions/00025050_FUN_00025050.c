/* Address: 00025050; name: FUN_00025050; body bytes: 78 */

undefined4 FUN_00025050(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(*param_1 + 0x24))(param_1,param_2,0,param_3);
  if (iVar1 != 1) {
    while( true ) {
      if (iVar1 != 2) {
                    /* WARNING: Could not recover jumptable at 0x0002509c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar2 = (**(code **)(*param_1 + 0x10))(param_1,param_2,param_3);
        return uVar2;
      }
      iVar1 = FUN_0002509e(param_1,param_3);
      if (iVar1 == 0) break;
      iVar1 = (**(code **)(*param_1 + 0x24))(param_1,param_2,0,param_3);
    }
  }
  return 0;
}

