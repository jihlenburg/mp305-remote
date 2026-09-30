/* Address: 0004146e; name: FUN_0004146e; body bytes: 42 */

undefined8 FUN_0004146e(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iStack_20;
  int *piStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iStack_20 = param_1;
  piStack_1c = param_2;
  if (*(int *)(iVar1 + 0x10) != 0) {
    uStack_18 = param_3;
    uStack_14 = param_4;
    if (param_2 == (int *)0x0) {
      FUN_000297a4(param_1,&iStack_20);
      param_2 = &iStack_20;
    }
    (**(code **)(iVar1 + 0x10))(param_1,param_2);
  }
  return CONCAT44(piStack_1c,iStack_20);
}

