/* Address: 000236ba; name: FUN_000236ba; body bytes: 118 */

int FUN_000236ba(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int local_20;
  int local_1c;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    local_20 = param_3;
    local_1c = param_4;
    local_20 = FUN_0004f456();
    if (local_20 != 0) {
      uVar2 = *(undefined4 *)(local_20 + 0x10);
      uVar1 = FUN_0003f174(uVar2,*(undefined4 *)(param_1 + 4));
      FUN_0004a404(uVar2,param_2,*(undefined4 *)(param_1 + 4));
      local_1c = FUN_0004a162(param_1 + 0x30);
      if (local_1c == 0) {
        FUN_0004f3ea(param_1 + 0x24,local_20);
        local_20 = 0;
      }
      else {
        FUN_0004a404(local_1c,&local_20,4);
        uVar2 = FUN_000376e4(param_1,local_20);
        FUN_0004a404(uVar2,&local_1c,4);
        FUN_0003f194(uVar1,param_1,*(undefined4 *)(param_1 + 4));
      }
    }
    return local_20;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

