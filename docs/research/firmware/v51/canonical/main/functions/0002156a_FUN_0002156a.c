/* Address: 0002156a; name: FUN_0002156a; body bytes: 48 */

undefined4 FUN_0002156a(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    iVar1 = FUN_000236ba();
    uVar2 = 0;
    if (iVar1 != 0) {
      uVar2 = FUN_0003f174(*(undefined4 *)(iVar1 + 0x10),*(undefined4 *)(param_1 + 4));
      iVar1 = (**(code **)(param_1 + 0x3c))(param_2);
      *(int *)(param_1 + 0xc) = iVar1 + *(int *)(param_1 + 0xc);
    }
    return uVar2;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

