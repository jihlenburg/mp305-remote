/* Address: 00046cd8; name: FUN_00046cd8; body bytes: 150 */

undefined4 FUN_00046cd8(int *param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint local_20;
  undefined4 local_1c;
  
  if (param_2 == 0) {
    uVar4 = 0xb;
  }
  else {
    local_20 = param_3;
    local_1c = param_4;
    FUN_00046f24(&local_20);
    iVar1 = FUN_00046c74(local_20 & 0xff);
    if (iVar1 == 0) {
      uVar4 = 3;
    }
    else if ((*(code **)(iVar1 + 8) == (code *)0x0) ||
            (iVar2 = (**(code **)(iVar1 + 8))(), iVar2 != 0)) {
      if (*(int *)(iVar1 + 0xc) == 0) {
        uVar4 = 9;
      }
      else {
        param_1[1] = iVar1;
        if (*(int *)(iVar1 + 4) == -1) {
          *param_1 = (int)param_1;
        }
        else {
          iVar2 = (**(code **)(iVar1 + 0xc))(iVar1,local_1c,param_3);
          if ((iVar2 == 0) || (iVar2 == -1)) {
            return 0xc;
          }
          *param_1 = iVar2;
        }
        if (*(int *)(iVar1 + 4) != 0) {
          puVar3 = (undefined4 *)FUN_0004a360(0x10);
          param_1[2] = (int)puVar3;
          if (puVar3 == (undefined4 *)0x0) {
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
          if (*(int *)(iVar1 + 4) == -1) {
            puVar3[3] = *(undefined4 *)(param_2 + 4);
            *(undefined4 *)param_1[2] = 0;
            *(undefined4 *)(param_1[2] + 8) = 0;
            uVar4 = *(undefined4 *)(param_2 + 8);
          }
          else {
            *puVar3 = 0xffffffff;
            uVar4 = 0xfffffffe;
          }
          *(undefined4 *)(param_1[2] + 4) = uVar4;
        }
        uVar4 = 0;
      }
    }
    else {
      uVar4 = 1;
    }
  }
  return uVar4;
}

