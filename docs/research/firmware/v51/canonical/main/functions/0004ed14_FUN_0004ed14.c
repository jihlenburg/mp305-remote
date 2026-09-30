/* Address: 0004ed14; name: FUN_0004ed14; body bytes: 478 */

int FUN_0004ed14(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uStack_28;
  
  iVar5 = 0;
  uVar4 = 0;
  uStack_28 = param_4;
  do {
    if ((*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4 <= uVar4) {
      return iVar5;
    }
    uVar1 = *(uint *)(*(int *)(param_1 + 0xc) + uVar4 * 8 + 4);
    if ((-1 < (int)(uVar1 << 6)) &&
       (uVar1 = uVar1 & 0xffff, ((uVar1 & ~param_2) == 0) != ((uVar1 & ~param_3) == 0))) {
      uVar2 = *(undefined4 *)(*(int *)(param_1 + 0xc) + uVar4 * 8);
      iVar3 = FUN_00050a74(uVar2,0x10,&uStack_28);
      if (((((iVar3 != 0) ||
            (((((iVar3 = FUN_00050a74(uVar2,0x11,&uStack_28), iVar3 != 0 ||
                (iVar3 = FUN_00050a74(uVar2,0x12,&uStack_28), iVar3 != 0)) ||
               (iVar3 = FUN_00050a74(uVar2,0x13,&uStack_28), iVar3 != 0)) ||
              ((iVar3 = FUN_00050a74(uVar2,0x15,&uStack_28), iVar3 != 0 ||
               (iVar3 = FUN_00050a74(uVar2,0x14,&uStack_28), iVar3 != 0)))) ||
             (iVar3 = FUN_00050a74(uVar2,0x16,&uStack_28), iVar3 != 0)))) ||
           (((iVar3 = FUN_00050a74(uVar2,0x6a,&uStack_28), iVar3 != 0 ||
             (iVar3 = FUN_00050a74(uVar2,0x6b,&uStack_28), iVar3 != 0)) ||
            (iVar3 = FUN_00050a74(uVar2,1,&uStack_28), iVar3 != 0)))) ||
          (((iVar3 = FUN_00050a74(uVar2,2,&uStack_28), iVar3 != 0 ||
            (iVar3 = FUN_00050a74(uVar2,4,&uStack_28), iVar3 != 0)) ||
           (iVar3 = FUN_00050a74(uVar2,5,&uStack_28), iVar3 != 0)))) ||
         (((iVar3 = FUN_00050a74(uVar2,6,&uStack_28), iVar3 != 0 ||
           (iVar3 = FUN_00050a74(uVar2,7,&uStack_28), iVar3 != 0)) ||
          (iVar3 = FUN_00050a74(uVar2,0x30,&uStack_28), iVar3 != 0)))) {
        return 3;
      }
      iVar3 = FUN_00050a74(uVar2,0x68,&uStack_28);
      if ((((iVar3 == 0) && (iVar3 = FUN_00050a74(uVar2,0x69,&uStack_28), iVar3 == 0)) &&
          (((iVar3 = FUN_00050a74(uVar2,0x6e,&uStack_28), iVar3 == 0 &&
            (((iVar3 = FUN_00050a74(uVar2,0x6c,&uStack_28), iVar3 == 0 &&
              (iVar3 = FUN_00050a74(uVar2,0x6d,&uStack_28), iVar3 == 0)) &&
             (iVar3 = FUN_00050a74(uVar2,0x3a,&uStack_28), iVar3 == 0)))) &&
           ((((iVar3 = FUN_00050a74(uVar2,0x3b,&uStack_28), iVar3 == 0 &&
              (iVar3 = FUN_00050a74(uVar2,0x38,&uStack_28), iVar3 == 0)) &&
             (iVar3 = FUN_00050a74(uVar2,0x3c,&uStack_28), iVar3 == 0)) &&
            ((iVar3 = FUN_00050a74(uVar2,0x3e,&uStack_28), iVar3 == 0 &&
             (iVar3 = FUN_00050a74(uVar2,0x40,&uStack_28), iVar3 == 0)))))))) &&
         ((iVar3 = FUN_00050a74(uVar2,0x41,&uStack_28), iVar3 == 0 &&
          ((iVar3 = FUN_00050a74(uVar2,0x42,&uStack_28), iVar3 == 0 &&
           (iVar3 = FUN_00050a74(uVar2,0x48,&uStack_28), iVar3 == 0)))))) {
        if (iVar5 == 0) {
          iVar5 = 1;
        }
      }
      else {
        iVar5 = 2;
      }
    }
    uVar4 = uVar4 + 1;
  } while( true );
}

