/* Address: 0003f1ca; name: FUN_0003f1ca; body bytes: 78 */

void FUN_0003f1ca(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_0004aa44();
  FUN_0003f1b0(param_2,param_3);
  iVar1 = FUN_0003f17c(param_2);
  if ((iVar1 == 0) && (iVar1 = FUN_0003f1a8(param_2), iVar1 != 0)) {
    uVar2 = FUN_0003f16a(param_2);
    (**(code **)(param_1 + 0x18))(uVar2,param_3);
    FUN_0003f158(param_2);
  }
  FUN_0004aa48(param_1 + 0x1c);
  return;
}

