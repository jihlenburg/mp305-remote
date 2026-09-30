/* Address: 00047d8e; name: FUN_00047d8e; body bytes: 318 */

void FUN_00047d8e(int param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint local_34;
  uint local_30;
  undefined2 local_28 [2];
  undefined2 local_24;
  
  FUN_0004d3d8();
  uVar2 = FUN_00047ecc(param_2);
  if (uVar2 == 3) {
    bVar1 = *(byte *)(param_1 + 0x58) & 3;
    if ((bVar1 == 2) || (bVar1 == 1)) {
      FUN_00046bec(*(undefined4 *)(param_1 + 0x2c));
    }
    *(undefined4 *)(param_1 + 0x2c) = 0;
    *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) | 3;
  }
  else {
    iVar3 = FUN_0004775c(param_2,&local_34);
    if (iVar3 == 1) {
      if (uVar2 == 0) {
        bVar1 = *(byte *)(param_1 + 0x58) & 3;
        if ((bVar1 == 1) || (bVar1 == 2)) {
          FUN_00046bec(*(undefined4 *)(param_1 + 0x2c));
        }
        *(int *)(param_1 + 0x2c) = param_2;
      }
      else if ((uVar2 == 1) || (uVar2 == 2)) {
        if (*(int *)(param_1 + 0x2c) != param_2) {
          bVar1 = *(byte *)(param_1 + 0x58) & 3;
          if ((bVar1 == 1) || (iVar3 = 0, bVar1 == 2)) {
            iVar3 = *(int *)(param_1 + 0x2c);
          }
          iVar4 = FUN_00050a40(param_2);
          if (iVar4 == 0) {
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
          *(int *)(param_1 + 0x2c) = iVar4;
          if (iVar3 != 0) {
            FUN_00046bec(iVar3);
          }
        }
        if (uVar2 == 2) {
          uVar5 = FUN_0004c924(param_1,0,0x5a);
          uVar6 = FUN_0004c924(param_1,0,0x5b);
          uVar7 = FUN_0004c924(param_1,0,0x5c);
          FUN_00051970(local_28,param_2,uVar5,uVar6,uVar7,0x1fffffff,0);
          local_30 = CONCAT22(local_24,local_28[0]);
        }
      }
      *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) & 0xfffffffc | uVar2 & 3;
      *(uint *)(param_1 + 0x3c) = local_30 & 0xffff;
      *(uint *)(param_1 + 0x40) = local_30 >> 0x10;
      *(uint *)(param_1 + 0x58) =
           *(uint *)(param_1 + 0x58) & 0xffffff83 | (local_34 >> 8 & 0x1f) << 2;
      FUN_0004deac(param_1);
      FUN_00065144(param_1);
      if (((*(int *)(param_1 + 0x44) != 0) || (*(int *)(param_1 + 0x48) != 0x100)) ||
         (*(int *)(param_1 + 0x4c) != 0x100)) {
        FUN_0004de6c(param_1);
      }
      FUN_0004d3d8(param_1);
    }
  }
  return;
}

