/* Address: 0005b280; name: FUN_0005b280; body bytes: 50 */

undefined4 FUN_0005b280(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (**(code **)(param_1 + 0x3c))(param_2);
  }
  if (*(uint *)(param_1 + 8) < uVar1) {
    return 1;
  }
  if (*(uint *)(param_1 + 8) < uVar1 + param_3 + *(int *)(param_1 + 0xc)) {
    return 2;
  }
  return 0;
}

