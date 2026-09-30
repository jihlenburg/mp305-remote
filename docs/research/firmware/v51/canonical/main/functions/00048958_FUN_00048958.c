/* Address: 00048958; name: FUN_00048958; body bytes: 232 */

void FUN_00048958(int param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  uint local_30 [2];
  uint local_28;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  
  puVar2 = local_30;
  if (((param_1 != 0) || (param_1 = FUN_00040890(), param_1 != 0)) &&
     (iVar1 = FUN_00040994(), iVar1 != 0)) {
    if (*(int *)(param_1 + 0x38) << 0xe < 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (param_2 == 0) {
      *(undefined4 *)(param_1 + 0x25c) = 0;
    }
    else {
      local_20 = 0;
      local_1c = 0;
      local_18 = FUN_000408b0(param_1);
      local_18 = local_18 + -1;
      local_14 = FUN_00040960(param_1);
      local_14 = local_14 + -1;
      iVar1 = FUN_0003db4c(local_30,param_2,&local_20);
      if (iVar1 != 0) {
        if (*(char *)(param_1 + 0x3b) == '\a') {
          local_30[0] = local_30[0] & 0xfffffff8;
          local_28 = local_28 | 7;
        }
        if (*(char *)(param_1 + 0x39) == '\x02') {
          *(undefined4 *)(param_1 + 0x3c) = local_20;
          *(undefined4 *)(param_1 + 0x40) = local_1c;
          *(int *)(param_1 + 0x44) = local_18;
          *(int *)(param_1 + 0x48) = local_14;
          iVar1 = 1;
        }
        else {
          iVar1 = FUN_00040acc(param_1,0x32,local_30);
          if (iVar1 != 1) {
            return;
          }
          for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 0x25c); uVar3 = uVar3 + 1 & 0xffff) {
            iVar1 = FUN_0003db8c(local_30,param_1 + uVar3 * 0x10 + 0x3c,0);
            if (iVar1 != 0) {
              return;
            }
          }
          if (0x1f < *(uint *)(param_1 + 0x25c)) {
            puVar2 = &local_20;
            *(undefined4 *)(param_1 + 0x25c) = 0;
          }
          FUN_0003d9b6(param_1 + *(int *)(param_1 + 0x25c) * 0x10 + 0x3c,puVar2);
          iVar1 = *(int *)(param_1 + 0x25c) + 1;
        }
        *(int *)(param_1 + 0x25c) = iVar1;
        FUN_00040acc(param_1,0x35,0);
      }
    }
  }
  return;
}

